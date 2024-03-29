/*
4coder_code_index_listers.cpp - Listers for exploring the contents of the code index.
*/

// TOP

struct Tiny_Jump{
  Buffer_ID buffer;
  i64 pos;
};

CUSTOM_UI_COMMAND_SIG(jump_to_definition)
CUSTOM_DOC("List all definitions in the code index and jump to one chosen by the user.")
{
  char *query = "Definition:";
  
  Scratch_Block scratch(app);
  Lister_Block lister(app, scratch);
  lister_set_query(lister, query);
  lister_set_default_handlers(lister);
  
  code_index_lock();
  for (Buffer_ID buffer = get_buffer_next(app, 0, Access_Always);
       buffer != 0;
       buffer = get_buffer_next(app, buffer, Access_Always)){
    Code_Index_File *file = code_index_get_file(buffer);
    if (file != 0)
    {
      for (i32 i = 0; i < file->note_array.count; i += 1)
      {
        Code_Index_Note *note = file->note_array.ptrs[i];
        Tiny_Jump *jump = push_array(scratch, Tiny_Jump, 1);
        jump->buffer = buffer;
        jump->pos = note->pos.first;
        
        String_Const_u8 sort = {};
        String_Const_u8 text = note->text;
        switch (note->note_kind)
        {
          case CodeIndexNote_Type:
          {
            sort = string_u8_litexpr("Type");
          }break;
          case CodeIndexNote_Function:
          {
            sort = string_u8_litexpr("Function");
            text = note->function_text;
          }break;
          case CodeIndexNote_Macro:
          {
            sort = string_u8_litexpr("Macro");
          }break;
          
          case CodeIndexNote_Enum:
          {
            sort = string_u8_litexpr("Enum");
          } break;
          
          case CodeIndexNote_ForwardDeclaration:
          {
            sort = string_u8_litexpr("Declaration");
          } break;
          
          case CodeIndexNote_CommentNOTE:
          {
            continue;
          } break;
          
          case CodeIndexNote_CommentTODO:
          {
            continue;
          } break;
          
          case CodeIndexNote_Namespace:
          {
            continue;
          } break;
          
          case CodeIndexNote_4coderCommand:
          {
            continue;
          } break;
          
          InvalidDefaultCase;
        }
        lister_add_item(lister, text, sort, jump, 0);
      }
    }
  }
  code_index_unlock();
  
  Lister_Result l_result = run_lister(app, lister);
  Tiny_Jump result = {};
  if (!l_result.canceled && l_result.user_data != 0){
    block_copy_struct(&result, (Tiny_Jump*)l_result.user_data);
  }
  
  if (result.buffer != 0){
    View_ID view = get_this_ctx_view(app, Access_Always);
    point_stack_push_view_cursor(app, view);
    jump_to_location(app, view, result.buffer, result.pos);
  }
}

struct Note_Buffer_Pair
{
  Code_Index_Note *note;
  Buffer_ID buffer;
};

CUSTOM_UI_COMMAND_SIG(jump_to_definition_at_cursor)
CUSTOM_DOC("Jump to the first definition in the code index matching an identifier at the cursor")
{
  View_ID view = get_active_view(app, Access_Visible);
  
  if (view != 0)
  {
    Scratch_Block scratch(app);
    String_Const_u8 query = push_token_or_word_under_active_cursor(app, scratch);
    
    Temp_Memory restore_point = begin_temp(scratch);
    i32 matching_pair_count = 0;
    Note_Buffer_Pair*start = push_array(scratch, Note_Buffer_Pair, 1);
    pop_array(scratch, Note_Buffer_Pair, 1);
    
    code_index_lock();
    for (Buffer_ID buffer = get_buffer_next(app, 0, Access_Always);
         buffer != 0;
         buffer = get_buffer_next(app, buffer, Access_Always))
    {
      Code_Index_File *file = code_index_get_file(buffer);
      if (file != 0)
      {
        for (i32 i = 0; i < file->note_array.count; i += 1)
        {
          Code_Index_Note *note = file->note_array.ptrs[i];
          if (string_match(note->text, query))
          {
            Note_Buffer_Pair *record = push_array(scratch, Note_Buffer_Pair, 1);
            record->note = note;
            record->buffer = buffer;
            matching_pair_count++;
          }
        }
      }
    }
    code_index_unlock();
    
    Note_Buffer_Pair *found_pair = 0;
    for(i32 index = 0;
        index < matching_pair_count;
        ++index)
    {
      Note_Buffer_Pair *pair = start + index;
      
			if(pair->note->note_kind == CodeIndexNote_Macro)
			{
				found_pair = pair;
				break;
			}
			
      if(pair->note->note_kind == CodeIndexNote_ForwardDeclaration &&
         found_pair == 0)
      {
        found_pair = pair;
      }
      
      if(pair->note->note_kind != CodeIndexNote_ForwardDeclaration)
      {
        found_pair = pair;
      }
    }
    
    if(found_pair)
    {
      point_stack_push_view_cursor(app, view);
      jump_to_location(app, view, found_pair->buffer, found_pair->note->pos.first);
    }
    
    end_temp(restore_point);
  }
}

CUSTOM_UI_COMMAND_SIG(jump_to_definition_at_cursor_other_panel)
CUSTOM_DOC("Jump to the first definition in the code index matching an identifier at the cursor")
{
  View_ID view = get_active_view(app, Access_Visible);
  
  if (view != 0)
  {
    view = get_next_view_looped_primary_panels(app, view, Access_Always);
    Scratch_Block scratch(app);
    String_Const_u8 query = push_token_or_word_under_active_cursor(app, scratch);
    
    Temp_Memory restore_point = begin_temp(scratch);
    i32 matching_pair_count = 0;
    Note_Buffer_Pair*start = push_array(scratch, Note_Buffer_Pair, 1);
    pop_array(scratch, Note_Buffer_Pair, 1);
    
    code_index_lock();
    for (Buffer_ID buffer = get_buffer_next(app, 0, Access_Always);
         buffer != 0;
         buffer = get_buffer_next(app, buffer, Access_Always))
    {
      Code_Index_File *file = code_index_get_file(buffer);
      if (file != 0)
      {
        for (i32 i = 0; i < file->note_array.count; i += 1)
        {
          Code_Index_Note *note = file->note_array.ptrs[i];
          if (string_match(note->text, query))
          {
            Note_Buffer_Pair *record = push_array(scratch, Note_Buffer_Pair, 1);
            record->note = note;
            record->buffer = buffer;
            matching_pair_count++;
          }
        }
      }
    }
    code_index_unlock();
    
    Note_Buffer_Pair *found_pair = 0;
    for(i32 index = 0;
        index < matching_pair_count;
        ++index)
    {
      Note_Buffer_Pair *pair = start + index;
      
			if(pair->note->note_kind == CodeIndexNote_Macro)
			{
				found_pair = pair;
				break;
			}
			
      if(pair->note->note_kind == CodeIndexNote_ForwardDeclaration &&
         found_pair == 0)
      {
        found_pair = pair;
      }
      
      if(pair->note->note_kind != CodeIndexNote_ForwardDeclaration)
      {
        found_pair = pair;
      }
    }
    
    if(found_pair)
    {
      point_stack_push_view_cursor(app, view);
      jump_to_location(app, view, found_pair->buffer, found_pair->note->pos.first);
    }
    
    end_temp(restore_point);
  }
}
// BOTTOM

