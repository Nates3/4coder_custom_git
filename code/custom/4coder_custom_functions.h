/* date = July 6th 2022 9:15 pm */

#ifndef FCODER_CUSTOM_FUNCTIONS_H
#define FCODER_CUSTOM_FUNCTIONS_H

internal void set_modal_mode_buffer(Application_Links *app, Buffer_ID buffer, Command_Map_ID mapid);
internal Command_Map_ID get_modal_mapid(void);
internal void bind_mapping_to_all_view_buffers(Application_Links *app, Command_Map_ID mapid);

#endif //4CODER_CUSTOM_FUNCTIONS_H
