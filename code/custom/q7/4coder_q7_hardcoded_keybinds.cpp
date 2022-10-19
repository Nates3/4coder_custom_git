// TODO(nates): Figure out a way to load bindings from a file
// it should support keymaps aswell

/////////////////////////////////
// NOTE(nates): Cakez's bindings

function void
cakez_bind_global_keys(Mapping *m, Command_Map *map)
{
	Bind(goto_line, KeyCode_G, KeyCode_Control);
	Bind(goto_jump_at_cursor, KeyCode_Q, KeyCode_Control);
	Bind(load_project, KeyCode_R, KeyCode_Shift, KeyCode_Control);
	Bind(q7_list_projects, KeyCode_L, KeyCode_Shift, KeyCode_Control);
	Bind(list_all_substring_locations_case_insensitive, KeyCode_F, KeyCode_Shift, KeyCode_Control);
	Bind(comment_line_toggle, KeyCode_ForwardSlash, KeyCode_Control);
	Bind(q7_toggle_compilation_expand, KeyCode_Tick, KeyCode_Control);
	Bind(center_view, KeyCode_L, KeyCode_Control);
	Bind(goto_next_jump, KeyCode_N, KeyCode_Alt);
	Bind(goto_prev_jump, KeyCode_P, KeyCode_Alt);
	Bind(move_line_up, KeyCode_K, KeyCode_Alt);
	Bind(move_line_down, KeyCode_J, KeyCode_Alt);
	Bind(q7_change_to_normal_mode, KeyCode_Escape);
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
	Bind(quick_swap_buffer, KeyCode_BackwardSlash, KeyCode_Alt);
	Bind(save, KeyCode_S, KeyCode_Control);
	Bind(save_all_dirty_buffers, KeyCode_S, KeyCode_Control, KeyCode_Shift);
	Bind(paste, KeyCode_V, KeyCode_Control);
	Bind(q7_toggle_compilation_expand, KeyCode_Insert);
	
	BindMouse(q7_jump_to_definition_under_mouse, MouseCode_Left, KeyCode_Control);
	BindMouse(click_set_cursor_and_mark, MouseCode_Left);
	BindMouseMove(click_set_cursor_if_lbutton);
	BindMouseWheel(mouse_wheel_scroll);
	BindMouseWheel(mouse_wheel_change_face_size, KeyCode_Control);
	
	Bind(jump_to_definition_at_cursor, KeyCode_W, KeyCode_Control);
	Bind(jump_to_last_point, KeyCode_Minus, KeyCode_Control);
	Bind(jump_to_definition_at_cursor_other_panel, KeyCode_W, KeyCode_Alt);
	
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
cakez_bind_normal_mode_keys(Mapping *m, Command_Map *map)
{
	Bind(q7_delete_alpha_numeric_identifier, KeyCode_X);
	Bind(q7_cancel_command, KeyCode_Escape);
	Bind(q7_cut, KeyCode_C);
	Bind(q7_cut, KeyCode_D);
	Bind(q7_paste, KeyCode_P);
	Bind(q7_yank_line, KeyCode_Y, KeyCode_Shift);
	Bind(copy, KeyCode_Y);
	Bind(set_mark, KeyCode_Space);

 Bind(q7_jump_downwards_using_prevsearch, KeyCode_N);
 Bind(q7_jump_upwards_using_prevsearch, KeyCode_N, KeyCode_Shift);

 // TODO(nates): replace this with jump list 
 // that records jump like searches or changing to other files
#if 0
	Bind(q7_goto_next_mark, KeyCode_Equal);
	Bind(q7_goto_prev_mark, KeyCode_Minus);
#endif
	Bind(q7_select_lines, KeyCode_V, KeyCode_Shift);
	Bind(q7_join_lines, KeyCode_J, KeyCode_Shift);
	Bind(undo, KeyCode_U);
	Bind(redo, KeyCode_R, KeyCode_Control);
	Bind(q7_change_to_insert_mode_after, KeyCode_A);
	Bind(q7_change_to_insert_mode, KeyCode_I);
	Bind(q7_insert_start_of_line, KeyCode_I, KeyCode_Shift);
	Bind(q7_insert_line_below, KeyCode_O);
	Bind(search, KeyCode_F, KeyCode_Control);
	Bind(q7_jump_to_matching_brace, KeyCode_5, KeyCode_Shift);
	
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
cakez_bind_insert_mode_keys(Mapping *m, Command_Map *map)
{
	Bind(backspace_alpha_numeric_boundary, KeyCode_Backspace, KeyCode_Control);
	BindTextInput(write_text_and_auto_indent);
}

#if 0
internal void
nates_bind_global_keys(Mapping *m, Command_Map *map)
{
	Bind(goto_line, KeyCode_G, KeyCode_Control);
	Bind(goto_jump_at_cursor, KeyCode_Q, KeyCode_Control);
	Bind(load_project, KeyCode_R, KeyCode_Shift, KeyCode_Control);
	Bind(q7_list_projects, KeyCode_L, KeyCode_Shift, KeyCode_Control);
	Bind(list_all_locations, KeyCode_F, KeyCode_Shift, KeyCode_Control);
	Bind(comment_line_toggle, KeyCode_ForwardSlash, KeyCode_Control);
	Bind(q7_toggle_compilation_expand, KeyCode_Tick, KeyCode_Control);
	Bind(center_view, KeyCode_L, KeyCode_Control);
	Bind(goto_next_jump, KeyCode_N, KeyCode_Alt);
	Bind(goto_prev_jump, KeyCode_P, KeyCode_Alt);
	Bind(move_line_up, KeyCode_K, KeyCode_Alt);
	Bind(move_line_down, KeyCode_J, KeyCode_Alt);

	Bind(q7_change_to_normal_mode, KeyCode_Escape);
 Bind(q7_change_to_normal_mode, KeyCode_C, KeyCode_Control);

	Bind(command_lister, KeyCode_Q, KeyCode_Alt);
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
	Bind(quick_swap_buffer, KeyCode_BackwardSlash, KeyCode_Alt);
	Bind(save, KeyCode_S, KeyCode_Control);
	Bind(save_all_dirty_buffers, KeyCode_S, KeyCode_Control, KeyCode_Shift);
	Bind(paste, KeyCode_V, KeyCode_Control);
	Bind(q7_toggle_compilation_expand, KeyCode_Insert);
	
	BindMouse(q7_jump_to_definition_under_mouse, MouseCode_Left, KeyCode_Control);
	BindMouse(click_set_cursor_and_mark, MouseCode_Left);
	BindMouseMove(click_set_cursor_if_lbutton);
	BindMouseWheel(mouse_wheel_scroll);
	BindMouseWheel(mouse_wheel_change_face_size, KeyCode_Control);
	
	Bind(jump_to_definition_at_cursor, KeyCode_W, KeyCode_Control);
	Bind(jump_to_last_point, KeyCode_Minus, KeyCode_Control);
	Bind(jump_to_definition_at_cursor_other_panel, KeyCode_W, KeyCode_Alt);
	
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
nates_bind_normalmode_keys(Mapping *m, Command_Map *map)
{
	Bind(q7_delete_alpha_numeric_identifier, KeyCode_X);
	Bind(q7_cancel_command, KeyCode_Escape);
	Bind(q7_cut, KeyCode_C);
	Bind(q7_cut, KeyCode_D);
	Bind(q7_paste, KeyCode_P);
	Bind(q7_yank_line, KeyCode_Y, KeyCode_Shift);
	Bind(copy, KeyCode_Y);
	Bind(set_mark, KeyCode_Space);
	Bind(q7_select_lines, KeyCode_V, KeyCode_Shift);
	Bind(q7_join_lines, KeyCode_J, KeyCode_Shift);
	Bind(undo, KeyCode_U);
	Bind(redo, KeyCode_R, KeyCode_Control);
	Bind(q7_change_to_insert_mode, KeyCode_I);
	Bind(q7_change_to_insert_mode_after, KeyCode_A);
	Bind(q7_insert_start_of_line, KeyCode_I, KeyCode_Shift);
	Bind(q7_insert_line_below, KeyCode_O);
	Bind(search, KeyCode_F, KeyCode_Control);
	Bind(q7_jump_to_matching_brace, KeyCode_5, KeyCode_Shift);
	
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
nates_bind_insertmode_keys(Mapping *m, Command_Map *map)
{
	Bind(backspace_alpha_numeric_boundary, KeyCode_Backspace, KeyCode_Control);
	BindTextInput(write_text_and_auto_indent);
}
#endif
