

// TODO(nates): Figure out a way to load bindings from a file 
// it should support keymaps aswell


/////////////////////////////////
// NOTE(nates): Cakez's bindings

internal void
cakez_bind_shared_keys(Mapping *m, Command_Map *map)
{
  Bind(change_to_command_mode, KeyCode_Escape);
  Bind(command_lister, KeyCode_X, KeyCode_Alt);
  Bind(backspace_char, KeyCode_Backspace);
  Bind(delete_char, KeyCode_Delete);
  Bind(interactive_open_or_new, KeyCode_O, KeyCode_Control);
  Bind(interactive_switch_buffer, KeyCode_I, KeyCode_Control);
  Bind(word_complete, KeyCode_Tab);
  Bind(word_complete_drop_down, KeyCode_Tab, KeyCode_Shift);
  Bind(change_active_panel, KeyCode_1, KeyCode_Control);
  Bind(build_in_build_panel, KeyCode_B, KeyCode_Control, KeyCode_Shift);
  Bind(toggle_fullscreen, KeyCode_F11);
  Bind(exit_4coder, KeyCode_F4, KeyCode_Alt);
  Bind(load_project, KeyCode_L, KeyCode_Control, KeyCode_Shift);
  Bind(quick_swap_buffer, KeyCode_BackwardSlash, KeyCode_Alt);
  Bind(save, KeyCode_S, KeyCode_Control);
  Bind(save_all_dirty_buffers, KeyCode_S, KeyCode_Control, KeyCode_Shift);
  
  BindMouse(control_plus_click_jump_to_definition, MouseCode_Left, KeyCode_Control);
  BindMouse(click_set_cursor_and_mark, MouseCode_Left);
  BindMouseMove(click_set_cursor_if_lbutton);
  BindMouseWheel(mouse_wheel_scroll);
  BindMouseWheel(mouse_wheel_change_face_size, KeyCode_Control);
  
  Bind(jump_to_definition_at_cursor, KeyCode_W, KeyCode_Control);
  Bind(jump_to_definition_at_cursor_other_panel, KeyCode_W, KeyCode_Alt);
  Bind(jump_to_definition, KeyCode_Q, KeyCode_Control);
  
  Bind(move_left, KeyCode_Left);
  Bind(move_right, KeyCode_Right);
  Bind(move_up, KeyCode_Up);
  Bind(move_down, KeyCode_Down);
}

internal void
cakez_bind_command_keys(Mapping *m, Command_Map *map)
{
  Bind(cut, KeyCode_C);
  Bind(copy, KeyCode_Y);
  Bind(set_mark, KeyCode_Space);
  Bind(goto_next_mark, KeyCode_Equal);
  Bind(goto_prev_mark, KeyCode_Minus);
  Bind(delete_range, KeyCode_D);
  //Bind(select_entire_line, KeyCode_V, KeyCode_Shift);
  Bind(combine_two_lines, KeyCode_J, KeyCode_Shift);
  Bind(undo, KeyCode_U);
  Bind(redo, KeyCode_R, KeyCode_Control);
  Bind(change_to_text_mode, KeyCode_A);
  Bind(change_to_text_mode_2, KeyCode_I);
  BindTextInput(insert_return);
  Bind(auto_indent_range, KeyCode_F, KeyCode_Shift);
  Bind(search, KeyCode_F);
  Bind(reverse_search, KeyCode_F, KeyCode_Shift);
  Bind(jump_from_brace_to_brace, KeyCode_5, KeyCode_Shift);
  
  Bind(move_up, KeyCode_K);
  Bind(move_down, KeyCode_J);
  Bind(move_left, KeyCode_H);
  Bind(move_right, KeyCode_L);
  
  Bind(move_up_10, KeyCode_J, KeyCode_Alt);
  Bind(move_down_10, KeyCode_K, KeyCode_Alt);
  
  Bind(move_right_alpha_numeric_boundary, KeyCode_E);
  Bind(move_left_alpha_numeric_boundary, KeyCode_W);
  Bind(seek_end_of_line, KeyCode_E, KeyCode_Shift);
  Bind(seek_beginning_of_line, KeyCode_W, KeyCode_Shift);
}

internal void
cakez_bind_text_input(Mapping *m, Command_Map *map)
{
  BindTextInput(write_text_and_auto_indent);
}


/////////////////////////////
// NOTE(nates): Meh bindings

internal void
nates_bind_shared_keys(Mapping *m, Command_Map *map)
{
  Bind(change_to_command_mode, KeyCode_Escape);
  Bind(command_lister, KeyCode_Q, KeyCode_Alt);
  Bind(backspace_char, KeyCode_Backspace);
  Bind(backspace_alpha_numeric_boundary, KeyCode_Backspace, KeyCode_Control);
  Bind(delete_char, KeyCode_Delete);
  Bind(delete_alpha_numeric_boundary, KeyCode_Delete, KeyCode_Control);
  Bind(quick_swap_buffer, KeyCode_BackwardSlash, KeyCode_Alt);
  Bind(word_complete, KeyCode_Tab);
  Bind(word_complete_drop_down, KeyCode_Tab, KeyCode_Control);
  Bind(save, KeyCode_S, KeyCode_Control);
  Bind(save_all_dirty_buffers, KeyCode_S, KeyCode_Control, KeyCode_Shift);
  
  BindMouse(control_plus_click_jump_to_definition, MouseCode_Left, KeyCode_Control);
  BindMouse(click_set_cursor_and_mark, MouseCode_Left);
  BindMouseMove(click_set_cursor_if_lbutton);
  BindMouseWheel(mouse_wheel_scroll);
  BindMouseWheel(mouse_wheel_change_face_size, KeyCode_Control);
  
  Bind(interactive_open_or_new, KeyCode_R, KeyCode_Control);
  Bind(interactive_switch_buffer, KeyCode_C, KeyCode_Control);
  Bind(change_active_panel, KeyCode_J, KeyCode_Alt);
  Bind(build_in_build_panel, KeyCode_M, KeyCode_Alt);
  Bind(toggle_fullscreen, KeyCode_F11);
  Bind(exit_4coder, KeyCode_F4, KeyCode_Alt);
  Bind(load_project, KeyCode_L, KeyCode_Control, KeyCode_Shift);
  
  Bind(jump_to_definition_at_cursor, KeyCode_Comma, KeyCode_Control);
  Bind(jump_to_definition_at_cursor_other_panel, KeyCode_Comma, KeyCode_Alt);
  Bind(jump_to_definition, KeyCode_Quote, KeyCode_Control);
  Bind(goto_next_jump, KeyCode_N, KeyCode_Alt);
  Bind(goto_prev_jump, KeyCode_N, KeyCode_Alt, KeyCode_Shift);
  
  Bind(move_left, KeyCode_Left);
  Bind(move_right, KeyCode_Right);
  Bind(move_up, KeyCode_Up);
  Bind(move_down, KeyCode_Down);
}

internal void
nates_bind_command_keys(Mapping *m, Command_Map *map)
{
  Bind(cut, KeyCode_Q);
  Bind(copy, KeyCode_J);
  Bind(paste, KeyCode_K);
  Bind(set_mark, KeyCode_Space);
  Bind(goto_next_mark, KeyCode_Equal);
  Bind(goto_prev_mark, KeyCode_Minus);
  
  Bind(delete_range, KeyCode_E);
  //Bind(select_entire_line, KeyCode_J, KeyCode_Shift);
  Bind(search, KeyCode_U);
  Bind(reverse_search, KeyCode_U, KeyCode_Shift);
  //Bind(combine_two_lines, KeyCode_H, KeyCode_Shift);
  Bind(undo, KeyCode_Semicolon);
  Bind(redo, KeyCode_Semicolon, KeyCode_Shift);
  Bind(change_to_text_mode, KeyCode_A);
  //Bind(change_to_text_mode_2, KeyCode_I);
  BindTextInput(insert_return);
  
  Bind(move_up, KeyCode_C);
  Bind(move_down, KeyCode_T);
  Bind(move_left, KeyCode_H);
  Bind(move_right, KeyCode_N);
  
  Bind(move_up_10, KeyCode_C, KeyCode_Alt);
  Bind(move_down_10, KeyCode_T, KeyCode_Alt);
  
  Bind(move_right_alpha_numeric_boundary, KeyCode_N, KeyCode_Control);
  Bind(move_left_alpha_numeric_boundary, KeyCode_H, KeyCode_Control);
  Bind(seek_end_of_line, KeyCode_N, KeyCode_Shift);
  Bind(seek_beginning_of_line, KeyCode_H, KeyCode_Shift);
}

internal void
nates_bind_text_input(Mapping *m, Command_Map *map)
{
  BindTextInput(write_text_and_auto_indent);
}

internal void
vedant_bind_command_keys(Mapping *m, Command_Map *map) {
  Bind(goto_beginning_of_file, KeyCode_G, KeyCode_Alt);
  Bind(goto_end_of_file, KeyCode_G, KeyCode_Shift);
  Bind(change_to_append_mode, KeyCode_A);
}
