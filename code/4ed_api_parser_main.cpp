/*
 * Mr. 4th Dimention - Allen Webster
 *
 * 06.10.2019
 *
 * Parser that extracts an API from C++ source code.
 *
 */

// TOP

#include "4coder_base_types.h"
#include "4coder_token.h"
#include "generated/lexer_cpp.h"
#include "4ed_api_definition.h"

#include "4coder_base_types.cpp"
#include "4coder_stringf.cpp"
#include "4coder_malloc_allocator.cpp"
#include "4coder_token.cpp"
#include "generated/lexer_cpp.cpp"
#include "4coder_file.cpp"
#include "4ed_api_definition.cpp"
#include "4ed_api_parser.cpp"

#include <stdio.h>

////////////////////////////////

int
main(int argc, char **argv)
{
 Arena arena = make_arena_malloc();
 
 if (argc < 2){
  printf("usage: <script> <source> {<source>}\n"
         " source : file to load and parse into the output list\n");
  exit(1);
 }
 
 API_Definition_List list = {};
 for (i32 i = 1; i < argc; i += 1){
  char *file_name = argv[i];
  FILE *file = fopen(file_name, "rb");
  if (file == 0){
   printf("error: could not open input file: '%s'\n", argv[i]);
   continue;
  }
  
  String_Const_u8 text = data_from_file(&arena, file);
  fclose(file);
  
  if (text.size > 0){
   api_parse_source_add_to_list(&arena, SCu8(file_name), text, &list);
  }
 }
 
 // NOTE(nates): the api_parser should be located in the misc directory
 String_Const_u8 exe_location = SCu8((u8 *)argv[0]);
 String_Const_u8 repo_dir = string_remove_front_folder_of_path(string_remove_front_folder_of_path(exe_location));
 
 u8 buffer[260] = {};
 for(u32 index = 0;
     index < repo_dir.size;
     ++index)
 {
  buffer[index] = repo_dir.str[index];
 }
 
 String_u8 code_partial = Su8(buffer, repo_dir.size, sizeof(buffer));
 if(string_append(&code_partial, SCu8("code\\")))
 {
  String_Const_u8 code_directory = code_partial.string;
  for (API_Definition *node = list.first;
       node != 0;
       node = node->next){
   api_definition_generate_api_includes(&arena, node, GeneratedGroup_Custom, 
                                        APIGeneration_NoAPINameOnCallables,
                                        code_directory);
  }
 }
 else
 {
  fprintf(stderr, "couldn't append code location to repo_directory");
 }
}

// BOTTOM
