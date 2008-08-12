// crash.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char* argv[])
{
	*(int*)0 = 0;
	return 0;
}

