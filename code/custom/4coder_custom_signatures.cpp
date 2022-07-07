
///////////////////////////////////////
// NOTE(nates): Own custom commands


#if 0
CUSTOM_COMMAND_SIG(select_lines)
CUSTOM_DOC("selects entire line")
{
  View_ID view = get_active_view(app, Access_ReadVisible);
  Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
  i64 cursor_pos = view_get_cursor_pos(app, view);
  i64 line_number = get_line_number_from_pos(app, buffer, cursor_pos);
  i64 line_end_pos = get_line_end_pos(app, buffer, line_number);
  
  
  view_set_cursor_and_preferred_x(app, view, seek_pos(line_end_pos));
  view_set_mark(app, view, seek_pos(line_start_pos));
}
#endif

CUSTOM_COMMAND_SIG(combine_two_lines)
CUSTOM_DOC("combine some lines yo")
{
  seek_end_of_line(app);
  delete_char(app);
}

CUSTOM_COMMAND_SIG(insert_return)
CUSTOM_DOC("dummy_wrapper for return")
{
  User_Input in = get_current_input(app);
  char Value = in.event.text.string.str[0];
  if(Value == 10)
  {
    write_text_input(app);
  }
  else
  {
    leave_current_input_unhandled(app);
  }
}

CUSTOM_COMMAND_SIG(control_plus_click_jump_to_definition)
CUSTOM_DOC("control + click to jump to the definition")
{
  View_ID view = get_active_view(app, Access_ReadVisible);
  Mouse_State mouse = get_mouse_state(app);
  i64 pos = view_pos_from_xy(app, view, V2f32(mouse.p));
  view_set_cursor_and_preferred_x(app, view, seek_pos(pos));
  no_mark_snap_to_cursor(app, view);
  jump_to_definition_at_cursor_other_panel(app);
}


CUSTOM_UI_COMMAND_SIG(jump_to_definition_sorted)
CUSTOM_DOC("Sorts all note types and lists the ones user choeses.")
{
  Scratch_Block scratch(app);
  
  Lister_Block sort_lister(app, scratch);
  char *sort_query = "Type:";
  lister_set_query(sort_lister, sort_query);
  lister_set_default_handlers(sort_lister);
  
  
  Code_Index_Note_Kind type_kind = CodeIndexNote_Type;
  Code_Index_Note_Kind function_kind = CodeIndexNote_Function;
  Code_Index_Note_Kind macro_kind = CodeIndexNote_Macro;
  Code_Index_Note_Kind enum_kind = CodeIndexNote_Enum;
  
  lister_add_item(sort_lister, SCu8("types"), SCu8(""), &type_kind, 0);
  lister_add_item(sort_lister, SCu8("functions"), SCu8(""), &function_kind, 0);
  lister_add_item(sort_lister, SCu8("macros"), SCu8(""), &macro_kind, 0);
  lister_add_item(sort_lister, SCu8("enums"), SCu8(""), &enum_kind, 0);
  
  Lister_Result sort_result = run_lister(app, sort_lister);
  if(!sort_result.canceled)
  {
    Code_Index_Note_Kind users_type = *(Code_Index_Note_Kind *)sort_result.user_data;
    
    
    char *query = "Definition:";
    Lister_Block lister(app, scratch);
    lister_set_query(lister, query);
    lister_set_default_handlers(lister);
    
    code_index_lock();
    for (Buffer_ID buffer = get_buffer_next(app, 0, Access_Always);
         buffer != 0;
         buffer = get_buffer_next(app, buffer, Access_Always)){
      Code_Index_File *file = code_index_get_file(buffer);
      if (file != 0){
        for (i32 i = 0; i < file->note_array.count; i += 1){
          Code_Index_Note *note = file->note_array.ptrs[i];
          Tiny_Jump *jump = push_array(scratch, Tiny_Jump, 1);
          jump->buffer = buffer;
          jump->pos = note->pos.first;
          
          String_Const_u8 sort = {};
          if(users_type == note->note_kind)
          {
            switch (note->note_kind)
            {
              case CodeIndexNote_Type:
              {
                sort = string_u8_litexpr("type");
              }break;
              case CodeIndexNote_Function:
              {
                sort = string_u8_litexpr("function");
              }break;
              case CodeIndexNote_Macro:
              {
                sort = string_u8_litexpr("macro");
              }break;
              case CodeIndexNote_Enum:
              {
                sort = string_u8_litexpr("enum");
              }break;
            }
            lister_add_item(lister, note->text, sort, jump, 0);
          }
        }
      }
    }
    code_index_unlock();
    
    Lister_Result l_result = run_lister(app, lister);
    Tiny_Jump result = {};
    if (!l_result.canceled && l_result.user_data != 0){
      block_copy_struct(&result, (Tiny_Jump*)l_result.user_data);
    }
    
    if (result.buffer != 0){
      View_ID view = get_this_ctx_view(app, Access_Always);
      point_stack_push_view_cursor(app, view);
      jump_to_location(app, view, result.buffer, result.pos);
    }
  }
}


CUSTOM_COMMAND_SIG(goto_next_mark)
CUSTOM_DOC("moves forward in mark history if user has searched backwards in history")
{
  View_ID view = get_active_view(app, Access_ReadVisible);
  Mark_History *mark_history = view_get_mark_history(app, view);
  
  if(global_relative_mark_history_index < 0)
  {
    global_relative_mark_history_index++;
    i32 index = mark_history->recent_index + global_relative_mark_history_index;
    if(index < 0)
    {
      index += mark_history->max_mark_count;
    }
    
    i64 mark_pos = mark_history->marks[index];
    view_set_cursor_and_preferred_x(app, view, seek_pos(mark_pos));
  }
  
}

CUSTOM_COMMAND_SIG(goto_prev_mark)
CUSTOM_DOC("moves backward in mark history")
{
  View_ID view = get_active_view(app, Access_ReadVisible);
  Mark_History *mark_history = view_get_mark_history(app, view);
  
  if(global_relative_mark_history_index > -(mark_history->mark_count - 1))
  {
    global_relative_mark_history_index--;
    i32 index = mark_history->recent_index + global_relative_mark_history_index;
    if(index < 0)
    {
      index += mark_history->max_mark_count;
    }
    
    i64 mark_pos = mark_history->marks[index];
    view_set_cursor_and_preferred_x(app, view, seek_pos(mark_pos));
  }
}