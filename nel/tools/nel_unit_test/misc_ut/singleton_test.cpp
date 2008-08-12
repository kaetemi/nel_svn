

#include "singleton_test.h"




Test::Suite *createSafeSingletonTS(const std::string &workingPath)
{
	return new CSafeSingletonTS(workingPath);
}

