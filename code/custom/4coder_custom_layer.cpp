

#if !defined(FCODER_CUSTOM_LAYER_CPP)
#define FCODER_CUSTOM_LAYER_CPP

#include "4coder_default_include.cpp"

// NOTE(allen): Users can declare their own managed IDs here.

#if !defined(META_PASS)
#include "generated/managed_id_metadata.cpp"
#endif

global b32 global_is_command_mode = false;
String_ID shared_mapid;
String_ID command_mode_mapid;
String_ID text_mode_mapid;

void bind_mapping_to_buffer( Application_Links* app, Command_Map_ID mapid ) 
{
  
  // NOTE(nates): Totaly didn't steal this code from 
  // https://4coder.handmade.network/forums/articles/t/7319-customization_layer_-_getting_started__4coder_4.1_
  View_ID view = get_active_view( app, 0 );
  Buffer_ID buffer = view_get_buffer( app, view, 0 );
  Managed_Scope scope = buffer_get_managed_scope( app, buffer );
  Command_Map_ID* map_id_ptr = scope_attachment( app, scope, buffer_map_id, Command_Map_ID );
  *map_id_ptr = mapid;
}

#define COMMAND_MODE_BUFFER_MARGIN_COLOR 0xffff0000
#define TEXT_MODE_BUFFER_MARGIN_COLOR 0xff00ff00

// NOTE(nates): All these CUSTOM_COMMAND_SIGS's are just functions
// you can call them if you want to!
CUSTOM_COMMAND_SIG(change_to_command_mode)
CUSTOM_DOC("all the commands in the world, right here!")
{
  bind_mapping_to_buffer(app, command_mode_mapid);
  // active_color_table.arrays[defcolor_cursor].vals[0] = something;
  active_color_table.arrays[defcolor_margin_active].vals[0] = COMMAND_MODE_BUFFER_MARGIN_COLOR;
}

CUSTOM_COMMAND_SIG(change_to_text_mode)
CUSTOM_DOC("alll the text in the world, right here!")
{
  bind_mapping_to_buffer(app, text_mode_mapid);
  // active_color_table.arrays[defcolor_cursor].vals[0] = something;
  active_color_table.arrays[defcolor_margin_active].vals[0] = TEXT_MODE_BUFFER_MARGIN_COLOR;
}

CUSTOM_COMMAND_SIG(change_to_text_mode_2)
CUSTOM_DOC("alll the text in the world, right here!")
{
  bind_mapping_to_buffer(app, text_mode_mapid);
  // active_color_table.arrays[defcolor_cursor].vals[0] = something;
  active_color_table.arrays[defcolor_margin_active].vals[0] = TEXT_MODE_BUFFER_MARGIN_COLOR;
}

CUSTOM_COMMAND_SIG(change_binding_mode)
CUSTOM_DOC("yo yo yo, change the mode and go!")
{
  if(global_is_command_mode)
  {
    global_is_command_mode = !global_is_command_mode;
    change_to_text_mode(app);
  }
  else
  {
    global_is_command_mode = !global_is_command_mode;
    change_to_command_mode(app);
  }
}


#include "4coder_keybind_functions.cpp"
#include "4coder_custom_signatures.cpp"

void
custom_layer_init(Application_Links *app){
  Thread_Context *tctx = get_thread_context(app);
  
  // NOTE(allen): setup for default framework
  default_framework_init(app);
  
  // NOTE(allen): default hooks and command maps
  set_all_default_hooks(app);
  mapping_init(tctx, &framework_mapping);
  
  String_ID global_map_id = vars_save_string_lit("keys_global");
  String_ID file_map_id = vars_save_string_lit("keys_file");
  String_ID code_map_id = vars_save_string_lit("keys_code");
  
  shared_mapid = vars_save_string_lit( "mapid_shared" );
  command_mode_mapid = vars_save_string_lit( "mapid_command_mode" );
  text_mode_mapid = vars_save_string_lit( "mapid_text_mode" );
  
  MappingScope( );
  SelectMapping( &framework_mapping );
  
  SelectMap( global_map_id );
  
  SelectMap( shared_mapid );
  BindCore(default_startup, CoreCode_Startup);
  BindCore(default_try_exit, CoreCode_TryExit);
  cakez_bind_shared_keys(m, map);
  
  SelectMap(command_mode_mapid);
  ParentMap(shared_mapid);
  cakez_bind_command_keys(m, map);
  
  SelectMap(text_mode_mapid);
  ParentMap(shared_mapid);
  cakez_bind_text_input(m, map);
  
  /* This is to make sure that the default bindings on the buffers will be mapid_normal. */
  SelectMap(file_map_id);
  ParentMap(command_mode_mapid);
  
  SelectMap(code_map_id);
  ParentMap(command_mode_mapid);
}



#endif