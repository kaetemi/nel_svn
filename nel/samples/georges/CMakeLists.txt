FILE(GLOB SRC *.cpp)

DECORATE_NEL_LIB("nelgeorges")
SET(NLGEORGES_LIB ${LIBNAME})

ADD_EXECUTABLE(nl_sample_georges ${SRC})

IF(UNIX)
  ADD_DEFINITIONS(-DGF_DIR="\\"${NL_SHARE_PREFIX}/nl_sample_georges/\\"")
ENDIF(UNIX)

INCLUDE_DIRECTORIES(${LIBXML2_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(nl_sample_georges ${PLATFORM_LINKFLAGS} ${NLGEORGES_LIB})
IF(WIN32)
  SET_TARGET_PROPERTIES(nl_sample_georges PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libcmt")
ENDIF(WIN32)
ADD_DEFINITIONS(${LIBXML2_DEFINITIONS})

INSTALL(TARGETS nl_sample_georges RUNTIME DESTINATION ${NL_BIN_PREFIX} COMPONENT samplesgeorges)
INSTALL(FILES boolean.typ coolfilesinfo.dfn default.sample_config int.typ positiondata.dfn sample_config.dfn string.typ sheet_id.bin
	DESTINATION ${NL_SHARE_PREFIX}/nl_sample_georges/ COMPONENT samplesgeorges)
