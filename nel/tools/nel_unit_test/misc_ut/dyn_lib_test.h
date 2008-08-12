

#include "nel/misc/dynloadlib.h"
#include "nel/misc/app_context.h"

#ifndef DYN_LIB_TEST_H
#define  DYN_LIB_TEST_H

class IDynLibTest : public NLMISC::INelLibrary
{
public:

	virtual void testSingleton(class CSafeSingletonTS *testSuite) =0;
};


#endif // DYN_LIB_TEST_H
