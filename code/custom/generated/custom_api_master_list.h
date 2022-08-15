api(custom) function b32 global_set_setting(Application_Links* app, Global_Setting_ID setting, i64 value);
api(custom) function Rect_f32 global_get_screen_rectangle(Application_Links* app);
api(custom) function Thread_Context* get_thread_context(Application_Links* app);
api(custom) function Child_Process_ID create_child_process(Application_Links* app, String_Const_u8 path, String_Const_u8 command);
api(custom) function b32 child_process_set_target_buffer(Application_Links* app, Child_Process_ID child_process_id, Buffer_ID buffer_id, Child_Process_Set_Target_Flags flags);
api(custom) function Child_Process_ID buffer_get_attached_child_process(Application_Links* app, Buffer_ID buffer_id);
api(custom) function Buffer_ID child_process_get_attached_buffer(Application_Links* app, Child_Process_ID child_process_id);
api(custom) function Process_State child_process_get_state(Application_Links* app, Child_Process_ID child_process_id);
api(custom) function b32 enqueue_virtual_event(Application_Links* app, Input_Event* event);
api(custom) function i32 get_buffer_count(Application_Links* app);
api(custom) function Buffer_ID get_buffer_next(Application_Links* app, Buffer_ID buffer_id, Access_Flag access);
api(custom) function Buffer_ID get_buffer_by_name(Application_Links* app, String_Const_u8 name, Access_Flag access);
api(custom) function Buffer_ID get_buffer_by_file_name(Application_Links* app, String_Const_u8 file_name, Access_Flag access);
api(custom) function b32 buffer_read_range(Application_Links* app, Buffer_ID buffer_id, Range_i64 range, u8* out);
api(custom) function b32 buffer_replace_range(Application_Links* app, Buffer_ID buffer_id, Range_i64 range, String_Const_u8 string);
api(custom) function b32 buffer_batch_edit(Application_Links* app, Buffer_ID buffer_id, Batch_Edit* batch, u32 multi_cursor_index);
api(custom) function String_Match buffer_seek_string(Application_Links* app, Buffer_ID buffer, String_Const_u8 needle, Scan_Direction direction, i64 start_pos);
api(custom) function Range_i64 buffer_seek_character_predicate_range(Application_Links* app, Buffer_ID buffer, Character_Predicate* predicate, i64 cursor_pos);
api(custom) function void load_project_list_file_func(Application_Links* app);
api(custom) function Project_List get_project_list(Application_Links* app);
api(custom) function String_Match buffer_seek_character_class(Application_Links* app, Buffer_ID buffer, Character_Predicate* predicate, Scan_Direction direction, i64 start_pos);
api(custom) function f32 buffer_line_y_difference(Application_Links* app, Buffer_ID buffer_id, f32 width, Face_ID face_id, i64 line_a, i64 line_b);
api(custom) function Line_Shift_Vertical buffer_line_shift_y(Application_Links* app, Buffer_ID buffer_id, f32 width, Face_ID face_id, i64 line, f32 y_shift);
api(custom) function i64 buffer_pos_at_relative_xy(Application_Links* app, Buffer_ID buffer_id, f32 width, Face_ID face_id, i64 base_line, Vec2_f32 relative_xy);
api(custom) function Rect_f32 buffer_relative_box_of_pos(Application_Links* app, Buffer_ID buffer_id, f32 width, Face_ID face_id, i64 base_line, i64 pos);
api(custom) function Rect_f32 buffer_padded_box_of_pos(Application_Links* app, Buffer_ID buffer_id, f32 width, Face_ID face_id, i64 base_line, i64 pos);
api(custom) function i64 buffer_relative_character_from_pos(Application_Links* app, Buffer_ID buffer_id, f32 width, Face_ID face_id, i64 base_line, i64 pos);
api(custom) function i64 buffer_pos_from_relative_character(Application_Links* app, Buffer_ID buffer_id, f32 width, Face_ID face_id, i64 base_line, i64 relative_character);
api(custom) function f32 view_line_y_difference(Application_Links* app, View_ID view_id, i64 line_a, i64 line_b);
api(custom) function Line_Shift_Vertical view_line_shift_y(Application_Links* app, View_ID view_id, i64 line, f32 y_shift);
api(custom) function i64 view_pos_at_relative_xy(Application_Links* app, View_ID view_id, i64 base_line, Vec2_f32 relative_xy);
api(custom) function Rect_f32 view_relative_box_of_pos(Application_Links* app, View_ID view_id, i64 base_line, i64 pos);
api(custom) function Rect_f32 view_padded_box_of_pos(Application_Links* app, View_ID view_id, i64 base_line, i64 pos);
api(custom) function i64 view_relative_character_from_pos(Application_Links* app, View_ID view_id, i64 base_line, i64 pos);
api(custom) function i64 view_pos_from_relative_character(Application_Links* app, View_ID view_id, i64 base_line, i64 character);
api(custom) function b32 buffer_exists(Application_Links* app, Buffer_ID buffer_id);
api(custom) function Access_Flag buffer_get_access_flags(Application_Links* app, Buffer_ID buffer_id);
api(custom) function i64 buffer_get_size(Application_Links* app, Buffer_ID buffer_id);
api(custom) function i64 buffer_get_line_count(Application_Links* app, Buffer_ID buffer_id);
api(custom) function String_Const_u8 push_buffer_base_name(Application_Links* app, Arena* arena, Buffer_ID buffer_id);
api(custom) function String_Const_u8 push_buffer_unique_name(Application_Links* app, Arena* out, Buffer_ID buffer_id);
api(custom) function String_Const_u8 push_buffer_file_name(Application_Links* app, Arena* arena, Buffer_ID buffer_id);
api(custom) function Dirty_State buffer_get_dirty_state(Application_Links* app, Buffer_ID buffer_id);
api(custom) function b32 buffer_set_dirty_state(Application_Links* app, Buffer_ID buffer_id, Dirty_State dirty_state);
api(custom) function b32 buffer_set_layout(Application_Links* app, Buffer_ID buffer_id, Layout_Function* layout_func);
api(custom) function b32 buffer_clear_layout_cache(Application_Links* app, Buffer_ID buffer_id);
api(custom) function Layout_Function* buffer_get_layout(Application_Links* app, Buffer_ID buffer_id);
api(custom) function b32 buffer_get_setting(Application_Links* app, Buffer_ID buffer_id, Buffer_Setting_ID setting, i64* value_out);
api(custom) function b32 buffer_set_setting(Application_Links* app, Buffer_ID buffer_id, Buffer_Setting_ID setting, i64 value);
api(custom) function Managed_Scope buffer_get_managed_scope(Application_Links* app, Buffer_ID buffer_id);
api(custom) function b32 buffer_send_end_signal(Application_Links* app, Buffer_ID buffer_id);
api(custom) function Buffer_ID create_buffer(Application_Links* app, String_Const_u8 file_name, Buffer_Create_Flag flags);
api(custom) function b32 buffer_save(Application_Links* app, Buffer_ID buffer_id, String_Const_u8 file_name, Buffer_Save_Flag flags);
api(custom) function Buffer_Kill_Result buffer_kill(Application_Links* app, Buffer_ID buffer_id, Buffer_Kill_Flag flags);
api(custom) function Buffer_Reopen_Result buffer_reopen(Application_Links* app, Buffer_ID buffer_id, Buffer_Reopen_Flag flags);
api(custom) function File_Attributes buffer_get_file_attributes(Application_Links* app, Buffer_ID buffer_id);
api(custom) function View_ID get_view_next(Application_Links* app, View_ID view_id, Access_Flag access);
api(custom) function i32 app_get_view_count(Application_Links* app);
api(custom) function View_ID get_view_prev(Application_Links* app, View_ID view_id, Access_Flag access);
api(custom) function View_ID get_this_ctx_view(Application_Links* app, Access_Flag access);
api(custom) function View_ID get_active_view(Application_Links* app, Access_Flag access);
api(custom) function b32 view_exists(Application_Links* app, View_ID view_id);
api(custom) function Buffer_ID view_get_buffer(Application_Links* app, View_ID view_id, Access_Flag access);
api(custom) function i64 view_get_cursor(Application_Links* app, View_ID view_id);
api(custom) function i64 view_get_mark(Application_Links* app, View_ID view_id);
api(custom) function i64 view_get_multi_mark(Application_Links* app, View_ID view_id, u32 multi_cursor_index);
api(custom) function i64 view_get_selection_begin(Application_Links* app, View_ID view_id);
api(custom) function i64 view_get_selection_end(Application_Links* app, View_ID view_id);
api(custom) function Modal_State view_get_modal_state(Application_Links* app, View_ID view_id);
api(custom) function f32 view_get_preferred_x(Application_Links* app, View_ID view_id, u32 multi_cursor_index);
api(custom) function b32 view_set_preferred_x(Application_Links* app, View_ID view_id, f32 x, u32 multi_cursor_index);
api(custom) function Rect_f32 view_get_screen_rect(Application_Links* app, View_ID view_id);
api(custom) function Panel_ID view_get_panel(Application_Links* app, View_ID view_id);
api(custom) function View_ID panel_get_view(Application_Links* app, Panel_ID panel_id, Access_Flag access);
api(custom) function b32 panel_is_split(Application_Links* app, Panel_ID panel_id);
api(custom) function b32 panel_is_leaf(Application_Links* app, Panel_ID panel_id);
api(custom) function b32 panel_split(Application_Links* app, Panel_ID panel_id, Dimension split_dim);
api(custom) function b32 panel_set_split(Application_Links* app, Panel_ID panel_id, Panel_Split_Kind kind, f32 t);
api(custom) function b32 panel_swap_children(Application_Links* app, Panel_ID panel_id);
api(custom) function Panel_ID panel_get_root(Application_Links* app);
api(custom) function Panel_ID panel_get_parent(Application_Links* app, Panel_ID panel_id);
api(custom) function Panel_ID panel_get_child(Application_Links* app, Panel_ID panel_id, Side which_child);
api(custom) function b32 view_close(Application_Links* app, View_ID view_id);
api(custom) function Rect_f32 view_get_buffer_region(Application_Links* app, View_ID view_id);
api(custom) function Buffer_Scroll view_get_buffer_scroll(Application_Links* app, View_ID view_id);
api(custom) function b32 view_set_active(Application_Links* app, View_ID view_id);
api(custom) function b32 view_enqueue_command_function(Application_Links* app, View_ID view_id, Custom_Command_Function* custom_func);
api(custom) function b32 view_get_setting(Application_Links* app, View_ID view_id, View_Setting_ID setting, i64* value_out);
api(custom) function b32 view_set_setting(Application_Links* app, View_ID view_id, View_Setting_ID setting, i64 value);
api(custom) function Managed_Scope view_get_managed_scope(Application_Links* app, View_ID view_id);
api(custom) function Buffer_Cursor buffer_compute_cursor(Application_Links* app, Buffer_ID buffer, Buffer_Seek seek);
api(custom) function Buffer_Cursor view_compute_cursor(Application_Links* app, View_ID view_id, Buffer_Seek seek);
api(custom) function b32 view_set_camera_bounds(Application_Links* app, View_ID view_id, Vec2_f32 margin, Vec2_f32 push_in_multiplier);
api(custom) function b32 view_get_camera_bounds(Application_Links* app, View_ID view_id, Vec2_f32* margin, Vec2_f32* push_in_multiplier);
api(custom) function b32 view_set_cursor(Application_Links* app, View_ID view_id, Buffer_Seek seek);
api(custom) function b32 view_set_cursor_no_set_mark_rel_index(Application_Links* app, View_ID view_id, Buffer_Seek seek);
api(custom) function b32 view_set_buffer_scroll(Application_Links* app, View_ID view_id, Buffer_Scroll scroll, Set_Buffer_Scroll_Rule rule);
api(custom) function Mark_History* view_get_mark_history(Application_Links* app, View_ID view_id);
api(custom) function void view_record_mark(Application_Links* app, View_ID view_id, u32 multi_cursor_index);
api(custom) function b32 view_set_mark(Application_Links* app, View_ID view_id, Buffer_Seek seek);
api(custom) function b32 view_set_mark_record(Application_Links* app, View_ID view, Buffer_Seek seek);
api(custom) function b32 view_set_multi_mark(Application_Links* app, View_ID view_id, u32 multi_cursor_index, Buffer_Seek seek);
api(custom) function b32 view_get_line_selection_mode(Application_Links* app, View_ID view_id);
api(custom) function void view_set_line_selection_mode(Application_Links* app, View_ID view_id, b32 value);
api(custom) function Multi_Cursor_Mode view_get_multi_cursor_mode(Application_Links* app, View_ID view_id);
api(custom) function void view_set_multi_cursor_mode(Application_Links* app, View_ID view_id, Multi_Cursor_Mode mode);
api(custom) function i64 view_get_multi_cursor_count(Application_Links* app, View_ID view_id);
api(custom) function i64 view_get_multi_cursor(Application_Links* app, View_ID view_id, u32 multi_cursor_index);
api(custom) function i64 view_get_first_or_current_multi_cursor(Application_Links* app, View_ID view_id);
api(custom) function i64 view_get_top_most_multi_cursor(Application_Links* app, View_ID view_id);
api(custom) function i64 view_get_bottom_most_multi_cursor(Application_Links* app, View_ID view_id);
api(custom) function i64 view_get_most_recent_multi_cursor(Application_Links* app, View_ID view_id);
api(custom) function void view_set_multi_cursor(Application_Links* app, View_ID view_id, u32 multi_cursor_index, Buffer_Seek seek);
api(custom) function void view_set_multi_cursor_preferred_x(Application_Links* app, View_ID view_id, u32 multi_cursor_index, Buffer_Seek seek);
api(custom) function void view_add_multi_cursor(Application_Links* app, View_ID view_id, i64 cursor_pos);
api(custom) function void view_remove_most_recent_multi_cursor(Application_Links* app, View_ID view_id);
api(custom) function void view_clear_multi_cursors(Application_Links* app, View_ID view_id);
api(custom) function b32 app_get_yanked_entire_line(Application_Links* app);
api(custom) function void app_set_yanked_entire_line(Application_Links* app, b32 value);
api(custom) function b32 view_get_vim_cutting_mode(Application_Links* app, View_ID view_id);
api(custom) function void view_set_vim_cutting_mode(Application_Links* app, View_ID view_id, b32 value);
api(custom) function void view_set_selection_begin(Application_Links* app, View_ID view_id, i64 line_num);
api(custom) function void view_set_selection_end(Application_Links* app, View_ID view_id, i64 line_num);
api(custom) function b32 view_set_modal_state(Application_Links* app, View_ID view_id, Modal_State modal_state);
api(custom) function Modal_State app_get_global_modal_state(Application_Links* app);
api(custom) function void app_set_global_modal_state(Application_Links* app, Modal_State state);
api(custom) function b32 app_get_is_global_modal(Application_Links* app);
api(custom) function void app_set_is_global_modal(Application_Links* app, b32 value);
api(custom) function void app_set_maps(Application_Links* app, i64 command_mapid, i64 insert_mapid);
api(custom) function b32 view_quit_ui(Application_Links* app, View_ID view_id);
api(custom) function b32 view_set_buffer(Application_Links* app, View_ID view_id, Buffer_ID buffer_id, Set_Buffer_Flag flags);
api(custom) function b32 view_push_context(Application_Links* app, View_ID view_id, View_Context* ctx);
api(custom) function b32 view_pop_context(Application_Links* app, View_ID view_id);
api(custom) function b32 view_alter_context(Application_Links* app, View_ID view_id, View_Context* ctx);
api(custom) function View_Context view_current_context(Application_Links* app, View_ID view_id);
api(custom) function String_Const_u8 view_current_context_hook_memory(Application_Links* app, View_ID view_id, Hook_ID hook_id);
api(custom) function Managed_Scope create_user_managed_scope(Application_Links* app);
api(custom) function b32 destroy_user_managed_scope(Application_Links* app, Managed_Scope scope);
api(custom) function Managed_Scope get_global_managed_scope(Application_Links* app);
api(custom) function Managed_Scope get_managed_scope_with_multiple_dependencies(Application_Links* app, Managed_Scope* scopes, i32 count);
api(custom) function b32 managed_scope_clear_contents(Application_Links* app, Managed_Scope scope);
api(custom) function b32 managed_scope_clear_self_all_dependent_scopes(Application_Links* app, Managed_Scope scope);
api(custom) function Base_Allocator* managed_scope_allocator(Application_Links* app, Managed_Scope scope);
api(custom) function u64 managed_id_group_highest_id(Application_Links* app, String_Const_u8 group);
api(custom) function Managed_ID managed_id_declare(Application_Links* app, String_Const_u8 group, String_Const_u8 name);
api(custom) function Managed_ID managed_id_get(Application_Links* app, String_Const_u8 group, String_Const_u8 name);
api(custom) function void* managed_scope_get_attachment(Application_Links* app, Managed_Scope scope, Managed_ID id, u64 size);
api(custom) function b32 managed_scope_attachment_erase(Application_Links* app, Managed_Scope scope, Managed_ID id);
api(custom) function Managed_Object alloc_managed_memory_in_scope(Application_Links* app, Managed_Scope scope, i32 item_size, i32 count);
api(custom) function Managed_Object alloc_buffer_markers_on_buffer(Application_Links* app, Buffer_ID buffer_id, i32 count, Managed_Scope* optional_extra_scope);
api(custom) function u32 managed_object_get_item_size(Application_Links* app, Managed_Object object);
api(custom) function u32 managed_object_get_item_count(Application_Links* app, Managed_Object object);
api(custom) function void* managed_object_get_pointer(Application_Links* app, Managed_Object object);
api(custom) function Managed_Object_Type managed_object_get_type(Application_Links* app, Managed_Object object);
api(custom) function Managed_Scope managed_object_get_containing_scope(Application_Links* app, Managed_Object object);
api(custom) function b32 managed_object_free(Application_Links* app, Managed_Object object);
api(custom) function b32 managed_object_store_data(Application_Links* app, Managed_Object object, u32 first_index, u32 count, void* mem);
api(custom) function b32 managed_object_load_data(Application_Links* app, Managed_Object object, u32 first_index, u32 count, void* mem_out);
api(custom) function User_Input get_next_input_raw(Application_Links* app);
api(custom) function i64 get_current_input_sequence_number(Application_Links* app);
api(custom) function User_Input get_current_input(Application_Links* app);
api(custom) function void set_current_input(Application_Links* app, User_Input* input);
api(custom) function void leave_current_input_unhandled(Application_Links* app);
api(custom) function void set_custom_hook(Application_Links* app, Hook_ID hook_id, Void_Func* func_ptr);
api(custom) function Void_Func* get_custom_hook(Application_Links* app, Hook_ID hook_id);
api(custom) function b32 set_custom_hook_memory_size(Application_Links* app, Hook_ID hook_id, u64 size);
api(custom) function Mouse_State get_mouse_state(Application_Links* app);
api(custom) function b32 get_active_query_bars(Application_Links* app, View_ID view_id, i32 max_result_count, Query_Bar_Ptr_Array* array_out);
api(custom) function b32 start_query_bar(Application_Links* app, Query_Bar* bar, u32 flags);
api(custom) function void end_query_bar(Application_Links* app, Query_Bar* bar, u32 flags);
api(custom) function void clear_all_query_bars(Application_Links* app, View_ID view_id);
api(custom) function void print_message(Application_Links* app, String_Const_u8 message);
api(custom) function b32 log_string(Application_Links* app, String_Const_u8 str);
api(custom) function Face_ID get_largest_face_id(Application_Links* app);
api(custom) function b32 set_global_face(Application_Links* app, Face_ID id);
api(custom) function History_Record_Index buffer_history_get_max_record_index(Application_Links* app, Buffer_ID buffer_id);
api(custom) function Record_Info buffer_history_get_record_info(Application_Links* app, Buffer_ID buffer_id, History_Record_Index index);
api(custom) function Record_Info buffer_history_get_group_sub_record(Application_Links* app, Buffer_ID buffer_id, History_Record_Index index, i32 sub_index);
api(custom) function History_Record_Index buffer_history_get_current_state_index(Application_Links* app, Buffer_ID buffer_id);
api(custom) function b32 buffer_history_set_current_state_index(Application_Links* app, Buffer_ID buffer_id, History_Record_Index index);
api(custom) function b32 buffer_history_merge_record_range(Application_Links* app, Buffer_ID buffer_id, History_Record_Index first_index, History_Record_Index last_index, Record_Merge_Flag flags);
api(custom) function b32 buffer_history_clear_after_current_state(Application_Links* app, Buffer_ID buffer_id);
api(custom) function void global_history_edit_group_begin(Application_Links* app);
api(custom) function void global_history_edit_group_end(Application_Links* app);
api(custom) function b32 buffer_set_face(Application_Links* app, Buffer_ID buffer_id, Face_ID id);
api(custom) function Face_Description get_face_description(Application_Links* app, Face_ID face_id);
api(custom) function Face_Metrics get_face_metrics(Application_Links* app, Face_ID face_id);
api(custom) function Face_Advance_Map get_face_advance_map(Application_Links* app, Face_ID face_id);
api(custom) function Face_ID get_face_id(Application_Links* app, Buffer_ID buffer_id);
api(custom) function Face_ID try_create_new_face(Application_Links* app, Face_Description* description);
api(custom) function b32 try_modify_face(Application_Links* app, Face_ID id, Face_Description* description);
api(custom) function b32 try_release_face(Application_Links* app, Face_ID id, Face_ID replacement_id);
api(custom) function String_Const_u8 push_hot_directory(Application_Links* app, Arena* arena);
api(custom) function void set_hot_directory(Application_Links* app, String_Const_u8 string);
api(custom) function void send_exit_signal(Application_Links* app);
api(custom) function void hard_exit(Application_Links* app);
api(custom) function void set_window_title(Application_Links* app, String_Const_u8 title);
api(custom) function void acquire_global_frame_mutex(Application_Links* app);
api(custom) function void release_global_frame_mutex(Application_Links* app);
api(custom) function Vec2_f32 draw_string_oriented(Application_Links* app, Face_ID font_id, ARGB_Color color, String_Const_u8 str, Vec2_f32 point, u32 flags, Vec2_f32 delta);
api(custom) function f32 get_string_advance(Application_Links* app, Face_ID font_id, String_Const_u8 str);
api(custom) function void draw_rectangle(Application_Links* app, Rect_f32 rect, f32 roundness, ARGB_Color color);
api(custom) function void draw_rectangle_outline(Application_Links* app, Rect_f32 rect, f32 roundness, f32 thickness, ARGB_Color color);
api(custom) function Rect_f32 draw_set_clip(Application_Links* app, Rect_f32 new_clip);
api(custom) function Text_Layout_ID text_layout_create(Application_Links* app, Buffer_ID buffer_id, Rect_f32 rect, Buffer_Point buffer_point);
api(custom) function Rect_f32 text_layout_region(Application_Links* app, Text_Layout_ID text_layout_id);
api(custom) function Buffer_ID text_layout_get_buffer(Application_Links* app, Text_Layout_ID text_layout_id);
api(custom) function Range_i64 text_layout_get_visible_range(Application_Links* app, Text_Layout_ID text_layout_id);
api(custom) function Range_f32 text_layout_line_on_screen(Application_Links* app, Text_Layout_ID layout_id, i64 line_number);
api(custom) function Rect_f32 text_layout_character_on_screen(Application_Links* app, Text_Layout_ID layout_id, i64 pos);
api(custom) function void paint_text_color(Application_Links* app, Text_Layout_ID layout_id, Range_i64 range, ARGB_Color color);
api(custom) function void paint_text_color_blend(Application_Links* app, Text_Layout_ID layout_id, Range_i64 range, ARGB_Color color, f32 blend);
api(custom) function b32 text_layout_free(Application_Links* app, Text_Layout_ID text_layout_id);
api(custom) function void draw_text_layout(Application_Links* app, Text_Layout_ID layout_id, ARGB_Color special_color, ARGB_Color ghost_color);
api(custom) function void open_color_picker(Application_Links* app, Color_Picker* picker);
api(custom) function void animate_in_n_milliseconds(Application_Links* app, u32 n);
api(custom) function String_Match_List buffer_find_all_matches(Application_Links* app, Arena* arena, Buffer_ID buffer, i32 string_id, Range_i64 range, String_Const_u8 needle, Character_Predicate* predicate, Scan_Direction direction);
api(custom) function Profile_Global_List* get_core_profile_list(Application_Links* app);
api(custom) function Doc_Cluster* get_custom_layer_boundary_docs(Application_Links* app, Arena* arena);
