function void
q7_render_buffer(Application_Links *app, View_ID view_id, Face_ID face_id,
								 Buffer_ID buffer, Text_Layout_ID text_layout_id,
								 Rect_f32 rect)
{
	ProfileScope(app, "q7 render buffer");
	
	View_ID active_view = get_active_view(app, Access_Always);
	b32 is_active_view = (active_view == view_id);
	Rect_f32 prev_clip = draw_set_clip(app, rect);
	
	Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
	
	// NOTE(allen): Cursor shape
	Face_Metrics metrics = get_face_metrics(app, face_id);
	u64 cursor_roundness_100 = def_get_config_u64(app, vars_save_string_lit("cursor_roundness"));
	f32 cursor_roundness = metrics.normal_advance * cursor_roundness_100 * 0.01f;
	f32 mark_thickness = (f32)def_get_config_u64(app, vars_save_string_lit("mark_thickness"));
	
	// NOTE(allen): Token colorizing
	Token_Array token_array = get_token_array_from_buffer(app, buffer);
	if (token_array.tokens != 0)
	{
		draw_cpp_token_colors(app, text_layout_id, &token_array);
		
		// NOTE(allen): Scan for TODOs and NOTEs
		b32 use_comment_keyword = def_get_config_b32(vars_save_string_lit("use_comment_keyword"));
		if (use_comment_keyword)
		{
			Comment_Highlight_Pair pairs[] =
			{
				{string_u8_litexpr("NOTE"), finalize_color(defcolor_comment_pop, 0)},
				{string_u8_litexpr("TODO"), finalize_color(defcolor_comment_pop, 1)},
			};
			draw_comment_highlights(app, buffer, text_layout_id, &token_array, pairs, ArrayCount(pairs));
		}
		
		
		// nates: loop over and highlight tokens
		Scratch_Block scratch(app);
		i64 range_first = clamp_bot(visible_range.first - 1, 0);
		Token_Iterator_Array it = token_iterator_pos(0, &token_array, range_first);
		Token_Iterator_Array end = token_iterator_pos(0, &token_array, visible_range.one_past_last);
		Code_Index_File *index_file = code_index_get_file(buffer);
		while(it.ptr <= end.ptr)
		{
			Token *token = token_it_read(&it);
			String_Const_u8 contents = push_token_lexeme(app, scratch, buffer, token);
			Code_Index_Nest *nest = code_index_get_nest(index_file, token->pos);
			
			if(token->kind == TokenBaseKind_Operator) {
				ARGB_Color argb = active_color_table.arrays[custom_color_operators].vals[0];
				paint_text_color(app, text_layout_id, Ii64_size(token->pos, token->size), argb);
			}
			else if(token->sub_kind != TokenCppKind_LineComment &&
							token->sub_kind != TokenCppKind_BlockComment) {
				i64 token_index = token_it_index(&it);
				Code_Index_Note_List *list = code_index__list_from_string(contents);
				Code_Index_Note *found_note = 0;
				for(Code_Index_Note *note = list->first;
						note != 0;
						note = note->next_in_hash)
				{
					if(string_match(note->text, contents))
					{
						if(note->note_kind == CodeIndexNote_Macro)
						{
							found_note = note;
							break;
						}
						
						if(note->is_name_space)
						{
							Surrounding_Range range = get_surrounding_range(app, buffer, token->pos);
							Token_Iterator_Array find_it = token_iterator_pos(0, &token_array, range.r.min);
							token_it_dec(&find_it);
							Token *test = token_it_read(&find_it);
							if(test)
							{
								String_Const_u8 test_string = push_token_lexeme(app, scratch, buffer, test);
								
								if(string_match(test_string, note->name_space))
								{
									found_note = note;
									break;
								}
								else
								{
									if(token_index > 1)
									{
										Token *previous = it.tokens + (token_index - 1);
										if(previous->kind == TokenBaseKind_Operator &&
											 previous->sub_kind == TokenCppKind_ColonColon)
										{
											Token *namespace_token = it.tokens + (token_index - 2);
											String_Const_u8 namespace_token_str = push_token_lexeme(app, scratch, buffer, namespace_token);
											Code_Index_Note *namespace_note = code_index_note_from_string(namespace_token_str);
											if(namespace_note && string_match(note->name_space, namespace_note->text))
											{
												found_note = note;
												break;
											}
										}
										else
										{
											continue;
										}
									}
									else
									{
										continue;
									}
								}
							}
						}
						
						if(note->note_kind == CodeIndexNote_ForwardDeclaration &&
							 found_note == 0)
						{
							found_note = note;
						}
						
						if(note->note_kind != CodeIndexNote_ForwardDeclaration &&
							 note->note_kind != CodeIndexNote_Macro)
						{
							if(token_index > 1)
							{
								Token *previous = it.tokens + (token_index - 1);
								if(previous->kind == TokenBaseKind_Operator &&
									 previous->sub_kind == TokenCppKind_ColonColon)
								{
									continue;
								}
							}
							
							found_note = note;
						}
					}
				}
				
				b32 allowed = code_index_note_is_allowed(found_note, nest);
				
				
				ARGB_Color argb = 0xff000000;
				if(allowed)
				{
					switch (found_note->note_kind)
					{
						case CodeIndexNote_Type:
						{
							argb = active_color_table.arrays[custom_color_code_index_type].vals[0];
						}
						break;
						
						case CodeIndexNote_Function:
						{
							argb = active_color_table.arrays[custom_color_code_index_function].vals[0];
						}
						break;
						
						case CodeIndexNote_Macro:
						{
							argb = active_color_table.arrays[custom_color_code_index_macro].vals[0];
						}
						break;
						
						case CodeIndexNote_Enum:
						{
							argb = active_color_table.arrays[custom_color_code_index_enum].vals[0];
						}
						break;
						
						case CodeIndexNote_ForwardDeclaration:
						{
							argb = active_color_table.arrays[custom_color_code_index_forward_declaration].vals[0];
						} break;
						
						case CodeIndexNote_Namespace:
						{
							argb = active_color_table.arrays[custom_color_code_index_namespace].vals[0];
						} break;
						
						case CodeIndexNote_4coderCommand:
						{
							argb = 0xff0000ff;
						} break;
						
						InvalidDefaultCase;
					}
					
					paint_text_color(app, text_layout_id, Ii64_size(token->pos, token->size), argb);
				}
			}
			
			if (!token_it_inc_non_whitespace(&it))
			{
				break;
			}
		}
	}
	else
	{
		paint_text_color_fcolor(app, text_layout_id, visible_range, fcolor_id(defcolor_text_default));
	}
	
	i64 cursor_pos = 0;
	// NOTE(nates): Correct multi cursors / marks
	{
		i64 multi_cursor_count = view_get_multi_cursor_count(app, view_id);
		for(u32 multi_cursor_index = 0;
				multi_cursor_index < multi_cursor_count;
				++multi_cursor_index)
		{
			// Cursors
			{
				i64 pos = view_get_multi_cursor(app, view_id, multi_cursor_index);
				i64 new_pos = view_set_pos_by_character_delta(app, view_id, pos, 0);
				if(multi_cursor_index == 0)
				{
					cursor_pos = new_pos;
				}
				view_set_multi_cursor(app, view_id, multi_cursor_index, seek_pos(new_pos));
			}
			
			// Marks
			{
				i64 mark_pos = view_get_multi_mark(app, view_id, multi_cursor_index);
				i64 mark_new_pos = view_set_pos_by_character_delta(app, view_id, mark_pos, 0);
				view_set_multi_mark(app, view_id, multi_cursor_index, seek_pos(mark_new_pos));
			}
		}
	}
	
	
	// NOTE(allen): Scope highlight
	b32 use_scope_highlight = def_get_config_b32(vars_save_string_lit("use_scope_highlight"));
	if (use_scope_highlight)
	{
		Color_Array colors = finalize_color_array(defcolor_back_cycle);
		draw_scope_highlight(app, buffer, text_layout_id, cursor_pos, colors.vals, colors.count);
	}
	
	b32 use_error_highlight = def_get_config_b32(vars_save_string_lit("use_error_highlight"));
	b32 use_jump_highlight = def_get_config_b32(vars_save_string_lit("use_jump_highlight"));
	if (use_error_highlight || use_jump_highlight)
	{
		// NOTE(allen): Error highlight
		String_Const_u8 name = string_u8_litexpr("*compilation*");
		Buffer_ID compilation_buffer = get_buffer_by_name(app, name, Access_Always);
		if (use_error_highlight)
		{
			draw_jump_highlights(app, buffer, text_layout_id, compilation_buffer,
													 fcolor_id(defcolor_highlight_junk));
		}
		
		// NOTE(allen): Search highlight
		if (use_jump_highlight)
		{
			Buffer_ID jump_buffer = get_locked_jump_buffer(app);
			if (jump_buffer != compilation_buffer)
			{
				draw_jump_highlights(app, buffer, text_layout_id, jump_buffer,
														 fcolor_id(defcolor_highlight_white));
			}
		}
	}
	
	// NOTE(allen): Color parens
	b32 use_paren_helper = def_get_config_b32(vars_save_string_lit("use_paren_helper"));
	if (use_paren_helper)
	{
		Color_Array colors = finalize_color_array(defcolor_text_cycle);
		draw_paren_highlight(app, buffer, text_layout_id, cursor_pos, colors.vals, colors.count);
	}
	
	// NOTE(allen): Line highlight
	b32 highlight_line_at_cursor = def_get_config_b32(vars_save_string_lit("highlight_line_at_cursor"));
	if (highlight_line_at_cursor && is_active_view)
	{
		i64 line_number = get_line_number_from_pos(app, buffer, cursor_pos);
		draw_line_highlight(app, text_layout_id, line_number, fcolor_id(defcolor_highlight_cursor_line));
	}
	
	// NOTE(allen): Whitespace highlight
	b64 show_whitespace = false;
	view_get_setting(app, view_id, ViewSetting_ShowWhitespace, &show_whitespace);
	if (show_whitespace)
	{
		if (token_array.tokens == 0)
		{
			draw_whitespace_highlight(app, buffer, text_layout_id, cursor_roundness);
		}
		else
		{
			draw_whitespace_highlight(app, text_layout_id, &token_array, cursor_roundness);
		}
	}
	
	Multi_Cursor_Mode multi_cursor_mode = view_get_multi_cursor_mode(app, view_id);
	if(multi_cursor_mode == Multi_Cursor_Disabled)
	{
		// NOTE(allen): Cursor
		switch (fcoder_mode)
		{
			case FCoderMode_Original:
			{
				draw_original_4coder_style_cursor_mark_highlight(app, view_id, is_active_view, buffer, text_layout_id, cursor_roundness, mark_thickness);
			}
			break;
			case FCoderMode_NotepadLike:
			{
				draw_notepad_style_cursor_highlight(app, view_id, buffer, text_layout_id, cursor_roundness);
			}
			break;
		}
	}
	else if(multi_cursor_mode == Multi_Cursor_PlaceCursors ||
					multi_cursor_mode == Multi_Cursor_Enabled)
	{
		i64 multi_cursor_count = view_get_multi_cursor_count(app, view_id);
		for(u32 multi_cursor_index = 0;
				multi_cursor_index < multi_cursor_count;
				++multi_cursor_index)
		{
			switch(fcoder_mode)
			{
				case FCoderMode_Original:
				{
					draw_original_4coder_style_multi_cursor_mark_highlight(app, view_id, is_active_view, buffer, text_layout_id, 
																																 multi_cursor_index, cursor_roundness, mark_thickness);
				} break;
				case FCoderMode_NotepadLike:
				{
					Assert(!"Notepad mode doesn't support multi cursor yet");
					draw_notepad_style_cursor_highlight(app, view_id, buffer, text_layout_id, 
																							multi_cursor_index, cursor_roundness);
				} break;
			}
		}
	}
	
	// NOTE(allen): Fade ranges
	paint_fade_ranges(app, text_layout_id, buffer);
	
	// NOTE(allen): put the actual text on the actual screen
	draw_text_layout_default(app, text_layout_id);
	
	draw_set_clip(app, prev_clip);
}



function void
q7_render_caller(Application_Links *app, Frame_Info frame_info, View_ID view_id)
{
	ProfileScope(app, "default render caller");
	View_ID active_view = get_active_view(app, Access_Always);
	b32 is_active_view = (active_view == view_id);
	
	Rect_f32 region = draw_background_and_margin(app, view_id, is_active_view);
	Rect_f32 prev_clip = draw_set_clip(app, region);
	
	Buffer_ID buffer = view_get_buffer(app, view_id, Access_Always);
	Face_ID face_id = get_face_id(app, buffer);
	Face_Metrics face_metrics = get_face_metrics(app, face_id);
	f32 line_height = face_metrics.line_height;
	f32 digit_advance = face_metrics.decimal_digit_advance;
	
	// NOTE(allen): file bar
	b64 showing_file_bar = false;
	if (view_get_setting(app, view_id, ViewSetting_ShowFileBar, &showing_file_bar) && showing_file_bar)
	{
		Rect_f32_Pair pair = layout_file_bar_on_top(region, line_height);
		draw_file_bar(app, view_id, buffer, face_id, pair.min);
		region = pair.max;
	}
	
	Buffer_Scroll scroll = view_get_buffer_scroll(app, view_id);
	
	Buffer_Point_Delta_Result delta = delta_apply(app, view_id,
																								frame_info.animation_dt, scroll);
	if (!block_match_struct(&scroll.position, &delta.point))
	{
		block_copy_struct(&scroll.position, &delta.point);
		view_set_buffer_scroll(app, view_id, scroll, SetBufferScroll_NoCursorChange);
	}
	if (delta.still_animating)
	{
		animate_in_n_milliseconds(app, 0);
	}
	
	// NOTE(allen): query bars
	region = default_draw_query_bars(app, region, view_id, face_id);
	
	// NOTE(allen): FPS hud
	if (show_fps_hud)
	{
		Rect_f32_Pair pair = layout_fps_hud_on_bottom(region, line_height);
		draw_fps_hud(app, frame_info, face_id, pair.max);
		region = pair.min;
		animate_in_n_milliseconds(app, 1000);
	}
	
	// NOTE(allen): layout line numbers
	b32 show_line_number_margins = def_get_config_b32(vars_save_string_lit("show_line_number_margins"));
	Rect_f32 line_number_rect = {};
	if (show_line_number_margins)
	{
		Rect_f32_Pair pair = layout_line_number_margin(app, buffer, region, digit_advance);
		line_number_rect = pair.min;
		region = pair.max;
	}
	
	// NOTE(allen): begin buffer render
	Buffer_Point buffer_point = scroll.position;
	Text_Layout_ID text_layout_id = text_layout_create(app, buffer, region, buffer_point);
	
	// NOTE(allen): draw line numbers
	if (show_line_number_margins)
	{
		draw_line_number_margin(app, view_id, buffer, face_id, text_layout_id, line_number_rect);
	}
	
	// NOTE(allen): draw the buffer
	q7_render_buffer(app, view_id, face_id, buffer, text_layout_id, region);
	
	b32 line_selection_mode = view_get_line_selection_mode(app, view_id);
	if(line_selection_mode)
	{
		i64 start_line_number = view_get_selection_begin(app, view_id);
		i64 end_line_number = view_get_selection_end(app, view_id);
		
		if (start_line_number > end_line_number)
		{
			// Swap
			i64 tmp = start_line_number;
			start_line_number = end_line_number;
			end_line_number = tmp;
		}
		
		for (i64 line_number = start_line_number;
				 line_number <= end_line_number;
				 line_number += 1)
		{
			// NOTE(nates):                  r     g     b     a
			FColor color = fcolor_argb(V4f32(1.0f, 0.0f, 0.0f, 0.2f));
			draw_line_highlight(app, text_layout_id, line_number, color); // fcolor_id(defcolor_highlight_cursor_line));
		}
	}
	
	b32 vim_cutting_mode = view_get_vim_cutting_mode(app, view_id);
	if (vim_cutting_mode)
	{
		FColor color = fcolor_argb(V4f32(1.0f, 0.0f, 0.0f, 0.2f));
		i64 cursor_pos = view_get_cursor(app, view_id);
		i64 cursor_line_number = get_line_number_from_pos(app, buffer, cursor_pos);
		draw_line_highlight(app, text_layout_id, cursor_line_number, color); // fcolor_id(defcolor_highlight_cursor_line));
	}
	
	text_layout_free(app, text_layout_id);
	draw_set_clip(app, prev_clip);
}