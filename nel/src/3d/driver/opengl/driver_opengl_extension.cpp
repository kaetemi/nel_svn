/** \file driver_opengl_extension.cpp
 * OpenGL driver extension registry
 *
 * $Id: driver_opengl_extension.cpp,v 1.54 2007/03/09 09:49:30 boucher Exp $
 */

/* Copyright, 2000 Nevrax Ltd.
 *
 * This file is part of NEVRAX NEL.
 * NEVRAX NEL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX NEL is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX NEL; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */


#include "stdopengl.h"

#include "driver_opengl.h"
#include "driver_opengl_extension.h"
#include "nel/3d/material.h"

// ***************************************************************************
#ifdef NL_OS_WINDOWS
#define	nelglGetProcAddress wglGetProcAddress
#else	// NL_OS_WINDOWS
void (*nelglGetProcAddress(const char *procName))()
{
	return glXGetProcAddressARB((const GLubyte *)procName);
}
#endif	// NL_OS_WINDOWS


// ***************************************************************************
// The exported function names

// ARB_multitexture
//=================
NEL_PFNGLACTIVETEXTUREARBPROC nglActiveTextureARB;
NEL_PFNGLCLIENTACTIVETEXTUREARBPROC nglClientActiveTextureARB;

NEL_PFNGLMULTITEXCOORD1SARBPROC nglMultiTexCoord1sARB;
NEL_PFNGLMULTITEXCOORD1IARBPROC nglMultiTexCoord1iARB;
NEL_PFNGLMULTITEXCOORD1FARBPROC nglMultiTexCoord1fARB;
NEL_PFNGLMULTITEXCOORD1DARBPROC nglMultiTexCoord1dARB;
NEL_PFNGLMULTITEXCOORD2SARBPROC nglMultiTexCoord2sARB;
NEL_PFNGLMULTITEXCOORD2IARBPROC nglMultiTexCoord2iARB;
NEL_PFNGLMULTITEXCOORD2FARBPROC nglMultiTexCoord2fARB;
NEL_PFNGLMULTITEXCOORD2DARBPROC nglMultiTexCoord2dARB;
NEL_PFNGLMULTITEXCOORD3SARBPROC nglMultiTexCoord3sARB;
NEL_PFNGLMULTITEXCOORD3IARBPROC nglMultiTexCoord3iARB;
NEL_PFNGLMULTITEXCOORD3FARBPROC nglMultiTexCoord3fARB;
NEL_PFNGLMULTITEXCOORD3DARBPROC nglMultiTexCoord3dARB;
NEL_PFNGLMULTITEXCOORD4SARBPROC nglMultiTexCoord4sARB;
NEL_PFNGLMULTITEXCOORD4IARBPROC nglMultiTexCoord4iARB;
NEL_PFNGLMULTITEXCOORD4FARBPROC nglMultiTexCoord4fARB;
NEL_PFNGLMULTITEXCOORD4DARBPROC nglMultiTexCoord4dARB;

NEL_PFNGLMULTITEXCOORD1SVARBPROC nglMultiTexCoord1svARB;
NEL_PFNGLMULTITEXCOORD1IVARBPROC nglMultiTexCoord1ivARB;
NEL_PFNGLMULTITEXCOORD1FVARBPROC nglMultiTexCoord1fvARB;
NEL_PFNGLMULTITEXCOORD1DVARBPROC nglMultiTexCoord1dvARB;
NEL_PFNGLMULTITEXCOORD2SVARBPROC nglMultiTexCoord2svARB;
NEL_PFNGLMULTITEXCOORD2IVARBPROC nglMultiTexCoord2ivARB;
NEL_PFNGLMULTITEXCOORD2FVARBPROC nglMultiTexCoord2fvARB;
NEL_PFNGLMULTITEXCOORD2DVARBPROC nglMultiTexCoord2dvARB;
NEL_PFNGLMULTITEXCOORD3SVARBPROC nglMultiTexCoord3svARB;
NEL_PFNGLMULTITEXCOORD3IVARBPROC nglMultiTexCoord3ivARB;
NEL_PFNGLMULTITEXCOORD3FVARBPROC nglMultiTexCoord3fvARB;
NEL_PFNGLMULTITEXCOORD3DVARBPROC nglMultiTexCoord3dvARB;
NEL_PFNGLMULTITEXCOORD4SVARBPROC nglMultiTexCoord4svARB;
NEL_PFNGLMULTITEXCOORD4IVARBPROC nglMultiTexCoord4ivARB;
NEL_PFNGLMULTITEXCOORD4FVARBPROC nglMultiTexCoord4fvARB;
NEL_PFNGLMULTITEXCOORD4DVARBPROC nglMultiTexCoord4dvARB;


// ARB_TextureCompression.
//========================
NEL_PFNGLCOMPRESSEDTEXIMAGE3DARBPROC	nglCompressedTexImage3DARB;
NEL_PFNGLCOMPRESSEDTEXIMAGE2DARBPROC	nglCompressedTexImage2DARB;
NEL_PFNGLCOMPRESSEDTEXIMAGE1DARBPROC	nglCompressedTexImage1DARB;
NEL_PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC	nglCompressedTexSubImage3DARB;
NEL_PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC	nglCompressedTexSubImage2DARB;
NEL_PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC	nglCompressedTexSubImage1DARB;
NEL_PFNGLGETCOMPRESSEDTEXIMAGEARBPROC	nglGetCompressedTexImageARB;


// VertexArrayRangeNV.
//====================
NEL_PFNGLFLUSHVERTEXARRAYRANGENVPROC	nglFlushVertexArrayRangeNV;
NEL_PFNGLVERTEXARRAYRANGENVPROC			nglVertexArrayRangeNV;
#ifdef NL_OS_WINDOWS
PFNWGLALLOCATEMEMORYNVPROC			wglAllocateMemoryNV;
PFNWGLFREEMEMORYNVPROC				wglFreeMemoryNV;
#endif


// FenceNV.
//====================
NEL_PFNGLDELETEFENCESNVPROC				nglDeleteFencesNV;
NEL_PFNGLGENFENCESNVPROC				nglGenFencesNV;
NEL_PFNGLISFENCENVPROC					nglIsFenceNV;
NEL_PFNGLTESTFENCENVPROC				nglTestFenceNV;
NEL_PFNGLGETFENCEIVNVPROC				nglGetFenceivNV;
NEL_PFNGLFINISHFENCENVPROC				nglFinishFenceNV;
NEL_PFNGLSETFENCENVPROC					nglSetFenceNV;


// VertexWeighting.
//====================
NEL_PFNGLVERTEXWEIGHTFEXTPROC			nglVertexWeightfEXT;
NEL_PFNGLVERTEXWEIGHTFVEXTPROC			nglVertexWeightfvEXT;
NEL_PFNGLVERTEXWEIGHTPOINTEREXTPROC		nglVertexWeightPointerEXT;


// VertexProgramExtension.
//========================
NEL_PFNGLAREPROGRAMSRESIDENTNVPROC		nglAreProgramsResidentNV;
NEL_PFNGLBINDPROGRAMNVPROC				nglBindProgramNV;
NEL_PFNGLDELETEPROGRAMSNVPROC			nglDeleteProgramsNV;
NEL_PFNGLEXECUTEPROGRAMNVPROC			nglExecuteProgramNV;
NEL_PFNGLGENPROGRAMSNVPROC				nglGenProgramsNV;
NEL_PFNGLGETPROGRAMPARAMETERDVNVPROC	nglGetProgramParameterdvNV;
NEL_PFNGLGETPROGRAMPARAMETERFVNVPROC	nglGetProgramParameterfvNV;
NEL_PFNGLGETPROGRAMIVNVPROC				nglGetProgramivNV;
NEL_PFNGLGETPROGRAMSTRINGNVPROC			nglGetProgramStringNV;
NEL_PFNGLGETTRACKMATRIXIVNVPROC			nglGetTrackMatrixivNV;
NEL_PFNGLGETVERTEXATTRIBDVNVPROC		nglGetVertexAttribdvNV;
NEL_PFNGLGETVERTEXATTRIBFVNVPROC		nglGetVertexAttribfvNV;
NEL_PFNGLGETVERTEXATTRIBIVNVPROC		nglGetVertexAttribivNV;
NEL_PFNGLGETVERTEXATTRIBPOINTERVNVPROC	nglGetVertexAttribPointervNV;
NEL_PFNGLISPROGRAMNVPROC				nglIsProgramNV;
NEL_PFNGLLOADPROGRAMNVPROC				nglLoadProgramNV;
NEL_PFNGLPROGRAMPARAMETER4DNVPROC		nglProgramParameter4dNV;
NEL_PFNGLPROGRAMPARAMETER4DVNVPROC		nglProgramParameter4dvNV;
NEL_PFNGLPROGRAMPARAMETER4FNVPROC		nglProgramParameter4fNV;
NEL_PFNGLPROGRAMPARAMETER4FVNVPROC		nglProgramParameter4fvNV;
NEL_PFNGLPROGRAMPARAMETERS4DVNVPROC		nglProgramParameters4dvNV;
NEL_PFNGLPROGRAMPARAMETERS4FVNVPROC		nglProgramParameters4fvNV;
NEL_PFNGLREQUESTRESIDENTPROGRAMSNVPROC	nglRequestResidentProgramsNV;
NEL_PFNGLTRACKMATRIXNVPROC				nglTrackMatrixNV;
NEL_PFNGLVERTEXATTRIBPOINTERNVPROC		nglVertexAttribPointerNV;
NEL_PFNGLVERTEXATTRIB1DNVPROC			nglVertexAttrib1dNV;
NEL_PFNGLVERTEXATTRIB1DVNVPROC			nglVertexAttrib1dvNV;
NEL_PFNGLVERTEXATTRIB1FNVPROC			nglVertexAttrib1fNV;
NEL_PFNGLVERTEXATTRIB1FVNVPROC			nglVertexAttrib1fvNV;
NEL_PFNGLVERTEXATTRIB1SNVPROC			nglVertexAttrib1sNV;
NEL_PFNGLVERTEXATTRIB1SVNVPROC			nglVertexAttrib1svNV;
NEL_PFNGLVERTEXATTRIB2DNVPROC			nglVertexAttrib2dNV;
NEL_PFNGLVERTEXATTRIB2DVNVPROC			nglVertexAttrib2dvNV;
NEL_PFNGLVERTEXATTRIB2FNVPROC			nglVertexAttrib2fNV;
NEL_PFNGLVERTEXATTRIB2FVNVPROC			nglVertexAttrib2fvNV;
NEL_PFNGLVERTEXATTRIB2SNVPROC			nglVertexAttrib2sNV;
NEL_PFNGLVERTEXATTRIB2SVNVPROC			nglVertexAttrib2svNV;
NEL_PFNGLVERTEXATTRIB3DNVPROC			nglVertexAttrib3dNV;
NEL_PFNGLVERTEXATTRIB3DVNVPROC			nglVertexAttrib3dvNV;
NEL_PFNGLVERTEXATTRIB3FNVPROC			nglVertexAttrib3fNV;
NEL_PFNGLVERTEXATTRIB3FVNVPROC			nglVertexAttrib3fvNV;
NEL_PFNGLVERTEXATTRIB3SNVPROC			nglVertexAttrib3sNV;
NEL_PFNGLVERTEXATTRIB3SVNVPROC			nglVertexAttrib3svNV;
NEL_PFNGLVERTEXATTRIB4DNVPROC			nglVertexAttrib4dNV;
NEL_PFNGLVERTEXATTRIB4DVNVPROC			nglVertexAttrib4dvNV;
NEL_PFNGLVERTEXATTRIB4FNVPROC			nglVertexAttrib4fNV;
NEL_PFNGLVERTEXATTRIB4FVNVPROC			nglVertexAttrib4fvNV;
NEL_PFNGLVERTEXATTRIB4SNVPROC			nglVertexAttrib4sNV;
NEL_PFNGLVERTEXATTRIB4SVNVPROC			nglVertexAttrib4svNV;
NEL_PFNGLVERTEXATTRIB4UBVNVPROC			nglVertexAttrib4ubvNV;
NEL_PFNGLVERTEXATTRIBS1DVNVPROC			nglVertexAttribs1dvNV;
NEL_PFNGLVERTEXATTRIBS1FVNVPROC			nglVertexAttribs1fvNV;
NEL_PFNGLVERTEXATTRIBS1SVNVPROC			nglVertexAttribs1svNV;
NEL_PFNGLVERTEXATTRIBS2DVNVPROC			nglVertexAttribs2dvNV;
NEL_PFNGLVERTEXATTRIBS2FVNVPROC			nglVertexAttribs2fvNV;
NEL_PFNGLVERTEXATTRIBS2SVNVPROC			nglVertexAttribs2svNV;
NEL_PFNGLVERTEXATTRIBS3DVNVPROC			nglVertexAttribs3dvNV;
NEL_PFNGLVERTEXATTRIBS3FVNVPROC			nglVertexAttribs3fvNV;
NEL_PFNGLVERTEXATTRIBS3SVNVPROC			nglVertexAttribs3svNV;
NEL_PFNGLVERTEXATTRIBS4DVNVPROC			nglVertexAttribs4dvNV;
NEL_PFNGLVERTEXATTRIBS4FVNVPROC			nglVertexAttribs4fvNV;
NEL_PFNGLVERTEXATTRIBS4SVNVPROC			nglVertexAttribs4svNV;
NEL_PFNGLVERTEXATTRIBS4UBVNVPROC		nglVertexAttribs4ubvNV;

// VertexShaderExt extension
//==========================
NEL_PFNGLBEGINVERTEXSHADEREXTPROC			nglBeginVertexShaderEXT;
NEL_PFNGLENDVERTEXSHADEREXTPROC				nglEndVertexShaderEXT;
NEL_PFNGLBINDVERTEXSHADEREXTPROC			nglBindVertexShaderEXT;
NEL_PFNGLGENVERTEXSHADERSEXTPROC			nglGenVertexShadersEXT;
NEL_PFNGLDELETEVERTEXSHADEREXTPROC			nglDeleteVertexShaderEXT;
NEL_PFNGLSHADEROP1EXTPROC					nglShaderOp1EXT;
NEL_PFNGLSHADEROP2EXTPROC					nglShaderOp2EXT;
NEL_PFNGLSHADEROP3EXTPROC					nglShaderOp3EXT;
NEL_PFNGLSWIZZLEEXTPROC						nglSwizzleEXT;
NEL_PFNGLWRITEMASKEXTPROC					nglWriteMaskEXT;
NEL_PFNGLINSERTCOMPONENTEXTPROC				nglInsertComponentEXT;
NEL_PFNGLEXTRACTCOMPONENTEXTPROC			nglExtractComponentEXT;
NEL_PFNGLGENSYMBOLSEXTPROC					nglGenSymbolsEXT;
NEL_PFNGLSETINVARIANTEXTPROC				nglSetInvariantEXT;
NEL_PFNGLSETLOCALCONSTANTEXTPROC			nglSetLocalConstantEXT;
NEL_PFNGLVARIANTPOINTEREXTPROC				nglVariantPointerEXT;
NEL_PFNGLENABLEVARIANTCLIENTSTATEEXTPROC	nglEnableVariantClientStateEXT;
NEL_PFNGLDISABLEVARIANTCLIENTSTATEEXTPROC	nglDisableVariantClientStateEXT;
NEL_PFNGLBINDLIGHTPARAMETEREXTPROC			nglBindLightParameterEXT;
NEL_PFNGLBINDMATERIALPARAMETEREXTPROC		nglBindMaterialParameterEXT;
NEL_PFNGLBINDTEXGENPARAMETEREXTPROC			nglBindTexGenParameterEXT;
NEL_PFNGLBINDTEXTUREUNITPARAMETEREXTPROC	nglBindTextureUnitParameterEXT;
NEL_PFNGLBINDPARAMETEREXTPROC				nglBindParameterEXT;
NEL_PFNGLISVARIANTENABLEDEXTPROC			nglIsVariantEnabledEXT;
NEL_PFNGLGETVARIANTBOOLEANVEXTPROC			nglGetVariantBooleanvEXT;
NEL_PFNGLGETVARIANTINTEGERVEXTPROC			nglGetVariantIntegervEXT;
NEL_PFNGLGETVARIANTFLOATVEXTPROC			nglGetVariantFloatvEXT;
NEL_PFNGLGETVARIANTPOINTERVEXTPROC			nglGetVariantPointervEXT;
NEL_PFNGLGETINVARIANTBOOLEANVEXTPROC		nglGetInvariantBooleanvEXT;
NEL_PFNGLGETINVARIANTINTEGERVEXTPROC		nglGetInvariantIntegervEXT;
NEL_PFNGLGETINVARIANTFLOATVEXTPROC			nglGetInvariantFloatvEXT;
NEL_PFNGLGETLOCALCONSTANTBOOLEANVEXTPROC	nglGetLocalConstantBooleanvEXT;
NEL_PFNGLGETLOCALCONSTANTINTEGERVEXTPROC	nglGetLocalConstantIntegervEXT;
NEL_PFNGLGETLOCALCONSTANTFLOATVEXTPROC		nglGetLocalConstantFloatvEXT;


// SecondaryColor extension
//========================
NEL_PFNGLSECONDARYCOLOR3BEXTPROC		nglSecondaryColor3bEXT;
NEL_PFNGLSECONDARYCOLOR3BVEXTPROC		nglSecondaryColor3bvEXT;
NEL_PFNGLSECONDARYCOLOR3DEXTPROC		nglSecondaryColor3dEXT;
NEL_PFNGLSECONDARYCOLOR3DVEXTPROC		nglSecondaryColor3dvEXT;
NEL_PFNGLSECONDARYCOLOR3FEXTPROC		nglSecondaryColor3fEXT;
NEL_PFNGLSECONDARYCOLOR3FVEXTPROC		nglSecondaryColor3fvEXT;
NEL_PFNGLSECONDARYCOLOR3IEXTPROC		nglSecondaryColor3iEXT;
NEL_PFNGLSECONDARYCOLOR3IVEXTPROC		nglSecondaryColor3ivEXT;
NEL_PFNGLSECONDARYCOLOR3SEXTPROC		nglSecondaryColor3sEXT;
NEL_PFNGLSECONDARYCOLOR3SVEXTPROC		nglSecondaryColor3svEXT;
NEL_PFNGLSECONDARYCOLOR3UBEXTPROC		nglSecondaryColor3ubEXT;
NEL_PFNGLSECONDARYCOLOR3UBVEXTPROC		nglSecondaryColor3ubvEXT;
NEL_PFNGLSECONDARYCOLOR3UIEXTPROC		nglSecondaryColor3uiEXT;
NEL_PFNGLSECONDARYCOLOR3UIVEXTPROC		nglSecondaryColor3uivEXT;
NEL_PFNGLSECONDARYCOLOR3USEXTPROC		nglSecondaryColor3usEXT;
NEL_PFNGLSECONDARYCOLOR3USVEXTPROC		nglSecondaryColor3usvEXT;
NEL_PFNGLSECONDARYCOLORPOINTEREXTPROC	nglSecondaryColorPointerEXT;


// BlendColor extension
//========================
NEL_PFNGLBLENDCOLOREXTPROC				nglBlendColorEXT;


// GL_ATI_vertex_array_object extension
//========================
NEL_PFNGLNEWOBJECTBUFFERATIPROC			nglNewObjectBufferATI;
NEL_PFNGLISOBJECTBUFFERATIPROC			nglIsObjectBufferATI;
NEL_PFNGLUPDATEOBJECTBUFFERATIPROC		nglUpdateObjectBufferATI;
NEL_PFNGLGETOBJECTBUFFERFVATIPROC		nglGetObjectBufferfvATI;
NEL_PFNGLGETOBJECTBUFFERIVATIPROC		nglGetObjectBufferivATI;
NEL_PFNGLDELETEOBJECTBUFFERATIPROC		nglDeleteObjectBufferATI;
NEL_PFNGLARRAYOBJECTATIPROC				nglArrayObjectATI;
NEL_PFNGLGETARRAYOBJECTFVATIPROC		nglGetArrayObjectfvATI;
NEL_PFNGLGETARRAYOBJECTIVATIPROC		nglGetArrayObjectivATI;
NEL_PFNGLVARIANTARRAYOBJECTATIPROC		nglVariantArrayObjectATI;
NEL_PFNGLGETVARIANTARRAYOBJECTFVATIPROC	nglGetVariantArrayObjectfvATI;
NEL_PFNGLGETVARIANTARRAYOBJECTIVATIPROC	nglGetVariantArrayObjectivATI;

// GL_ATI_map_object_buffer
//===================================

NEL_PFNGLMAPOBJECTBUFFERATIPROC   nglMapObjectBufferATI;
NEL_PFNGLUNMAPOBJECTBUFFERATIPROC nglUnmapObjectBufferATI;


// GL_ATI_vertex_attrib_array_object
//==================================
NEL_PFNGLVERTEXATTRIBARRAYOBJECTATIPROC nglVertexAttribArrayObjectATI;
NEL_PFNGLGETVERTEXATTRIBARRAYOBJECTFVATIPROC nglGetVertexAttribArrayObjectfvATI;
NEL_PFNGLGETVERTEXATTRIBARRAYOBJECTIVATIPROC nglGetVertexAttribArrayObjectivATI;


// GL_ATI_envmap_bumpmap extension
//========================
PFNGLTEXBUMPPARAMETERIVATIPROC nglTexBumpParameterivATI;
PFNGLTEXBUMPPARAMETERFVATIPROC nglTexBumpParameterfvATI;
PFNGLGETTEXBUMPPARAMETERIVATIPROC nglGetTexBumpParameterivATI;
PFNGLGETTEXBUMPPARAMETERFVATIPROC nglGetTexBumpParameterfvATI;

// GL_ATI_fragment_shader extension
//===================================
NEL_PFNGLGENFRAGMENTSHADERSATIPROC			nglGenFragmentShadersATI;
NEL_PFNGLBINDFRAGMENTSHADERATIPROC			nglBindFragmentShaderATI;
NEL_PFNGLDELETEFRAGMENTSHADERATIPROC			nglDeleteFragmentShaderATI;
NEL_PFNGLBEGINFRAGMENTSHADERATIPROC			nglBeginFragmentShaderATI;
NEL_PFNGLENDFRAGMENTSHADERATIPROC			nglEndFragmentShaderATI;
NEL_PFNGLPASSTEXCOORDATIPROC					nglPassTexCoordATI;
NEL_PFNGLSAMPLEMAPATIPROC					nglSampleMapATI;
NEL_PFNGLCOLORFRAGMENTOP1ATIPROC				nglColorFragmentOp1ATI;
NEL_PFNGLCOLORFRAGMENTOP2ATIPROC				nglColorFragmentOp2ATI;
NEL_PFNGLCOLORFRAGMENTOP3ATIPROC				nglColorFragmentOp3ATI;
NEL_PFNGLALPHAFRAGMENTOP1ATIPROC				nglAlphaFragmentOp1ATI;
NEL_PFNGLALPHAFRAGMENTOP2ATIPROC				nglAlphaFragmentOp2ATI;
NEL_PFNGLALPHAFRAGMENTOP3ATIPROC				nglAlphaFragmentOp3ATI;
NEL_PFNGLSETFRAGMENTSHADERCONSTANTATIPROC	nglSetFragmentShaderConstantATI;

// GL_ARB_fragment_program
//===================================

// the following functions are the sames than with GL_ARB_vertex_program

//NEL_PFNGLPROGRAMSTRINGARBPROC nglProgramStringARB;
//NEL_PFNGLBINDPROGRAMARBPROC nglBindProgramARB;
//NEL_PFNGLDELETEPROGRAMSARBPROC nglDeleteProgramsARB;
//NEL_PFNGLGENPROGRAMSARBPROC nglGenProgramsARB;
//NEL_PFNGLPROGRAMENVPARAMETER4DARBPROC nglProgramEnvParameter4dARB;
//NEL_PFNGLPROGRAMENVPARAMETER4DVARBPROC nglProgramEnvParameter4dvARB;
//NEL_PFNGLPROGRAMENVPARAMETER4FARBPROC nglProgramEnvParameter4fARB;
//NEL_PFNGLPROGRAMENVPARAMETER4FVARBPROC nglProgramEnvParameter4fvARB;
NEL_PFNGLPROGRAMLOCALPARAMETER4DARBPROC nglGetProgramLocalParameter4dARB;
NEL_PFNGLPROGRAMLOCALPARAMETER4DVARBPROC nglGetProgramLocalParameter4dvARB;
NEL_PFNGLPROGRAMLOCALPARAMETER4FARBPROC nglGetProgramLocalParameter4fARB;
NEL_PFNGLPROGRAMLOCALPARAMETER4FVARBPROC nglGetProgramLocalParameter4fvARB;
//NEL_PFNGLGETPROGRAMENVPARAMETERDVARBPROC nglGetProgramEnvParameterdvARB;
//NEL_PFNGLGETPROGRAMENVPARAMETERFVARBPROC nglGetProgramEnvParameterfvARB;
//NEL_PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC nglGetProgramLocalParameterdvARB;
//NEL_PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC nglGetProgramLocalParameterfvARB;
//NEL_PFNGLGETPROGRAMIVARBPROC nglGetProgramivARB;
//NEL_PFNGLGETPROGRAMSTRINGARBPROC nglGetProgramStringARB;
//NEL_PFNGLISPROGRAMARBPROC nglIsProgramARB;

// GL_ARB_vertex_buffer_object
//==================================
PFNGLBINDBUFFERARBPROC nglBindBufferARB;
PFNGLDELETEBUFFERSARBPROC nglDeleteBuffersARB;
PFNGLGENBUFFERSARBPROC nglGenBuffersARB;
PFNGLISBUFFERARBPROC nglIsBufferARB;
PFNGLBUFFERDATAARBPROC nglBufferDataARB;
PFNGLBUFFERSUBDATAARBPROC nglBufferSubDataARB;
PFNGLGETBUFFERSUBDATAARBPROC nglGetBufferSubDataARB;
PFNGLMAPBUFFERARBPROC nglMapBufferARB;
PFNGLUNMAPBUFFERARBPROC nglUnmapBufferARB;
PFNGLGETBUFFERPARAMETERIVARBPROC nglGetBufferParameterivARB;
PFNGLGETBUFFERPOINTERVARBPROC nglGetBufferPointervARB;


// GL_ARB_vertex_program
//==================================
PFNGLVERTEXATTRIB1SARBPROC nglVertexAttrib1sARB;
PFNGLVERTEXATTRIB1FARBPROC nglVertexAttrib1fARB;
PFNGLVERTEXATTRIB1DARBPROC nglVertexAttrib1dARB;
PFNGLVERTEXATTRIB2SARBPROC nglVertexAttrib2sARB;
PFNGLVERTEXATTRIB2FARBPROC nglVertexAttrib2fARB;
PFNGLVERTEXATTRIB2DARBPROC nglVertexAttrib2dARB;
PFNGLVERTEXATTRIB3SARBPROC nglVertexAttrib3sARB;
PFNGLVERTEXATTRIB3FARBPROC nglVertexAttrib3fARB;
PFNGLVERTEXATTRIB3DARBPROC nglVertexAttrib3dARB;
PFNGLVERTEXATTRIB4SARBPROC nglVertexAttrib4sARB;
PFNGLVERTEXATTRIB4FARBPROC nglVertexAttrib4fARB;
PFNGLVERTEXATTRIB4DARBPROC nglVertexAttrib4dARB;
PFNGLVERTEXATTRIB4NUBARBPROC nglVertexAttrib4NubARB;
PFNGLVERTEXATTRIB1SVARBPROC nglVertexAttrib1svARB;
PFNGLVERTEXATTRIB1FVARBPROC nglVertexAttrib1fvARB;
PFNGLVERTEXATTRIB1DVARBPROC nglVertexAttrib1dvARB;
PFNGLVERTEXATTRIB2SVARBPROC nglVertexAttrib2svARB;
PFNGLVERTEXATTRIB2FVARBPROC nglVertexAttrib2fvARB;
PFNGLVERTEXATTRIB2DVARBPROC nglVertexAttrib2dvARB;
PFNGLVERTEXATTRIB3SVARBPROC nglVertexAttrib3svARB;
PFNGLVERTEXATTRIB3FVARBPROC nglVertexAttrib3fvARB;
PFNGLVERTEXATTRIB3DVARBPROC nglVertexAttrib3dvARB;
PFNGLVERTEXATTRIB4BVARBPROC nglVertexAttrib4bvARB;
PFNGLVERTEXATTRIB4SVARBPROC nglVertexAttrib4svARB;
PFNGLVERTEXATTRIB4IVARBPROC nglVertexAttrib4ivARB;
PFNGLVERTEXATTRIB4UBVARBPROC nglVertexAttrib4ubvARB;
PFNGLVERTEXATTRIB4USVARBPROC nglVertexAttrib4usvARB;
PFNGLVERTEXATTRIB4UIVARBPROC nglVertexAttrib4uivARB;
PFNGLVERTEXATTRIB4FVARBPROC nglVertexAttrib4fvARB;
PFNGLVERTEXATTRIB4DVARBPROC nglVertexAttrib4dvARB;
PFNGLVERTEXATTRIB4NBVARBPROC nglVertexAttrib4NbvARB;
PFNGLVERTEXATTRIB4NSVARBPROC nglVertexAttrib4NsvARB;
PFNGLVERTEXATTRIB4NIVARBPROC nglVertexAttrib4NivARB;
PFNGLVERTEXATTRIB4NUBVARBPROC nglVertexAttrib4NubvARB;
PFNGLVERTEXATTRIB4NUSVARBPROC nglVertexAttrib4NusvARB;
PFNGLVERTEXATTRIB4NUIVARBPROC nglVertexAttrib4NuivARB;
PFNGLVERTEXATTRIBPOINTERARBPROC nglVertexAttribPointerARB;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC nglEnableVertexAttribArrayARB;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC nglDisableVertexAttribArrayARB;
PFNGLPROGRAMSTRINGARBPROC nglProgramStringARB;
PFNGLBINDPROGRAMARBPROC nglBindProgramARB;
PFNGLDELETEPROGRAMSARBPROC nglDeleteProgramsARB;
PFNGLGENPROGRAMSARBPROC nglGenProgramsARB;
PFNGLPROGRAMENVPARAMETER4FARBPROC nglProgramEnvParameter4fARB;
PFNGLPROGRAMENVPARAMETER4DARBPROC nglProgramEnvParameter4dARB;
PFNGLPROGRAMENVPARAMETER4FVARBPROC nglProgramEnvParameter4fvARB;
PFNGLPROGRAMENVPARAMETER4DVARBPROC nglProgramEnvParameter4dvARB;
PFNGLPROGRAMLOCALPARAMETER4FARBPROC nglProgramLocalParameter4fARB;
PFNGLPROGRAMLOCALPARAMETER4DARBPROC nglProgramLocalParameter4dARB;
PFNGLPROGRAMLOCALPARAMETER4FVARBPROC nglProgramLocalParameter4fvARB;
PFNGLPROGRAMLOCALPARAMETER4DVARBPROC nglProgramLocalParameter4dvARB;
PFNGLGETPROGRAMENVPARAMETERFVARBPROC nglGetProgramEnvParameterfvARB;
PFNGLGETPROGRAMENVPARAMETERDVARBPROC nglGetProgramEnvParameterdvARB;
PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC nglGetProgramLocalParameterfvARB;
PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC nglGetProgramLocalParameterdvARB;
PFNGLGETPROGRAMIVARBPROC nglGetProgramivARB;
PFNGLGETPROGRAMSTRINGARBPROC nglGetProgramStringARB;
PFNGLGETVERTEXATTRIBDVARBPROC nglGetVertexAttribdvARB;
PFNGLGETVERTEXATTRIBFVARBPROC nglGetVertexAttribfvARB;
PFNGLGETVERTEXATTRIBIVARBPROC nglGetVertexAttribivARB;
PFNGLGETVERTEXATTRIBPOINTERVARBPROC nglGetVertexAttribPointervARB;
PFNGLISPROGRAMARBPROC nglIsProgramARB;

// NV_occlusion_query
//=====================
NEL_PFNGLGENOCCLUSIONQUERIESNVPROC nglGenOcclusionQueriesNV;
NEL_PFNGLDELETEOCCLUSIONQUERIESNVPROC nglDeleteOcclusionQueriesNV;
NEL_PFNGLISOCCLUSIONQUERYNVPROC nglIsOcclusionQueryNV;
NEL_PFNGLBEGINOCCLUSIONQUERYNVPROC nglBeginOcclusionQueryNV;
NEL_PFNGLENDOCCLUSIONQUERYNVPROC nglEndOcclusionQueryNV;
NEL_PFNGLGETOCCLUSIONQUERYIVNVPROC nglGetOcclusionQueryivNV;
NEL_PFNGLGETOCCLUSIONQUERYUIVNVPROC nglGetOcclusionQueryuivNV;

// GL_EXT_framebuffer_object
//=====================
NEL_PFNGLISRENDERBUFFEREXTPROC			nglIsRenderbufferEXT;
NEL_PFNGLISFRAMEBUFFEREXTPROC			nglIsFramebufferEXT;
NEL_PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC	nglCheckFramebufferStatusEXT;
NEL_PFNGLGENFRAMEBUFFERSEXTPROC			nglGenFramebuffersEXT;
NEL_PFNGLBINDFRAMEBUFFEREXTPROC			nglBindFramebufferEXT;
NEL_PFNGLFRAMEBUFFERTEXTURE2DEXTPROC	nglFramebufferTexture2DEXT;
NEL_PFNGLGENRENDERBUFFERSEXTPROC		nglGenRenderbuffersEXT;
NEL_PFNGLBINDRENDERBUFFEREXTPROC		nglBindRenderbufferEXT;
NEL_PFNGLRENDERBUFFERSTORAGEEXTPROC		nglRenderbufferStorageEXT;
NEL_PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC	nglFramebufferRenderbufferEXT;
NEL_PFNGLDELETERENDERBUFFERSEXTPROC		nglDeleteRenderbuffersEXT;
NEL_PFNGLDELETEFRAMEBUFFERSEXTPROC		nglDeleteFramebuffersEXT;



// Pbuffer extension
//==================
#ifdef NL_OS_WINDOWS
PFNWGLCREATEPBUFFERARBPROC			wglCreatePbufferARB;
PFNWGLGETPUFFERDCARBPROC			wglGetPbufferDCARB;
PFNWGLRELEASEPUFFERDCARBPROC		wglReleasePbufferDCARB;
PFNWGLDESTROYPUFFERARBPROC			wglDestroyPbufferARB;
PFNWGLQUERYPBUFFERARBPROC			wglQueryPbufferARB;
#endif


// Get Pixel format extension
//===========================
#ifdef NL_OS_WINDOWS
PFNWGLGETPIXELFORMATATTRIBIVARBPROC	wglGetPixelFormatAttribivARB;
PFNWGLGETPIXELFORMATATTRIBFVARBPROC	wglGetPixelFormatAttribfvARB;
PFNWGLCHOOSEPIXELFORMATARBPROC		wglChoosePixelFormatARB;
#endif


// Swap control extension
//===========================
#ifdef NL_OS_WINDOWS
PFNWGLSWAPINTERVALEXTPROC			wglSwapIntervalEXT;
PFNWGLGETSWAPINTERVALEXTPROC		wglGetSwapIntervalEXT;
#endif

// WGL_ARB_extensions_string
#ifdef NL_OS_WINDOWS
PFNWGFGETEXTENSIONSSTRINGARB		wglGetExtensionsStringARB;
#endif





// ***************************************************************************
// ***************************************************************************
// ***************************************************************************
// ***************************************************************************


namespace	NL3D
{


// ***************************************************************************
// Extensions registrations, and Windows function Registration.


// *********************************
static bool setupARBMultiTexture(const char	*glext)
{
	H_AUTO_OGL(setupARBMultiTexture)
	if(strstr(glext, "GL_ARB_multitexture")==NULL)
		return false;

	if(!(nglActiveTextureARB=(NEL_PFNGLACTIVETEXTUREARBPROC)nelglGetProcAddress("glActiveTextureARB")))return false;
	if(!(nglClientActiveTextureARB=(NEL_PFNGLCLIENTACTIVETEXTUREARBPROC)nelglGetProcAddress("glClientActiveTextureARB")))return false;

	if(!(nglMultiTexCoord1sARB=(NEL_PFNGLMULTITEXCOORD1SARBPROC)nelglGetProcAddress("glMultiTexCoord1sARB")))return false;
	if(!(nglMultiTexCoord1iARB=(NEL_PFNGLMULTITEXCOORD1IARBPROC)nelglGetProcAddress("glMultiTexCoord1iARB")))return false;
	if(!(nglMultiTexCoord1fARB=(NEL_PFNGLMULTITEXCOORD1FARBPROC)nelglGetProcAddress("glMultiTexCoord1fARB")))return false;
	if(!(nglMultiTexCoord1dARB=(NEL_PFNGLMULTITEXCOORD1DARBPROC)nelglGetProcAddress("glMultiTexCoord1dARB")))return false;
	if(!(nglMultiTexCoord2sARB=(NEL_PFNGLMULTITEXCOORD2SARBPROC)nelglGetProcAddress("glMultiTexCoord2sARB")))return false;
	if(!(nglMultiTexCoord2iARB=(NEL_PFNGLMULTITEXCOORD2IARBPROC)nelglGetProcAddress("glMultiTexCoord2iARB")))return false;
	if(!(nglMultiTexCoord2fARB=(NEL_PFNGLMULTITEXCOORD2FARBPROC)nelglGetProcAddress("glMultiTexCoord2fARB")))return false;
	if(!(nglMultiTexCoord2dARB=(NEL_PFNGLMULTITEXCOORD2DARBPROC)nelglGetProcAddress("glMultiTexCoord2dARB")))return false;
	if(!(nglMultiTexCoord3sARB=(NEL_PFNGLMULTITEXCOORD3SARBPROC)nelglGetProcAddress("glMultiTexCoord3sARB")))return false;
	if(!(nglMultiTexCoord3iARB=(NEL_PFNGLMULTITEXCOORD3IARBPROC)nelglGetProcAddress("glMultiTexCoord3iARB")))return false;
	if(!(nglMultiTexCoord3fARB=(NEL_PFNGLMULTITEXCOORD3FARBPROC)nelglGetProcAddress("glMultiTexCoord3fARB")))return false;
	if(!(nglMultiTexCoord3dARB=(NEL_PFNGLMULTITEXCOORD3DARBPROC)nelglGetProcAddress("glMultiTexCoord3dARB")))return false;
	if(!(nglMultiTexCoord4sARB=(NEL_PFNGLMULTITEXCOORD4SARBPROC)nelglGetProcAddress("glMultiTexCoord4sARB")))return false;
	if(!(nglMultiTexCoord4iARB=(NEL_PFNGLMULTITEXCOORD4IARBPROC)nelglGetProcAddress("glMultiTexCoord4iARB")))return false;
	if(!(nglMultiTexCoord4fARB=(NEL_PFNGLMULTITEXCOORD4FARBPROC)nelglGetProcAddress("glMultiTexCoord4fARB")))return false;
	if(!(nglMultiTexCoord4dARB=(NEL_PFNGLMULTITEXCOORD4DARBPROC)nelglGetProcAddress("glMultiTexCoord4dARB")))return false;

	if(!(nglMultiTexCoord1svARB=(NEL_PFNGLMULTITEXCOORD1SVARBPROC)nelglGetProcAddress("glMultiTexCoord1svARB")))return false;
	if(!(nglMultiTexCoord1ivARB=(NEL_PFNGLMULTITEXCOORD1IVARBPROC)nelglGetProcAddress("glMultiTexCoord1ivARB")))return false;
	if(!(nglMultiTexCoord1fvARB=(NEL_PFNGLMULTITEXCOORD1FVARBPROC)nelglGetProcAddress("glMultiTexCoord1fvARB")))return false;
	if(!(nglMultiTexCoord1dvARB=(NEL_PFNGLMULTITEXCOORD1DVARBPROC)nelglGetProcAddress("glMultiTexCoord1dvARB")))return false;
	if(!(nglMultiTexCoord2svARB=(NEL_PFNGLMULTITEXCOORD2SVARBPROC)nelglGetProcAddress("glMultiTexCoord2svARB")))return false;
	if(!(nglMultiTexCoord2ivARB=(NEL_PFNGLMULTITEXCOORD2IVARBPROC)nelglGetProcAddress("glMultiTexCoord2ivARB")))return false;
	if(!(nglMultiTexCoord2fvARB=(NEL_PFNGLMULTITEXCOORD2FVARBPROC)nelglGetProcAddress("glMultiTexCoord2fvARB")))return false;
	if(!(nglMultiTexCoord2dvARB=(NEL_PFNGLMULTITEXCOORD2DVARBPROC)nelglGetProcAddress("glMultiTexCoord2dvARB")))return false;
	if(!(nglMultiTexCoord3svARB=(NEL_PFNGLMULTITEXCOORD3SVARBPROC)nelglGetProcAddress("glMultiTexCoord3svARB")))return false;
	if(!(nglMultiTexCoord3ivARB=(NEL_PFNGLMULTITEXCOORD3IVARBPROC)nelglGetProcAddress("glMultiTexCoord3ivARB")))return false;
	if(!(nglMultiTexCoord3fvARB=(NEL_PFNGLMULTITEXCOORD3FVARBPROC)nelglGetProcAddress("glMultiTexCoord3fvARB")))return false;
	if(!(nglMultiTexCoord3dvARB=(NEL_PFNGLMULTITEXCOORD3DVARBPROC)nelglGetProcAddress("glMultiTexCoord3dvARB")))return false;
	if(!(nglMultiTexCoord4svARB=(NEL_PFNGLMULTITEXCOORD4SVARBPROC)nelglGetProcAddress("glMultiTexCoord4svARB")))return false;
	if(!(nglMultiTexCoord4ivARB=(NEL_PFNGLMULTITEXCOORD4IVARBPROC)nelglGetProcAddress("glMultiTexCoord4ivARB")))return false;
	if(!(nglMultiTexCoord4fvARB=(NEL_PFNGLMULTITEXCOORD4FVARBPROC)nelglGetProcAddress("glMultiTexCoord4fvARB")))return false;
	if(!(nglMultiTexCoord4dvARB=(NEL_PFNGLMULTITEXCOORD4DVARBPROC)nelglGetProcAddress("glMultiTexCoord4dvARB")))return false;

	return true;
}


// *********************************
static bool setupEXTTextureEnvCombine(const char	*glext)
{
	H_AUTO_OGL(setupEXTTextureEnvCombine)
	if(strstr(glext, "GL_EXT_texture_env_combine")==NULL)
		return false;

	return true;
}


// *********************************
static bool	setupARBTextureCompression(const char	*glext)
{
	H_AUTO_OGL(setupARBTextureCompression)
	if(strstr(glext, "GL_ARB_texture_compression")==NULL)
	  return false;

	if(!(nglCompressedTexImage3DARB=(NEL_PFNGLCOMPRESSEDTEXIMAGE3DARBPROC)nelglGetProcAddress("glCompressedTexImage3DARB")))return false;
	if(!(nglCompressedTexImage2DARB=(NEL_PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)nelglGetProcAddress("glCompressedTexImage2DARB")))return false;
	if(!(nglCompressedTexImage1DARB=(NEL_PFNGLCOMPRESSEDTEXIMAGE1DARBPROC)nelglGetProcAddress("glCompressedTexImage1DARB")))return false;
	if(!(nglCompressedTexSubImage3DARB=(NEL_PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC)nelglGetProcAddress("glCompressedTexSubImage3DARB")))return false;
	if(!(nglCompressedTexSubImage2DARB=(NEL_PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC)nelglGetProcAddress("glCompressedTexSubImage2DARB")))return false;
	if(!(nglCompressedTexSubImage1DARB=(NEL_PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC)nelglGetProcAddress("glCompressedTexSubImage1DARB")))return false;
	if(!(nglGetCompressedTexImageARB=(NEL_PFNGLGETCOMPRESSEDTEXIMAGEARBPROC)nelglGetProcAddress("glGetCompressedTexImageARB")))return false;

	return true;
}


// *********************************
static bool	setupNVVertexArrayRange(const char	*glext)
{
	H_AUTO_OGL(setupNVVertexArrayRange)
	// \todo_yoyo: TODO_LINUX: for now, just return false.
#ifndef NL_OS_WINDOWS
	return false;
#endif


	// Test if VAR is present.
	if(strstr(glext, "GL_NV_vertex_array_range")==NULL)
		return false;
	// Tess Fence too.
	if( strstr(glext, "GL_NV_fence")==NULL )
		return false;


	// Get VAR adress.
	if(!(nglFlushVertexArrayRangeNV=(NEL_PFNGLFLUSHVERTEXARRAYRANGENVPROC)nelglGetProcAddress("glFlushVertexArrayRangeNV")))return false;
	if(!(nglVertexArrayRangeNV=(NEL_PFNGLVERTEXARRAYRANGENVPROC)nelglGetProcAddress("glVertexArrayRangeNV")))return false;
#ifdef NL_OS_WINDOWS
	if(!(wglAllocateMemoryNV= (PFNWGLALLOCATEMEMORYNVPROC)nelglGetProcAddress("wglAllocateMemoryNV")))return false;
	if(!(wglFreeMemoryNV= (PFNWGLFREEMEMORYNVPROC)nelglGetProcAddress("wglFreeMemoryNV")))return false;
#endif

	// Get fence adress.
	if(!(nglDeleteFencesNV= (NEL_PFNGLDELETEFENCESNVPROC)nelglGetProcAddress("glDeleteFencesNV")))return false;
	if(!(nglGenFencesNV= (NEL_PFNGLGENFENCESNVPROC)nelglGetProcAddress("glGenFencesNV")))return false;
	if(!(nglIsFenceNV= (NEL_PFNGLISFENCENVPROC)nelglGetProcAddress("glIsFenceNV")))return false;
	if(!(nglTestFenceNV= (NEL_PFNGLTESTFENCENVPROC)nelglGetProcAddress("glTestFenceNV")))return false;
	if(!(nglGetFenceivNV= (NEL_PFNGLGETFENCEIVNVPROC)nelglGetProcAddress("glGetFenceivNV")))return false;
	if(!(nglFinishFenceNV= (NEL_PFNGLFINISHFENCENVPROC)nelglGetProcAddress("glFinishFenceNV")))return false;
	if(!(nglSetFenceNV= (NEL_PFNGLSETFENCENVPROC)nelglGetProcAddress("glSetFenceNV")))return false;


	return true;
}


// *********************************
static bool	setupEXTTextureCompressionS3TC(const char	*glext)
{
	H_AUTO_OGL(setupEXTTextureCompressionS3TC)
	if(strstr(glext, "GL_EXT_texture_compression_s3tc")==NULL)
		return false;

	return true;
}


// *********************************
static bool	setupEXTVertexWeighting(const char	*glext)
{
	H_AUTO_OGL(setupEXTVertexWeighting)
	if(strstr (glext, "GL_EXT_vertex_weighting")==NULL)
		return false;


	if(!(nglVertexWeightfEXT=(NEL_PFNGLVERTEXWEIGHTFEXTPROC)nelglGetProcAddress("glVertexWeightfEXT")))return false;
	if(!(nglVertexWeightfvEXT=(NEL_PFNGLVERTEXWEIGHTFVEXTPROC)nelglGetProcAddress("glVertexWeightfvEXT")))return false;
	if(!(nglVertexWeightPointerEXT=(NEL_PFNGLVERTEXWEIGHTPOINTEREXTPROC)nelglGetProcAddress("glVertexWeightPointerEXT")))return false;

	return true;
}


// *********************************
static bool	setupEXTSeparateSpecularColor(const char	*glext)
{
	H_AUTO_OGL(setupEXTSeparateSpecularColor)
	if(strstr(glext, "GL_EXT_separate_specular_color")==NULL)
		return false;

	return true;
}


// *********************************
static bool	setupNVTextureEnvCombine4(const char	*glext)
{
	H_AUTO_OGL(setupNVTextureEnvCombine4)
	if(strstr(glext, "GL_NV_texture_env_combine4")==NULL)
		return false;

	return true;
}

// *********************************
static bool	setupATITextureEnvCombine3(const char	*glext)
{
	H_AUTO_OGL(setupATITextureEnvCombine3)
	if(strstr(glext, "GL_ATI_texture_env_combine3")==NULL)
		return false;

	return true;
}

// *********************************
static bool	setupATIXTextureEnvRoute(const char *glext)
{
	H_AUTO_OGL(setupATIXTextureEnvRoute)
	return false;
	/*if(strstr(glext, "GL_ATIX_texture_env_route")==NULL)
		return false;*/
	
	return true;
}

// *********************************
static bool	setupATIEnvMapBumpMap(const char	*glext)
{
	H_AUTO_OGL(setupATIEnvMapBumpMap)
	if(strstr(glext, "GL_ATI_envmap_bumpmap")==NULL)
		return false;
	if (!(nglTexBumpParameterivATI = (PFNGLTEXBUMPPARAMETERIVATIPROC) nelglGetProcAddress("glTexBumpParameterivATI"))) return false;
	if (!(nglTexBumpParameterfvATI = (PFNGLTEXBUMPPARAMETERFVATIPROC) nelglGetProcAddress("glTexBumpParameterfvATI"))) return false;
	if (!(nglGetTexBumpParameterivATI = (PFNGLGETTEXBUMPPARAMETERIVATIPROC) nelglGetProcAddress("glGetTexBumpParameterivATI"))) return false;
	if (!(nglGetTexBumpParameterfvATI = (PFNGLGETTEXBUMPPARAMETERFVATIPROC) nelglGetProcAddress("glGetTexBumpParameterfvATI"))) return false;		

	return true;
}

// *********************************
static bool	setupARBTextureCubeMap(const char	*glext)
{
	H_AUTO_OGL(setupARBTextureCubeMap)
	if(strstr(glext, "GL_ARB_texture_cube_map")==NULL)
		return false;

	return true;
}


// *********************************
static bool	setupNVVertexProgram(const char	*glext)
{	
	H_AUTO_OGL(setupNVVertexProgram)
	if(strstr(glext, "GL_NV_vertex_program")==NULL)
		return false;


	if(!(nglAreProgramsResidentNV= (NEL_PFNGLAREPROGRAMSRESIDENTNVPROC)nelglGetProcAddress("glAreProgramsResidentNV"))) return false;
	if(!(nglBindProgramNV= (NEL_PFNGLBINDPROGRAMNVPROC)nelglGetProcAddress("glBindProgramNV"))) return false;
	if(!(nglDeleteProgramsNV= (NEL_PFNGLDELETEPROGRAMSNVPROC)nelglGetProcAddress("glDeleteProgramsNV"))) return false;
	if(!(nglExecuteProgramNV= (NEL_PFNGLEXECUTEPROGRAMNVPROC)nelglGetProcAddress("glExecuteProgramNV"))) return false;
	if(!(nglGenProgramsNV= (NEL_PFNGLGENPROGRAMSNVPROC)nelglGetProcAddress("glGenProgramsNV"))) return false;
	if(!(nglGetProgramParameterdvNV= (NEL_PFNGLGETPROGRAMPARAMETERDVNVPROC)nelglGetProcAddress("glGetProgramParameterdvNV"))) return false;
	if(!(nglGetProgramParameterfvNV= (NEL_PFNGLGETPROGRAMPARAMETERFVNVPROC)nelglGetProcAddress("glGetProgramParameterfvNV"))) return false;
	if(!(nglGetProgramivNV= (NEL_PFNGLGETPROGRAMIVNVPROC)nelglGetProcAddress("glGetProgramivNV"))) return false;
	if(!(nglGetProgramStringNV= (NEL_PFNGLGETPROGRAMSTRINGNVPROC)nelglGetProcAddress("glGetProgramStringNV"))) return false;
	if(!(nglGetTrackMatrixivNV= (NEL_PFNGLGETTRACKMATRIXIVNVPROC)nelglGetProcAddress("glGetTrackMatrixivNV"))) return false;
	if(!(nglGetVertexAttribdvNV= (NEL_PFNGLGETVERTEXATTRIBDVNVPROC)nelglGetProcAddress("glGetVertexAttribdvNV"))) return false;
	if(!(nglGetVertexAttribfvNV= (NEL_PFNGLGETVERTEXATTRIBFVNVPROC)nelglGetProcAddress("glGetVertexAttribfvNV"))) return false;
	if(!(nglGetVertexAttribivNV= (NEL_PFNGLGETVERTEXATTRIBIVNVPROC)nelglGetProcAddress("glGetVertexAttribivNV"))) return false;
	if(!(nglGetVertexAttribPointervNV= (NEL_PFNGLGETVERTEXATTRIBPOINTERVNVPROC)nelglGetProcAddress("glGetVertexAttribPointervNV"))) return false;
	if(!(nglIsProgramNV= (NEL_PFNGLISPROGRAMNVPROC)nelglGetProcAddress("glIsProgramNV"))) return false;
	if(!(nglLoadProgramNV= (NEL_PFNGLLOADPROGRAMNVPROC)nelglGetProcAddress("glLoadProgramNV"))) return false;
	if(!(nglProgramParameter4dNV= (NEL_PFNGLPROGRAMPARAMETER4DNVPROC)nelglGetProcAddress("glProgramParameter4dNV"))) return false;
	if(!(nglProgramParameter4dvNV= (NEL_PFNGLPROGRAMPARAMETER4DVNVPROC)nelglGetProcAddress("glProgramParameter4dvNV"))) return false;
	if(!(nglProgramParameter4fNV= (NEL_PFNGLPROGRAMPARAMETER4FNVPROC)nelglGetProcAddress("glProgramParameter4fNV"))) return false;
	if(!(nglProgramParameter4fvNV= (NEL_PFNGLPROGRAMPARAMETER4FVNVPROC)nelglGetProcAddress("glProgramParameter4fvNV"))) return false;
	if(!(nglProgramParameters4dvNV= (NEL_PFNGLPROGRAMPARAMETERS4DVNVPROC)nelglGetProcAddress("glProgramParameters4dvNV"))) return false;
	if(!(nglProgramParameters4fvNV= (NEL_PFNGLPROGRAMPARAMETERS4FVNVPROC)nelglGetProcAddress("glProgramParameters4fvNV"))) return false;
	if(!(nglRequestResidentProgramsNV= (NEL_PFNGLREQUESTRESIDENTPROGRAMSNVPROC)nelglGetProcAddress("glRequestResidentProgramsNV"))) return false;
	if(!(nglTrackMatrixNV= (NEL_PFNGLTRACKMATRIXNVPROC)nelglGetProcAddress("glTrackMatrixNV"))) return false;
	if(!(nglVertexAttribPointerNV= (NEL_PFNGLVERTEXATTRIBPOINTERNVPROC)nelglGetProcAddress("glVertexAttribPointerNV"))) return false;
	if(!(nglVertexAttrib1dNV= (NEL_PFNGLVERTEXATTRIB1DNVPROC)nelglGetProcAddress("glVertexAttrib1dNV"))) return false;
	if(!(nglVertexAttrib1dvNV= (NEL_PFNGLVERTEXATTRIB1DVNVPROC)nelglGetProcAddress("glVertexAttrib1dvNV"))) return false;
	if(!(nglVertexAttrib1fNV= (NEL_PFNGLVERTEXATTRIB1FNVPROC)nelglGetProcAddress("glVertexAttrib1fNV"))) return false;
	if(!(nglVertexAttrib1fvNV= (NEL_PFNGLVERTEXATTRIB1FVNVPROC)nelglGetProcAddress("glVertexAttrib1fvNV"))) return false;
	if(!(nglVertexAttrib1sNV= (NEL_PFNGLVERTEXATTRIB1SNVPROC)nelglGetProcAddress("glVertexAttrib1sNV"))) return false;
	if(!(nglVertexAttrib1svNV= (NEL_PFNGLVERTEXATTRIB1SVNVPROC)nelglGetProcAddress("glVertexAttrib1svNV"))) return false;
	if(!(nglVertexAttrib2dNV= (NEL_PFNGLVERTEXATTRIB2DNVPROC)nelglGetProcAddress("glVertexAttrib2dNV"))) return false;
	if(!(nglVertexAttrib2dvNV= (NEL_PFNGLVERTEXATTRIB2DVNVPROC)nelglGetProcAddress("glVertexAttrib2dvNV"))) return false;
	if(!(nglVertexAttrib2fNV= (NEL_PFNGLVERTEXATTRIB2FNVPROC)nelglGetProcAddress("glVertexAttrib2fNV"))) return false;
	if(!(nglVertexAttrib2fvNV= (NEL_PFNGLVERTEXATTRIB2FVNVPROC)nelglGetProcAddress("glVertexAttrib2fvNV"))) return false;
	if(!(nglVertexAttrib2sNV= (NEL_PFNGLVERTEXATTRIB2SNVPROC)nelglGetProcAddress("glVertexAttrib2sNV"))) return false;
	if(!(nglVertexAttrib2svNV= (NEL_PFNGLVERTEXATTRIB2SVNVPROC)nelglGetProcAddress("glVertexAttrib2svNV"))) return false;
	if(!(nglVertexAttrib3dNV= (NEL_PFNGLVERTEXATTRIB3DNVPROC)nelglGetProcAddress("glVertexAttrib3dNV"))) return false;
	if(!(nglVertexAttrib3dvNV= (NEL_PFNGLVERTEXATTRIB3DVNVPROC)nelglGetProcAddress("glVertexAttrib3dvNV"))) return false;
	if(!(nglVertexAttrib3fNV= (NEL_PFNGLVERTEXATTRIB3FNVPROC)nelglGetProcAddress("glVertexAttrib3fNV"))) return false;
	if(!(nglVertexAttrib3fvNV= (NEL_PFNGLVERTEXATTRIB3FVNVPROC)nelglGetProcAddress("glVertexAttrib3fvNV"))) return false;
	if(!(nglVertexAttrib3sNV= (NEL_PFNGLVERTEXATTRIB3SNVPROC)nelglGetProcAddress("glVertexAttrib3sNV"))) return false;
	if(!(nglVertexAttrib3svNV= (NEL_PFNGLVERTEXATTRIB3SVNVPROC)nelglGetProcAddress("glVertexAttrib3svNV"))) return false;
	if(!(nglVertexAttrib4dNV= (NEL_PFNGLVERTEXATTRIB4DNVPROC)nelglGetProcAddress("glVertexAttrib4dNV"))) return false;
	if(!(nglVertexAttrib4dvNV= (NEL_PFNGLVERTEXATTRIB4DVNVPROC)nelglGetProcAddress("glVertexAttrib4dvNV"))) return false;
	if(!(nglVertexAttrib4fNV= (NEL_PFNGLVERTEXATTRIB4FNVPROC)nelglGetProcAddress("glVertexAttrib4fNV"))) return false;
	if(!(nglVertexAttrib4fvNV= (NEL_PFNGLVERTEXATTRIB4FVNVPROC)nelglGetProcAddress("glVertexAttrib4fvNV"))) return false;
	if(!(nglVertexAttrib4sNV= (NEL_PFNGLVERTEXATTRIB4SNVPROC)nelglGetProcAddress("glVertexAttrib4sNV"))) return false;
	if(!(nglVertexAttrib4svNV= (NEL_PFNGLVERTEXATTRIB4SVNVPROC)nelglGetProcAddress("glVertexAttrib4svNV"))) return false;
	if(!(nglVertexAttrib4ubvNV= (NEL_PFNGLVERTEXATTRIB4UBVNVPROC)nelglGetProcAddress("glVertexAttrib4ubvNV"))) return false;
	if(!(nglVertexAttribs1dvNV= (NEL_PFNGLVERTEXATTRIBS1DVNVPROC)nelglGetProcAddress("glVertexAttribs1dvNV"))) return false;
	if(!(nglVertexAttribs1fvNV= (NEL_PFNGLVERTEXATTRIBS1FVNVPROC)nelglGetProcAddress("glVertexAttribs1fvNV"))) return false;
	if(!(nglVertexAttribs1svNV= (NEL_PFNGLVERTEXATTRIBS1SVNVPROC)nelglGetProcAddress("glVertexAttribs1svNV"))) return false;
	if(!(nglVertexAttribs2dvNV= (NEL_PFNGLVERTEXATTRIBS2DVNVPROC)nelglGetProcAddress("glVertexAttribs2dvNV"))) return false;
	if(!(nglVertexAttribs2fvNV= (NEL_PFNGLVERTEXATTRIBS2FVNVPROC)nelglGetProcAddress("glVertexAttribs2fvNV"))) return false;
	if(!(nglVertexAttribs2svNV= (NEL_PFNGLVERTEXATTRIBS2SVNVPROC)nelglGetProcAddress("glVertexAttribs2svNV"))) return false;
	if(!(nglVertexAttribs3dvNV= (NEL_PFNGLVERTEXATTRIBS3DVNVPROC)nelglGetProcAddress("glVertexAttribs3dvNV"))) return false;
	if(!(nglVertexAttribs3fvNV= (NEL_PFNGLVERTEXATTRIBS3FVNVPROC)nelglGetProcAddress("glVertexAttribs3fvNV"))) return false;
	if(!(nglVertexAttribs3svNV= (NEL_PFNGLVERTEXATTRIBS3SVNVPROC)nelglGetProcAddress("glVertexAttribs3svNV"))) return false;
	if(!(nglVertexAttribs4dvNV= (NEL_PFNGLVERTEXATTRIBS4DVNVPROC)nelglGetProcAddress("glVertexAttribs4dvNV"))) return false;
	if(!(nglVertexAttribs4fvNV= (NEL_PFNGLVERTEXATTRIBS4FVNVPROC)nelglGetProcAddress("glVertexAttribs4fvNV"))) return false;
	if(!(nglVertexAttribs4svNV= (NEL_PFNGLVERTEXATTRIBS4SVNVPROC)nelglGetProcAddress("glVertexAttribs4svNV"))) return false;
	if(!(nglVertexAttribs4ubvNV= (NEL_PFNGLVERTEXATTRIBS4UBVNVPROC)nelglGetProcAddress("glVertexAttribs4ubvNV"))) return false;


	return true;
}

// *********************************
static bool	setupEXTVertexShader(const char	*glext)
{					
	H_AUTO_OGL(setupEXTVertexShader)
	if(strstr(glext, "GL_EXT_vertex_shader")==NULL)
		return false;
	if (!(nglBeginVertexShaderEXT = (NEL_PFNGLBEGINVERTEXSHADEREXTPROC)nelglGetProcAddress("glBeginVertexShaderEXT"))) return false;
	if (!(nglEndVertexShaderEXT = (NEL_PFNGLENDVERTEXSHADEREXTPROC)nelglGetProcAddress("glEndVertexShaderEXT"))) return false;
	if (!(nglBindVertexShaderEXT = (NEL_PFNGLBINDVERTEXSHADEREXTPROC)nelglGetProcAddress("glBindVertexShaderEXT"))) return false;
	if (!(nglGenVertexShadersEXT = (NEL_PFNGLGENVERTEXSHADERSEXTPROC)nelglGetProcAddress("glGenVertexShadersEXT"))) return false;
	if (!(nglDeleteVertexShaderEXT = (NEL_PFNGLDELETEVERTEXSHADEREXTPROC)nelglGetProcAddress("glDeleteVertexShaderEXT"))) return false;
	if (!(nglShaderOp1EXT = (NEL_PFNGLSHADEROP1EXTPROC)nelglGetProcAddress("glShaderOp1EXT"))) return false;
	if (!(nglShaderOp2EXT = (NEL_PFNGLSHADEROP2EXTPROC)nelglGetProcAddress("glShaderOp2EXT"))) return false;
	if (!(nglShaderOp3EXT = (NEL_PFNGLSHADEROP3EXTPROC)nelglGetProcAddress("glShaderOp3EXT"))) return false;
	if (!(nglSwizzleEXT = (NEL_PFNGLSWIZZLEEXTPROC)nelglGetProcAddress("glSwizzleEXT"))) return false;
	if (!(nglWriteMaskEXT = (NEL_PFNGLWRITEMASKEXTPROC)nelglGetProcAddress("glWriteMaskEXT"))) return false;
	if (!(nglInsertComponentEXT = (NEL_PFNGLINSERTCOMPONENTEXTPROC)nelglGetProcAddress("glInsertComponentEXT"))) return false;
	if (!(nglExtractComponentEXT = (NEL_PFNGLEXTRACTCOMPONENTEXTPROC)nelglGetProcAddress("glExtractComponentEXT"))) return false;
	if (!(nglGenSymbolsEXT = (NEL_PFNGLGENSYMBOLSEXTPROC)nelglGetProcAddress("glGenSymbolsEXT"))) return false;
	if (!(nglSetInvariantEXT = (NEL_PFNGLSETINVARIANTEXTPROC)nelglGetProcAddress("glSetInvariantEXT"))) return false;
	if (!(nglSetLocalConstantEXT = (NEL_PFNGLSETLOCALCONSTANTEXTPROC)nelglGetProcAddress("glSetLocalConstantEXT"))) return false;
	if (!(nglVariantPointerEXT = (NEL_PFNGLVARIANTPOINTEREXTPROC)nelglGetProcAddress("glVariantPointerEXT"))) return false;
	if (!(nglEnableVariantClientStateEXT = (NEL_PFNGLENABLEVARIANTCLIENTSTATEEXTPROC)nelglGetProcAddress("glEnableVariantClientStateEXT"))) return false;
	if (!(nglDisableVariantClientStateEXT = (NEL_PFNGLDISABLEVARIANTCLIENTSTATEEXTPROC)nelglGetProcAddress("glDisableVariantClientStateEXT"))) return false;
	if (!(nglBindLightParameterEXT = (NEL_PFNGLBINDLIGHTPARAMETEREXTPROC)nelglGetProcAddress("glBindLightParameterEXT"))) return false;
	if (!(nglBindMaterialParameterEXT = (NEL_PFNGLBINDMATERIALPARAMETEREXTPROC)nelglGetProcAddress("glBindMaterialParameterEXT"))) return false;
	if (!(nglBindTexGenParameterEXT = (NEL_PFNGLBINDTEXGENPARAMETEREXTPROC)nelglGetProcAddress("glBindTexGenParameterEXT"))) return false;
	if (!(nglBindTextureUnitParameterEXT = (NEL_PFNGLBINDTEXTUREUNITPARAMETEREXTPROC)nelglGetProcAddress("glBindTextureUnitParameterEXT"))) return false;
	if (!(nglBindParameterEXT = (NEL_PFNGLBINDPARAMETEREXTPROC)nelglGetProcAddress("glBindParameterEXT"))) return false;
	if (!(nglIsVariantEnabledEXT = (NEL_PFNGLISVARIANTENABLEDEXTPROC)nelglGetProcAddress("glIsVariantEnabledEXT"))) return false;
	if (!(nglGetVariantBooleanvEXT = (NEL_PFNGLGETVARIANTBOOLEANVEXTPROC)nelglGetProcAddress("glGetVariantBooleanvEXT"))) return false;
	if (!(nglGetVariantIntegervEXT = (NEL_PFNGLGETVARIANTINTEGERVEXTPROC)nelglGetProcAddress("glGetVariantIntegervEXT"))) return false;
	if (!(nglGetVariantFloatvEXT = (NEL_PFNGLGETVARIANTFLOATVEXTPROC)nelglGetProcAddress("glGetVariantFloatvEXT"))) return false;
	if (!(nglGetVariantPointervEXT = (NEL_PFNGLGETVARIANTPOINTERVEXTPROC)nelglGetProcAddress("glGetVariantPointervEXT"))) return false;
	if (!(nglGetInvariantBooleanvEXT = (NEL_PFNGLGETINVARIANTBOOLEANVEXTPROC)nelglGetProcAddress("glGetInvariantBooleanvEXT"))) return false;
	if (!(nglGetInvariantIntegervEXT = (NEL_PFNGLGETINVARIANTINTEGERVEXTPROC)nelglGetProcAddress("glGetInvariantIntegervEXT"))) return false;
	if (!(nglGetInvariantFloatvEXT = (NEL_PFNGLGETINVARIANTFLOATVEXTPROC)nelglGetProcAddress("glGetInvariantFloatvEXT"))) return false;
	if (!(nglGetLocalConstantBooleanvEXT = (NEL_PFNGLGETLOCALCONSTANTBOOLEANVEXTPROC)nelglGetProcAddress("glGetLocalConstantBooleanvEXT"))) return false;
	if (!(nglGetLocalConstantIntegervEXT = (NEL_PFNGLGETLOCALCONSTANTINTEGERVEXTPROC)nelglGetProcAddress("glGetLocalConstantIntegervEXT"))) return false;
	if (!(nglGetLocalConstantFloatvEXT = (NEL_PFNGLGETLOCALCONSTANTFLOATVEXTPROC)nelglGetProcAddress("glGetLocalConstantFloatvEXT"))) return false;

	// we require at least 128 instructions, 15 local register (r0, r1,..,r11) + 3 temporary vector for swizzle emulation + 1 vector for indexing temp + 3 temporary scalar for LOGG, EXPP and LIT emulation,  1 address register
	// we require 11 variants (4 textures + position + normal + primary color + secondary color + weight + palette skin + fog)
	// we also require 2 local constants (0 and 1)
	// 96 invariants (c[0], c[1] ..) + 1 invariants for fog emulation (fog coordinate must range from 0 to 1 with EXT_VERTEX_shader)
	GLint numVSInst;
	glGetIntegerv(GL_MAX_OPTIMIZED_VERTEX_SHADER_INSTRUCTIONS_EXT, &numVSInst);
	if (numVSInst < 128) return false;
	//
	GLint numVSLocals;
	glGetIntegerv(GL_MAX_VERTEX_SHADER_LOCALS_EXT, &numVSLocals);
	if (numVSLocals < 4 * (12 + 4) + 1 + 3)
	{
		nlwarning("EXT_vertex_shader extension has not much register. Some vertex programm may fail loading");
		return false;
	}
	//
	GLint numVSLocalConstants;
	glGetIntegerv(GL_MAX_VERTEX_SHADER_LOCAL_CONSTANTS_EXT, &numVSLocalConstants);
	if (numVSLocalConstants < 2) return false;	
	//
	GLint numVSInvariants;
	glGetIntegerv(GL_MAX_OPTIMIZED_VERTEX_SHADER_INVARIANTS_EXT, &numVSInvariants);
	if (numVSInvariants < 96 + 1) return false;
	//	
	GLint numVSVariants;
	glGetIntegerv(GL_MAX_VERTEX_SHADER_VARIANTS_EXT, &numVSVariants);
	if (numVSInvariants < 4) return false;

	return true;
	
}



// *********************************
static bool	setupEXTSecondaryColor(const char	*glext)
{
	H_AUTO_OGL(setupEXTSecondaryColor)
	if(strstr(glext, "GL_EXT_secondary_color")==NULL)
		return false;


	if(!(nglSecondaryColor3bEXT= (NEL_PFNGLSECONDARYCOLOR3BEXTPROC)nelglGetProcAddress("glSecondaryColor3bEXT"))) return false;
	if(!(nglSecondaryColor3bvEXT= (NEL_PFNGLSECONDARYCOLOR3BVEXTPROC)nelglGetProcAddress("glSecondaryColor3bvEXT"))) return false;
	if(!(nglSecondaryColor3dEXT= (NEL_PFNGLSECONDARYCOLOR3DEXTPROC)nelglGetProcAddress("glSecondaryColor3dEXT"))) return false;
	if(!(nglSecondaryColor3dvEXT= (NEL_PFNGLSECONDARYCOLOR3DVEXTPROC)nelglGetProcAddress("glSecondaryColor3dvEXT"))) return false;
	if(!(nglSecondaryColor3fEXT= (NEL_PFNGLSECONDARYCOLOR3FEXTPROC)nelglGetProcAddress("glSecondaryColor3fEXT"))) return false;
	if(!(nglSecondaryColor3fvEXT= (NEL_PFNGLSECONDARYCOLOR3FVEXTPROC)nelglGetProcAddress("glSecondaryColor3fvEXT"))) return false;
	if(!(nglSecondaryColor3iEXT= (NEL_PFNGLSECONDARYCOLOR3IEXTPROC)nelglGetProcAddress("glSecondaryColor3iEXT"))) return false;
	if(!(nglSecondaryColor3ivEXT= (NEL_PFNGLSECONDARYCOLOR3IVEXTPROC)nelglGetProcAddress("glSecondaryColor3ivEXT"))) return false;
	if(!(nglSecondaryColor3sEXT= (NEL_PFNGLSECONDARYCOLOR3SEXTPROC)nelglGetProcAddress("glSecondaryColor3sEXT"))) return false;
	if(!(nglSecondaryColor3svEXT= (NEL_PFNGLSECONDARYCOLOR3SVEXTPROC)nelglGetProcAddress("glSecondaryColor3svEXT"))) return false;
	if(!(nglSecondaryColor3ubEXT= (NEL_PFNGLSECONDARYCOLOR3UBEXTPROC)nelglGetProcAddress("glSecondaryColor3ubEXT"))) return false;
	if(!(nglSecondaryColor3ubvEXT= (NEL_PFNGLSECONDARYCOLOR3UBVEXTPROC)nelglGetProcAddress("glSecondaryColor3ubvEXT"))) return false;
	if(!(nglSecondaryColor3uiEXT= (NEL_PFNGLSECONDARYCOLOR3UIEXTPROC)nelglGetProcAddress("glSecondaryColor3uiEXT"))) return false;
	if(!(nglSecondaryColor3uivEXT= (NEL_PFNGLSECONDARYCOLOR3UIVEXTPROC)nelglGetProcAddress("glSecondaryColor3uivEXT"))) return false;
	if(!(nglSecondaryColor3usEXT= (NEL_PFNGLSECONDARYCOLOR3USEXTPROC)nelglGetProcAddress("glSecondaryColor3usEXT"))) return false;
	if(!(nglSecondaryColor3usvEXT= (NEL_PFNGLSECONDARYCOLOR3USVEXTPROC)nelglGetProcAddress("glSecondaryColor3usvEXT"))) return false;
	if(!(nglSecondaryColorPointerEXT= (NEL_PFNGLSECONDARYCOLORPOINTEREXTPROC)nelglGetProcAddress("glSecondaryColorPointerEXT"))) return false;


	return true;
}

// *********************************
static bool	setupWGLARBPBuffer(const char	*glext)
{
	H_AUTO_OGL(setupWGLARBPBuffer)
	if(strstr(glext, "WGL_ARB_pbuffer")==NULL)
		return false;

#ifdef NL_OS_WINDOWS
	if(!(wglCreatePbufferARB= (PFNWGLCREATEPBUFFERARBPROC)nelglGetProcAddress("wglCreatePbufferARB"))) return false;
	if(!(wglGetPbufferDCARB= (PFNWGLGETPUFFERDCARBPROC)nelglGetProcAddress("wglGetPbufferDCARB"))) return false;
	if(!(wglReleasePbufferDCARB= (PFNWGLRELEASEPUFFERDCARBPROC)nelglGetProcAddress("wglReleasePbufferDCARB"))) return false;
	if(!(wglDestroyPbufferARB= (PFNWGLDESTROYPUFFERARBPROC)nelglGetProcAddress("wglDestroyPbufferARB"))) return false;
	if(!(wglQueryPbufferARB= (PFNWGLQUERYPBUFFERARBPROC)nelglGetProcAddress("wglQueryPbufferARB"))) return false;
#endif

	return true;
}

#ifdef NL_OS_WINDOWS
// *********************************
static bool	setupWGLARBPixelFormat (const char	*glext)
{
	H_AUTO_OGL(setupWGLARBPixelFormat)
	if(strstr(glext, "WGL_ARB_pixel_format")==NULL)
		return false;

	if(!(wglGetPixelFormatAttribivARB= (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)nelglGetProcAddress("wglGetPixelFormatAttribivARB"))) return false;
	if(!(wglGetPixelFormatAttribfvARB= (PFNWGLGETPIXELFORMATATTRIBFVARBPROC)nelglGetProcAddress("wglGetPixelFormatAttribfvARB"))) return false;
	if(!(wglChoosePixelFormatARB= (PFNWGLCHOOSEPIXELFORMATARBPROC)nelglGetProcAddress("wglChoosePixelFormatARB"))) return false;

	return true;
}
#endif

// *********************************
static bool	setupNVTextureShader(const char	*glext)
{
	H_AUTO_OGL(setupNVTextureShader)
	if(strstr(glext, "GL_NV_texture_shader")==NULL)
		return false;

	return true;
}


// *********************************
static bool	setupEXTBlendColor(const char	*glext)
{
	H_AUTO_OGL(setupEXTBlendColor)
	if(strstr(glext, "GL_EXT_blend_color")==NULL)
		return false;

	if(!(nglBlendColorEXT= (NEL_PFNGLBLENDCOLOREXTPROC)nelglGetProcAddress("glBlendColorEXT"))) return false;

	return true;
}


// *********************************
static bool	setupNVVertexArrayRange2(const char	*glext)
{
	H_AUTO_OGL(setupNVVertexArrayRange2)
	if(strstr(glext, "GL_NV_vertex_array_range2")==NULL)
		return false;

	return true;
}


// *********************************
static bool	setupATIVertexArrayObject(const char *glext)
{
	H_AUTO_OGL(setupATIVertexArrayObject)
	if(strstr(glext, "GL_ATI_vertex_array_object")==NULL)
		return false;
	
	if(!(nglNewObjectBufferATI= (NEL_PFNGLNEWOBJECTBUFFERATIPROC)nelglGetProcAddress("glNewObjectBufferATI"))) return false;
	if(!(nglIsObjectBufferATI= (NEL_PFNGLISOBJECTBUFFERATIPROC)nelglGetProcAddress("glIsObjectBufferATI"))) return false;
	if(!(nglUpdateObjectBufferATI= (NEL_PFNGLUPDATEOBJECTBUFFERATIPROC)nelglGetProcAddress("glUpdateObjectBufferATI"))) return false;
	if(!(nglGetObjectBufferfvATI= (NEL_PFNGLGETOBJECTBUFFERFVATIPROC)nelglGetProcAddress("glGetObjectBufferfvATI"))) return false;
	if(!(nglGetObjectBufferivATI= (NEL_PFNGLGETOBJECTBUFFERIVATIPROC)nelglGetProcAddress("glGetObjectBufferivATI"))) return false;
	
	if(!(nglDeleteObjectBufferATI= (NEL_PFNGLDELETEOBJECTBUFFERATIPROC)nelglGetProcAddress("glDeleteObjectBufferATI")))
	{
		// seems that on matrox parhelia driver, this procedure is named glFreeObjectBufferATI !!
		if(!(nglDeleteObjectBufferATI= (NEL_PFNGLDELETEOBJECTBUFFERATIPROC)nelglGetProcAddress("glFreeObjectBufferATI"))) return false;
	}
	if(!(nglArrayObjectATI= (NEL_PFNGLARRAYOBJECTATIPROC)nelglGetProcAddress("glArrayObjectATI"))) return false;
	if(!(nglGetArrayObjectfvATI= (NEL_PFNGLGETARRAYOBJECTFVATIPROC)nelglGetProcAddress("glGetArrayObjectfvATI"))) return false;
	if(!(nglGetArrayObjectivATI= (NEL_PFNGLGETARRAYOBJECTIVATIPROC)nelglGetProcAddress("glGetArrayObjectivATI"))) return false;
	if(strstr(glext, "GL_EXT_vertex_shader") != NULL)
	{	
		// the following exist only if ext vertex shader is present
		if(!(nglVariantArrayObjectATI= (NEL_PFNGLVARIANTARRAYOBJECTATIPROC)nelglGetProcAddress("glVariantArrayObjectATI"))) return false;
		if(!(nglGetVariantArrayObjectfvATI= (NEL_PFNGLGETVARIANTARRAYOBJECTFVATIPROC)nelglGetProcAddress("glGetVariantArrayObjectfvATI"))) return false;
		if(!(nglGetVariantArrayObjectivATI= (NEL_PFNGLGETVARIANTARRAYOBJECTIVATIPROC)nelglGetProcAddress("glGetVariantArrayObjectivATI"))) return false;
	}
	return true;
}


static bool	setupATIMapObjectBuffer(const char *glext)
{		
	H_AUTO_OGL(setupATIMapObjectBuffer)
	if(strstr(glext, "GL_ATI_map_object_buffer")==NULL)
		return false;
	if (!(nglMapObjectBufferATI= (NEL_PFNGLMAPOBJECTBUFFERATIPROC)nelglGetProcAddress("glMapObjectBufferATI"))) return false;
	if (!(nglUnmapObjectBufferATI= (NEL_PFNGLUNMAPOBJECTBUFFERATIPROC)nelglGetProcAddress("glUnmapObjectBufferATI"))) return false;
	return true;	
}



// *********************************
static bool	setupATIFragmentShader(const char *glext)
{
	H_AUTO_OGL(setupATIFragmentShader)
	if(strstr(glext, "GL_ATI_fragment_shader")==NULL)
		return false;
	if (!(nglGenFragmentShadersATI= (NEL_PFNGLGENFRAGMENTSHADERSATIPROC)nelglGetProcAddress("glGenFragmentShadersATI"))) return false;
	if (!(nglBindFragmentShaderATI = (NEL_PFNGLBINDFRAGMENTSHADERATIPROC)nelglGetProcAddress("glBindFragmentShaderATI"))) return false;
	if (!(nglDeleteFragmentShaderATI = (NEL_PFNGLDELETEFRAGMENTSHADERATIPROC)nelglGetProcAddress("glDeleteFragmentShaderATI"))) return false;
	if (!(nglBeginFragmentShaderATI = (NEL_PFNGLBEGINFRAGMENTSHADERATIPROC)nelglGetProcAddress("glBeginFragmentShaderATI"))) return false;
	if (!(nglEndFragmentShaderATI = (NEL_PFNGLENDFRAGMENTSHADERATIPROC)nelglGetProcAddress("glEndFragmentShaderATI"))) return false;
	if (!(nglPassTexCoordATI = (NEL_PFNGLPASSTEXCOORDATIPROC)nelglGetProcAddress("glPassTexCoordATI"))) return false;
	if (!(nglSampleMapATI = (NEL_PFNGLSAMPLEMAPATIPROC)nelglGetProcAddress("glSampleMapATI"))) return false;
	if (!(nglColorFragmentOp1ATI = (NEL_PFNGLCOLORFRAGMENTOP1ATIPROC)nelglGetProcAddress("glColorFragmentOp1ATI"))) return false;
	if (!(nglColorFragmentOp2ATI = (NEL_PFNGLCOLORFRAGMENTOP2ATIPROC)nelglGetProcAddress("glColorFragmentOp2ATI"))) return false;
	if (!(nglColorFragmentOp3ATI = (NEL_PFNGLCOLORFRAGMENTOP3ATIPROC)nelglGetProcAddress("glColorFragmentOp3ATI"))) return false;
	if (!(nglAlphaFragmentOp1ATI = (NEL_PFNGLALPHAFRAGMENTOP1ATIPROC)nelglGetProcAddress("glAlphaFragmentOp1ATI"))) return false;
	if (!(nglAlphaFragmentOp2ATI = (NEL_PFNGLALPHAFRAGMENTOP2ATIPROC)nelglGetProcAddress("glAlphaFragmentOp2ATI"))) return false;
	if (!(nglAlphaFragmentOp3ATI = (NEL_PFNGLALPHAFRAGMENTOP3ATIPROC)nelglGetProcAddress("glAlphaFragmentOp3ATI"))) return false;
	if (!(nglSetFragmentShaderConstantATI = (NEL_PFNGLSETFRAGMENTSHADERCONSTANTATIPROC)nelglGetProcAddress("glSetFragmentShaderConstantATI"))) return false;

	return true;
}

// *********************************
static bool setupATIVertexAttribArrayObject(const char *glext)
{
	H_AUTO_OGL(setupATIVertexAttribArrayObject)
	if (strstr(glext, "GL_ATI_vertex_attrib_array_object")==NULL)
		return false;
	if (!(nglVertexAttribArrayObjectATI= (NEL_PFNGLVERTEXATTRIBARRAYOBJECTATIPROC)nelglGetProcAddress("glVertexAttribArrayObjectATI"))) return false;
	if (!(nglGetVertexAttribArrayObjectfvATI= (NEL_PFNGLGETVERTEXATTRIBARRAYOBJECTFVATIPROC)nelglGetProcAddress("glGetVertexAttribArrayObjectfvATI"))) return false;
	if (!(nglGetVertexAttribArrayObjectivATI= (NEL_PFNGLGETVERTEXATTRIBARRAYOBJECTIVATIPROC)nelglGetProcAddress("glGetVertexAttribArrayObjectivATI"))) return false;
	return true;
}

// *********************************
static bool	setupARBFragmentProgram(const char *glext)
{
	H_AUTO_OGL(setupARBFragmentProgram)
	if(strstr(glext, "GL_ARB_fragment_program")==NULL)
		return false;

	if (!(nglProgramStringARB= (NEL_PFNGLPROGRAMSTRINGARBPROC)nelglGetProcAddress("glProgramStringARB"))) return false;
	if (!(nglBindProgramARB= (NEL_PFNGLBINDPROGRAMARBPROC)nelglGetProcAddress("glBindProgramARB"))) return false;
	if (!(nglDeleteProgramsARB= (NEL_PFNGLDELETEPROGRAMSARBPROC)nelglGetProcAddress("glDeleteProgramsARB"))) return false;
	if (!(nglGenProgramsARB= (NEL_PFNGLGENPROGRAMSARBPROC)nelglGetProcAddress("glGenProgramsARB"))) return false;
	if (!(nglProgramEnvParameter4dARB= (NEL_PFNGLPROGRAMENVPARAMETER4DARBPROC)nelglGetProcAddress("glProgramEnvParameter4dARB"))) return false;
	if (!(nglProgramEnvParameter4dvARB= (NEL_PFNGLPROGRAMENVPARAMETER4DVARBPROC)nelglGetProcAddress("glProgramEnvParameter4dvARB"))) return false;
	if (!(nglProgramEnvParameter4fARB= (NEL_PFNGLPROGRAMENVPARAMETER4FARBPROC)nelglGetProcAddress("glProgramEnvParameter4fARB"))) return false;
	if (!(nglProgramEnvParameter4fvARB= (NEL_PFNGLPROGRAMENVPARAMETER4FVARBPROC)nelglGetProcAddress("glProgramEnvParameter4fvARB"))) return false;
	if (!(nglGetProgramLocalParameter4dARB= (NEL_PFNGLPROGRAMLOCALPARAMETER4DARBPROC)nelglGetProcAddress("glProgramLocalParameter4dARB"))) return false;
	if (!(nglGetProgramLocalParameter4dvARB= (NEL_PFNGLPROGRAMLOCALPARAMETER4DVARBPROC)nelglGetProcAddress("glProgramLocalParameter4dvARB"))) return false;
	if (!(nglGetProgramLocalParameter4fARB= (NEL_PFNGLPROGRAMLOCALPARAMETER4FARBPROC)nelglGetProcAddress("glProgramLocalParameter4fARB"))) return false;
	if (!(nglGetProgramLocalParameter4fvARB= (NEL_PFNGLPROGRAMLOCALPARAMETER4FVARBPROC)nelglGetProcAddress("glProgramLocalParameter4fvARB"))) return false;
	if (!(nglGetProgramEnvParameterdvARB= (NEL_PFNGLGETPROGRAMENVPARAMETERDVARBPROC)nelglGetProcAddress("glGetProgramEnvParameterdvARB"))) return false;
	if (!(nglGetProgramEnvParameterfvARB= (NEL_PFNGLGETPROGRAMENVPARAMETERFVARBPROC)nelglGetProcAddress("glGetProgramEnvParameterfvARB"))) return false;
	if (!(nglGetProgramLocalParameterdvARB= (NEL_PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC)nelglGetProcAddress("glGetProgramLocalParameterdvARB"))) return false;
	if (!(nglGetProgramLocalParameterfvARB= (NEL_PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC)nelglGetProcAddress("glGetProgramLocalParameterfvARB"))) return false;
	if (!(nglGetProgramivARB= (NEL_PFNGLGETPROGRAMIVARBPROC)nelglGetProcAddress("glGetProgramivARB"))) return false;
	if (!(nglGetProgramStringARB= (NEL_PFNGLGETPROGRAMSTRINGARBPROC)nelglGetProcAddress("glGetProgramStringARB"))) return false;
	if (!(nglIsProgramARB= (NEL_PFNGLISPROGRAMARBPROC)nelglGetProcAddress("glIsProgramARB"))) return false;

	return true;
}

// ***************************************************************************
static bool	setupARBVertexBufferObject(const char	*glext)
{
	H_AUTO_OGL(setupARBVertexBufferObject)
	if(strstr(glext, "GL_ARB_vertex_buffer_object")==NULL)
		return false;
	if (!(nglBindBufferARB= (PFNGLBINDBUFFERARBPROC)nelglGetProcAddress("glBindBufferARB"))) return false;
	if (!(nglDeleteBuffersARB= (PFNGLDELETEBUFFERSARBPROC)nelglGetProcAddress("glDeleteBuffersARB"))) return false;
	if (!(nglGenBuffersARB= (PFNGLGENBUFFERSARBPROC)nelglGetProcAddress("glGenBuffersARB"))) return false;
	if (!(nglIsBufferARB= (PFNGLISBUFFERARBPROC)nelglGetProcAddress("glIsBufferARB"))) return false;
	if (!(nglBufferDataARB= (PFNGLBUFFERDATAARBPROC)nelglGetProcAddress("glBufferDataARB"))) return false;
	if (!(nglBufferSubDataARB= (PFNGLBUFFERSUBDATAARBPROC)nelglGetProcAddress("glBufferSubDataARB"))) return false;
	if (!(nglGetBufferSubDataARB= (PFNGLGETBUFFERSUBDATAARBPROC)nelglGetProcAddress("glGetBufferSubDataARB"))) return false;
	if (!(nglMapBufferARB= (PFNGLMAPBUFFERARBPROC)nelglGetProcAddress("glMapBufferARB"))) return false;
	if (!(nglUnmapBufferARB= (PFNGLUNMAPBUFFERARBPROC)nelglGetProcAddress("glUnmapBufferARB"))) return false;
	if (!(nglGetBufferParameterivARB= (PFNGLGETBUFFERPARAMETERIVARBPROC)nelglGetProcAddress("glGetBufferParameterivARB"))) return false;
	if (!(nglGetBufferPointervARB= (PFNGLGETBUFFERPOINTERVARBPROC)nelglGetProcAddress("glGetBufferPointervARB"))) return false;	
	
	return true;
}

// ***************************************************************************
static bool	setupARBVertexProgram(const char	*glext)
{
	H_AUTO_OGL(setupARBVertexProgram)
	if(strstr(glext, "GL_ARB_vertex_program")==NULL)
		return false;
	 if (!(nglVertexAttrib1sARB= (PFNGLVERTEXATTRIB1SARBPROC)nelglGetProcAddress("glVertexAttrib1sARB"))) return false;
	 if (!(nglVertexAttrib1fARB= (PFNGLVERTEXATTRIB1FARBPROC)nelglGetProcAddress("glVertexAttrib1fARB"))) return false;
	 if (!(nglVertexAttrib1dARB= (PFNGLVERTEXATTRIB1DARBPROC)nelglGetProcAddress("glVertexAttrib1dARB"))) return false;
	 if (!(nglVertexAttrib2sARB= (PFNGLVERTEXATTRIB2SARBPROC)nelglGetProcAddress("glVertexAttrib2sARB"))) return false;
	 if (!(nglVertexAttrib2fARB= (PFNGLVERTEXATTRIB2FARBPROC)nelglGetProcAddress("glVertexAttrib2fARB"))) return false;
	 if (!(nglVertexAttrib2dARB= (PFNGLVERTEXATTRIB2DARBPROC)nelglGetProcAddress("glVertexAttrib2dARB"))) return false;
	 if (!(nglVertexAttrib3sARB= (PFNGLVERTEXATTRIB3SARBPROC)nelglGetProcAddress("glVertexAttrib3sARB"))) return false;
	 if (!(nglVertexAttrib3fARB= (PFNGLVERTEXATTRIB3FARBPROC)nelglGetProcAddress("glVertexAttrib3fARB"))) return false;
	 if (!(nglVertexAttrib3dARB= (PFNGLVERTEXATTRIB3DARBPROC)nelglGetProcAddress("glVertexAttrib3dARB"))) return false;
	 if (!(nglVertexAttrib4sARB= (PFNGLVERTEXATTRIB4SARBPROC)nelglGetProcAddress("glVertexAttrib4sARB"))) return false;
	 if (!(nglVertexAttrib4fARB= (PFNGLVERTEXATTRIB4FARBPROC)nelglGetProcAddress("glVertexAttrib4fARB"))) return false;
	 if (!(nglVertexAttrib4dARB= (PFNGLVERTEXATTRIB4DARBPROC)nelglGetProcAddress("glVertexAttrib4dARB"))) return false;
	 if (!(nglVertexAttrib4NubARB= (PFNGLVERTEXATTRIB4NUBARBPROC)nelglGetProcAddress("glVertexAttrib4NubARB"))) return false;
	 if (!(nglVertexAttrib1svARB= (PFNGLVERTEXATTRIB1SVARBPROC)nelglGetProcAddress("glVertexAttrib1svARB"))) return false;
	 if (!(nglVertexAttrib1fvARB= (PFNGLVERTEXATTRIB1FVARBPROC)nelglGetProcAddress("glVertexAttrib1fvARB"))) return false;
	 if (!(nglVertexAttrib1dvARB= (PFNGLVERTEXATTRIB1DVARBPROC)nelglGetProcAddress("glVertexAttrib1dvARB"))) return false;
	 if (!(nglVertexAttrib2svARB= (PFNGLVERTEXATTRIB2SVARBPROC)nelglGetProcAddress("glVertexAttrib2svARB"))) return false;
	 if (!(nglVertexAttrib2fvARB= (PFNGLVERTEXATTRIB2FVARBPROC)nelglGetProcAddress("glVertexAttrib2fvARB"))) return false;
	 if (!(nglVertexAttrib2dvARB= (PFNGLVERTEXATTRIB2DVARBPROC)nelglGetProcAddress("glVertexAttrib2dvARB"))) return false;
	 if (!(nglVertexAttrib3svARB= (PFNGLVERTEXATTRIB3SVARBPROC)nelglGetProcAddress("glVertexAttrib3svARB"))) return false;
	 if (!(nglVertexAttrib3fvARB= (PFNGLVERTEXATTRIB3FVARBPROC)nelglGetProcAddress("glVertexAttrib3fvARB"))) return false;
	 if (!(nglVertexAttrib3dvARB= (PFNGLVERTEXATTRIB3DVARBPROC)nelglGetProcAddress("glVertexAttrib3dvARB"))) return false;
	 if (!(nglVertexAttrib4bvARB= (PFNGLVERTEXATTRIB4BVARBPROC)nelglGetProcAddress("glVertexAttrib4bvARB"))) return false;
	 if (!(nglVertexAttrib4svARB= (PFNGLVERTEXATTRIB4SVARBPROC)nelglGetProcAddress("glVertexAttrib4svARB"))) return false;
	 if (!(nglVertexAttrib4ivARB= (PFNGLVERTEXATTRIB4IVARBPROC)nelglGetProcAddress("glVertexAttrib4ivARB"))) return false;
	 if (!(nglVertexAttrib4ubvARB= (PFNGLVERTEXATTRIB4UBVARBPROC)nelglGetProcAddress("glVertexAttrib4ubvARB"))) return false;
	 if (!(nglVertexAttrib4usvARB= (PFNGLVERTEXATTRIB4USVARBPROC)nelglGetProcAddress("glVertexAttrib4usvARB"))) return false;
	 if (!(nglVertexAttrib4uivARB= (PFNGLVERTEXATTRIB4UIVARBPROC)nelglGetProcAddress("glVertexAttrib4uivARB"))) return false;
	 if (!(nglVertexAttrib4fvARB= (PFNGLVERTEXATTRIB4FVARBPROC)nelglGetProcAddress("glVertexAttrib4fvARB"))) return false;
	 if (!(nglVertexAttrib4dvARB= (PFNGLVERTEXATTRIB4DVARBPROC)nelglGetProcAddress("glVertexAttrib4dvARB"))) return false;
	 if (!(nglVertexAttrib4NbvARB= (PFNGLVERTEXATTRIB4NBVARBPROC)nelglGetProcAddress("glVertexAttrib4NbvARB"))) return false;
	 if (!(nglVertexAttrib4NsvARB= (PFNGLVERTEXATTRIB4NSVARBPROC)nelglGetProcAddress("glVertexAttrib4NsvARB"))) return false;
	 if (!(nglVertexAttrib4NivARB= (PFNGLVERTEXATTRIB4NIVARBPROC)nelglGetProcAddress("glVertexAttrib4NivARB"))) return false;
	 if (!(nglVertexAttrib4NubvARB= (PFNGLVERTEXATTRIB4NUBVARBPROC)nelglGetProcAddress("glVertexAttrib4NubvARB"))) return false;
	 if (!(nglVertexAttrib4NusvARB= (PFNGLVERTEXATTRIB4NUSVARBPROC)nelglGetProcAddress("glVertexAttrib4NusvARB"))) return false;
	 if (!(nglVertexAttrib4NuivARB= (PFNGLVERTEXATTRIB4NUIVARBPROC)nelglGetProcAddress("glVertexAttrib4NuivARB"))) return false;
	 if (!(nglVertexAttribPointerARB= (PFNGLVERTEXATTRIBPOINTERARBPROC)nelglGetProcAddress("glVertexAttribPointerARB"))) return false;
	 if (!(nglEnableVertexAttribArrayARB= (PFNGLENABLEVERTEXATTRIBARRAYARBPROC)nelglGetProcAddress("glEnableVertexAttribArrayARB"))) return false;
	 if (!(nglDisableVertexAttribArrayARB= (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC)nelglGetProcAddress("glDisableVertexAttribArrayARB"))) return false;
	 if (!(nglProgramStringARB= (PFNGLPROGRAMSTRINGARBPROC)nelglGetProcAddress("glProgramStringARB"))) return false;
	 if (!(nglBindProgramARB= (PFNGLBINDPROGRAMARBPROC)nelglGetProcAddress("glBindProgramARB"))) return false;
	 if (!(nglDeleteProgramsARB= (PFNGLDELETEPROGRAMSARBPROC)nelglGetProcAddress("glDeleteProgramsARB"))) return false;
	 if (!(nglGenProgramsARB= (PFNGLGENPROGRAMSARBPROC)nelglGetProcAddress("glGenProgramsARB"))) return false;
	 if (!(nglProgramEnvParameter4fARB= (PFNGLPROGRAMENVPARAMETER4FARBPROC)nelglGetProcAddress("glProgramEnvParameter4fARB"))) return false;
	 if (!(nglProgramEnvParameter4dARB= (PFNGLPROGRAMENVPARAMETER4DARBPROC)nelglGetProcAddress("glProgramEnvParameter4dARB"))) return false;
	 if (!(nglProgramEnvParameter4fvARB= (PFNGLPROGRAMENVPARAMETER4FVARBPROC)nelglGetProcAddress("glProgramEnvParameter4fvARB"))) return false;
	 if (!(nglProgramEnvParameter4dvARB= (PFNGLPROGRAMENVPARAMETER4DVARBPROC)nelglGetProcAddress("glProgramEnvParameter4dvARB"))) return false;
	 if (!(nglProgramLocalParameter4fARB= (PFNGLPROGRAMLOCALPARAMETER4FARBPROC)nelglGetProcAddress("glProgramLocalParameter4fARB"))) return false;
	 if (!(nglProgramLocalParameter4dARB= (PFNGLPROGRAMLOCALPARAMETER4DARBPROC)nelglGetProcAddress("glProgramLocalParameter4dARB"))) return false;
	 if (!(nglProgramLocalParameter4fvARB= (PFNGLPROGRAMLOCALPARAMETER4FVARBPROC)nelglGetProcAddress("glProgramLocalParameter4fvARB"))) return false;
	 if (!(nglProgramLocalParameter4dvARB= (PFNGLPROGRAMLOCALPARAMETER4DVARBPROC)nelglGetProcAddress("glProgramLocalParameter4dvARB"))) return false;
	 if (!(nglGetProgramEnvParameterfvARB= (PFNGLGETPROGRAMENVPARAMETERFVARBPROC)nelglGetProcAddress("glGetProgramEnvParameterfvARB"))) return false;
	 if (!(nglGetProgramEnvParameterdvARB= (PFNGLGETPROGRAMENVPARAMETERDVARBPROC)nelglGetProcAddress("glGetProgramEnvParameterdvARB"))) return false;
	 if (!(nglGetProgramLocalParameterfvARB= (PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC)nelglGetProcAddress("glGetProgramLocalParameterfvARB"))) return false;
	 if (!(nglGetProgramLocalParameterdvARB= (PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC)nelglGetProcAddress("glGetProgramLocalParameterdvARB"))) return false;
	 if (!(nglGetProgramivARB= (PFNGLGETPROGRAMIVARBPROC)nelglGetProcAddress("glGetProgramivARB"))) return false;
	 if (!(nglGetProgramStringARB= (PFNGLGETPROGRAMSTRINGARBPROC)nelglGetProcAddress("glGetProgramStringARB"))) return false;
	 if (!(nglGetVertexAttribdvARB= (PFNGLGETVERTEXATTRIBDVARBPROC)nelglGetProcAddress("glGetVertexAttribdvARB"))) return false;
	 if (!(nglGetVertexAttribfvARB= (PFNGLGETVERTEXATTRIBFVARBPROC)nelglGetProcAddress("glGetVertexAttribfvARB"))) return false;
	 if (!(nglGetVertexAttribivARB= (PFNGLGETVERTEXATTRIBIVARBPROC)nelglGetProcAddress("glGetVertexAttribivARB"))) return false;
	 if (!(nglGetVertexAttribPointervARB= (PFNGLGETVERTEXATTRIBPOINTERVARBPROC)nelglGetProcAddress("glGetVertexAttribPointervARB"))) return false;
	 if (!(nglIsProgramARB= (PFNGLISPROGRAMARBPROC)nelglGetProcAddress("glIsProgramARB"))) return false;	
	 return true;
}

// ***************************************************************************
static bool	setupNVOcclusionQuery(const char	*glext)
{
	H_AUTO_OGL(setupNVOcclusionQuery)
	if(strstr(glext, "GL_NV_occlusion_query")==NULL)
		return false;	
	if (!(nglGenOcclusionQueriesNV= (NEL_PFNGLGENOCCLUSIONQUERIESNVPROC)nelglGetProcAddress("glGenOcclusionQueriesNV"))) return false;
	if (!(nglDeleteOcclusionQueriesNV= (NEL_PFNGLDELETEOCCLUSIONQUERIESNVPROC)nelglGetProcAddress("glDeleteOcclusionQueriesNV"))) return false;
	if (!(nglIsOcclusionQueryNV= (NEL_PFNGLISOCCLUSIONQUERYNVPROC)nelglGetProcAddress("glIsOcclusionQueryNV"))) return false;
	if (!(nglBeginOcclusionQueryNV= (NEL_PFNGLBEGINOCCLUSIONQUERYNVPROC)nelglGetProcAddress("glBeginOcclusionQueryNV"))) return false;
	if (!(nglEndOcclusionQueryNV= (NEL_PFNGLENDOCCLUSIONQUERYNVPROC)nelglGetProcAddress("glEndOcclusionQueryNV"))) return false;
	if (!(nglGetOcclusionQueryivNV= (NEL_PFNGLGETOCCLUSIONQUERYIVNVPROC)nelglGetProcAddress("glGetOcclusionQueryivNV"))) return false;
	if (!(nglGetOcclusionQueryuivNV= (NEL_PFNGLGETOCCLUSIONQUERYUIVNVPROC)nelglGetProcAddress("glGetOcclusionQueryuivNV"))) return false;
	return true;	
}


// ***************************************************************************
static bool	setupNVTextureRectangle(const char	*glext)
{
	H_AUTO_OGL(setupNVTextureRectangle)
	return strstr(glext, "GL_NV_texture_rectangle")!=NULL;
}

// ***************************************************************************
static bool	setupFrameBufferObject(const char	*glext)
{
	H_AUTO_OGL(setupFrameBufferObject)
	if(strstr(glext, "GL_EXT_framebuffer_object")==NULL)
		return false;	

	if (!(nglIsRenderbufferEXT= (NEL_PFNGLISRENDERBUFFEREXTPROC)nelglGetProcAddress("glIsRenderbufferEXT"))) return false;
	if (!(nglIsFramebufferEXT= (NEL_PFNGLISFRAMEBUFFEREXTPROC)nelglGetProcAddress("glIsFramebufferEXT"))) return false;
	if (!(nglCheckFramebufferStatusEXT= (NEL_PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)nelglGetProcAddress("glCheckFramebufferStatusEXT"))) return false;
	if (!(nglGenFramebuffersEXT= (NEL_PFNGLGENFRAMEBUFFERSEXTPROC)nelglGetProcAddress("glGenFramebuffersEXT"))) return false;
	if (!(nglBindFramebufferEXT= (NEL_PFNGLBINDFRAMEBUFFEREXTPROC)nelglGetProcAddress("glBindFramebufferEXT"))) return false;
	if (!(nglFramebufferTexture2DEXT= (NEL_PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)nelglGetProcAddress("glFramebufferTexture2DEXT"))) return false;
	if (!(nglGenRenderbuffersEXT= (NEL_PFNGLGENRENDERBUFFERSEXTPROC)nelglGetProcAddress("glGenRenderbuffersEXT"))) return false;
	if (!(nglBindRenderbufferEXT= (NEL_PFNGLBINDRENDERBUFFEREXTPROC)nelglGetProcAddress("glBindRenderbufferEXT"))) return false;
	if (!(nglRenderbufferStorageEXT= (NEL_PFNGLRENDERBUFFERSTORAGEEXTPROC)nelglGetProcAddress("glRenderbufferStorageEXT"))) return false;
	if (!(nglFramebufferRenderbufferEXT= (NEL_PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)nelglGetProcAddress("glFramebufferRenderbufferEXT"))) return false;
	if (!(nglDeleteRenderbuffersEXT= (NEL_PFNGLDELETERENDERBUFFERSEXTPROC)nelglGetProcAddress("glDeleteRenderbuffersEXT"))) return false;
	if (!(nglDeleteFramebuffersEXT= (NEL_PFNGLDELETEFRAMEBUFFERSEXTPROC)nelglGetProcAddress("glDeleteFramebuffersEXT"))) return false;

	return true;	
}

// ***************************************************************************
static bool	setupPackedDepthStencil(const char	*glext)
{
	H_AUTO_OGL(setupPackedDepthStencil)
	return strstr(glext, "GL_EXT_packed_depth_stencil")!=NULL;
}

// ***************************************************************************
// Extension Check.
void	registerGlExtensions(CGlExtensions &ext)
{
	H_AUTO_OGL(registerGlExtensions)
	// OpenGL 1.2 ??
	const char	*glVersion= (const char *) glGetString (GL_VERSION);
	sint	a=0, b=0;
	// 1.2***  ???
	sscanf(glVersion, "%d.%d", &a, &b);
	ext.Version1_2= (a==1 && b>=2) || (a>=2);


	// Extensions.
	const char	*glext= (const char*)glGetString(GL_EXTENSIONS);
	GLint	ntext;

	nldebug("GLExt: %s", glext);


	// Check ARBMultiTexture
	ext.ARBMultiTexture= setupARBMultiTexture(glext);
	if(ext.ARBMultiTexture)
	{
		glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &ntext);
		// We could have more than IDRV_MAT_MAXTEXTURES but the interface only 
		// support IDRV_MAT_MAXTEXTURES texture stages so take min
		ext.NbTextureStages= (ntext<((GLint)IDRV_MAT_MAXTEXTURES)?ntext:IDRV_MAT_MAXTEXTURES);
	}

	// Check EXTTextureEnvCombine
	ext.EXTTextureEnvCombine= setupEXTTextureEnvCombine(glext);

	// Check ARBTextureCompression
	ext.ARBTextureCompression= setupARBTextureCompression(glext);

	// Check NVVertexArrayRange
	// Disable feature ???			
	if(!ext.DisableHardwareVertexArrayAGP)
		ext.NVVertexArrayRange= setupNVVertexArrayRange(glext);	
	if(ext.NVVertexArrayRange)
	{
		GLint	nverts;
		glGetIntegerv((GLenum)GL_MAX_VERTEX_ARRAY_RANGE_ELEMENT_NV, &nverts);
		ext.NVVertexArrayRangeMaxVertex= nverts;
	}	


	// Compression S3TC OK iff ARBTextureCompression.
	ext.EXTTextureCompressionS3TC= (ext.ARBTextureCompression && setupEXTTextureCompressionS3TC(glext)); 

	// Check if NVidia GL_EXT_vertex_weighting is available.
	ext.EXTVertexWeighting= setupEXTVertexWeighting(glext);

	// Check EXTSeparateSpecularColor.
	ext.EXTSeparateSpecularColor= setupEXTSeparateSpecularColor(glext);

	// Check NVTextureEnvCombine4.
	ext.NVTextureEnvCombine4= setupNVTextureEnvCombine4(glext);
	

	// Check for cube mapping
	ext.ARBTextureCubeMap = setupARBTextureCubeMap(glext);

	// Check vertex program
	// Disable feature ???
	if(!ext.DisableHardwareVertexProgram)
	{		
		ext.NVVertexProgram = setupNVVertexProgram(glext);
		ext.EXTVertexShader = setupEXTVertexShader(glext);
		ext.ARBVertexProgram= setupARBVertexProgram(glext);				
	}
	else
	{
		ext.NVVertexProgram = false;
		ext.EXTVertexShader = false;
		ext.ARBVertexProgram = false;
	}
			
	// Check texture shaders
	// Disable feature ???
	if(!ext.DisableHardwareTextureShader)
	{	
		ext.NVTextureShader = setupNVTextureShader(glext);		
		ext.ATIEnvMapBumpMap = setupATIEnvMapBumpMap(glext);		
		ext.ATIFragmentShader = setupATIFragmentShader(glext);	
		ext.ARBFragmentProgram = setupARBFragmentProgram(glext);		
	}
	else
	{
		ext.ATIEnvMapBumpMap = false;
		ext.NVTextureShader = false;
		ext.ATIFragmentShader = false;
		ext.ARBFragmentProgram = false;
	}

	

	// For now, the only way to know if emulation, is to test some extension which exist only on GeForce3.
	// if GL_NV_texture_shader is not here, then we are not on GeForce3.
	ext.NVVertexProgramEmulated= ext.NVVertexProgram && (strstr(glext, "GL_NV_texture_shader")==NULL);

	// Check EXTSecondaryColor
	ext.EXTSecondaryColor= setupEXTSecondaryColor(glext);

	// Check EXTBlendColor
	ext.EXTBlendColor= setupEXTBlendColor(glext);

	// Check NVVertexArrayRange2		
	ext.NVVertexArrayRange2= setupNVVertexArrayRange2(glext);
	// if supported
	if(ext.NVVertexArrayRange2)
		// VBHard swap without flush of the VAR.
		ext.NVStateVARWithoutFlush= GL_VERTEX_ARRAY_RANGE_WITHOUT_FLUSH_NV;
	else
		// VBHard with unusefull flush of the VAR.
		ext.NVStateVARWithoutFlush= GL_VERTEX_ARRAY_RANGE_NV;

	// Check NV_occlusion_query
	ext.NVOcclusionQuery = setupNVOcclusionQuery(glext);

	// Check GL_NV_texture_rectangle
	ext.NVTextureRectangle = setupNVTextureRectangle(glext);

	// Check GL_EXT_framebuffer_object
	ext.FrameBufferObject = setupFrameBufferObject(glext);

	// Check GL_EXT_packed_depth_stencil
	ext.PackedDepthStencil = setupPackedDepthStencil(glext);

	// ATI extensions
	// -------------

	// Check ATIVertexArrayObject
	// Disable feature ???
	if(!ext.DisableHardwareVertexArrayAGP)
	{	
		ext.ATIVertexArrayObject= setupATIVertexArrayObject(glext);
		ext.ATIMapObjectBuffer= setupATIMapObjectBuffer(glext);
		ext.ATIVertexAttribArrayObject = setupATIVertexAttribArrayObject(glext);		
	}
	// Check ATIXTextureEnvCombine3.
	ext.ATITextureEnvCombine3= setupATITextureEnvCombine3(glext);
	// Check ATIXTextureEnvRoute
	ext.ATIXTextureEnvRoute= setupATIXTextureEnvRoute(glext);
		
	if (ext.ATITextureEnvCombine3)
	{
		ext.IsATI9500OrAbove = setupARBFragmentProgram(glext);
	}

	// ARB extensions
	// -------------
	if(!ext.DisableHardwareVertexArrayAGP)
	{
		ext.ARBVertexBufferObject = setupARBVertexBufferObject(glext);
	}		
	// In my tries ATI_fragment_shader doesn't like to be used With ARB_fragment_program (maybe a driver bug, display become corrupted)
	if (ext.IsATI9500OrAbove)
	{		
		ext.ATIFragmentShader = false;
	}	

	ext.IsGeforceFXOrAbove = setupNVVertexProgram(glext) && setupARBFragmentProgram(glext);
	 
	// fix for radeon 7200 -> disable agp
	if (ext.NbTextureStages == 3 && (ext.ATIVertexArrayObject || ext.ARBVertexBufferObject))
	{
		ext.ATIVertexArrayObject = false;
		ext.ARBVertexBufferObject = false;
		ext.ATIMapObjectBuffer = false;
		ext.ATIVertexAttribArrayObject = false;
	}
}


// *********************************
static bool	setupWGLEXTSwapControl(const char	*glext)
{
	H_AUTO_OGL(setupWGLEXTSwapControl)
	if(strstr(glext, "WGL_EXT_swap_control")==NULL)
		return false;

#ifdef NL_OS_WINDOWS
	if(!(wglSwapIntervalEXT= (PFNWGLSWAPINTERVALEXTPROC)nelglGetProcAddress("wglSwapIntervalEXT"))) return false;
	if(!(wglGetSwapIntervalEXT= (PFNWGLGETSWAPINTERVALEXTPROC)nelglGetProcAddress("wglGetSwapIntervalEXT"))) return false;
#endif

	return true;
}


#ifdef NL_OS_WINDOWS
// ***************************************************************************
void	registerWGlExtensions(CGlExtensions &ext, HDC hDC)
{
	H_AUTO_OGL(registerWGlExtensions)
	// Get proc adress
	if(!(wglGetExtensionsStringARB=(PFNWGFGETEXTENSIONSSTRINGARB)nelglGetProcAddress("wglGetExtensionsStringARB")))
	{
		nlwarning ("wglGetExtensionsStringARB not supported");
		return;
	}

	// Get extension string
	const char *glext = wglGetExtensionsStringARB (hDC);
	if (glext == NULL)
	{
		nlwarning ("wglGetExtensionsStringARB failed");
		return;
	}

	nldebug("WGLExt: %s", glext);

	// Check for pbuffer
	ext.WGLARBPBuffer= setupWGLARBPBuffer(glext);

	// Check for pixel format
	ext.WGLARBPixelFormat= setupWGLARBPixelFormat(glext);

	// Check for swap control
	ext.WGLEXTSwapControl= setupWGLEXTSwapControl(glext);
}
#endif // NL_OS_WINDOWS


}

























