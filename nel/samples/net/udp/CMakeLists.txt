FILE(GLOB SRC *.cpp)

DECORATE_NEL_LIB("nelnet")
SET(NLNET_LIB ${LIBNAME})

ADD_EXECUTABLE(nl_sample_udpclient client.cpp graph.cpp graph.h simlag.cpp simlag.h)

IF(WIN32)
  ADD_EXECUTABLE(nl_sample_udpserver WIN32 bench_service.cpp receive_task.cpp receive_task.h)
ELSE(WIN32)
  ADD_EXECUTABLE(nl_sample_udpserver bench_service.cpp receive_task.cpp receive_task.h)
ENDIF(WIN32)

IF(UNIX)
  ADD_DEFINITIONS(-DUDP_DIR="\\"${NL_SHARE_PREFIX}/nl_sample_udp/\\"")
ENDIF(UNIX)

IF(WITH_3D)
  ADD_DEFINITIONS(-DUSE_3D)
  DECORATE_NEL_LIB("nel3d")
  SET(NL3D_LIB ${LIBNAME})
ELSE(WITH_3D)
  SET(NL3D_LIB "")
ENDIF(WITH_3D)

INCLUDE_DIRECTORIES(${LIBXML2_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(nl_sample_udpclient ${PLATFORM_LINKFLAGS} ${NLNET_LIB} ${NL3D_LIB})
TARGET_LINK_LIBRARIES(nl_sample_udpserver ${PLATFORM_LINKFLAGS} ${NLNET_LIB})
IF(WIN32)
  SET_TARGET_PROPERTIES(nl_sample_udpclient PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libcmt")
  SET_TARGET_PROPERTIES(nl_sample_udpserver PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libcmt")
ENDIF(WIN32)
ADD_DEFINITIONS(${LIBXML2_DEFINITIONS})

INSTALL(TARGETS nl_sample_udpclient nl_sample_udpserver RUNTIME DESTINATION ${NL_BIN_PREFIX} COMPONENT samplesnet)
INSTALL(FILES bench_service.cfg client.cfg readme.txt DESTINATION ${NL_SHARE_PREFIX}/nl_sample_udp COMPONENT samplesnet)

IF(WITH_3D)
  INSTALL(FILES n019003l.pfb DESTINATION ${NL_SHARE_PREFIX}/nl_sample_udp COMPONENT samplesnet)
ENDIF(WITH_3D)
