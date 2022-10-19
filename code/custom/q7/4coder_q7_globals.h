/* date = July 5th 2022 11:30 pm */
#ifndef FCODER_N7_GLOBALS_H
#define FCODER_N7_GLOBALS_H

global i32 menu_f1_index;

String_ID g_normalmode_mapid;
String_ID g_insertmode_mapid;

#define COMPILATION_MIN_SIZE 0.0f
#define COMPILATION_MAX_SIZE 20.0f

#define JUMP_BUFFER_RANGE 50

global View_ID global_compilation_view = 0;
global b32 global_compilation_view_expanded = false;

//#define CAKEZ
#define LISTER_MOVE_UP_KEY KeyCode_K
#define LISTER_MOVE_DOWN_KEY KeyCode_J
#define KEYCODE_WORD_COMPLETE_UP KeyCode_K
#define KEYCODE_WORD_COMPLETE_DOWN KeyCode_J
#define KEYCODE_SEARCH_UP KeyCode_K
#define KEYCODE_SEARCH_DOWN KeyCode_J
#define ENABLE_LISTER_TAB 1

#endif //4CODER_CUSTOM_VARIABLES_H
