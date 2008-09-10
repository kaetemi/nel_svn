###
# Build Library Name
#
# Arguments: name - undecorated library name
# Sets: LIBNAME - decorated library name
###
MACRO(DECORATE_NEL_LIB name)

  IF(WIN32)
    IF(NL_BUILD_MODE MATCHES "NL_RELEASE_DEBUG")
      SET(LIBNAME "${name}_rd")
    ELSE(NL_BUILD_MODE MATCHES "NL_RELEASE_DEBUG")
      IF(NL_BUILD_MODE MATCHES "NL_DEBUG")
        SET(LIBNAME "${name}_d")
      ELSE(NL_BUILD_MODE MATCHES "NL_DEBUG")
        SET(LIBNAME "${name}_r")
      ENDIF(NL_BUILD_MODE MATCHES "NL_DEBUG")
    ENDIF(NL_BUILD_MODE MATCHES "NL_RELEASE_DEBUG")
  ELSE(WIN32)
    SET(LIBNAME "${name}")
  ENDIF(WIN32)

ENDMACRO(DECORATE_NEL_LIB)

###
# Checks build vs. source location. Prevents In-Source builds.
###
MACRO(CHECK_OUT_OF_SOURCE)
  IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    MESSAGE(FATAL_ERROR "

CMake generation for this project is not allowed within the source directory!
Remove the CMakeCache.txt file and try again from another folder, e.g.:

   rm CMakeCache.txt
   mkdir cmake
   cd cmake
   cmake -G \"Unix Makefiles\" ..
    ")
  ENDIF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})

ENDMACRO(CHECK_OUT_OF_SOURCE)

MACRO(NL_SETUP_DEFAULT_OPTIONS)
  ###
  # Features
  ###
  OPTION(WITH_LOGGING             "With Logging"                                  ON )
  OPTION(WITH_COVERAGE            "With Code Coverage Support"                    OFF)

  ###
  # Core libraries
  ###
  OPTION(WITH_NET                 "Build NLNET"                                   OFF)
  OPTION(WITH_3D                  "Build NL3D"                                    OFF)
  OPTION(WITH_PACS                "Build NLPACS"                                  OFF)
  OPTION(WITH_GEORGES             "Build NLGEORGES"                               OFF)
  OPTION(WITH_LIGO                "Build NLLIGO"                                  OFF)
  OPTION(WITH_SOUND               "Build NLSOUND"                                 OFF)

  ###
  # Drivers Support
  ###
  OPTION(WITH_DRIVER_OPENAL       "Build OpenAL Driver"                           OFF)
  OPTION(WITH_DRIVER_OPENGL       "Build OpenGL Driver"                           OFF)
  OPTION(WITH_DRIVER_DIRECT3D     "Build Direct3D Driver"                         OFF)

  ###
  # Optional support
  ###
  OPTION(WITH_CEGUI       "Build CEGUI Renderer"                                  OFF)
  OPTION(WITH_TOOLS       "Build NeL Tools"                                       OFF)
  OPTION(WITH_SAMPLES     "Build NeL Samples"                                     ON )
  OPTION(WITH_TESTS       "Build NeL Unit Tests"                                  OFF)
  OPTION(WITH_GTK         "With GTK Support"                                      OFF)

ENDMACRO(NL_SETUP_DEFAULT_OPTIONS)

MACRO(NL_SETUP_BUILD)

  #-----------------------------------------------------------------------------
  # Setup the buildmode variables.
  #
  # None                  = NL_RELEASE_DEBUG
  # Debug                 = NL_DEBUG
  # Release               = NL_RELEASE
  # RelWithDebInfo        = NL_RELEASE_DEBUG
  # MinSizeRel            = NL_RELEASE_DEBUG

  IF(CMAKE_BUILD_TYPE MATCHES "Debug")
    SET(NL_BUILD_MODE "NL_DEBUG")
  ELSE(CMAKE_BUILD_TYPE MATCHES "Debug")
    IF(CMAKE_BUILD_TYPE MATCHES "Release")
      SET(NL_BUILD_MODE "NL_RELEASE")
    ELSE(CMAKE_BUILD_TYPE MATCHES "Release")
      SET(NL_BUILD_MODE "NL_RELEASE_DEBUG")
    ENDIF(CMAKE_BUILD_TYPE MATCHES "Release")
  ENDIF(CMAKE_BUILD_TYPE MATCHES "Debug")

  IF(WIN32)
    SET(NL_DEBUG_CFLAGS "/ZI /Gy /GS-")
    SET(NL_RELEASE_CFLAGS "/Ox /Ob2 /Oi /Ot /Oy /GT /GL /GF")
    SET(NL_RELEASEDEBUG_CFLAGS "/DNL_RELEASE_DEBUG /Ob2 /GF")
  ELSE(WIN32)
    SET(PLATFORM_CFLAGS "-ftemplate-depth-24 -D_REENTRANT -Wall -ansi -W -Wpointer-arith -Wsign-compare -Wno-deprecated-declarations -Wno-multichar -Wno-long-long -Wno-unused")
    SET(PLATFORM_LINKFLAGS "${CMAKE_THREAD_LIBS_INIT} -lc -lm -lstdc++ -lrt")
    SET(NL_DEBUG_CFLAGS "-DNL_DEBUG -g")
    SET(NL_RELEASE_CFLAGS "-DNL_RELEASE -O6")
    SET(NL_RELEASEDEBUG_CFLAGS "-DNL_RELEASE_DEBUG -g -finline-functions -O3 ")
    SET(NL_NONE_CFLAGS "-DNL_RELEASE_DEBUG -g -finline-functions -O3 ")
  ENDIF(WIN32)
ENDMACRO(NL_SETUP_BUILD)

MACRO(NL_SETUP_BUILD_FLAGS)
  ## None
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${NL_NONE_CFLAGS} ${PLATFORM_CFLAGS} ")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${NL_NONE_CFLAGS} ${PLATFORM_CFLAGS} ")

  ## Debug
  SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${NL_DEBUG_CFLAGS} ${PLATFORM_CFLAGS} ")
  SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${NL_DEBUG_CFLAGS} ${PLATFORM_CFLAGS} ")

  ## Release
  SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${NL_RELEASE_CFLAGS} ${PLATFORM_CFLAGS} ")
  SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${NL_RELEASE_CFLAGS} ${PLATFORM_CFLAGS} ")

  ## RelWithDebInfo
  SET(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} ${NL_RELEASEDEBUG_CFLAGS} ${PLATFORM_CFLAGS} ")
  SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${NL_RELEASEDEBUG_CFLAGS} ${PLATFORM_CFLAGS} ")

  ## MinSizeRel
  SET(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} ${NL_RELEASEDEBUG_CFLAGS} ${PLATFORM_CFLAGS} ")
  SET(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} ${NL_RELEASEDEBUG_CFLAGS} ${PLATFORM_CFLAGS} ")
ENDMACRO(NL_SETUP_BUILD_FLAGS)
