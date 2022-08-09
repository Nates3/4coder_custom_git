/* date = July 7th 2022 4:00 am */

#ifndef FCODER_SHARED_H
#define FCODER_SHARED_H

#define MARK_HISTORY_ARRAY_COUNT 128
struct Mark_History
{
  i64 marks[MARK_HISTORY_ARRAY_COUNT];
  i32 recent_index; // NOTE(nates): This is the most recent mark set
  i32 rel_index; // NOTE(nates): for this mark index, this is the rel index used by the user
  // to index through the mark history
  i32 mark_count;
};

#define VIEW_MULTI_CURSOR_MAXIMUM_COUNT 128

enum Modal_State
{
	Modal_State_Null,
  Modal_State_Insert,
  Modal_State_Command
};

enum Multi_Cursor_Mode
{
	Multi_Cursor_Disabled,
	Multi_Cursor_Place_Cursors,
	Multi_Cursor_Enabled,
};

struct Project_List_Node
{
	Project_List_Node *prev;
	Project_List_Node *next;
	String_Const_u8 full_path;
	String_Const_u8 name;
};

struct Project_List
{
	Project_List_Node *first;
	Project_List_Node *last;
  u32 count;
};


#endif //4CODER_SHARED_H
