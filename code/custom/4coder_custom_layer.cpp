

#if !defined(FCODER_CUSTOM_LAYER_CPP)
#define FCODER_CUSTOM_LAYER_CPP

#include "4coder_default_include.cpp"

#if !defined(META_PASS)
#include "generated/managed_id_metadata.cpp"
#endif


internal void
set_modal_mode_buffer(Application_Links *app, Buffer_ID buffer,
                      Command_Map_ID mapid)
{
  Managed_Scope scope = buffer_get_managed_scope(app, buffer);
  Command_Map_ID *map_id_ptr = scope_attachment(app, scope, buffer_map_id, Command_Map_ID);
  *map_id_ptr = mapid;
}

internal void
set_modal_mode_view(Application_Links *app, View_ID view, Command_Map_ID mapid)
{
  Buffer_ID buffer = view_get_buffer(app, view, 0);
  set_modal_mode_buffer(app, buffer, mapid);
}

internal Command_Map_ID
get_modal_mapid(void)
{
  Command_Map_ID result = 0;
  if(global_is_command_mode)
  {
    result = (Command_Map_ID)command_mode_mapid;
  }
  else
  {
    result = (Command_Map_ID)text_mode_mapid;
  }
  
  return(result);
}

internal void 
bind_mapping_to_all_view_buffers(Application_Links *app, Command_Map_ID mapid)
{
  // NOTE(nates): Totaly didn't steal this code from
  // https://4coder.handmade.network/forums/articles/t/7319-customization_layer_-_getting_started__4coder_4.1_
  for (View_ID view = get_active_view(app, 0);
       view != 0;
       view = get_view_next(app, view, 0))
  {
    Buffer_ID buffer = view_get_buffer(app, view, 0);
    set_modal_mode_buffer(app, buffer, mapid);
  }
}


// NOTE(nates): Look at 4coder_custom_variables.h
//              and 4coder_custom_functions.cpp

// TODO(nates): Add support for these using theme-name.4coder file
#define COMMAND_MODE_BUFFER_MARGIN_COLOR 0xffff0000
#define TEXT_MODE_BUFFER_MARGIN_COLOR 0xff00ff00

// NOTE(nates): All these CUSTOM_COMMAND_SIGS's are just functions
// you can call them if you want to!
CUSTOM_COMMAND_SIG(change_to_command_mode)
CUSTOM_DOC("all the commands in the world, right here!")
{
  global_is_command_mode = true;
  bind_mapping_to_all_view_buffers(app, command_mode_mapid);
  // active_color_table.arrays[defcolor_cursor].vals[0] = something;
  active_color_table.arrays[defcolor_margin_active].vals[0] = COMMAND_MODE_BUFFER_MARGIN_COLOR;
}

CUSTOM_COMMAND_SIG(change_to_text_mode)
CUSTOM_DOC("alll the text in the world, right here!")
{
  global_is_command_mode = false;
  bind_mapping_to_all_view_buffers(app, text_mode_mapid);
  // active_color_table.arrays[defcolor_cursor].vals[0] = something;
  active_color_table.arrays[defcolor_margin_active].vals[0] = TEXT_MODE_BUFFER_MARGIN_COLOR;
}

CUSTOM_COMMAND_SIG(change_to_text_mode_2)
CUSTOM_DOC("alll the text in the world, right here!")
{
  global_is_command_mode = false;
  bind_mapping_to_all_view_buffers(app, text_mode_mapid);
  // active_color_table.arrays[defcolor_cursor].vals[0] = something;
  active_color_table.arrays[defcolor_margin_active].vals[0] = TEXT_MODE_BUFFER_MARGIN_COLOR;
}

CUSTOM_COMMAND_SIG(jump_from_brace_to_brace)
CUSTOM_DOC("Jump from Brace to brace")
{
  View_ID viewID = get_active_view(app, 0);
  Buffer_ID bufferID = view_get_buffer(app, viewID, 0);
  i64 cursorPos = view_get_cursor_pos(app, viewID);
  u8 charUnderCursor = buffer_get_char(app, bufferID, cursorPos);
  u8 prevCharUnderCursor = buffer_get_char(app, bufferID, cursorPos - 1);
  i64 bracePos;
  
  if (charUnderCursor == '{' || prevCharUnderCursor == '{')
  {
    if (find_nest_side(app, bufferID, prevCharUnderCursor == '{' ? cursorPos : cursorPos + 1,
                       FindNest_Scope | FindNest_Balanced | FindNest_EndOfToken,
                       Scan_Forward, NestDelim_Close, &bracePos))
    {
      view_set_cursor(app, viewID, Buffer_Seek{buffer_seek_pos, bracePos - 1});
    }
  }
  else if (charUnderCursor == '}' || prevCharUnderCursor == '}')
  {
    if (find_nest_side(app, bufferID, prevCharUnderCursor == '}' ? cursorPos - 2 : cursorPos - 1,
                       FindNest_Scope | FindNest_Balanced,
                       Scan_Backward, NestDelim_Open, &bracePos))
    {
      view_set_cursor(app, viewID, Buffer_Seek{buffer_seek_pos, bracePos});
    }
  }
  else
  {
    if (find_nest_side(app, bufferID, cursorPos, FindNest_Scope,
                       Scan_Forward, NestDelim_Open, &bracePos))
    {
      view_set_cursor(app, viewID, Buffer_Seek{buffer_seek_pos, bracePos});
    }
  }
}

#include "4coder_keybind_functions.cpp"
#include "4coder_custom_signatures.cpp"

void custom_layer_init(Application_Links *app)
{
  Thread_Context *tctx = get_thread_context(app);
  
  // NOTE(allen): setup for default framework
  default_framework_init(app);
  
  // NOTE(allen): default hooks and command maps
  set_all_default_hooks(app);
  mapping_init(tctx, &framework_mapping);
  
  String_ID global_map_id = vars_save_string_lit("keys_global");
  String_ID file_map_id = vars_save_string_lit("keys_file");
  String_ID code_map_id = vars_save_string_lit("keys_code");
  
  shared_mapid = vars_save_string_lit("mapid_shared");
  command_mode_mapid = vars_save_string_lit("mapid_command_mode");
  text_mode_mapid = vars_save_string_lit("mapid_text_mode");
  
  MappingScope();
  SelectMapping(&framework_mapping);
  
  SelectMap(global_map_id);
  
  SelectMap(shared_mapid);
  BindCore(default_startup, CoreCode_Startup);
  BindCore(default_try_exit, CoreCode_TryExit);
  cakez_bind_shared_keys(m, map);
  
  SelectMap(command_mode_mapid);
  ParentMap(shared_mapid);
  cakez_bind_command_keys(m, map);
  
  SelectMap(text_mode_mapid);
  ParentMap(shared_mapid);
  cakez_bind_text_input(m, map);
  
  // NOTE(nates): You have to bind the "global_map, file_map, and code_map for some reason"
  SelectMap(file_map_id);
  ParentMap(command_mode_mapid);
  
  SelectMap(code_map_id);
  ParentMap(command_mode_mapid);
}

#endif