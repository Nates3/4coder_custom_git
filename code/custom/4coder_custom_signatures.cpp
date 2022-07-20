
///////////////////////////////////////
// NOTE(nates): Own custom commands

// NOTE(nates): Look at 4coder_custom_variables.h
//              and 4coder_custom_functions.cpp

// NOTE(nates): All these CUSTOM_COMMAND_SIGS's are just functions
// you can call them if you want to!

CUSTOM_COMMAND_SIG(change_to_command_mode)
CUSTOM_DOC("Sets the view's buffer keymap to the command_keymap")
{
  View_ID view = get_active_view(app, 0);
  Buffer_ID buffer = view_get_buffer(app, view, 0);
  
  Modal_State_ID modal_state;
  b32 *is_global_modal = app_get_is_global_modal_state_ptr(app);
  Modal_State_ID *app_modal_state = app_get_global_modal_state_ptr(app);
  if (*is_global_modal)
  {
    modal_state = *app_modal_state;
  }
  else
  {
    modal_state = view_get_modal_state(app, view);
  }
  
  if (modal_state != Modal_State_Command)
  {
    if (*is_global_modal)
    {
      *app_modal_state = Modal_State_Command;
    }
    else
    {
      view_set_modal_state(app, view, Modal_State_Command);
    }
    
    i64 cursor_pos = view_get_cursor_pos(app, view);
    if (cursor_pos > 0)
    {
      i64 cursor_line_before = get_line_number_from_pos(app, buffer, cursor_pos);
      i64 cursor_line_after = get_line_number_from_pos(app, buffer, cursor_pos - 1);
      
      if (cursor_line_after == cursor_line_before)
      {
        view_set_cursor(app, view, seek_pos(cursor_pos - 1));
      }
    }
    
    // Set Keybinds for Command Mode only
    b32 result = view_set_buffer(app, view, buffer, 0);
    set_command_map_id(app, buffer, (Command_Map_ID)command_mapid);
  }
}

CUSTOM_COMMAND_SIG(change_to_command_mode_dont_move)
CUSTOM_DOC("Sets the view's buffer keymap to the command_keymap, but doesn't move the cursor")
{
  View_ID view = get_active_view(app, 0);
  Buffer_ID buffer = view_get_buffer(app, view, 0);
  
  Modal_State_ID modal_state;
  b32 *is_global_modal = app_get_is_global_modal_state_ptr(app);
  Modal_State_ID *app_modal_state = app_get_global_modal_state_ptr(app);
  if (*is_global_modal)
  {
    modal_state = *app_modal_state;
  }
  else
  {
    modal_state = view_get_modal_state(app, view);
  }
  
  if (modal_state != Modal_State_Command)
  {
    if (*is_global_modal)
    {
      *app_modal_state = Modal_State_Command;
    }
    else
    {
      view_set_modal_state(app, view, Modal_State_Command);
    }
    
    // Set Keybinds for Command Mode only
    b32 result = view_set_buffer(app, view, buffer, 0);
    set_command_map_id(app, buffer, (Command_Map_ID)command_mapid);
  }
}

CUSTOM_COMMAND_SIG(change_to_insert_mode_front)
CUSTOM_DOC("Sets the view's buffer keymap to the insert_keymap")
{
  View_ID view = get_active_view(app, 0);
  Buffer_ID buffer = view_get_buffer(app, view, 0);
  
  // TODO(cakez77): Switch on the view type? Only change in certain views?
  Modal_State_ID modal_state;
  
  b32 *is_global_modal = app_get_is_global_modal_state_ptr(app);
  Modal_State_ID *app_modal_state = app_get_global_modal_state_ptr(app);
  if (*is_global_modal)
  {
    modal_state = *app_modal_state;
  }
  else
  {
    modal_state = view_get_modal_state(app, view);
  }
  
  if (modal_state != Modal_State_Insert)
  {
    if (*is_global_modal)
    {
      *app_modal_state = Modal_State_Insert;
    }
    else
    {
      view_set_modal_state(app, view, Modal_State_Insert);
    }
    
    // Set Keybinds for Command Mode only
    b32 result = view_set_buffer(app, view, buffer, 0);
    set_command_map_id(app, buffer, (Command_Map_ID)insert_mapid);
  }
}

CUSTOM_COMMAND_SIG(change_to_insert_mode_after)
CUSTOM_DOC("Sets the view's buffer keymap to the insert_keymap")
{
  View_ID view = get_active_view(app, 0);
  Buffer_ID buffer = view_get_buffer(app, view, 0);
  
  // TODO(cakez77): Switch on the view type? Only change in certain views?
  Modal_State_ID modal_state;
  
  b32 *is_global_modal = app_get_is_global_modal_state_ptr(app);
  Modal_State_ID *app_modal_state = app_get_global_modal_state_ptr(app);
  if (*is_global_modal)
  {
    modal_state = *app_modal_state;
  }
  else
  {
    modal_state = view_get_modal_state(app, view);
  }
  
  if (modal_state != Modal_State_Insert)
  {
    if (*is_global_modal)
    {
      *app_modal_state = Modal_State_Insert;
    }
    else
    {
      view_set_modal_state(app, view, Modal_State_Insert);
    }
    
    // Set Keybinds for Command Mode only
    b32 result = view_set_buffer(app, view, buffer, 0);
    set_command_map_id(app, buffer, (Command_Map_ID)insert_mapid);
  }
  
  i64 cursor_pos = view_get_cursor_pos(app, view);
  view_set_cursor(app, view, seek_pos(cursor_pos + 1));
}

CUSTOM_COMMAND_SIG(jump_from_brace_to_brace)
CUSTOM_DOC("Jump from Brace to brace")
{
  View_ID view = get_active_view(app, Access_ReadVisible);
  Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
  i64 cursor_pos = view_get_cursor_pos(app, view);
  u8 char_under_cursor = buffer_get_char(app, buffer, cursor_pos);
  u8 prev_char_under_cursor = buffer_get_char(app, buffer, cursor_pos - 1);
  i64 bracePos;
  
  if (char_under_cursor == '{' || prev_char_under_cursor == '{')
  {
    if (find_nest_side(app, buffer, prev_char_under_cursor == '{' ? cursor_pos : cursor_pos + 1,
                       FindNest_Scope | FindNest_Balanced | FindNest_EndOfToken,
                       Scan_Forward, NestDelim_Close, &bracePos))
    {
      view_set_cursor(app, view, Buffer_Seek{buffer_seek_pos, bracePos - 1});
    }
  }
  else if (char_under_cursor == '}' || prev_char_under_cursor == '}')
  {
    if (find_nest_side(app, buffer, prev_char_under_cursor == '}' ? cursor_pos - 2 : cursor_pos - 1,
                       FindNest_Scope | FindNest_Balanced,
                       Scan_Backward, NestDelim_Open, &bracePos))
    {
      view_set_cursor(app, view, Buffer_Seek{buffer_seek_pos, bracePos});
    }
  }
  else
  {
    if (find_nest_side(app, buffer, cursor_pos, FindNest_Scope,
                       Scan_Forward, NestDelim_Open, &bracePos))
    {
      view_set_cursor(app, view, Buffer_Seek{buffer_seek_pos, bracePos});
    }
  }
}

CUSTOM_COMMAND_SIG(vim_yank_line)
CUSTOM_DOC("Copies lines if in select mode, but yanks line if otherwise")
{
  View_ID view = get_active_view(app, Access_ReadVisible);
  Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
  
  b32 *is_selecting = view_get_is_selecting(app, view);
  if (is_selecting && *is_selecting)
  {
    copy(app);
  }
  else
  {
    b32 *yanked_entire_line = view_get_yanked_entire_line(app, view);
    if (yanked_entire_line)
    {
      *yanked_entire_line = true;
    }
    i64 cursor_pos = view_get_cursor_pos(app, view);
    i64 cursor_line = get_line_number_from_pos(app, buffer, cursor_pos);
    Range_i64 line_range = {cursor_line, cursor_line};
    Range_i64 range = get_pos_range_from_line_range(app, buffer, line_range);
    clipboard_post_buffer_range(app, 0, buffer, range);
  }
}

CUSTOM_COMMAND_SIG(vim_paste)
CUSTOM_DOC("If you yank a line, this will add a new line under the line you're on and paste the yank result there")
{
  View_ID view = get_active_view(app, Access_ReadVisible);
  Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
  
  History_Group group = history_group_begin(app, buffer);
  
  b32 *yanked_entire_line = view_get_yanked_entire_line(app, view);
  if (yanked_entire_line && *yanked_entire_line)
  {
    seek_end_of_textual_line(app);
    write_text(app, SCu8("\n"));
  }
  
  paste(app);
  
  history_group_end(group);
}

CUSTOM_COMMAND_SIG(select_lines)
CUSTOM_DOC("Selects a line region that can be used inside other commantds like copy, paste, cut, or delete")
{
  View_ID view = get_active_view(app, Access_ReadVisible);
  Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
  
  b32 *is_selecting = view_get_is_selecting(app, view);
  b32 *is_cutting = view_get_is_cutting(app, view);
  if (is_selecting && is_cutting && !(*is_cutting))
  {
    if (!(*is_selecting))
    {
      *is_selecting = true;
      i64 cursor_pos = view_get_cursor_pos(app, view);
      i64 cursor_line = get_line_number_from_pos(app, buffer, cursor_pos);
      
      view_set_selection_begin(app, view, cursor_line);
      view_set_selection_end(app, view, cursor_line);
    }
    else
    {
      *is_selecting = false;
    }
  }
}

CUSTOM_COMMAND_SIG(combine_two_lines)
CUSTOM_DOC("combine two lines")
{
  seek_end_of_line(app);
  delete_char(app);
}

CUSTOM_COMMAND_SIG(new_line_and_switch_to_insert)
CUSTOM_DOC("add new line and switch to insert mode")
{
  seek_end_of_textual_line(app);
  change_to_insert_mode_front(app);
  write_text(app, SCu8("\n"));
}

CUSTOM_COMMAND_SIG(move_cursor_to_beginning_and_switch_to_insert)
CUSTOM_DOC("add new line and switch to insert mode")
{
  seek_beginning_of_textual_line(app);
  change_to_insert_mode_front(app);
}


CUSTOM_COMMAND_SIG(cancel_command)
CUSTOM_DOC("cancel context modes")
{
  View_ID view = get_active_view(app, Access_ReadWriteVisible);
  b32 *is_selecting = view_get_is_selecting(app, view);
  b32 *is_cutting = view_get_is_cutting(app, view);
  
  if (is_selecting && *is_selecting)
  {
    *is_selecting = false;
  }
  
  if (is_cutting && *is_cutting)
  {
    *is_cutting = false;
  }
}

CUSTOM_COMMAND_SIG(insert_return)
CUSTOM_DOC("copy of text input but just for return, so you can hit return in command mode")
{
  User_Input in = get_current_input(app);
  char Value = in.event.text.string.str[0];
  if (Value == 10)
  {
    write_text_and_auto_indent(app);
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
  jump_to_definition_at_cursor(app);
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
  Code_Index_Note_Kind forward_declare_kind = CodeIndexNote_ForwardDeclaration;
  Code_Index_Note_Kind comment_note_kind = CodeIndexNote_CommentNOTE;
  Code_Index_Note_Kind comment_todo_kind = CodeIndexNote_CommentTODO;
  Code_Index_Note_Kind namespace_kind = CodeIndexNote_Namespace;
  
  lister_add_item(sort_lister, SCu8("Types"), SCu8(""), &type_kind, 0);
  lister_add_item(sort_lister, SCu8("Functions"), SCu8(""), &function_kind, 0);
  lister_add_item(sort_lister, SCu8("Macros"), SCu8(""), &macro_kind, 0);
  lister_add_item(sort_lister, SCu8("Enums"), SCu8(""), &enum_kind, 0);
  lister_add_item(sort_lister, SCu8("Declarations"), SCu8(""), &forward_declare_kind, 0);
  lister_add_item(sort_lister, SCu8("Todos"), SCu8(""), &comment_todo_kind, 0);
  lister_add_item(sort_lister, SCu8("Notes"), SCu8(""), &comment_note_kind, 0);
  lister_add_item(sort_lister, SCu8("Namespaces"), SCu8(""), &namespace_kind, 0);
  
  Lister_Result sort_result = run_lister(app, sort_lister);
  if (!sort_result.canceled &&
      sort_result.user_data)
  {
    Code_Index_Note_Kind users_type = *(Code_Index_Note_Kind *)sort_result.user_data;
    
    char *query = "Definition:";
    Lister_Block lister(app, scratch);
    lister_set_query(lister, query);
    lister_set_default_handlers(lister);
    
    code_index_lock();
    for (Buffer_ID buffer = get_buffer_next(app, 0, Access_Always);
         buffer != 0;
         buffer = get_buffer_next(app, buffer, Access_Always))
    {
      Code_Index_File *file = code_index_get_file(buffer);
      if (file != 0)
      {
        for (i32 i = 0; i < file->note_array.count; i += 1)
        {
          Code_Index_Note *note = file->note_array.ptrs[i];
          Tiny_Jump *jump = push_array(scratch, Tiny_Jump, 1);
          jump->buffer = buffer;
          jump->pos = note->pos.first;
          
          String_Const_u8 sort = {};
          if (users_type == note->note_kind)
          {
            switch (note->note_kind)
            {
              case CodeIndexNote_Type:
              {
                sort = string_u8_litexpr("Type");
              }
              break;
              case CodeIndexNote_Function:
              {
                sort = string_u8_litexpr("Function");
              }
              break;
              case CodeIndexNote_Macro:
              {
                sort = string_u8_litexpr("Macro");
              }
              break;
              case CodeIndexNote_Enum:
              {
                sort = string_u8_litexpr("Enum");
              }
              break;
              
              case CodeIndexNote_ForwardDeclaration:
              {
                sort = string_u8_litexpr("Declaration");
              }
              break;
              
              case CodeIndexNote_CommentNOTE:
              {
                sort = string_u8_litexpr("Note");
              }
              break;
              
              case CodeIndexNote_CommentTODO:
              {
                sort = string_u8_litexpr("Todo");
              }
              break;
              
              case CodeIndexNote_Namespace:
              {
                sort = string_u8_litexpr("Namespace");
              } break;
              
              case CodeIndexNote_4coderCommand:
              {
                continue;
              }
              
              InvalidDefaultCase;
            }
            
            lister_add_item(lister, note->text, sort, jump, 0);
          }
        }
      }
    }
    code_index_unlock();
    
    Lister_Result l_result = run_lister(app, lister);
    Tiny_Jump result = {};
    if (!l_result.canceled && l_result.user_data != 0)
    {
      block_copy_struct(&result, (Tiny_Jump *)l_result.user_data);
    }
    
    if (result.buffer != 0)
    {
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
  
  if (mark_history->rel_index <= 1)
  {
    if (mark_history->rel_index == 1)
    {
      mark_history->rel_index = 0;
    }
    
    if (mark_history->rel_index < 0)
    {
      mark_history->rel_index++;
    }
    
    i32 index = mark_history->recent_index + mark_history->rel_index;
    if (index < 0)
    {
      index += MARK_HISTORY_ARRAY_COUNT;
    }
    
    i64 mark_pos = mark_history->marks[index];
    view_set_cursor_and_preferred_x_no_set_mark_rel_index(app, view, seek_pos(mark_pos));
  }
}

CUSTOM_COMMAND_SIG(goto_prev_mark)
CUSTOM_DOC("moves backward in mark history")
{
  View_ID view = get_active_view(app, Access_ReadVisible);
  Mark_History *mark_history = view_get_mark_history(app, view);
  
  if (mark_history->rel_index > -mark_history->mark_count)
  {
    if (mark_history->rel_index > -mark_history->mark_count + 1)
    {
      mark_history->rel_index--;
    }
    
    i32 index = mark_history->recent_index + mark_history->rel_index;
    if (index < 0)
    {
      index += MARK_HISTORY_ARRAY_COUNT;
    }
    
    i64 mark_pos = mark_history->marks[index];
    view_set_cursor_and_preferred_x_no_set_mark_rel_index(app, view, seek_pos(mark_pos));
  }
}


CUSTOM_COMMAND_SIG(toggle_compilation_expand)
CUSTOM_DOC("Expand the compilation window.")
{
  Buffer_ID buffer = view_get_buffer(app, global_compilation_view, Access_Always);
  Face_ID face_id = get_face_id(app, buffer);
  Face_Metrics metrics = get_face_metrics(app, face_id);
  if(global_compilation_view_expanded ^= 1)
  {
    view_set_split_pixel_size(app, global_compilation_view, (i32)(metrics.line_height*40.0f));
  }
  else
  {
    view_set_split_pixel_size(app, global_compilation_view, (i32)(metrics.line_height*4.0f));
  }
}

CUSTOM_COMMAND_SIG(custom_startup)
CUSTOM_DOC("custom startup")
{
  User_Input input = get_current_input(app);
  if(!match_core_code(&input, CoreCode_Startup))
  {
    return;
  }
  
  String_Const_u8_Array file_names = input.event.core.file_names;
  load_themes_default_folder(app);
  default_4coder_initialize(app, file_names);
  
  // NOTE(nates): Create buffers
  {
    {
      Buffer_ID buffer = create_buffer(app, string_u8_litexpr("*compilation*"),
                                       BufferCreate_NeverAttachToFile |
                                       BufferCreate_AlwaysNew);
      buffer_set_setting(app, buffer, BufferSetting_Unimportant, true);
      buffer_set_setting(app, buffer, BufferSetting_ReadOnly, true);
    }
  }
  
  // NOTE(nates): Set up panels
  {
    Buffer_Identifier comp = buffer_identifier(string_u8_litexpr("*compilation*"));
    Buffer_Identifier left = buffer_identifier(string_u8_litexpr("*scratch*"));
    Buffer_Identifier right = buffer_identifier(string_u8_litexpr("*messages*"));
    Buffer_ID comp_id = buffer_identifier_to_id(app, comp);
    Buffer_ID left_id = buffer_identifier_to_id(app, left);
    Buffer_ID right_id = buffer_identifier_to_id(app, right);
    
    View_ID view = get_active_view(app, Access_Always);
    new_view_settings(app, view);
    view_set_buffer(app, view, left_id, 0);
    
    // NOTE(nates): Compilation panel
    View_ID compilation_view = 0;
    {
      compilation_view = open_view(app, view, ViewSplit_Bottom);
      new_view_settings(app, compilation_view);
      Buffer_ID buffer = view_get_buffer(app, compilation_view, Access_Always);
      Face_ID face_id = get_face_id(app, buffer);
      Face_Metrics metrics = get_face_metrics(app, face_id);
      view_set_split_pixel_size(app, compilation_view, (i32)(metrics.line_height*4.f));
      view_set_passive(app, compilation_view, true);
      global_compilation_view = compilation_view;
      view_set_buffer(app, compilation_view, comp_id, 0);
    }
    
    view_set_active(app, view);
    
    // NOTE(nates): Right Panel
    open_panel_vsplit(app);
    
    View_ID right_view = get_active_view(app, Access_Always);
    view_set_buffer(app, right_view, right_id, 0);
    
    // NOTE(nates): Restore Active to Left
    view_set_active(app, view);
  }
  
  // NOTE(nates): Audio
  {
    def_audio_init();
  }
  
  // NOTE(nates): Load project
  {
    b32 auto_load = def_get_config_b32(vars_save_string_lit("automatically_load_project"));
    if (auto_load)
    {
      load_project(app);
    }
  }
  
  
  // NOTE(nates): View stuff
  {
    app_set_maps(app, command_mapid, insert_mapid);
    b32 *is_global_modal = app_get_is_global_modal_state_ptr(app);
    *is_global_modal = false;
    if(*is_global_modal)
    {
      Modal_State_ID *global_state = app_get_global_modal_state_ptr(app);
      *global_state = Modal_State_Command;
    }
  }
}
