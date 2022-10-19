

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
	
	g_normalmode_mapid = vars_save_string_lit("normalmode_mapid_string");
	g_insertmode_mapid  = vars_save_string_lit("insertmode_mapid_string");
	
	MappingScope();
	SelectMapping(&framework_mapping);
	
	SelectMap(global_mapid);
	BindCore(q7_initialize, CoreCode_Startup);
	BindCore(default_try_exit, CoreCode_TryExit);
 cakez_bind_global_keys(m, map);
	
	SelectMap(g_normalmode_mapid);
	ParentMap(global_mapid);
 cakez_bind_normal_mode_keys(m, map);
	
	SelectMap(g_insertmode_mapid);
	ParentMap(global_mapid);
 cakez_bind_insert_mode_keys(m, map);
	
 // NOTE(nates): code_mapid && file_mapid are used in default_begin_buffer
	SelectMap(file_mapid);
	ParentMap(g_normalmode_mapid);
	
	SelectMap(code_mapid);
	ParentMap(g_normalmode_mapid);

	app_set_maps(app, g_normalmode_mapid, g_insertmode_mapid);
}

#endif
