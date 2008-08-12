// mkdir_date.cpp : Defines the entry point for the console application.
//

#include <time.h>
#include <stdio.h>
#include <direct.h> 
#include <string.h> 

int main(int argc, char* argv[])
{
	// Help
	bool keepExt = false;
	bool help = ( (argc<3) || (argc>4) );
	if (argc == 4)
	{
		if (strcmp (argv[3], "-keepExt") == 0)
			keepExt = true;
		else
			help = true;
	}

	if (help)
	{
		printf ("ren_date [old_name] [new_base_name] [-keepExt]");
		return 0;
	}

	// Get the time
	time_t aclock;
	time(&aclock);

	// Get time information
	const struct tm *timeptr=localtime(&aclock);

	// Extension
	char ext[512];

	// Empty string 
	strcpy (ext, "");

	// Keep the extension
	if (keepExt)
	{
		// Get the extension
		char *point = strrchr (argv[2], '.');
		if (point)
		{
			strcpy (ext, point);
			*point = 0;
		}
	}

	// Format the string
	char date[512];
	strftime( date, sizeof(date), "%Y %m %d %Hh%M", timeptr);

	// Name of the directory
	char directory[512];
	sprintf (directory, "%s %s%s", argv[2], date, ext);

	// Create a directory
	return rename ( argv[1], directory )==0;
}
