#-----------------------------------------------------------------------------
#
# Snowballs
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
INCLUDE(CMakeModules/opennel.cmake)

#-----------------------------------------------------------------------------
# Force out of source builds.
CHECK_OUT_OF_SOURCE()

IF(WIN32)
  SET(CMAKE_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/../3rdParty/include;${CMAKE_INCLUDE_PATH}")
  SET(CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/../3rdParty/lib;${CMAKE_LIBRARY_PATH}")
ENDIF(WIN32)

IF(DEFINED NEL_PREFIX_PATH)
  SET(CMAKE_INCLUDE_PATH "${NEL_PREFIX_PATH}/include;${CMAKE_INCLUDE_PATH}")
  SET(CMAKE_LIBRARY_PATH "${NEL_PREFIX_PATH}/lib;${CMAKE_LIBRARY_PATH}")
ENDIF(DEFINED NEL_PREFIX_PATH)

CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

PROJECT(Snowballs CXX C)
SET(SB_VERSION_MAJOR 0)
SET(SB_VERSION_MINOR 3)
SET(SB_VERSION_PATCH 0)
SET(SB_VERSION "${SB_VERSION_MAJOR}.${SB_VERSION_MINOR}.${SB_VERSION_PATCH}")

#-----------------------------------------------------------------------------
# Redirect output files
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)

#-----------------------------------------------------------------------------
# Set default config options
#
NL_SETUP_DEFAULT_OPTIONS()

#-----------------------------------------------------------------------------
# Override default options
OPTION(BUILD_CLIENT "Build the Snowballs Client" ON)
OPTION(BUILD_SERVER "Build the Snowballs Servers" ON)
SET(SNOWBALLS_CONFIG_FILE "${CMAKE_INSTALL_PREFIX}/share/nel/snowballs" CACHE FILEPATH "Snowballs config file location")
SET(SNOWBALLS_LOG_FILE "${CMAKE_INSTALL_PREFIX}/var/log/snowballs" CACHE FILEPATH "Snowballs log file location")

#-----------------------------------------------------------------------------
#Platform specifics

FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(LibXml2 REQUIRED)

NL_SETUP_BUILD()

FIND_PACKAGE(NeLMISC)
FIND_PACKAGE(NeLNET)

###
# An example of finding NeL 3D and CEGUI Renderer.
###
IF(BUILD_CLIENT)
  FIND_PACKAGE(FreeType)
  FIND_PACKAGE(NeL3D)
  FIND_PACKAGE(Jpeg)
  FIND_PACKAGE(NeLSOUND)
  FIND_PACKAGE(NeLSNDDRV)
  FIND_PACKAGE(NeLPACS)
  FIND_PACKAGE(NeLLIGO)
  FIND_PACKAGE(NeLGEORGES)
  
#    FIND_PACKAGE(CEGUI)
#    FIND_PACKAGE(NeLCEGUIRenderer)
ENDIF(BUILD_CLIENT)

IF(WIN32)
  INCLUDE(${CMAKE_ROOT}/Modules/Platform/Windows-cl.cmake)
  SET(WINSOCK2_LIB ws2_32.lib)
ENDIF(WIN32)

NL_SETUP_BUILD_FLAGS()

#IF(UNIX)
  #SET(PKGDIR "${CMAKE_INSTALL_PREFIX}/share/nel/snowballs/")
  #SET(LOGDIR "${CMAKE_INSTALL_PREFIX}/var/log/snowballs/")
  SET(PKGDIR "share/nel/snowballs")
  SET(LOGDIR "var/log/snowballs")
  #ADD_DEFINITIONS(-DSNOWBALLS_CONFIG="\\"${CMAKE_INSTALL_PREFIX}/${PKGDIR}/\\"" -DSNOWBALLS_STATE="\\"${CMAKE_INSTALL_PREFIX}/${PKGDIR}/\\"" -DSNOWBALLS_LOGS="\\"${CMAKE_INSTALL_PREFIX}/${LOGDIR}/\\"")
  ADD_DEFINITIONS(-DSNOWBALLS_CONFIG="\\"${SNOWBALLS_CONFIG_FILE}/\\"" -DSNOWBALLS_STATE="\\"${SNOWBALLS_LOG_FILE}/\\"" -DSNOWBALLS_LOGS="\\"${CMAKE_INSTALL_PREFIX}/${LOGDIR}/\\"")
#ENDIF(UNIX)

IF(BUILD_CLIENT)
  ADD_SUBDIRECTORY(client)
ENDIF(BUILD_CLIENT)

IF(BUILD_SERVER)
  ADD_SUBDIRECTORY(server)
ENDIF(BUILD_SERVER)

# packaging information
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "NeL MMORPG Framework - Snowballs Demo")
SET(CPACK_PACKAGE_VENDOR "OpenNeL")
SET(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_SOURCE_DIR}/README)
SET(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/COPYING)
SET(CPACK_PACKAGE_VERSION_MAJOR "${SB_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${SB_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${SB_VERSION_PATCH}")
SET(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR};Snowballs;ALL;/")
SET(CPACK_PACKAGE_EXECUTABLES "snowballs-${SB_VERSION}" "snowballs")

## Source Packages
SET(CPACK_PACKAGE_FILE_NAME "snowballs-${SB_VERSION}")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "snowballs-${SB_VERSION}")
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
