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

enum Modal_State_ID
{
  Modal_State_Insert,
  Modal_State_Command
};

struct String_Node
{
  String_Node *prev;
  String_Node *next;
  String_Const_u8 contents;
};

struct Project_List
{
  String_Node *first;
  String_Node *last;
  u32 count;
};


#endif //4CODER_SHARED_H
