#FILE(GLOB SRC *.cpp *.h)

DECORATE_NEL_LIB("nel_ut_misc")

ADD_LIBRARY(${LIBNAME} SHARED co_task_test.cpp config_file_test.cpp csstring_test.cpp misc_unit_test.cpp object_command_test.cpp pure_nel_lib_test.cpp singleton_test.cpp singleton_test.h stream_test.cpp test_pack_file.cpp)

TARGET_LINK_LIBRARIES(${LIBNAME} ${LIBXML2_LIBRARIES} )
SET_TARGET_PROPERTIES(${LIBNAME} PROPERTIES VERSION ${NL_VERSION})

IF(WIN32)
  SET_TARGET_PROPERTIES(${LIBNAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libcmt")
ENDIF(WIN32)

ADD_DEFINITIONS(${LIBXML2_DEFINITIONS})

INSTALL(TARGETS ${LIBNAME} LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
