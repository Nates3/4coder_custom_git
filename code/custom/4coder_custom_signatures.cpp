
///////////////////////////////////////
// NOTE(nates): Own custom commands


CUSTOM_COMMAND_SIG(select_entire_line)
CUSTOM_DOC("selects entire line")
{
  View_ID view = get_active_view(app, Access_ReadVisible);
  Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
  i64 cursor_pos = view_get_cursor_pos(app, view);
  i64 line_number = get_line_number_from_pos(app, buffer, cursor_pos);
  i64 line_start_pos = get_line_start_pos(app, buffer, line_number);
  i64 line_end_pos = get_line_end_pos(app, buffer, line_number);
  
  view_set_cursor_and_preferred_x(app, view, seek_pos(line_start_pos));
  view_set_mark(app, view, seek_pos(line_end_pos));
}

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