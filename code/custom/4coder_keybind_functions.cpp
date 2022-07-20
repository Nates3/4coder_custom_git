

// TODO(nates): Figure out a way to load bindings from a file
// it should support keymaps aswell

/////////////////////////////////
// NOTE(nates): Cakez's bindings

internal void
cakez_bind_shared_keys(Mapping *m, Command_Map *map)
{
  Bind(goto_next_jump, KeyCode_N, KeyCode_Alt);
  Bind(goto_prev_jump, KeyCode_P, KeyCode_Alt);
  Bind(move_line_up, KeyCode_K, KeyCode_Alt);
  Bind(move_line_down, KeyCode_J, KeyCode_Alt);
  Bind(change_to_command_mode, KeyCode_Escape);
  Bind(command_lister, KeyCode_X, KeyCode_Alt);
  Bind(backspace_char, KeyCode_Backspace);
  Bind(delete_char, KeyCode_Delete);
  Bind(interactive_open_or_new, KeyCode_O, KeyCode_Control);
  Bind(interactive_switch_buffer, KeyCode_Tab, KeyCode_Control);
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
  Bind(paste, KeyCode_V, KeyCode_Control);
  Bind(toggle_compilation_expand, KeyCode_Insert);
  
  BindMouse(control_plus_click_jump_to_definition, MouseCode_Left, KeyCode_Control);
  BindMouse(click_set_cursor_and_mark, MouseCode_Left);
  BindMouseMove(click_set_cursor_if_lbutton);
  BindMouseWheel(mouse_wheel_scroll);
  BindMouseWheel(mouse_wheel_change_face_size, KeyCode_Control);
  
  Bind(jump_to_definition_at_cursor, KeyCode_W, KeyCode_Control);
  Bind(jump_to_last_point, KeyCode_Minus, KeyCode_Control);
  Bind(jump_to_definition_at_cursor_other_panel, KeyCode_W, KeyCode_Alt);
  Bind(jump_to_definition, KeyCode_Q, KeyCode_Control);
  
  Bind(move_left, KeyCode_Left);
  Bind(move_right, KeyCode_Right);
  Bind(move_up, KeyCode_Up);
  Bind(move_down, KeyCode_Down);
  
  Bind(project_fkey_command, KeyCode_F1);
  Bind(project_fkey_command, KeyCode_F2);
  Bind(project_fkey_command, KeyCode_F3);
  Bind(project_fkey_command, KeyCode_F4);
  Bind(project_fkey_command, KeyCode_F5);
  Bind(project_fkey_command, KeyCode_F6);
  Bind(project_fkey_command, KeyCode_F7);
  Bind(project_fkey_command, KeyCode_F8);
  Bind(project_fkey_command, KeyCode_F9);
  Bind(project_fkey_command, KeyCode_F10);
  // Bind(project_fkey_command, KeyCode_F11);
  Bind(project_fkey_command, KeyCode_F12);
  Bind(project_fkey_command, KeyCode_F13);
  Bind(project_fkey_command, KeyCode_F14);
  Bind(project_fkey_command, KeyCode_F15);
  Bind(project_fkey_command, KeyCode_F16);
}

internal void
cakez_bind_command_keys(Mapping *m, Command_Map *map)
{
  Bind(cancel_command, KeyCode_Escape);
  Bind(vim_cut, KeyCode_C);
  Bind(vim_cut, KeyCode_D);
  Bind(vim_paste, KeyCode_P);
  Bind(vim_yank_line, KeyCode_Y, KeyCode_Shift);
  Bind(copy, KeyCode_Y);
  Bind(set_mark, KeyCode_Space);
  Bind(goto_next_mark, KeyCode_Equal);
  Bind(goto_prev_mark, KeyCode_Minus);
  Bind(select_lines, KeyCode_V, KeyCode_Shift);
  Bind(combine_two_lines, KeyCode_J, KeyCode_Shift);
  Bind(undo, KeyCode_U);
  Bind(redo, KeyCode_R, KeyCode_Control);
  Bind(change_to_insert_mode_after, KeyCode_A);
  Bind(change_to_insert_mode_front, KeyCode_I);
  Bind(move_cursor_to_beginning_and_switch_to_insert, KeyCode_I, KeyCode_Shift);
  Bind(new_line_and_switch_to_insert, KeyCode_O);
  BindTextInput(insert_return);
  Bind(auto_indent_range, KeyCode_F, KeyCode_Shift);
  Bind(search, KeyCode_F);
  Bind(reverse_search, KeyCode_F, KeyCode_Shift);
  Bind(jump_from_brace_to_brace, KeyCode_5, KeyCode_Shift);
  
  Bind(move_up, KeyCode_K);
  Bind(move_down, KeyCode_J);
  Bind(move_left, KeyCode_H);
  Bind(move_right, KeyCode_L);
  
  Bind(move_right_alpha_numeric_boundary, KeyCode_E);
  Bind(move_left_alpha_numeric_boundary, KeyCode_B);
  Bind(seek_end_of_line, KeyCode_4, KeyCode_Shift);
  Bind(seek_beginning_of_line, KeyCode_3, KeyCode_Shift);
  Bind(goto_end_of_file, KeyCode_G, KeyCode_Shift);
  Bind(goto_beginning_of_file, KeyCode_G);
}

internal void
cakez_bind_text_input(Mapping *m, Command_Map *map)
{
  Bind(backspace_alpha_numeric_boundary, KeyCode_Backspace, KeyCode_Control);
  
  BindTextInput(write_text_and_auto_indent);
}

/////////////////////////////
// NOTE(nates): Meh bindings

internal void
nates_bind_shared_keys(Mapping *m, Command_Map *map)
{
  Bind(change_to_command_mode_dont_move, KeyCode_Tab);
  Bind(command_lister, KeyCode_Q, KeyCode_Alt);
  Bind(backspace_char, KeyCode_Backspace);
  Bind(backspace_alpha_numeric_boundary, KeyCode_Backspace, KeyCode_Control);
  Bind(delete_char, KeyCode_Delete);
  Bind(delete_alpha_numeric_boundary, KeyCode_Delete, KeyCode_Control);
  Bind(quick_swap_buffer, KeyCode_BackwardSlash, KeyCode_Alt);
  Bind(view_buffer_other_panel, KeyCode_1, KeyCode_Control);
  Bind(swap_panels, KeyCode_A, KeyCode_Alt);
  Bind(word_complete, KeyCode_P, KeyCode_Control);
  Bind(word_complete_drop_down, KeyCode_P, KeyCode_Alt);
  Bind(center_view, KeyCode_Period, KeyCode_Control);
  Bind(left_adjust_view, KeyCode_Period, KeyCode_Alt);
  Bind(save, KeyCode_S, KeyCode_Control);
  Bind(save_all_dirty_buffers, KeyCode_S, KeyCode_Control, KeyCode_Shift);
  Bind(toggle_compilation_expand, KeyCode_Insert);
  
  Bind(page_up, KeyCode_PageUp);
  Bind(page_down, KeyCode_PageDown);
  
  Bind(cursor_mark_swap, KeyCode_Quote, KeyCode_Alt);
  
  BindMouse(control_plus_click_jump_to_definition, MouseCode_Left, KeyCode_Control);
  BindMouse(click_set_cursor_and_mark, MouseCode_Left);
  BindMouseMove(click_set_cursor_if_lbutton);
  BindMouseWheel(mouse_wheel_scroll);
  BindMouseWheel(mouse_wheel_change_face_size, KeyCode_Control);
  
  Bind(interactive_open_or_new, KeyCode_R, KeyCode_Control);
  Bind(interactive_switch_buffer, KeyCode_G, KeyCode_Control);
  Bind(change_active_panel, KeyCode_J, KeyCode_Alt);
  Bind(build_in_build_panel, KeyCode_M, KeyCode_Alt);
  Bind(toggle_fullscreen, KeyCode_F11);
  Bind(exit_4coder, KeyCode_F4, KeyCode_Alt);
  Bind(load_project, KeyCode_L, KeyCode_Control, KeyCode_Shift);
  
  Bind(jump_to_definition_at_cursor, KeyCode_Comma, KeyCode_Control);
  Bind(jump_to_definition_at_cursor_other_panel, KeyCode_Comma, KeyCode_Alt);
  Bind(jump_to_definition_sorted, KeyCode_Quote, KeyCode_Control);
  Bind(goto_next_jump, KeyCode_B, KeyCode_Alt);
  Bind(goto_prev_jump, KeyCode_B, KeyCode_Alt, KeyCode_Shift);
  
  Bind(move_left, KeyCode_Left);
  Bind(move_right, KeyCode_Right);
  Bind(move_up, KeyCode_Up);
  Bind(move_down, KeyCode_Down);
  
  Bind(move_up_10, KeyCode_Up, KeyCode_Alt);
  Bind(move_down_10, KeyCode_Down, KeyCode_Alt);
  
  Bind(move_right_alpha_numeric_boundary, KeyCode_Right, KeyCode_Control);
  Bind(move_left_alpha_numeric_boundary, KeyCode_Left, KeyCode_Control);
  Bind(move_right_alpha_numeric_or_camel_boundary, KeyCode_Right, KeyCode_Alt);
  Bind(move_left_alpha_numeric_or_camel_boundary, KeyCode_Left, KeyCode_Alt);
  
  Bind(seek_end_of_textual_line, KeyCode_Right, KeyCode_Shift);
  Bind(seek_beginning_of_textual_line, KeyCode_Left, KeyCode_Shift);
  
  
  Bind(project_fkey_command, KeyCode_F1);
  Bind(project_fkey_command, KeyCode_F2);
  Bind(project_fkey_command, KeyCode_F3);
  Bind(project_fkey_command, KeyCode_F4);
  Bind(project_fkey_command, KeyCode_F5);
  Bind(project_fkey_command, KeyCode_F6);
  Bind(project_fkey_command, KeyCode_F7);
  Bind(project_fkey_command, KeyCode_F8);
  Bind(project_fkey_command, KeyCode_F9);
  Bind(project_fkey_command, KeyCode_F10);
  Bind(project_fkey_command, KeyCode_F11);
  Bind(project_fkey_command, KeyCode_F12);
  Bind(project_fkey_command, KeyCode_F13);
  Bind(project_fkey_command, KeyCode_F14);
  Bind(project_fkey_command, KeyCode_F15);
  Bind(project_fkey_command, KeyCode_F16);
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
  Bind(list_all_substring_locations_case_insensitive, KeyCode_Comma);
  Bind(goto_jump_at_cursor, KeyCode_Quote);
  Bind(jump_to_last_point, KeyCode_I);
  Bind(query_replace, KeyCode_O);
  Bind(replace_in_range, KeyCode_O, KeyCode_Control);
  
  Bind(move_line_up, KeyCode_PageUp, KeyCode_Alt);
  Bind(move_line_down, KeyCode_PageDown, KeyCode_Alt);
  
  Bind(delete_range, KeyCode_E);
  Bind(delete_line, KeyCode_E, KeyCode_Alt);
  Bind(select_lines, KeyCode_J, KeyCode_Shift);
  Bind(search, KeyCode_U);
  Bind(reverse_search, KeyCode_U, KeyCode_Shift);
  Bind(undo, KeyCode_Semicolon);
  Bind(redo, KeyCode_Semicolon, KeyCode_Shift);
  Bind(change_to_insert_mode_front, KeyCode_A);
  BindTextInput(insert_return);
  
  Bind(keyboard_macro_start_recording, KeyCode_Minus, KeyCode_Control);
  Bind(keyboard_macro_finish_recording, KeyCode_Minus, KeyCode_Control, KeyCode_Shift);
  Bind(keyboard_macro_replay, KeyCode_Minus, KeyCode_Alt);
  
  Bind(move_up, KeyCode_C);
  Bind(move_down, KeyCode_T);
  Bind(move_left, KeyCode_H);
  Bind(move_right, KeyCode_N);
  
  Bind(move_up_10, KeyCode_C, KeyCode_Alt);
  Bind(move_down_10, KeyCode_T, KeyCode_Alt);
  
  Bind(move_right_alpha_numeric_boundary, KeyCode_N, KeyCode_Control);
  Bind(move_left_alpha_numeric_boundary, KeyCode_H, KeyCode_Control);
  Bind(move_right_alpha_numeric_or_camel_boundary, KeyCode_N, KeyCode_Alt);
  Bind(move_left_alpha_numeric_or_camel_boundary, KeyCode_H, KeyCode_Alt);
  
  Bind(seek_end_of_textual_line, KeyCode_N, KeyCode_Shift);
  Bind(seek_beginning_of_textual_line, KeyCode_H, KeyCode_Shift);
  
  Bind(jump_from_brace_to_brace, KeyCode_Y);
}

internal void
nates_bind_text_input(Mapping *m, Command_Map *map)
{
  BindTextInput(write_text_and_auto_indent);
}
