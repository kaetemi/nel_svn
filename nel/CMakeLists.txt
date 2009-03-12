#-----------------------------------------------------------------------------
#
# NeL
#  Authors: Nevrax and the NeL Community
#  Version: 0.6.1
#
# Notes:
#   * Changing install location: add -DCMAKE_INSTALL_PREFIX:PATH=/my/new/path
#   * Enable building of documentation: add -DBUILD_DOCUMENTATION:BOOL=ON - new make target: DoxygenDoc
#   * Updating version: update header (above) but also update NL_VERSION below.
#   * To build binary archive, use the 'package' target.
#     To build source archive, use the 'package_source' target.

#-----------------------------------------------------------------------------
# Load some macros.
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
INCLUDE(${CMAKE_SOURCE_DIR}/CMakeModules/nel.cmake)
INCLUDE(${CMAKE_ROOT}/Modules/Documentation.cmake OPTIONAL)
INCLUDE(InstallRequiredSystemLibraries)

# Force out of source builds.
CHECK_OUT_OF_SOURCE()

IF(WIN32)
  SET(CMAKE_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/../3rdParty/include;${CMAKE_INCLUDE_PATH}")
  SET(CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/../3rdParty/lib;${CMAKE_LIBRARY_PATH}")
ENDIF(WIN32)

CMAKE_MINIMUM_REQUIRED(VERSION 2.4)
PROJECT(NeL CXX C)
SET(NL_VERSION_MAJOR 0)
SET(NL_VERSION_MINOR 6)
SET(NL_VERSION_PATCH 1)
SET(NL_VERSION "${NL_VERSION_MAJOR}.${NL_VERSION_MINOR}.${NL_VERSION_PATCH}")

#-----------------------------------------------------------------------------
# Redirect output files
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)

#-----------------------------------------------------------------------------
# Set CMake 2.6 Policies.
IF(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)

#-----------------------------------------------------------------------------
# Set default config options
#
NL_SETUP_DEFAULT_OPTIONS()

#-----------------------------------------------------------------------------
#Platform specifics

FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(LibXml2 REQUIRED)
FIND_PACKAGE(PNG REQUIRED)

NL_SETUP_BUILD()

IF(WITH_3D)
  FIND_PACKAGE(FreeType)
  FIND_PACKAGE(Jpeg)

  IF(WITH_DRIVER_OPENGL)
    FIND_PACKAGE(OpenGL)
  ENDIF(WITH_DRIVER_OPENGL)

  IF(WITH_CEGUI)
    FIND_PACKAGE(CEGUI) 
  ENDIF(WITH_CEGUI)

ENDIF(WITH_3D)

IF(WITH_SOUND)
  IF(WITH_DRIVER_OPENAL)
    FIND_PACKAGE(OpenAL)
  ENDIF(WITH_DRIVER_OPENAL)

  IF(WITH_DRIVER_FMOD)
    FIND_PACKAGE(FMOD)
  ENDIF(WITH_DRIVER_FMOD)
ENDIF(WITH_SOUND)

IF(WITH_GTK)
  FIND_PACKAGE(GTK2)
ENDIF(WITH_GTK)

IF(WITH_TESTS)
#  FIND_PACKAGE(CppUnit)
  FIND_PACKAGE(CppTest)
  ENABLE_TESTING()
  ADD_TEST(nel_unit_test ${EXECUTABLE_OUTPUT_PATH}/nel_unit_test --html)
ENDIF(WITH_TESTS)

IF(UNIX)
  SET(prefix ${CMAKE_INSTALL_PREFIX})
  SET(exec_prefix ${CMAKE_INSTALL_PREFIX}/bin)
  SET(libdir "${CMAKE_INSTALL_PREFIX}/lib ${PLATFORM_LINKFLAGS}")
  SET(includedir "${CMAKE_INSTALL_PREFIX}/include ${PLATFORM_CFLAGS}")
  SET(enable_ligo ${WITH_LIGO})
  SET(enable_logic ${WITH_LOGIC})
  SET(enable_georges ${WITH_GEORGES})
  SET(enable_net ${WITH_NET})
  SET(enable_3d ${WITH_3D})
  SET(enable_pacs ${WITH_PACS})
  SET(enable_sound ${WITH_SOUND})
  CONFIGURE_FILE(nel-config.in nel-config)

  INSTALL(PROGRAMS ${CMAKE_BINARY_DIR}/nel-config DESTINATION bin)
ENDIF(UNIX)

IF(WIN32)
  INCLUDE(${CMAKE_ROOT}/Modules/Platform/Windows-cl.cmake)
  
  SET(WINSOCK2_LIB ws2_32.lib)
  
ENDIF(WIN32)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

NL_SETUP_BUILD_FLAGS()

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(include)

IF(WITH_SAMPLES)
  ADD_SUBDIRECTORY(samples)
ENDIF(WITH_SAMPLES)

IF(WITH_TOOLS)
  ADD_SUBDIRECTORY(tools)
ENDIF(WITH_TOOLS)

# To build the documention, you will have to enable it
# and then do the equivalent of "make DoxygenDoc".
IF(BUILD_DOCUMENTATION)
    IF(DOT)
        SET(HAVE_DOT YES)
    ELSE(DOT)
        SET(HAVE_DOT NO)
    ENDIF(DOT)
    # This processes our Doxyfile.in and substitutes paths to generate
    # a final Doxyfile
    CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/doc/Doxyfile.cmake.in ${CMAKE_BINARY_DIR}/doc/Doxyfile)

    ADD_CUSTOM_TARGET(DoxygenDoc ${DOXYGEN} ${CMAKE_BINARY_DIR}/doc/Doxyfile)
ENDIF(BUILD_DOCUMENTATION)

# packaging information
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "NeL MMORPG Framework")
SET(CPACK_PACKAGE_VENDOR "NeL")
SET(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_SOURCE_DIR}/README)
SET(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/COPYING)
SET(CPACK_PACKAGE_VERSION_MAJOR "${NL_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${NL_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${NL_VERSION_PATCH}")
SET(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR};NeL;ALL;/")
SET(CPACK_PACKAGE_EXECUTABLES "nel${NL_VERSION}" "nel")

## Package component names
SET(CPACK_COMPONENTS_ALL libraries 3ddrivers sounddrivers headers)
set(CPACK_ALL_INSTALL_TYPES Full Developer)

#set(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "MyLib Application")
#set(CPACK_COMPONENT_APPLICATIONS_DESCRIPTION "An extremely useful application that makes use of MyLib")
#set(CPACK_COMPONENT_APPLICATIONS_GROUP "Runtime")

SET(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
SET(CPACK_COMPONENT_LIBRARIES_DESCRIPTION
   "Libraries used to build programs with NeL")
SET(CPACK_COMPONENT_LIBRARIES_GROUP "Development")
SET(CPACK_COMPONENT_LIBRARIES_INSTALL_TYPES Developer Full)
   
SET(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ Headers")
SET(CPACK_COMPONENT_HEADERS_DESCRIPTION
   "C++ headers used to build programs with NeL")
SET(CPACK_COMPONENT_HEADERS_GROUP "Development")
SET(CPACK_COMPONENT_HEADERS_INSTALL_TYPES Developer Full)   
   
SET(CPACK_COMPONENT_3DDRIVERS_DISPLAY_NAME "3D Drivers")
SET(CPACK_COMPONENT_3DDRIVERS_DESCRIPTION
   "3D Drivers for running NeL based applications.")
SET(CPACK_COMPONENT_3DDRIVERS_GROUP "Drivers")
set(CPACK_COMPONENT_3DDRIVERS_INSTALL_TYPES Full)
   
SET(CPACK_COMPONENT_SOUNDDRIVERS_DISPLAY_NAME "Sound Drivers")
SET(CPACK_COMPONENT_SOUNDDRIVERS_DESCRIPTION
   "Sound Drivers for running NeL based applications.")
SET(CPACK_COMPONENT_SOUNDDRIVERS_GROUP "Drivers")
set(CPACK_COMPONENT_SOUNDDRIVERS_INSTALL_TYPES Full)

set(CPACK_COMPONENT_GROUP_DEVELOPMENT_DESCRIPTION
   "All of the tools you'll ever need to develop software")

set(CPACK_COMPONENT_GROUP_DRIVERS_DESCRIPTION
   "The drivers needed to run NeL-based software.")
 
  
 
 set(CPACK_COMPONENT_APPLICATIONS_INSTALL_TYPES Full)




## Source Packages
SET(CPACK_PACKAGE_FILE_NAME "nel-${NL_VERSION}")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "nel-${NL_VERSION}")
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

## Debian Packages
#INCLUDE(UseDebian)
#IF(DEBIAN_FOUND)
#  ADD_DEBIAN_TARGETS(nel)
#ENDIF(DEBIAN_FOUND)
