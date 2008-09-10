FILE(GLOB SRC *.cpp)

DECORATE_NEL_LIB("nelnet")
SET(NLNET_LIB ${LIBNAME})

ADD_EXECUTABLE(nl_sample_udpclient client.cpp graph.cpp graph.h simlag.cpp simlag.h)

ADD_EXECUTABLE(nl_sample_udpserver bench_service.cpp receive_task.cpp receive_task.h)

INCLUDE_DIRECTORIES(${LIBXML2_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(nl_sample_udpclient ${PLATFORM_LINKFLAGS} ${NLNET_LIB})
TARGET_LINK_LIBRARIES(nl_sample_udpserver ${PLATFORM_LINKFLAGS} ${NLNET_LIB})
IF(WIN32)
  SET_TARGET_PROPERTIES(nl_sample_udpclient PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libcmt")
  SET_TARGET_PROPERTIES(nl_sample_udpserver PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libcmt")
ENDIF(WIN32)
ADD_DEFINITIONS(${LIBXML2_DEFINITIONS})

INSTALL(TARGETS nl_sample_udpclient nl_sample_udpserver RUNTIME DESTINATION bin)
INSTALL(FILES bench_service.cfg client.cfg readme.txt DESTINATION share/nel/nl_sample_udp)
