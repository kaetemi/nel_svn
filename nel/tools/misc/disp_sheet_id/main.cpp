/** \file main.cpp
 * Display info on sheetid.bin
 *
 * $Id: main.cpp,v 1.1 2003/09/26 15:04:30 berenguier Exp $
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

#include "nel/misc/types_nl.h"
#ifdef NL_OS_WINDOWS
#include <conio.h>
#else
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

/// This is our Unix-variant to the Windows _getch function.
int _getch()
{
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt=oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}

#endif

#include "nel/misc/path.h"
#include "nel/misc/sheet_id.h"
#include <vector>


using	namespace std;
using	namespace NLMISC;



// ***************************************************************************
class	CPred
{
public:
	bool	operator()(const CSheetId &a, const CSheetId &b)
	{
		return a.toString()<b.toString();
	}
};

// ***************************************************************************
/// Dispaly info cmd line
int		main(int argc, const char *argv[])
{
	if(argc<2)
	{
		puts("Usage: disp_sheet_id path");
		puts("    display a raw list of file names sorted by name with their sheet_id associated");
		puts("    output in sheetid.txt");
		puts("Press any key");
		_getch();
		return -1;
	}

	NLMISC::CApplicationContext appContext;

	CPath::addSearchPath(argv[1]);

	CSheetId::init(false);

	std::vector<CSheetId>	sheets;
	CSheetId::buildIdVector(sheets);

	// sort by name
	CPred	Pred;
	sort(sheets.begin(), sheets.end(), Pred);

	// display.
	FILE	*out= fopen("sheetid.txt", "wb");
	if(out)
	{
		for(uint i=0;i<sheets.size();i++)
		{
			fprintf(out, "%s : %d\n", sheets[i].toString().c_str(), sheets[i].asInt());
		}
		fclose(out);
	}
}
