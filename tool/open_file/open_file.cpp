// openhtml.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata)
{
    HKEY hkey;
    LONG retval = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hkey);

    if (retval == ERROR_SUCCESS) 
	{
        long datasize = MAX_PATH;
        TCHAR data[MAX_PATH];
        RegQueryValue(hkey, NULL, data, &datasize);
        lstrcpy(retdata,data);
        RegCloseKey(hkey);
    }

    return retval;
}

bool OpenFile (LPCTSTR filename, LPCTSTR ext, int showcmd)
{
    TCHAR key[MAX_PATH + MAX_PATH];

    // First try ShellExecute()
    HINSTANCE result = ShellExecute(NULL, "open", filename, NULL,NULL, showcmd);

    // If it failed, get the .htm regkey and lookup the program
    if ((UINT)result <= HINSTANCE_ERROR) 
	{
        if (GetRegKey(HKEY_CLASSES_ROOT, ext, key) == ERROR_SUCCESS) 
		{
            lstrcat(key, "\\shell\\open\\command");

            if (GetRegKey(HKEY_CLASSES_ROOT,key,key) == ERROR_SUCCESS) 
			{
                TCHAR *pos;
                pos = strstr(key, "\"%1\"");
                if (pos == NULL) {                     // No quotes found
                    pos = strstr(key, "%1");       // Check for %1, without quotes 
                    if (pos == NULL)                   // No parameter at all...
                        pos = key+lstrlen(key)-1;
                    else
                        *pos = '\0';                   // Remove the parameter
                }
                else
                    *pos = '\0';                       // Remove the parameter

                lstrcat(pos, " ");
                lstrcat(pos, filename);
                int res = WinExec(key,showcmd);
				return (res>31);
            }
        }
    }
	else
		return true;

	return false;
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	if (strcmp (lpCmdLine, "")==0)
	{
		MessageBox (NULL, "Open a file with the default application.\nUsage: open_file [filepath]", "Open file", MB_OK|MB_ICONINFORMATION);
	}
	else
	{
		char ext[512];
		_splitpath (lpCmdLine, NULL, NULL, NULL, ext);
		OpenFile(lpCmdLine, ext, SW_SHOW);
	}

	return 0;
}
