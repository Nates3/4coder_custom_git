/* date = July 5th 2022 11:30 pm */
#ifndef FCODER_CUSTOM_VARIABLES_H
#define FCODER_CUSTOM_VARIABLES_H

global b32 global_is_command_mode;
global i32 menu_f1_index;
global i32 global_relative_mark_history_index;

String_ID shared_mapid;
String_ID command_mode_mapid;
String_ID text_mode_mapid;

// TODO(nates): Add support for these using theme-name.4coder file
#define COMMAND_MODE_BUFFER_MARGIN_COLOR 0xffff0000
#define TEXT_MODE_BUFFER_MARGIN_COLOR 0xff00ff00

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
