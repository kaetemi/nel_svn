DECORATE_NEL_LIB("nelnet")
SET(NLNET_LIB ${LIBNAME})

ADD_EXECUTABLE(nl_sample_ct_ai_service ai_service.cpp)

ADD_EXECUTABLE(nl_sample_ct_gd_service gd_service.cpp)

ADD_DEFINITIONS(-DNL_CT_CFG="\\"${NL_SHARE_PREFIX}/nl_sample_class_transport/\\"")

INCLUDE_DIRECTORIES(${LIBXML2_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(nl_sample_ct_ai_service ${PLATFORM_LINKFLAGS} ${NLNET_LIB})
TARGET_LINK_LIBRARIES(nl_sample_ct_gd_service ${PLATFORM_LINKFLAGS} ${NLNET_LIB})
IF(WIN32)
  SET_TARGET_PROPERTIES(nl_sample_ct_ai_service PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libcmt /SUBSYSTEM:WINDOWS")
  SET_TARGET_PROPERTIES(nl_sample_ct_gd_service PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libcmt /SUBSYSTEM:WINDOWS")
ENDIF(WIN32)
ADD_DEFINITIONS(${LIBXML2_DEFINITIONS})

INSTALL(TARGETS nl_sample_ct_ai_service nl_sample_ct_gd_service RUNTIME DESTINATION bin COMPONENT samplesnet)
INSTALL(FILES ai_service.cfg gd_service.cfg DESTINATION share/nel/nl_sample_class_transport COMPONENT samplesnet)
