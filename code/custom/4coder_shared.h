/* date = July 7th 2022 4:00 am */

#ifndef FCODER_SHARED_H
#define FCODER_SHARED_H

#define MARK_HISTORY_ARRAY_COUNT 32
struct Mark_History
{
  i64 marks[MARK_HISTORY_ARRAY_COUNT];
  i32 recent_index;
  i32 mark_count;
};

enum View_State_ID{
  View_State_Insert,
  View_State_Command
};

#endif //4CODER_SHARED_H
