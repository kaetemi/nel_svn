
#include "nel/misc/common.h"
#include "nel/misc/path.h"
#include "cpptest.h"
#include "dyn_lib_test.h"

using namespace std;
using namespace NLMISC;

class CPureNelLibTS : public Test::Suite
{
	CLibrary	Lib1;
	CLibrary	Lib2;
	string		LibName;
	string		WorkingPath;
	string		OldPath;
public:
	CPureNelLibTS(const std::string &workingPath)
		: LibName("dyn_lib_test"),
		WorkingPath(workingPath)
	{
		TEST_ADD(CPureNelLibTS::initialLoad);
		TEST_ADD(CPureNelLibTS::unload);
		TEST_ADD(CPureNelLibTS::multipleLoad);
		TEST_ADD(CPureNelLibTS::libraryReplacement);
	}

	void setup()
	{
		OldPath = CPath::getCurrentPath();

		CPath::setCurrentPath(WorkingPath.c_str());
	}

	void tear_down()
	{
		CPath::setCurrentPath(OldPath.c_str());
	}
	
	void initialLoad()
	{
		TEST_ASSERT(!Lib1.isLibraryLoaded());
		TEST_ASSERT(!Lib1.isLibraryPure());
		TEST_ASSERT(Lib1.getNelLibraryInterface() == NULL);

		 
		if (Lib1.loadLibrary(LibName, true, true, true) != true)
		{
			TEST_ASSERT_MSG(false, NLMISC::toString("failed to load the library '%s'", LibName.c_str()).c_str());
			return;
		}

		TEST_ASSERT(Lib1.isLibraryLoaded());
		TEST_ASSERT(Lib1.isLibraryPure());
		TEST_ASSERT(Lib1.getNelLibraryInterface());

		IDynLibTest *dlt = dynamic_cast<IDynLibTest*>(Lib1.getNelLibraryInterface());
		TEST_ASSERT(dlt != NULL);

		TEST_ASSERT(dlt->getLoadingCounter() == 1);
	}

	void unload()
	{
		TEST_ASSERT(Lib1.isLibraryPure());

		Lib1.freeLibrary();

		TEST_ASSERT(!Lib1.isLibraryLoaded());
		TEST_ASSERT(!Lib1.isLibraryPure());
		TEST_ASSERT(Lib1.getNelLibraryInterface() == NULL);
	}

	void multipleLoad()
	{
		TEST_ASSERT(!Lib1.isLibraryLoaded());
		TEST_ASSERT(!Lib1.isLibraryPure());
		TEST_ASSERT(Lib1.getNelLibraryInterface() == NULL);
		TEST_ASSERT(!Lib2.isLibraryLoaded());
		TEST_ASSERT(!Lib2.isLibraryPure());
		TEST_ASSERT(Lib2.getNelLibraryInterface() == NULL);

		// first load
		if (Lib1.loadLibrary(LibName, true, true, true) != true)
		{
			TEST_ASSERT_MSG(false, toString("failed to load the library '%s'", LibName.c_str()).c_str());
			return;
		}

		TEST_ASSERT(Lib1.isLibraryLoaded());
		TEST_ASSERT(Lib1.isLibraryPure());
		TEST_ASSERT(Lib1.getNelLibraryInterface());

		IDynLibTest *dlt1 = dynamic_cast<IDynLibTest*>(Lib1.getNelLibraryInterface());
		TEST_ASSERT(dlt1 != NULL);

		TEST_ASSERT(dlt1->getLoadingCounter() == 1);

		// second load
		if (Lib2.loadLibrary(LibName, true, true, true) != true)
		{
			TEST_ASSERT_MSG(false, toString("failed to load the library '%s'", LibName.c_str()).c_str());
			return;
		}

		TEST_ASSERT(Lib2.isLibraryLoaded());
		TEST_ASSERT(Lib2.isLibraryPure());
		TEST_ASSERT(Lib2.getNelLibraryInterface());

		IDynLibTest *dlt2 = dynamic_cast<IDynLibTest*>(Lib2.getNelLibraryInterface());
		TEST_ASSERT(dlt2 != NULL);

		TEST_ASSERT(dlt2->getLoadingCounter() == 2);
	
		// unload one
		TEST_ASSERT(Lib1.isLibraryPure());

		Lib1.freeLibrary();

		TEST_ASSERT(!Lib1.isLibraryLoaded());
		TEST_ASSERT(!Lib1.isLibraryPure());
		TEST_ASSERT(Lib1.getNelLibraryInterface() == NULL);

		TEST_ASSERT(Lib2.isLibraryLoaded());
		TEST_ASSERT(Lib2.isLibraryPure());
		TEST_ASSERT(Lib2.getNelLibraryInterface());
		dlt2 = dynamic_cast<IDynLibTest*>(Lib2.getNelLibraryInterface());
		TEST_ASSERT(dlt2 != NULL);

		TEST_ASSERT(dlt2->getLoadingCounter() == 1);

		Lib2.freeLibrary();

		TEST_ASSERT(!Lib2.isLibraryLoaded());
		TEST_ASSERT(!Lib2.isLibraryPure());
		TEST_ASSERT(Lib2.getNelLibraryInterface() == NULL);

	}

	void libraryReplacement()
	{
		string srcName = CLibrary::makeLibName("dyn_lib_test");
		string dstName = CLibrary::makeLibName("temp_rep");
		TEST_ASSERT(CFile::copyFile(dstName.c_str(), srcName.c_str()));

		// first load
		if (Lib1.loadLibrary(dstName, false, true, true) != true)
		{
			TEST_ASSERT_MSG(false, toString("failed to load the library '%s'", dstName.c_str()).c_str());
			return;
		}

		TEST_ASSERT(Lib1.isLibraryLoaded());
		TEST_ASSERT(Lib1.isLibraryPure());
		TEST_ASSERT(Lib1.getNelLibraryInterface());

		IDynLibTest *dlt1 = dynamic_cast<IDynLibTest*>(Lib1.getNelLibraryInterface());
		TEST_ASSERT(dlt1 != NULL);

		TEST_ASSERT(dlt1->getLoadingCounter() == 1);

		// unload
		Lib1.freeLibrary();

		// delete the file
		TEST_ASSERT(CFile::deleteFile(dstName));

		// recopy
		TEST_ASSERT(CFile::copyFile(dstName.c_str(), srcName.c_str()));

		// and reload
		if (Lib1.loadLibrary(dstName, false, true, true) != true)
		{
			TEST_ASSERT_MSG(false, toString("failed to load the library '%s'", dstName.c_str()).c_str());
			return;
		}

		TEST_ASSERT(Lib1.isLibraryLoaded());
		TEST_ASSERT(Lib1.isLibraryPure());
		TEST_ASSERT(Lib1.getNelLibraryInterface());

		dlt1 = dynamic_cast<IDynLibTest*>(Lib1.getNelLibraryInterface());
		TEST_ASSERT(dlt1 != NULL);

		TEST_ASSERT(dlt1->getLoadingCounter() == 1);

		Lib1.freeLibrary();
	}
};

Test::Suite *createPureNelLibTS(const std::string &workingPath)
{
	return new CPureNelLibTS(workingPath);
}
