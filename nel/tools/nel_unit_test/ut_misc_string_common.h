#ifndef UT_MISC_STRING_COMMON
#define UT_MISC_STRING_COMMON

#include <nel/misc/string_common.h>

struct CUTMiscStringCommon : public Test::Suite
{
	CUTMiscStringCommon()
	{
		TEST_ADD(CUTMiscStringCommon::fromStringSint8);
		TEST_ADD(CUTMiscStringCommon::fromStringUint8);
		TEST_ADD(CUTMiscStringCommon::fromStringSint16);
		// Add a line here when adding a new test METHOD
	}

	void fromStringSint8()
	{
		bool ret;

		// tests for sint8
		sint8 si8;

		// positive value
		ret = NLMISC::fromString("1", si8);
		TEST_ASSERT(ret && si8 == 1);

		// negative value
		ret = NLMISC::fromString("-1", si8);
		TEST_ASSERT(ret && si8 == -1);

		// bad character
		ret = NLMISC::fromString("a", si8);
		TEST_ASSERT(!ret && si8 == 0);

		// right character and bad character
		ret = NLMISC::fromString("1a", si8);
		TEST_ASSERT(ret && si8 == 1);

		// min limit
		ret = NLMISC::fromString("-128", si8);
		TEST_ASSERT(ret && si8 == -128);

		// max limit
		ret = NLMISC::fromString("127", si8);
		TEST_ASSERT(ret && si8 == 127);

		// min limit -1
		ret = NLMISC::fromString("-129", si8);
		TEST_ASSERT(!ret && si8 == 0);

		// max limit +1
		ret = NLMISC::fromString("128", si8);
		TEST_ASSERT(!ret && si8 == 0);

		// with period
		ret = NLMISC::fromString("1.2", si8);
		TEST_ASSERT(ret && si8 == 1);

		// with coma
		ret = NLMISC::fromString("1,2", si8);
		TEST_ASSERT(ret && si8 == 1);

		// with spaces before
		ret = NLMISC::fromString("  10", si8);
		TEST_ASSERT(ret && si8 == 10);

		// with spaces after
		ret = NLMISC::fromString("10  ", si8);
		TEST_ASSERT(ret && si8 == 10);

		// with 0s before
		ret = NLMISC::fromString("001", si8);
		TEST_ASSERT(ret && si8 == 1);

		// with + before
		ret = NLMISC::fromString("+1", si8);
		TEST_ASSERT(ret && si8 == 1);
	}

	void fromStringUint8()
	{
		bool ret;

		// tests for uint8
		uint8 ui8;

		// positive value
		ret = NLMISC::fromString("1", ui8);
		TEST_ASSERT(ret && ui8 == 1);

		// bad character
		ret = NLMISC::fromString("a", ui8);
		TEST_ASSERT(!ret && ui8 == 0);

		// right character and bad character
		ret = NLMISC::fromString("1a", ui8);
		TEST_ASSERT(ret && ui8 == 1);

		// min limit
		ret = NLMISC::fromString("0", ui8);
		TEST_ASSERT(ret && ui8 == 0);

		// max limit
		ret = NLMISC::fromString("255", ui8);
		TEST_ASSERT(ret && ui8 == 255);

		// min limit -1
		ret = NLMISC::fromString("-1", ui8);
		TEST_ASSERT(!ret && ui8 == 0);

		// max limit +1
		ret = NLMISC::fromString("256", ui8);
		TEST_ASSERT(!ret && ui8 == 0);

		// with period
		ret = NLMISC::fromString("1.2", ui8);
		TEST_ASSERT(ret && ui8 == 1);

		// with coma
		ret = NLMISC::fromString("1,2", ui8);
		TEST_ASSERT(ret && ui8 == 1);

		// with spaces before
		ret = NLMISC::fromString("  10", ui8);
		TEST_ASSERT(ret && ui8 == 10);

		// with spaces after
		ret = NLMISC::fromString("10  ", ui8);
		TEST_ASSERT(ret && ui8 == 10);

		// with 0s before
		ret = NLMISC::fromString("001", ui8);
		TEST_ASSERT(ret && ui8 == 1);

		// with + before
		ret = NLMISC::fromString("+1", ui8);
		TEST_ASSERT(ret && ui8 == 1);
	}

	void fromStringSint16()
	{
		bool ret;

		// tests for sint16
		sint16 si16;

		// positive value
		ret = NLMISC::fromString("1", si16);
		TEST_ASSERT(ret && si16 == 1);

		// negative value
		ret = NLMISC::fromString("-1", si16);
		TEST_ASSERT(ret && si16 == -1);

		// bad character
		ret = NLMISC::fromString("a", si16);
		TEST_ASSERT(!ret && si16 == 0);

		// right character and bad character
		ret = NLMISC::fromString("1a", si16);
		TEST_ASSERT(ret && si16 == 1);

		// min limit
		ret = NLMISC::fromString("-32768", si16);
		TEST_ASSERT(ret && si16 == -32768);

		// max limit
		ret = NLMISC::fromString("32767", si16);
		TEST_ASSERT(ret && si16 == 32767);

		// min limit -1
		ret = NLMISC::fromString("-32769", si16);
		TEST_ASSERT(!ret && si16 == 0);

		// max limit +1
		ret = NLMISC::fromString("32768", si16);
		TEST_ASSERT(!ret && si16 == 0);

		// with period
		ret = NLMISC::fromString("1.2", si16);
		TEST_ASSERT(ret && si16 == 1);

		// with coma
		ret = NLMISC::fromString("1,2", si16);
		TEST_ASSERT(ret && si16 == 1);

		// with spaces before
		ret = NLMISC::fromString("  10", si16);
		TEST_ASSERT(ret && si16 == 10);

		// with spaces after
		ret = NLMISC::fromString("10  ", si16);
		TEST_ASSERT(ret && si16 == 10);

		// with 0s before
		ret = NLMISC::fromString("001", si16);
		TEST_ASSERT(ret && si16 == 1);

		// with + before
		ret = NLMISC::fromString("+1", si16);
		TEST_ASSERT(ret && si16 == 1);
	}

	void fromStringUint16()
	{
	}
};

#endif
