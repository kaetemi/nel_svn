#-----------------------------------------------------------------------------
#
# NeLNS
#    Author: Nevrax
#
# Notes:
#   * Changing install location: add -DCMAKE_INSTALL_PREFIX:PATH=/my/new/path
#   * Changing NeL prefix: add -DNEL_PREFIX_PATH:PATH=/my/nel/install
#
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Load some macros.
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
INCLUDE(CMakeModules/nel.cmake)

#-----------------------------------------------------------------------------
# Force out of source builds.
CHECK_OUT_OF_SOURCE()

IF(WIN32)
  SET(CMAKE_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/../3rdParty/include;${CMAKE_INCLUDE_PATH}")
  SET(CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/../3rdParty/lib;${CMAKE_INCLUDE_PATH}")
ENDIF(WIN32)

IF(DEFINED NEL_PREFIX_PATH)
  SET(CMAKE_INCLUDE_PATH "${NEL_PREFIX_PATH}/include;${CMAKE_INCLUDE_PATH}")
  SET(CMAKE_LIBRARY_PATH "${NEL_PREFIX_PATH}/lib;${CMAKE_INCLUDE_PATH}")
ENDIF(DEFINED NEL_PREFIX_PATH)

CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

PROJECT(NeLNS CXX C)
SET(NL_VERSION_MAJOR 0)
SET(NL_VERSION_MINOR 6)
SET(NL_VERSION_PATCH 1)
SET(NL_VERSION "${NL_VERSION_MAJOR}.${NL_VERSION_MINOR}.${NL_VERSION_PATCH}")

#-----------------------------------------------------------------------------
# Redirect output files
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)

#-----------------------------------------------------------------------------
# Set default config options
#
NL_SETUP_DEFAULT_OPTIONS()
NL_SETUP_PREFIX_PATHS()

#-----------------------------------------------------------------------------
# Override default options
#SET(WITH_COVERAGE       ON )
SET(WITH_3D	ON )

#-----------------------------------------------------------------------------
#Platform specifics

FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(LibXml2 REQUIRED)
FIND_PACKAGE(MySQL)

NL_SETUP_BUILD()

FIND_PACKAGE(NeLMISC)
FIND_PACKAGE(NeLNET)

IF(WIN32)
  INCLUDE(${CMAKE_ROOT}/Modules/Platform/Windows-cl.cmake)
  SET(WINSOCK2_LIB ws2_32.lib)
ENDIF(WIN32)

NL_SETUP_BUILD_FLAGS()

IF(UNIX)
  SET(ETCDIR "${NL_ETC_PREFIX}/nelns")
  SET(PKGDIR "${NL_SHARE_PREFIX}/nelns")
  SET(LOGDIR "${NL_LOG_PREFIX}/nelns")
  ADD_DEFINITIONS(-DNELNS_CONFIG="\\"${ETCDIR}\\"" -DNELNS_STATE="\\"${PKGDIR}\\"" -DNELNS_LOGS="\\"${LOGDIR}\\"")
  INSTALL(CODE "FILE(MAKE_DIRECTORY ${LOGDIR})")
ENDIF(UNIX)

ADD_SUBDIRECTORY(admin_executor_service)
ADD_SUBDIRECTORY(admin_service)
ADD_SUBDIRECTORY(naming_service)
ADD_SUBDIRECTORY(login_service)
ADD_SUBDIRECTORY(welcome_service)



#-----------------------------------------------------------------------------
#Packaging
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "NeL MMORPG Framework - Networking Services")
SET(CPACK_PACKAGE_VENDOR "OpenNeL")
SET(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_SOURCE_DIR}/README)
SET(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/COPYING)
SET(CPACK_PACKAGE_VERSION_MAJOR "${NL_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${NL_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${NL_VERSION_PATCH}")
SET(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR};NeLNS;ALL;/")
SET(CPACK_PACKAGE_EXECUTABLES "nelns-${NL_VERSION}" "nelns")

## Source Packages
SET(CPACK_PACKAGE_FILE_NAME "nelns-${NL_VERSION}")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "nelns-${NL_VERSION}")
IF(WIN32)
  SET(CPACK_GENERATOR "ZIP")
  SET(CPACK_SOURCE_GENERATOR "ZIP")
ELSE(WIN32)
  SET(CPACK_GENERATOR "TGZ")
  SET(CPACK_SOURCE_GENERATOR "TGZ")
ENDIF(WIN32)
set(CPACK_SOURCE_IGNORE_FILES
        "~$"
        "\\\\.cvsignore$"
        "^${CMAKE_SOURCE_DIR}.*/CVS/"
        "^${CMAKE_SOURCE_DIR}.*/\\\\.svn/"
        "^${CMAKE_SOURCE_DIR}/debian/"
        "^${CMAKE_SOURCE_DIR}/old/")
INCLUDE(${CMAKE_ROOT}/Modules/CPack.cmake)
