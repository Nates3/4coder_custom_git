

#if !defined(FCODER_CUSTOM_LAYER_CPP)
#define FCODER_CUSTOM_LAYER_CPP

#include "4coder_default_include.cpp"

#if !defined(META_PASS)
#include "generated/managed_id_metadata.cpp"
#endif

#include "4coder_q7_functions.cpp"
#include "4coder_q7_hardcoded_keybinds.cpp"
#include "4coder_q7_commands.cpp"

void custom_layer_init(Application_Links *app)
{
 Thread_Context *tctx = get_thread_context(app);
 
 // NOTE(allen): setup for default framework
 default_framework_init(app);
 
 // NOTE(allen): default hooks and command maps
 set_all_default_hooks(app);
 mapping_init(tctx, &framework_mapping);
 
 String_ID global_mapid = vars_save_string_lit("keys_global");
 String_ID file_mapid = vars_save_string_lit("keys_file");
 String_ID code_mapid = vars_save_string_lit("keys_code");
 
 command_mapid = vars_save_string_lit("command_mapid_string");
 insert_mapid = vars_save_string_lit("insert_mapid_string");
 
 MappingScope();
 SelectMapping(&framework_mapping);
 
 SelectMap(global_mapid);
 BindCore(custom_startup, CoreCode_Startup);
 BindCore(default_try_exit, CoreCode_TryExit);
 cakez_bind_shared_keys(m, map);
 
 SelectMap(command_mapid);
 ParentMap(global_mapid);
 cakez_bind_command_keys(m, map);
 
 SelectMap(insert_mapid);
 ParentMap(global_mapid);
 cakez_bind_text_input(m, map);
 
 // NOTE(nates): You have to bind the "global_map, file_map, and code_map for some reason"
 SelectMap(file_mapid);
 ParentMap(command_mapid);
 
 SelectMap(code_mapid);
 ParentMap(command_mapid);
}

#endif