
#ifndef NLMAX_PE_DLLMAIN_H
#define NLMAX_PE_DLLMAIN_H

#include "max.h"
#include "code/modifiers/editpatch/resource.h"

#define NEL_PATCH_EDIT_CLASSID Class_ID(0x10d46366, 0x3d707b45)

extern ClassDesc* GetNeLEditPatchModDesc();
TCHAR *GetString(int id);
extern HINSTANCE hInstance;

#define BIGFLOAT	float(999999)

#endif
