# Microsoft Developer Studio Project File - Name="3d" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=3d - Win32 DebugInstrument
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "3d.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "3d.mak" CFG="3d - Win32 DebugInstrument"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "3d - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "3d - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "3d - Win32 ReleaseDebug" (based on "Win32 (x86) Static Library")
!MESSAGE "3d - Win32 DebugFast" (based on "Win32 (x86) Static Library")
!MESSAGE "3d - Win32 DebugInstrument" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "3d - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../obj/Release/3d"
# PROP Intermediate_Dir "../obj/Release/3d"
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../include" /D "_LIB" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /Yu"std3d.h" /FD /Zm200 /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../lib/nl3d_r.lib"

!ELSEIF  "$(CFG)" == "3d - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../obj/Debug/3d"
# PROP Intermediate_Dir "../obj/Debug/3d"
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /I "../include" /D "_LIB" /D "__STL_DEBUG" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /Yu"std3d.h" /FD /GZ /Zm200 /c
# SUBTRACT CPP /Gf /Fr
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../lib/nl3d_d.lib"

!ELSEIF  "$(CFG)" == "3d - Win32 ReleaseDebug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../obj/ReleaseDebug/3d"
# PROP Intermediate_Dir "../obj/ReleaseDebug/3d"
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /I "../include" /D "_LIB" /D "NL_RELEASE_DEBUG" /D "LIBXML_STATIC" /D "WIN32" /D "NDEBUG" /D "_MBCS" /Yu"std3d.h" /FD /Zm200 /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../lib/nl3d_rd.lib"

!ELSEIF  "$(CFG)" == "3d - Win32 DebugFast"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../obj/DebugFast/3d"
# PROP Intermediate_Dir "../obj/DebugFast/3d"
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /Ob1 /I "../include" /D "_LIB" /D "NL_DEBUG_FAST" /D "_DEBUG" /D "_MBCS" /D "LIBXML_STATIC" /D "WIN32" /Yu"std3d.h" /FD /GZ /Zm200 /c
# SUBTRACT CPP /Gf /Gy /Fr
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../lib/nl3d_df.lib"

!ELSEIF  "$(CFG)" == "3d - Win32 DebugInstrument"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "3d___Win32_DebugInstrument"
# PROP BASE Intermediate_Dir "3d___Win32_DebugInstrument"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../obj/DebugInstrument/3d"
# PROP Intermediate_Dir "../obj/DebugInstrument/3d"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GR /GX /Zi /Od /Ob1 /I "../include" /D "_LIB" /D "NL_DEBUG_FAST" /D "_DEBUG" /D "_MBCS" /D "LIBXML_STATIC" /D "WIN32" /Yu"std3d.h" /FD /GZ /Zm200 /c
# SUBTRACT BASE CPP /Gf /Gy /Fr
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /I "../include" /D "_LIB" /D "NL_DEBUG_FAST" /D "_DEBUG" /D "_MBCS" /D "LIBXML_STATIC" /D "WIN32" /D "NL_DEBUG_INSTRUMENT" /Yu"std3d.h" /FD /GZ /Zm200 /c
# SUBTRACT CPP /Gf /Gy /Fr
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/nl3d_df.lib"
# ADD LIB32 /nologo /out:"../lib/nl3d_di.lib"

!ENDIF 

# Begin Target

# Name "3d - Win32 Release"
# Name "3d - Win32 Debug"
# Name "3d - Win32 ReleaseDebug"
# Name "3d - Win32 DebugFast"
# Name "3d - Win32 DebugInstrument"
# Begin Group "Traversals"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\anim_detail_trav.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\anim_detail_trav.h
# End Source File
# Begin Source File

SOURCE=.\3d\clip_trav.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\clip_trav.h
# End Source File
# Begin Source File

SOURCE=.\3d\hrc_trav.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\hrc_trav.h
# End Source File
# Begin Source File

SOURCE=.\3d\light_trav.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\light_trav.h
# End Source File
# Begin Source File

SOURCE=.\3d\load_balancing_trav.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\load_balancing_trav.h
# End Source File
# Begin Source File

SOURCE=.\3d\render_trav.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\render_trav.h
# End Source File
# Begin Source File

SOURCE=.\3d\trav_scene.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\trav_scene.h
# End Source File
# End Group
# Begin Group "Models"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\camera.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\camera.h
# End Source File
# Begin Source File

SOURCE=.\3d\flare_model.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\flare_model.h
# End Source File
# Begin Source File

SOURCE=.\3d\landscape_model.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\landscape_model.h
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_base_instance.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_base_instance.h
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_instance.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_instance.h
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_mrm_instance.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_mrm_instance.h
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_mrm_skinned_instance.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_mrm_skinned_instance.h
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_multi_lod_instance.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_multi_lod_instance.h
# End Source File
# Begin Source File

SOURCE=.\3d\particle_system_model.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\particle_system_model.h
# End Source File
# Begin Source File

SOURCE=.\3d\point_light_model.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\point_light_model.h
# End Source File
# Begin Source File

SOURCE=.\3d\root_model.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\root_model.h
# End Source File
# Begin Source File

SOURCE=.\3d\seg_remanence.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\seg_remanence.h
# End Source File
# Begin Source File

SOURCE=.\3d\skeleton_model.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\skeleton_model.h
# End Source File
# Begin Source File

SOURCE=.\3d\transform.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\transform.h
# End Source File
# Begin Source File

SOURCE=.\3d\transform_shape.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\transform_shape.h
# End Source File
# Begin Source File

SOURCE=.\3d\water_model.cpp

!IF  "$(CFG)" == "3d - Win32 Release"

# ADD CPP /W3

!ELSEIF  "$(CFG)" == "3d - Win32 Debug"

!ELSEIF  "$(CFG)" == "3d - Win32 ReleaseDebug"

!ELSEIF  "$(CFG)" == "3d - Win32 DebugFast"

!ELSEIF  "$(CFG)" == "3d - Win32 DebugInstrument"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\3d\water_model.h
# End Source File
# End Group
# Begin Group "Landscape"

# PROP Default_Filter ""
# Begin Group "ZoneManager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\zone_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\zone_manager.h
# End Source File
# Begin Source File

SOURCE=.\3d\zone_search.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\zone_search.h
# End Source File
# End Group
# Begin Group "Tools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\instance_lighter.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\instance_lighter.h
# End Source File
# Begin Source File

SOURCE=.\3d\zone_corner_smoother.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\zone_corner_smoother.h
# End Source File
# Begin Source File

SOURCE=.\3d\zone_lighter.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\zone_lighter.h
# End Source File
# Begin Source File

SOURCE=.\3d\zone_smoother.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\zone_smoother.h
# End Source File
# Begin Source File

SOURCE=.\3d\zone_symmetrisation.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\zone_symmetrisation.h
# End Source File
# Begin Source File

SOURCE=.\3d\zone_tgt_smoother.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\zone_tgt_smoother.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\3d\bezier_patch.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\bezier_patch.h
# End Source File
# Begin Source File

SOURCE=.\3d\landscape.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\landscape.h
# End Source File
# Begin Source File

SOURCE=.\3d\landscape_def.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\landscape_def.h
# End Source File
# Begin Source File

SOURCE=.\3d\landscape_face_vector_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\landscape_face_vector_manager.h
# End Source File
# Begin Source File

SOURCE=.\3d\landscape_profile.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\landscape_profile.h
# End Source File
# Begin Source File

SOURCE=.\3d\landscape_vegetable_block.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\landscape_vegetable_block.h
# End Source File
# Begin Source File

SOURCE=.\3d\landscapevb_allocator.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\landscapevb_allocator.h
# End Source File
# Begin Source File

SOURCE=.\3d\landscapevb_info.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\landscapevb_info.h
# End Source File
# Begin Source File

SOURCE=.\3d\patch.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\patch.h
# End Source File
# Begin Source File

SOURCE=.\3d\patch_lightmap.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\patch_noise.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\patch_rdr_pass.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\patch_rdr_pass.h
# End Source File
# Begin Source File

SOURCE=.\3d\patch_render.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\patch_vegetable.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\patchdlm_context.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\patchdlm_context.h
# End Source File
# Begin Source File

SOURCE=.\3d\patchuv_locator.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\patchuv_locator.h
# End Source File
# Begin Source File

SOURCE=.\3d\tess_block.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\tess_block.h
# End Source File
# Begin Source File

SOURCE=.\3d\tess_face_priority_list.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\tess_face_priority_list.h
# End Source File
# Begin Source File

SOURCE=.\3d\tess_list.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\tess_list.h
# End Source File
# Begin Source File

SOURCE=.\3d\tessellation.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\tessellation.h
# End Source File
# Begin Source File

SOURCE=.\3d\texture_dlm.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\texture_dlm.h
# End Source File
# Begin Source File

SOURCE=.\3d\texture_far.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\texture_far.h
# End Source File
# Begin Source File

SOURCE=.\3d\texture_near.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\texture_near.h
# End Source File
# Begin Source File

SOURCE=.\3d\tile_color.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\tile_color.h
# End Source File
# Begin Source File

SOURCE=.\3d\tile_element.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\tile_element.h
# End Source File
# Begin Source File

SOURCE=.\3d\tile_light_influence.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\tile_light_influence.h
# End Source File
# Begin Source File

SOURCE=.\3d\tile_lumel.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\tile_lumel.h
# End Source File
# Begin Source File

SOURCE=.\3d\zone.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\zone.h
# End Source File
# End Group
# Begin Group "Driver"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\driver.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\driver.h
# End Source File
# Begin Source File

SOURCE=.\3d\driver_material_inline.h
# End Source File
# Begin Source File

SOURCE=.\3d\dru.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\dru.h
# End Source File
# Begin Source File

SOURCE=.\3d\index_buffer.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\index_buffer.h
# End Source File
# Begin Source File

SOURCE=.\3d\light.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\light.h
# End Source File
# Begin Source File

SOURCE=.\3d\material.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\material.h
# End Source File
# Begin Source File

SOURCE=.\3d\occlusion_query.h
# End Source File
# Begin Source File

SOURCE=.\3d\shader.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\shader.h
# End Source File
# Begin Source File

SOURCE=.\3d\texture.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\texture.h
# End Source File
# Begin Source File

SOURCE=.\3d\vertex_buffer.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\vertex_buffer.h
# End Source File
# Begin Source File

SOURCE=.\3d\vertex_program.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\vertex_program.h
# End Source File
# Begin Source File

SOURCE=.\3d\vertex_program_parse.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\vertex_program_parse.h
# End Source File
# End Group
# Begin Group "Font"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\computed_string.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\computed_string.h
# End Source File
# Begin Source File

SOURCE=.\3d\font_generator.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\font_generator.h
# End Source File
# Begin Source File

SOURCE=.\3d\font_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\font_manager.h
# End Source File
# Begin Source File

SOURCE=.\3d\text_context.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\text_context.h
# End Source File
# End Group
# Begin Group "Container"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\bsp_tree.h
# End Source File
# Begin Source File

SOURCE=.\3d\cube_grid.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\cube_grid.h
# End Source File
# Begin Source File

SOURCE=.\3d\fast_ptr_list.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\fast_ptr_list.h
# End Source File
# Begin Source File

SOURCE=.\3d\layered_ordering_table.h
# End Source File
# Begin Source File

SOURCE=.\3d\ordering_table.h
# End Source File
# Begin Source File

SOURCE=.\3d\ptr_set.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ptr_set.h
# End Source File
# Begin Source File

SOURCE=.\3d\quad_grid.cpp

!IF  "$(CFG)" == "3d - Win32 Release"

!ELSEIF  "$(CFG)" == "3d - Win32 Debug"

!ELSEIF  "$(CFG)" == "3d - Win32 ReleaseDebug"

!ELSEIF  "$(CFG)" == "3d - Win32 DebugFast"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "3d - Win32 DebugInstrument"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\3d\quad_grid.h
# End Source File
# Begin Source File

SOURCE=.\3d\static_quad_grid.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\static_quad_grid.h
# End Source File
# End Group
# Begin Group "Tiles"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\tile_bank.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\tile_bank.h
# End Source File
# Begin Source File

SOURCE=.\3d\tile_far_bank.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\tile_far_bank.h
# End Source File
# Begin Source File

SOURCE=.\3d\tile_noise_map.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\tile_noise_map.h
# End Source File
# Begin Source File

SOURCE=.\3d\tile_vegetable_desc.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\tile_vegetable_desc.h
# End Source File
# End Group
# Begin Group "Shapes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\flare_shape.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\flare_shape.h
# End Source File
# Begin Source File

SOURCE=.\3d\mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mesh.h
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_base.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_base.h
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_blender.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_blender.h
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_block_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_block_manager.h
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_geom.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_geom.h
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_morpher.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_morpher.h
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_mrm.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_mrm.h
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_mrm_skin.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_mrm_skin_template.cpp

!IF  "$(CFG)" == "3d - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "3d - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "3d - Win32 ReleaseDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "3d - Win32 DebugFast"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "3d - Win32 DebugInstrument"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\3d\mesh_mrm_skinned.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_mrm_skinned.h
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_mrm_skinned_template.cpp

!IF  "$(CFG)" == "3d - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "3d - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "3d - Win32 ReleaseDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "3d - Win32 DebugFast"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "3d - Win32 DebugInstrument"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\3d\mesh_multi_lod.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_multi_lod.h
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_vertex_program.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mesh_vertex_program.h
# End Source File
# Begin Source File

SOURCE=.\3d\meshvp_per_pixel_light.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\meshvp_per_pixel_light.h
# End Source File
# Begin Source File

SOURCE=.\3d\meshvp_wind_tree.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\meshvp_wind_tree.h
# End Source File
# Begin Source File

SOURCE=.\3d\mrm_level_detail.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mrm_level_detail.h
# End Source File
# Begin Source File

SOURCE=.\3d\particle_system_shape.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\particle_system_shape.h
# End Source File
# Begin Source File

SOURCE=.\3d\raw_skin.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\raw_skin.h
# End Source File
# Begin Source File

SOURCE=.\3d\raw_skinned.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\raw_skinned.h
# End Source File
# Begin Source File

SOURCE=.\3d\seg_remanence_shape.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\seg_remanence_shape.h
# End Source File
# Begin Source File

SOURCE=.\3d\shadow_skin.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\shadow_skin.h
# End Source File
# Begin Source File

SOURCE=.\3d\shape.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\shape.h
# End Source File
# Begin Source File

SOURCE=.\3d\shape_bank.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\shape_bank.h
# End Source File
# Begin Source File

SOURCE=.\3d\shifted_triangle_cache.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\shifted_triangle_cache.h
# End Source File
# Begin Source File

SOURCE=.\3d\skeleton_shape.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\skeleton_shape.h
# End Source File
# Begin Source File

SOURCE=.\3d\tangent_space_build.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\tangent_space_build.h
# End Source File
# Begin Source File

SOURCE=.\3d\vertex_stream_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\vertex_stream_manager.h
# End Source File
# Begin Source File

SOURCE=.\3d\water_shape.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\water_shape.h
# End Source File
# End Group
# Begin Group "Textures"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\async_texture_block.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\async_texture_block.h
# End Source File
# Begin Source File

SOURCE=.\3d\async_texture_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\async_texture_manager.h
# End Source File
# Begin Source File

SOURCE=.\3d\cube_map_builder.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\cube_map_builder.h
# End Source File
# Begin Source File

SOURCE=.\3d\fasthls_modifier.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\fasthls_modifier.h
# End Source File
# Begin Source File

SOURCE=.\3d\hls_color_texture.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\hls_color_texture.h
# End Source File
# Begin Source File

SOURCE=.\3d\hls_texture_bank.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\hls_texture_bank.h
# End Source File
# Begin Source File

SOURCE=.\3d\hls_texture_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\hls_texture_manager.h
# End Source File
# Begin Source File

SOURCE=.\3d\texture_blank.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\texture_blank.h
# End Source File
# Begin Source File

SOURCE=.\3d\texture_blend.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\texture_blend.h
# End Source File
# Begin Source File

SOURCE=.\3d\texture_bloom.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\texture_bloom.h
# End Source File
# Begin Source File

SOURCE=.\3d\texture_bump.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\texture_bump.h
# End Source File
# Begin Source File

SOURCE=.\3d\texture_cube.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\texture_cube.h
# End Source File
# Begin Source File

SOURCE=.\3d\texture_emboss.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\texture_emboss.h
# End Source File
# Begin Source File

SOURCE=.\3d\texture_file.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\texture_file.h
# End Source File
# Begin Source File

SOURCE=.\3d\texture_font.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\texture_font.h
# End Source File
# Begin Source File

SOURCE=.\3d\texture_grouped.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\texture_grouped.h
# End Source File
# Begin Source File

SOURCE=.\3d\texture_mem.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\texture_mem.h
# End Source File
# Begin Source File

SOURCE=.\3d\texture_multi_file.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\texture_multi_file.h
# End Source File
# End Group
# Begin Group "Mrm"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\mrm_builder.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mrm_builder.h
# End Source File
# Begin Source File

SOURCE=.\3d\mrm_internal.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mrm_internal.h
# End Source File
# Begin Source File

SOURCE=.\3d\mrm_mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mrm_mesh.h
# End Source File
# Begin Source File

SOURCE=.\3d\mrm_parameters.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mrm_parameters.h
# End Source File
# End Group
# Begin Group "Animation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\anim_ctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\animatable.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\animatable.h
# End Source File
# Begin Source File

SOURCE=.\3d\animated_lightmap.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\animated_lightmap.h
# End Source File
# Begin Source File

SOURCE=.\3d\animated_material.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\animated_material.h
# End Source File
# Begin Source File

SOURCE=.\3d\animated_morph.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\animated_morph.h
# End Source File
# Begin Source File

SOURCE=.\3d\animated_value.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\animated_value.h
# End Source File
# Begin Source File

SOURCE=.\3d\animation.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\animation.h
# End Source File
# Begin Source File

SOURCE=.\3d\animation_optimizer.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\animation_optimizer.h
# End Source File
# Begin Source File

SOURCE=.\3d\animation_playlist.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\animation_playlist.h
# End Source File
# Begin Source File

SOURCE=.\3d\animation_set.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\animation_set.h
# End Source File
# Begin Source File

SOURCE=.\3d\animation_time.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\bone.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\bone.h
# End Source File
# Begin Source File

SOURCE=.\3d\channel_mixer.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\channel_mixer.h
# End Source File
# Begin Source File

SOURCE=.\3d\key.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\key.h
# End Source File
# Begin Source File

SOURCE=.\3d\play_list_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\play_list_manager.h
# End Source File
# Begin Source File

SOURCE=.\3d\skeleton_spawn_script.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\skeleton_spawn_script.h
# End Source File
# Begin Source File

SOURCE=.\3d\skeleton_weight.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\skeleton_weight.h
# End Source File
# Begin Source File

SOURCE=.\3d\target_anim_ctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\track.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\track.h
# End Source File
# Begin Source File

SOURCE=.\3d\track_bezier.h
# End Source File
# Begin Source File

SOURCE=.\3d\track_keyframer.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\track_keyframer.h
# End Source File
# Begin Source File

SOURCE=.\3d\track_sampled_common.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\track_sampled_common.h
# End Source File
# Begin Source File

SOURCE=.\3d\track_sampled_quat.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\track_sampled_quat.h
# End Source File
# Begin Source File

SOURCE=.\3d\track_sampled_quat_small_header.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\track_sampled_quat_small_header.h
# End Source File
# Begin Source File

SOURCE=.\3d\track_sampled_vector.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\track_sampled_vector.h
# End Source File
# Begin Source File

SOURCE=.\3d\track_tcb.h
# End Source File
# Begin Source File

SOURCE=.\3d\transformable.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\transformable.h
# End Source File
# End Group
# Begin Group "UserImp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\animation_set_user.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\animation_set_user.h
# End Source File
# Begin Source File

SOURCE=.\3d\cloud_scape_user.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\cloud_scape_user.h
# End Source File
# Begin Source File

SOURCE=.\3d\driver_user.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\driver_user.h
# End Source File
# Begin Source File

SOURCE=.\3d\driver_user2.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\frustum.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\height_map.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\instance_group_user.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\instance_group_user.h
# End Source File
# Begin Source File

SOURCE=.\3d\landscape_user.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\landscape_user.h
# End Source File
# Begin Source File

SOURCE=.\3d\landscapeig_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\light_user.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\light_user.h
# End Source File
# Begin Source File

SOURCE=.\3d\logic_info.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\particle_system_sound_user.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\play_list_manager_user.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\play_list_manager_user.h
# End Source File
# Begin Source File

SOURCE=.\3d\play_list_user.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\play_list_user.h
# End Source File
# Begin Source File

SOURCE=.\3d\primitive_profile.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\scene_user.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\scene_user.h
# End Source File
# Begin Source File

SOURCE=.\3d\scissor.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\shape_bank_user.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\shape_bank_user.h
# End Source File
# Begin Source File

SOURCE=.\3d\text_context_user.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\text_context_user.h
# End Source File
# Begin Source File

SOURCE=.\3d\texture_user.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\texture_user.h
# End Source File
# Begin Source File

SOURCE=.\3d\u_bone.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\u_camera.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\u_instance.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\u_instance_material.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\u_material.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\u_particle_system_instance.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\u_point_light.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\u_shape.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\u_skeleton.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\u_transform.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\u_transformable.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\u_visual_collision_mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\u_water.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\viewport.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\visual_collision_entity_user.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\visual_collision_entity_user.h
# End Source File
# Begin Source File

SOURCE=.\3d\visual_collision_manager_user.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\visual_collision_manager_user.h
# End Source File
# Begin Source File

SOURCE=.\3d\water_env_map_user.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\water_env_map_user.h
# End Source File
# End Group
# Begin Group "User"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\nel\3d\anim_ctrl.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\animation_time.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\frustum.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\height_map.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\landscapeig_manager.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\logic_info.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\point_light_influence.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\primitive_profile.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\scissor.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\target_anim_ctrl.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_3d_mouse_listener.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_animation.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_animation_set.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_bone.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_camera.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_cloud_scape.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_driver.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_instance.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_instance_group.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_instance_material.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_landscape.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_light.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_material.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_particle_system_instance.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_particle_system_sound.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_play_list.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_play_list_manager.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_point_light.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_ps_sound_impl.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_ps_sound_interface.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_scene.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_shape.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_shape_bank.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_skeleton.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_text_context.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_texture.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_track.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_transform.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_transformable.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_visual_collision_entity.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_visual_collision_manager.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_visual_collision_mesh.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_water.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\u_water_env_map.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\3d\viewport.h
# End Source File
# End Group
# Begin Group "Makefile"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\Makefile.am
# End Source File
# End Group
# Begin Group "Fx"

# PROP Default_Filter ""
# Begin Group "particles"

# PROP Default_Filter ""
# Begin Group "particles render"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\ps_dot.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_dot.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_face.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_face.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_face_look_at.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_face_look_at.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_fan_light.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_fan_light.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_macro.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_mesh.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_particle.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_particle.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_particle2.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_particle2.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_particle_basic.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_particle_basic.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_quad.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_quad.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_register_particles.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_ribbon.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_ribbon.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_ribbon_base.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_ribbon_base.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_ribbon_look_at.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_ribbon_look_at.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_shockwave.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_shockwave.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_tail_dot.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_tail_dot.h
# End Source File
# End Group
# Begin Group "attribs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\ps_attrib.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_attrib_maker.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_attrib_maker_bin_op.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_attrib_maker_bin_op.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_attrib_maker_bin_op_inline.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_attrib_maker_helper.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_attrib_maker_helper.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_attrib_maker_iterators.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_attrib_maker_template.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_attrib_maker_template.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_color.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_color.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_direction.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_float.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_float.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_int.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_int.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_plane_basis.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_plane_basis_maker.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_plane_basis_maker.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_register_attribs.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_register_color_attribs.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_register_float_attribs.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_register_int_attribs.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_register_plane_basis_attribs.h
# End Source File
# End Group
# Begin Group "forces"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\ps_force.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_force.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_register_forces.cpp
# End Source File
# End Group
# Begin Group "zones"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\ps_register_zones.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_zone.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_zone.h
# End Source File
# End Group
# Begin Group "emitters"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\ps_emitter.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_emitter.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_register_emitters.cpp
# End Source File
# End Group
# Begin Group "sounds"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\ps_sound.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_sound.h
# End Source File
# End Group
# Begin Group "lights"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\ps_light.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_light.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\3d\particle_system.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\particle_system.h
# End Source File
# Begin Source File

SOURCE=.\3d\particle_system_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\particle_system_manager.h
# End Source File
# Begin Source File

SOURCE=.\3d\particle_system_process.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\particle_system_process.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_allocator.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_allocator.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_edit.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_iterator.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_located.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_located.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_lod.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_misc.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_spawn_info.h
# End Source File
# Begin Source File

SOURCE=.\3d\ps_util.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ps_util.h
# End Source File
# End Group
# Begin Group "2d"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\deform_2d.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\deform_2d.h
# End Source File
# Begin Source File

SOURCE=.\3d\heat_haze.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\heat_haze.h
# End Source File
# Begin Source File

SOURCE=.\3d\motion_blur.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\motion_blur.h
# End Source File
# Begin Source File

SOURCE=.\3d\quad_effect.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\quad_effect.h
# End Source File
# End Group
# End Group
# Begin Group "Collisions"

# PROP Default_Filter ""
# Begin Group "packed col"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\packed_world.cpp

!IF  "$(CFG)" == "3d - Win32 Release"

!ELSEIF  "$(CFG)" == "3d - Win32 Debug"

!ELSEIF  "$(CFG)" == "3d - Win32 ReleaseDebug"

!ELSEIF  "$(CFG)" == "3d - Win32 DebugFast"

# ADD CPP /MDd

!ELSEIF  "$(CFG)" == "3d - Win32 DebugInstrument"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\3d\packed_world.h
# End Source File
# Begin Source File

SOURCE=.\3d\packed_zone.cpp

!IF  "$(CFG)" == "3d - Win32 Release"

!ELSEIF  "$(CFG)" == "3d - Win32 Debug"

!ELSEIF  "$(CFG)" == "3d - Win32 ReleaseDebug"

!ELSEIF  "$(CFG)" == "3d - Win32 DebugFast"

# ADD CPP /MDd

!ELSEIF  "$(CFG)" == "3d - Win32 DebugInstrument"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\3d\packed_zone.h
# End Source File
# Begin Source File

SOURCE=.\3d\shape_info.cpp

!IF  "$(CFG)" == "3d - Win32 Release"

!ELSEIF  "$(CFG)" == "3d - Win32 Debug"

!ELSEIF  "$(CFG)" == "3d - Win32 ReleaseDebug"

!ELSEIF  "$(CFG)" == "3d - Win32 DebugFast"

# ADD CPP /MDd

!ELSEIF  "$(CFG)" == "3d - Win32 DebugInstrument"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\3d\shape_info.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\3d\camera_col.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\camera_col.h
# End Source File
# Begin Source File

SOURCE=.\3d\landscape_collision_grid.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\landscape_collision_grid.h
# End Source File
# Begin Source File

SOURCE=.\3d\ray_mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ray_mesh.h
# End Source File
# Begin Source File

SOURCE=.\3d\visual_collision_entity.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\visual_collision_entity.h
# End Source File
# Begin Source File

SOURCE=.\3d\visual_collision_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\visual_collision_manager.h
# End Source File
# Begin Source File

SOURCE=.\3d\visual_collision_mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\visual_collision_mesh.h
# End Source File
# End Group
# Begin Group "ClipAccelerator"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\cluster.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\cluster.h
# End Source File
# Begin Source File

SOURCE=.\3d\portal.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\portal.h
# End Source File
# Begin Source File

SOURCE=.\3d\quad_grid_clip_cluster.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\quad_grid_clip_cluster.h
# End Source File
# Begin Source File

SOURCE=.\3d\quad_grid_clip_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\quad_grid_clip_manager.h
# End Source File
# End Group
# Begin Group "Water"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\water_env_map.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\water_env_map.h
# End Source File
# Begin Source File

SOURCE=.\3d\water_height_map.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\water_height_map.h
# End Source File
# Begin Source File

SOURCE=.\3d\water_pool_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\water_pool_manager.h
# End Source File
# End Group
# Begin Group "Stripifier"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\stripifier.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\stripifier.h
# End Source File
# End Group
# Begin Group "vegetable"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\vegetable.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable.h
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_blend_layer_model.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_blend_layer_model.h
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_clip_block.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_clip_block.h
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_def.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_def.h
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_instance_group.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_instance_group.h
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_light_ex.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_light_ex.h
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_manager.h
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_quadrant.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_quadrant.h
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_shape.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_shape.h
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_sort_block.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_sort_block.h
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_uv8.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\vegetable_uv8.h
# End Source File
# Begin Source File

SOURCE=.\3d\vegetablevb_allocator.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\vegetablevb_allocator.h
# End Source File
# End Group
# Begin Group "Util"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\matrix_3x4.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\matrix_3x4.h
# End Source File
# Begin Source File

SOURCE=.\3d\radix_sort.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\radix_sort.h
# End Source File
# End Group
# Begin Group "Lighting"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\ig_surface_light.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ig_surface_light.h
# End Source File
# Begin Source File

SOURCE=.\3d\ig_surface_light_build.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\ig_surface_light_build.h
# End Source File
# Begin Source File

SOURCE=.\3d\light_contribution.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\light_contribution.h
# End Source File
# Begin Source File

SOURCE=.\3d\light_influence_interpolator.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\light_influence_interpolator.h
# End Source File
# Begin Source File

SOURCE=.\3d\lighting_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\lighting_manager.h
# End Source File
# Begin Source File

SOURCE=.\3d\point_light.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\point_light.h
# End Source File
# Begin Source File

SOURCE=.\3d\point_light_named.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\point_light_named.h
# End Source File
# Begin Source File

SOURCE=.\3d\point_light_named_array.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\point_light_named_array.h
# End Source File
# Begin Source File

SOURCE=.\3d\surface_light_grid.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\surface_light_grid.h
# End Source File
# End Group
# Begin Group "LodSystems"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\coarse_mesh_build.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\coarse_mesh_build.h
# End Source File
# Begin Source File

SOURCE=.\3d\coarse_mesh_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\coarse_mesh_manager.h
# End Source File
# Begin Source File

SOURCE=.\3d\lod_character_builder.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\lod_character_builder.h
# End Source File
# Begin Source File

SOURCE=.\3d\lod_character_instance.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\lod_character_instance.h
# End Source File
# Begin Source File

SOURCE=.\3d\lod_character_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\lod_character_manager.h
# End Source File
# Begin Source File

SOURCE=.\3d\lod_character_shape.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\lod_character_shape.h
# End Source File
# Begin Source File

SOURCE=.\3d\lod_character_shape_bank.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\lod_character_shape_bank.h
# End Source File
# Begin Source File

SOURCE=.\3d\lod_character_texture.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\lod_character_texture.h
# End Source File
# End Group
# Begin Group "CloudScape"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\cloud.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\cloud.h
# End Source File
# Begin Source File

SOURCE=.\3d\cloud_scape.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\cloud_scape.h
# End Source File
# Begin Source File

SOURCE=.\3d\noise_3d.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\noise_3d.h
# End Source File
# End Group
# Begin Group "Shadows"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3d\shadow_map.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\shadow_map.h
# End Source File
# Begin Source File

SOURCE=.\3d\shadow_map_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\shadow_map_manager.h
# End Source File
# Begin Source File

SOURCE=.\3d\shadow_poly_receiver.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\shadow_poly_receiver.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\3d\async_file_manager.cpp

!IF  "$(CFG)" == "3d - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "3d - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "3d - Win32 ReleaseDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "3d - Win32 DebugFast"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "3d - Win32 DebugInstrument"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\3d\async_file_manager.h
# End Source File
# Begin Source File

SOURCE=.\3d\async_file_manager_3d.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\async_file_manager_3d.h
# End Source File
# Begin Source File

SOURCE=.\3d\debug_vb.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\debug_vb.h
# End Source File
# Begin Source File

SOURCE=.\3d\event_mouse_listener.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\event_mouse_listener.h
# End Source File
# Begin Source File

SOURCE=.\3d\init_3d.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\init_3d.h
# End Source File
# Begin Source File

SOURCE=.\3d\mini_col.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\mini_col.h
# End Source File
# Begin Source File

SOURCE=.\3d\nelu.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\nelu.h
# End Source File
# Begin Source File

SOURCE=.\3d\register_3d.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\register_3d.h
# End Source File
# Begin Source File

SOURCE=.\3d\scene.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\scene.h
# End Source File
# Begin Source File

SOURCE=.\3d\scene_group.cpp
# End Source File
# Begin Source File

SOURCE=.\3d\scene_group.h
# End Source File
# Begin Source File

SOURCE=.\3d\std3d.cpp
# ADD CPP /Yc"std3d.h"
# End Source File
# Begin Source File

SOURCE=.\3d\std3d.h
# End Source File
# Begin Source File

SOURCE=.\3d\vertex_buffer_heap.cpp

!IF  "$(CFG)" == "3d - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "3d - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "3d - Win32 ReleaseDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "3d - Win32 DebugFast"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "3d - Win32 DebugInstrument"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\3d\vertex_buffer_heap.h
# End Source File
# End Target
# End Project
