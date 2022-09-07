
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

internal void
set_margin_color(u32 color_u32)
{
 active_color_table.arrays[defcolor_margin_active].vals[0] = color_u32;
}

internal void
modal_state_set_margin_color(Application_Links *app, View_ID view)
{
 Modal_State modal_state;
 if(app_get_is_global_modal(app))
 {
  modal_state = app_get_global_modal_state(app);
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
