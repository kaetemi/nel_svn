#ifndef __INELLIBRARY_H__
#define __INELLIBRARY_H__

#include <nel/3d/u_driver.h>
#include <nel/cegui/inelrenderer.h>

class CCeguiRendererNelLibrary : public NLMISC::INelLibrary {
        void onLibraryLoaded(bool /* firstTime */) { }
        void onLibraryUnloaded(bool /* lastTime */) { }
};

const char *NELRENDERER_CREATE_PROC_NAME = "createNeLRendererInstance";
typedef CEGUI::INeLRenderer* (*NELRENDERER_CREATE_PROC)(NL3D::UDriver *, bool);

#endif // __INELLIBRARY_H__
