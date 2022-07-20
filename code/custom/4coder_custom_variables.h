/* date = July 5th 2022 11:30 pm */
#ifndef FCODER_CUSTOM_VARIABLES_H
#define FCODER_CUSTOM_VARIABLES_H

global i32 menu_f1_index;

String_ID command_mapid;
String_ID insert_mapid;

global View_ID global_compilation_view = 0;

#define INSERT_MODE_MARGIN_COLOR 0xff00ff00
#define COMMAND_MODE_MARGIN_COLOR 0xffff0000

#define CAKEZ 1
#if defined(CAKEZ)
#define LISTER_MOVE_UP_KEY KeyCode_K
#define LISTER_MOVE_DOWN_KEY KeyCode_J
#define KEYCODE_AUTO_COMPLETE_UP KeyCode_K
#define KEYCODE_AUTO_COMPLETE_DOWN KeyCode_J
#define KEYCODE_SEARCH_UP KeyCode_K
#define KEYCODE_SEARCH_DOWN KeyCode_J
#define ENABLE_LISTER_TAB 1
#else
#define LISTER_MOVE_UP_KEY KeyCode_C
#define LISTER_MOVE_DOWN_KEY KeyCode_T
#define KEYCODE_AUTO_COMPLETE_UP KeyCode_C
#define KEYCODE_AUTO_COMPLETE_DOWN KeyCode_T
#define KEYCODE_SEARCH_UP KeyCode_C
#define KEYCODE_SEARCH_DOWN KeyCode_T
#define ENABLE_LISTER_TAB 0
#endif

#endif //4CODER_CUSTOM_VARIABLES_H
