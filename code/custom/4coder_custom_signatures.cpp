
///////////////////////////////////////
// NOTE(nates): Own custom commands

// NOTE(nates): Look at 4coder_custom_variables.h
//              and 4coder_custom_functions.cpp

// NOTE(nates): All these CUSTOM_COMMAND_SIGS's are just functions
// you can call them if you want to!

CUSTOM_COMMAND_SIG(cycle_multi_cursor_mode)
CUSTOM_DOC("set the multi cursor mode")
{
	View_ID active_view = get_active_view(app, Access_ReadVisible);
	Multi_Cursor_Mode multi_cursor_mode = view_get_multi_cursor_mode(app, active_view);
	switch(multi_cursor_mode)
	{
		case Multi_Cursor_Disabled:
		{
			view_set_multi_cursor_mode(app, active_view, Multi_Cursor_Place_Cursors);
		} break;
		
		case Multi_Cursor_Place_Cursors:
		{
			view_set_multi_cursor_mode(app, active_view, Multi_Cursor_Enabled);
		} break;
		
		case Multi_Cursor_Enabled:
		{
			view_set_multi_cursor_mode(app, active_view, Multi_Cursor_Disabled);
			view_clear_multi_cursors(app, active_view);
		} break;
		
		InvalidDefaultCase;
	}
}

CUSTOM_COMMAND_SIG(load_project_list_file)
CUSTOM_DOC("loads project list file and parses for full paths to projet.4coder files")
{
	load_project_list_file_func(app);
}


CUSTOM_COMMAND_SIG(delete_to_end_of_line)
CUSTOM_DOC("Delete's from the cursor to the end of the line")
{
  View_ID view = get_active_view(app, 0);
  Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
	
	Multi_Cursor_Mode multi_cursor_mode = view_get_multi_cursor_mode(app, view);
	if(multi_cursor_mode == Multi_Cursor_Disabled)
	{
		i64 cursor_pos = view_get_cursor(app, view);
		i64 cursor_line = get_line_number_from_pos(app, buffer, cursor_pos);
		i64 line_end = get_line_end_pos(app, buffer, cursor_line);
		
		Range_i64 range = {};
		range.start = cursor_pos;
		range.end = line_end;
		buffer_replace_range(app, buffer, range, string_u8_empty);
	}
	else if(multi_cursor_mode == Multi_Cursor_Enabled)
	{
		History_Group history_group = history_group_begin(app, buffer);
		
		i64 multi_cursor_count = view_get_multi_cursor_count(app, view);
		for(u32 multi_cursor_index = 0;
				multi_cursor_index < multi_cursor_count;
				++multi_cursor_index)
		{
			i64 cursor_pos = view_get_multi_cursor(app, view, multi_cursor_index);
			i64 cursor_line = get_line_number_from_pos(app, buffer, cursor_pos);
			i64 line_end = get_line_end_pos(app, buffer, cursor_line);
			
			Range_i64 range = {};
			range.start = cursor_pos;
			range.end = line_end;
			buffer_replace_range(app, buffer, range, string_u8_empty);
		}
		history_group_end(history_group);
	}
}

CUSTOM_COMMAND_SIG(delete_to_start_of_line)
CUSTOM_DOC("Delete's from the start of line to the cursor position")
{
  View_ID view = get_active_view(app, 0);
  Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
	
	Multi_Cursor_Mode multi_cursor_mode = view_get_multi_cursor_mode(app, view);
	if(multi_cursor_mode == Multi_Cursor_Disabled)
	{
		i64 cursor_pos = view_get_cursor(app, view);
		i64 cursor_line = get_line_number_from_pos(app, buffer, cursor_pos);
		i64 line_end = get_line_start_pos(app, buffer, cursor_line);
		
		Range_i64 range = {};
		range.start = cursor_pos;
		range.end = line_end;
		buffer_replace_range(app, buffer, range, string_u8_empty);
	}
	else if(multi_cursor_mode == Multi_Cursor_Enabled)
	{
		History_Group history_group = history_group_begin(app, buffer);
		
		i64 multi_cursor_count = view_get_multi_cursor_count(app, view);
		for(u32 multi_cursor_index = 0;
				multi_cursor_index < multi_cursor_count;
				++multi_cursor_index)
		{
			i64 cursor_pos = view_get_multi_cursor(app, view, multi_cursor_index);
			i64 cursor_line = get_line_number_from_pos(app, buffer, cursor_pos);
			i64 line_end = get_line_start_pos(app, buffer, cursor_line);
			
			Range_i64 range = {};
			range.start = cursor_pos;
			range.end = line_end;
			buffer_replace_range(app, buffer, range, string_u8_empty);
		}
		history_group_end(history_group);
	}
}

CUSTOM_COMMAND_SIG(delete_alpha_numeric_identifier)
CUSTOM_DOC("deletes alpha numeric identifier at cursor position")
{
	Scratch_Block scratch(app);
	
	View_ID view = get_active_view(app, Access_ReadWriteVisible);
	Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
	i64 cursor_pos = view_get_cursor(app, view);
	Range_i64 range = buffer_seek_character_predicate_range(app, buffer, &character_predicate_alpha_numeric_underscore,
																													cursor_pos);
	if(range.min != -1)
	{
		buffer_replace_range(app, buffer, range, string_u8_empty);
	}
}

CUSTOM_COMMAND_SIG(copy_alpha_numeric_identifier)
CUSTOM_DOC("Copies characters between the seek left result for a alpha numeric and the seek right result.")
{
	Scratch_Block scratch(app);
	
	View_ID view = get_active_view(app, Access_ReadWriteVisible);
	Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
	i64 cursor_pos = view_get_cursor(app, view);
	Range_i64 range = buffer_seek_character_predicate_range(app, buffer, &character_predicate_alpha_numeric_underscore,
																													cursor_pos);
	if(range.min != -1)
	{
		clipboard_post_buffer_range(app, 0, buffer, range);
	}
}

CUSTOM_COMMAND_SIG(change_to_command_mode)
CUSTOM_DOC("Sets the view's buffer keymap to the command_keymap")
{
	View_ID view = get_active_view(app, 0);
	Buffer_ID buffer = view_get_buffer(app, view, 0);
	
	Modal_State modal_state;
	b32 is_global_modal = app_get_is_global_modal(app);
	if (is_global_modal)
	{
		modal_state = app_get_global_modal_state(app);
	}
	else
	{
		modal_state = view_get_modal_state(app, view);
	}
	
	if (modal_state != Modal_State_Command)
	{
		if (is_global_modal)
		{
			app_set_global_modal_state(app, Modal_State_Command);
		}
		else
		{
			view_set_modal_state(app, view, Modal_State_Command);
		}
		
		i64 cursor_pos = view_get_cursor(app, view);
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
	
	Modal_State modal_state;
	b32 is_global_modal = app_get_is_global_modal(app);
	if (is_global_modal)
	{
		modal_state = app_get_global_modal_state(app);
	}
	else
	{
		modal_state = view_get_modal_state(app, view);
	}
	
	if (modal_state != Modal_State_Command)
	{
		if (is_global_modal)
		{
			app_set_global_modal_state(app, Modal_State_Command);
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
	Modal_State modal_state;
	
	b32 is_global_modal = app_get_is_global_modal(app);
	if (is_global_modal)
	{
		modal_state = app_get_global_modal_state(app);
	}
	else
	{
		modal_state = view_get_modal_state(app, view);
	}
	
	if (modal_state != Modal_State_Insert)
	{
		if (is_global_modal)
		{
			app_set_global_modal_state(app, Modal_State_Insert);
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
	Modal_State modal_state;
	
	b32 is_global_modal = app_get_is_global_modal(app);
	if (is_global_modal)
	{
		modal_state = app_get_global_modal_state(app);
	}
	else
	{
		modal_state = view_get_modal_state(app, view);
	}
	
	if (modal_state != Modal_State_Insert)
	{
		if (is_global_modal)
		{
			app_set_global_modal_state(app, Modal_State_Insert);
		}
		else
		{
			view_set_modal_state(app, view, Modal_State_Insert);
		}
		
		// Set Keybinds for Command Mode only
		b32 result = view_set_buffer(app, view, buffer, 0);
		set_command_map_id(app, buffer, (Command_Map_ID)insert_mapid);
	}
	
	i64 cursor_pos = view_get_cursor(app, view);
	i64 cursor_line_before = get_line_number_from_pos(app, buffer, cursor_pos);
	i64 cursor_line_after = get_line_number_from_pos(app, buffer, cursor_pos + 1);
	
	if (cursor_line_after == cursor_line_before)
	{
		view_set_cursor(app, view, seek_pos(cursor_pos + 1));
	}
}

CUSTOM_COMMAND_SIG(jump_from_brace_to_brace)
CUSTOM_DOC("Jump from Brace to brace")
{
	View_ID view = get_active_view(app, Access_ReadVisible);
	Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
	i64 cursor_pos = view_get_cursor(app, view);
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
	
	b32 line_selection_mode = view_get_line_selection_mode(app, view);
	if (line_selection_mode)
	{
		view_set_yanked_entire_line(app, view, true);
		
		i64 min_line = view_get_selection_begin(app, view);
		i64 max_line = view_get_selection_end(app, view);
		
		if (min_line > max_line)
		{
			min_line ^= max_line;
			max_line ^= min_line;
			min_line ^= max_line;
		}
		
		Range_i64 line_range = {min_line, max_line};
		Range_i64 range = get_pos_range_from_line_range(app, buffer, line_range);
		clipboard_post_buffer_range(app, 0, buffer, range);
		
		view_set_line_selection_mode(app, view, false);
	}
	else
	{
		view_set_yanked_entire_line(app, view, true);
		
		i64 cursor_pos = view_get_cursor(app, view);
		i64 cursor_line = get_line_number_from_pos(app, buffer, cursor_pos);
		Range_i64 line_range = {cursor_line, cursor_line};
		Range_i64 range = get_pos_range_from_line_range(app, buffer, line_range);
		if(range.min == range.max)
		{
			range.max += 1;
		}
		
		clipboard_post_buffer_range(app, 0, buffer, range);
	}
}

CUSTOM_COMMAND_SIG(vim_cut)
CUSTOM_DOC("Cut the text in the range from the cursor to the mark onto the clipboard.")
{
	View_ID view = get_active_view(app, Access_ReadWriteVisible);
	Range_i64 range = {};
	
	b32 line_selection_mode = view_get_line_selection_mode(app, view);
	b32 vim_cutting_mode = view_get_vim_cutting_mode(app, view);
	Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
	if (line_selection_mode)
	{
		i64 min_line = view_get_selection_begin(app, view);
		i64 max_line = view_get_selection_end(app, view);
		
		if (min_line > max_line)
		{
			min_line ^= max_line;
			max_line ^= min_line;
			min_line ^= max_line;
		}
		
		Range_i64 line_range = {min_line, max_line};
		range = get_pos_range_from_line_range(app, buffer, line_range);
		
		view_set_line_selection_mode(app, view, false);
		
		if (clipboard_post_buffer_range(app, 0, buffer, range))
		{
			History_Group group = history_group_begin(app, buffer);
			buffer_replace_range(app, buffer, range, string_u8_empty);
			delete_line(app);
			history_group_end(group);
		}
	}
	else if (vim_cutting_mode)
	{
		i64 cursor_pos = view_get_cursor(app, view);
		i64 line_number_cursor = get_line_number_from_pos(app, buffer, cursor_pos);
		
		Range_i64 line_range = {line_number_cursor, line_number_cursor};
		range = get_pos_range_from_line_range(app, buffer, line_range);
		
		b32 edit_min = false;
		if(range.min == range.max)
		{
			range.max += 1;
		}
		else
		{
			edit_min = true;
		}
		
		view_set_vim_cutting_mode(app, view, false);
		if (clipboard_post_buffer_range(app, 0, buffer, range))
		{
			History_Group group = history_group_begin(app, buffer);
			
			if(edit_min)
			{
				range.min -= 1;
			}
			buffer_replace_range(app, buffer, range, string_u8_empty);
			history_group_end(group);
		}
	}
	else
	{
		view_set_vim_cutting_mode(app, view, true);
	}
}

CUSTOM_COMMAND_SIG(vim_paste)
CUSTOM_DOC("If you yank a line, this will add a new line under the line you're on and paste the yank result there")
{
	View_ID view = get_active_view(app, Access_ReadVisible);
	Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
	
	History_Group group = history_group_begin(app, buffer);
	
	b32 yanked_entire_line = view_get_yanked_entire_line(app, view);
	if (yanked_entire_line)
	{
		Scratch_Block scratch(app);
		String_Const_u8 string = push_clipboard_index(scratch, 0, 0);
		
		seek_end_of_textual_line(app);
		write_text_multi_cursor(app, SCu8("\n"));
		
		if(!(string.str[0] == '\n'))
		{
			paste(app);
		}
	}
	else
	{
		paste(app);
	}
	
	history_group_end(group);
}

CUSTOM_COMMAND_SIG(select_lines)
CUSTOM_DOC("Selects a line region that can be used inside other commantds like copy, paste, cut, or delete")
{
	View_ID view = get_active_view(app, Access_ReadVisible);
	Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
	
	b32 line_selection_mode = view_get_line_selection_mode(app, view);
	b32 vim_cutting_mode = view_get_vim_cutting_mode(app, view);
	if(!vim_cutting_mode)
	{
		if(line_selection_mode)
		{
			view_set_line_selection_mode(app, view, false);
			i64 cursor_pos = view_get_cursor(app, view);
			i64 cursor_line = get_line_number_from_pos(app, buffer, cursor_pos);
			
			view_set_selection_begin(app, view, cursor_line);
			view_set_selection_end(app, view, cursor_line);
		}
		else
		{
			view_set_line_selection_mode(app, view, true);
			i64 cursor_pos = view_get_cursor(app, view);
			i64 cursor_line = get_line_number_from_pos(app, buffer, cursor_pos);
			view_set_selection_begin(app, view, cursor_line);
			view_set_selection_end(app, view, cursor_line);
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
	write_text_multi_cursor(app, SCu8("\n"));
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
	view_set_vim_cutting_mode(app, view, false);
	view_set_line_selection_mode(app, view, false);
	view_set_multi_cursor_mode(app, view, Multi_Cursor_Disabled);
	view_clear_multi_cursors(app, view);
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
					String_Const_u8 text = note->text;
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
								text = note->function_text;
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
								continue;
							}
							
							case CodeIndexNote_4coderCommand:
							{
								continue;
							}
							
							InvalidDefaultCase;
						}
						
						lister_add_item(lister, text, sort, jump, 0);
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

CUSTOM_COMMAND_SIG(reload_changed_files)
CUSTOM_DOC("if you change the file outside a program and reload it with this command, it will carry over all changes from the unloaded file and ignore everything you added in 4ed buffer")
{
	Scratch_Block scratch(app);
	for (Buffer_ID buffer = get_buffer_next(app, 0, Access_ReadWriteVisible);
			 buffer != 0;
			 buffer = get_buffer_next(app, buffer, Access_ReadWriteVisible))
	{
		Dirty_State dirty = buffer_get_dirty_state(app, buffer);
		if(dirty == DirtyState_UnloadedChanges || dirty == DirtyState_UnsavedChangesAndUnloadedChanges)
		{
			String_Const_u8 file_name = push_buffer_file_name(app, scratch, buffer);
			buffer_kill(app, buffer, 0);
			create_buffer(app, file_name, 0);
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
		view_set_split_pixel_size(app, global_compilation_view, (i32)(metrics.line_height*COMPILATION_MAX_SIZE));
	}
	else
	{
		view_set_split_pixel_size(app, global_compilation_view, (i32)(metrics.line_height*COMPILATION_MIN_SIZE));
	}
}

CUSTOM_COMMAND_SIG(list_projects)
CUSTOM_DOC("loads the project_list.4coder file under same directory as 4ed.exe")
{
	Project_List projects = get_project_list(app);
	if(projects.count)
	{
		save_and_kill_all_buffers(app);
		
		Scratch_Block scratch(app);
		Lister_Block lister(app, scratch);
		char *query = "Project Path:";
		lister_set_query(lister, query);
		lister_set_default_handlers(lister);
		
		code_index_lock();
		String_Node *node = projects.first;
		for(u32 node_index = 0;
				node_index < projects.count;
				++node_index)
		{
			String_Const_u8 *string = &node->contents;
			if(character_predicate_check_character(character_predicate_alpha, string->str[0]))
			{
				u64 first = string_find_first(*string, 0, ' ');
				String_Const_u8 file_path = *string;
				String_Const_u8 name = {};
				if(first)
				{
					file_path = {string->str, first};
					u64 name_index = clamp_top(first + 1, string->size);
					if(string->size - name_index > 0)
					{
						name = SCu8(string->str + name_index, (string->size - name_index));
						lister_add_item(lister, name, SCu8(""), string, 0);
					}
					else
					{
						lister_add_item(lister, *string, SCu8(""), string, 0);
					}
				}
				else
				{
					lister_add_item(lister, *string, SCu8(""), string, 0);
				}
			}
			
			node = node->next;
		}
		code_index_unlock();
		
		
		Lister_Result lister_result = run_lister(app, lister);
		if(!lister_result.canceled && lister_result.user_data)
		{
			String_Const_u8 result_path = *(String_Const_u8 *)lister_result.user_data;
			load_project_from_path(app, result_path);
			set_hot_directory(app, result_path);
		}
	}
	else
	{
		print_message(app, SCu8("Couldn't find any project files because the file is missing _or_ there are no projects in it.\n"));
		
		Buffer_Identifier message_iden = buffer_identifier(string_u8_litexpr("*messages*"));
		Buffer_ID message_buffer_id = buffer_identifier_to_id(app, message_iden);
		View_ID view = get_active_view(app, Access_ReadVisible);
		view_set_buffer(app, view, message_buffer_id, 0);
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
			view_set_split_pixel_size(app, compilation_view, (i32)(metrics.line_height*COMPILATION_MIN_SIZE));
			view_set_passive(app, compilation_view, true);
			view_set_setting(app, compilation_view, ViewSetting_ShowFileBar, false);
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
	
	// NOTE(nates): Load Project Paths
	{
		load_project_list_file(app);
	}
	
	// NOTE(nates): View stuff
	{
		app_set_maps(app, command_mapid, insert_mapid);
		app_set_is_global_modal(app, false);
		b32 is_global_modal = app_get_is_global_modal(app);
		if(is_global_modal)
		{
			app_set_global_modal_state(app, Modal_State_Command);
		}
		else
		{
			View_ID active_view = get_active_view(app, Access_ReadVisible);
			view_set_modal_state(app, active_view, Modal_State_Command);
		}
	}
}
