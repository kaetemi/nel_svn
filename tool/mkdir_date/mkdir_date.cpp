// mkdir_date.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <stdio.h>
#include <direct.h> 

int main(int argc, char* argv[])
{
	// Help
	if (argc<2)
	{
		printf ("mkdir_date [directory]");
		return 0;
	}

	// Get the time
	time_t aclock;
	time(&aclock);

	// Get time information
	const struct tm *timeptr=localtime(&aclock);

	// Format the string
	char date[512];
	strftime( date, sizeof(date), "%Y %m %d %Hh%M", timeptr);

	// Name of the directory
	char directory[512];
	sprintf (directory, "%s %s", argv[1], date);

	// Create a directory
	return _mkdir( directory )==0;
}
