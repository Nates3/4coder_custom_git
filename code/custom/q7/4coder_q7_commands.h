
//- file for managing the q7 commands
// not included anywhere

//- format -> void name(Application_Links *app);
void q7_cycle_multi_cursor_mode(Application_Links *app);
void q7_jump_downwards_using_prevsearch(Application_Links *app);
void q7_jump_upwards_using_prevsearch(Application_Links *app);
void q7_load_project_list_file(Application_Links *appj;
void q7_delete_to_end_of_line(Application_Links *app);
void q7_delete_to_start_of_line(Application_Links *app);
void q7_delete_alpha_numeric_identifier(Application_Links *app);
void q7_copy_alpha_numeric_identifier(Application_Links *app);
void q7_change_to_normal_mode(Application_Links *app);
void q7_change_to_insert_mode(Application_Links *app);
void q7_change_to_insert_mode_after(Application_Links *app);
// TODO(natse): Support brackets && parenthesis in this function
void q7_jump_to_matching_brace(Application_Links *app);
// TODO(nates): Change these functions to use the key context
// thing in nvim where you press d and that can take motions or whatever
void q7_yank_line(Application_Links *app);
void q7_cut(Application_Links *app);
void q7_paste(Application_Links *app);
void q7_select_lines(Application_Links *app);

void q7_join_lines(Application_Links *app);
void q7_insert_line_below(Application_Links *app);
void q7_insert_start_of_line(Application_Links *app);
void q7_cancel_command(Application_Links *app);
void q7_insert_return(Application_Links *app);
void q7_jump_to_definition_under_mouse(Application_Links *app);
void q7_tag_context_menu(Application_Links *app);
void q7_reload_all_files(Application_Links *app);

// TODO(nates): rework the "mark" system to be a jump list
void q7_goto_next_mark(Application_Links *app);
void q7_goto_prev_jump(Application_Links *app);
void q7_toggle_compilation_expand(Application_Links *app);
void q7_list_projects(Application_Links *app);

void q7_initialize(Application_Links *app);
