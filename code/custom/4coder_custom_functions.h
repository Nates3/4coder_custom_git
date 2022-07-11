/* date = July 6th 2022 9:15 pm */

#ifndef FCODER_CUSTOM_FUNCTIONS_H
#define FCODER_CUSTOM_FUNCTIONS_H

internal void set_command_map_id(Application_Links *app, Buffer_ID buffer, Command_Map_ID mapid);
internal b32 view_set_mark_record(Application_Links *app, View_ID view, Buffer_Seek seek);
internal void set_global_rel_mark_index(Application_Links *app, View_ID view);
internal void view_state_set_margin_color(Application_Links *app, View_ID view);
#endif //4CODER_CUSTOM_FUNCTIONS_H
