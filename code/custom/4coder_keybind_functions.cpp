

// TODO(nates): Figure out a way to load bindings from a file 
// it should support keymaps aswell


/////////////////////////////////
// NOTE(nates): Cakez's bindings

internal void
cakez_bind_shared_keys(Mapping *m, Command_Map *map)
{
  Bind(change_binding_mode, KeyCode_Escape);
  Bind(command_lister, KeyCode_X, KeyCode_Alt);
  Bind(backspace_char, KeyCode_Backspace);
  Bind(delete_char, KeyCode_Delete);
  Bind(interactive_open_or_new, KeyCode_O, KeyCode_Control);
  Bind(interactive_switch_buffer, KeyCode_I, KeyCode_Control);
  
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
  Bind(delete_range, KeyCode_D);
  Bind(select_entire_line, KeyCode_V, KeyCode_Shift);
  Bind(combine_two_lines, KeyCode_J, KeyCode_Shift);
  Bind(undo, KeyCode_U);
  Bind(redo, KeyCode_R, KeyCode_Control);
  BindTextInput(insert_return);
  
  Bind(move_up, KeyCode_K);
  Bind(move_down, KeyCode_J);
  Bind(move_left, KeyCode_H);
  Bind(move_right, KeyCode_L);
  
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
}

internal void
nates_bind_command_keys(Mapping *m, Command_Map *map)
{
}

internal void
nates_bind_text_input(Mapping *m, Command_Map *map)
{
}