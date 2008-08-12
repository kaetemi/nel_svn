// ResSwap.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	DEVMODE		bkupMode, devMode;
	devMode.dmSize= sizeof(DEVMODE);
	devMode.dmDriverExtra= 0;
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode);
	devMode.dmFields= DM_BITSPERPEL;

	bkupMode= devMode;

	if(devMode.dmBitsPerPel==16)
	{
		devMode.dmBitsPerPel=32;
	}
	else
	{
		devMode.dmBitsPerPel=16;
	}
	ChangeDisplaySettings(&devMode, 0);
	ChangeDisplaySettings(&bkupMode, 0);

	return 0;
}



