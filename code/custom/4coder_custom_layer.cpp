

#if !defined(FCODER_CUSTOM_LAYER_CPP)
#define FCODER_CUSTOM_LAYER_CPP

#include "4coder_default_include.cpp"

#if !defined(META_PASS)
#include "generated/managed_id_metadata.cpp"
#endif

internal void
set_global_rel_mark_index(Application_Links *app, View_ID view)
{
  Mark_History *history = view_get_mark_history(app, view);
  history->rel_index = history->recent_index;
}

internal void
set_command_map_id(Application_Links *app, Buffer_ID buffer,
                   Command_Map_ID mapid)
{
  Managed_Scope scope = buffer_get_managed_scope(app, buffer);
  Command_Map_ID *map_id_ptr = scope_attachment(app, scope, buffer_map_id, Command_Map_ID);
  *map_id_ptr = mapid;
}

// NOTE(nates): So in default_render_caller, there is a call to render the active view
// margin, and in there it gets the color, so I just call "view_state_set_margin_color"
// *always* before it gets the color so it's correct. We don't even have to go through
// the active_color_table anymore if we didn't want to. Function name that I added that to
// is draw_background_and_margin(*app, view, is_active_view)
internal void
set_margin_color(u32 color_u32)
{
  active_color_table.arrays[defcolor_margin_active].vals[0] = color_u32;
}

internal void
modal_state_set_margin_color(Application_Links *app, View_ID view)
{
  Modal_State_ID modal_state;
  
  if(*app_get_is_global_modal_state_ptr(app))
  {
    modal_state = *app_get_global_modal_state_ptr(app);
  }
  else
  {
    modal_state = view_get_modal_state(app, view);
  }
  
  switch(modal_state)
  {
    case Modal_State_Insert:
    {
      set_margin_color(active_color_table.arrays[custom_color_margin_insert_mode_color].vals[0]);
    } break;
    
    case Modal_State_Command:
    {
      set_margin_color(active_color_table.arrays[custom_color_margin_command_mode_color].vals[0]);
    } break;
  }
}

internal b32 
view_set_mark_record(Application_Links *app, View_ID view, Buffer_Seek seek)
{
  b32 result = view_set_mark(app, view, seek);
  view_record_mark(app, view);
  return(result);
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
  
  String_ID global_mapid = vars_save_string_lit("keys_global");
  String_ID file_mapid = vars_save_string_lit("keys_file");
  String_ID code_mapid = vars_save_string_lit("keys_code");
  
  command_mapid = vars_save_string_lit("command_mapid_string");
  insert_mapid = vars_save_string_lit("insert_mapid_string");
  
  MappingScope();
  SelectMapping(&framework_mapping);
  
  SelectMap(global_mapid);
  BindCore(default_startup, CoreCode_Startup);
  BindCore(default_try_exit, CoreCode_TryExit);
  cakez_bind_shared_keys(m, map);
  
  SelectMap(command_mapid);
  ParentMap(global_mapid);
  cakez_bind_command_keys(m, map);
  
  SelectMap(insert_mapid);
  ParentMap(global_mapid);
  cakez_bind_text_input(m, map);
  
  // NOTE(nates): You have to bind the "global_map, file_map, and code_map for some reason"
  SelectMap(file_mapid);
  ParentMap(command_mapid);
  
  SelectMap(code_mapid);
  ParentMap(command_mapid);
  
  app_set_maps(app, command_mapid, insert_mapid);
  b32 *is_global_modal = app_get_is_global_modal_state_ptr(app);
  *is_global_modal = false;
  if(*is_global_modal)
  {
    Modal_State_ID *global_state = app_get_global_modal_state_ptr(app);
    *global_state = Modal_State_Command;
  }
}

#endif