# ====================================================================
# Configuration script for NeL
# ====================================================================
#
# $Id: configure.ac,v 1.8 2005/04/14 15:54:32 cado Exp $
# 

# ====================================================================
# Process this file with autoconf to produce a configure script.
# ====================================================================

# If you want to change the version, must must change AC_INIT
# *and* AC_SUBST(LIBTOOL_VERSION)

AC_PREREQ(2.57)
AC_INIT([nel],[0.4.0],[nel-all@nevrax.org])
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR(include/nel/misc/types_nl.h)
AM_CONFIG_HEADER(include/nelconfig.h)

AC_SUBST(LIBTOOL_VERSION, [0:4:0])

# Checks for programs.
AC_CANONICAL_HOST
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_YACC
AC_PROG_LIBTOOL
AM_PROG_LIBTOOL
AM_PROG_LEX
AM_SANITY_CHECK

AM_PATH_CCACHE
AM_MAINTAINER_MODE


# Template needed to generate the nelconfig.h.in
AH_TEMPLATE([NEL_DEFAULT_DISPLAYER],[Define to 1 if you want log on standard output])
AH_TEMPLATE([NEL_LOG_IN_FILE],[Define to 1 if you want a debug log.log file in the current directory])
AH_TEMPLATE([HAVE_X86],[Define to 1 if you are on a INTEL compatible processor])
AH_TEMPLATE([HAVE_X86_64],[Define to 1 if you are on AMD opteron 64bits processor])

# Get host type info
if test "$host_cpu" = "i386" -o "$host_cpu" = "i486" -o "$host_cpu" = "i586" \
     -o "$host_cpu" = "i686" -o "$host_cpu" = "i786" -o "$host_cpu" = "x86_64"
then
    AC_DEFINE([HAVE_X86])
fi

if test "$host_cpu" = "x86_64"
then
    AC_DEFINE([HAVE_X86_64])
fi

# The following hack should ensure that configure doesnt add optimizing
# or debugging flags to CFLAGS or CXXFLAGS
CFLAGS="$CFLAGS -ftemplate-depth-24"
CXXFLAGS="$CXXFLAGS -ftemplate-depth-24"


# ====================================================================
# Checks NeL modules (net, 3d) to install / Disable
# ====================================================================

# The misc is mandatory, it is use by the other modules.

NEL_SUBDIRS="misc"

# NeL libraries that are enabled by default

# Network library
AC_ARG_ENABLE([net],
              AC_HELP_STRING([--disable-net],
                             [disable compilation and install of NeL Network]),
              [],
              [enable_net=yes])

if test $enable_net = "no"
then
   AC_MSG_RESULT([disable NeL Network])
else
   NEL_SUBDIRS="$NEL_SUBDIRS net"
fi

# 3D library
AC_ARG_ENABLE([3d],
              AC_HELP_STRING([--disable-3d],
                             [disable compilation and install of NeL 3D]),
              [],
              [enable_3d=yes])

if test $enable_3d = "no"
then
   AC_MSG_RESULT([disable NeL 3D])
else
   NEL_SUBDIRS="$NEL_SUBDIRS 3d"
fi

# PACS library
AC_ARG_ENABLE([pacs],
              AC_HELP_STRING([--disable-pacs],
                             [disable compilation and install of NeL PACS]),
              [],
              [enable_pacs=yes])

if test $enable_pacs = "no"
then
   AC_MSG_RESULT([disable NeL PACS])
else
   NEL_SUBDIRS="$NEL_SUBDIRS pacs"
fi

# Georges library
AC_ARG_ENABLE([georges],
              AC_HELP_STRING([--disable-georges],
                             [disable compilation and install of NeL Georges]),
              [],
              [enable_georges=yes])

if test $enable_georges = "no"
then
   AC_MSG_RESULT([disable NeL Georges])
else
   NEL_SUBDIRS="$NEL_SUBDIRS georges"
fi

# Ligo library
AC_ARG_ENABLE([ligo],
              AC_HELP_STRING([--disable-ligo],
                             [disable compilation and install of NeL Ligo]),
              [],
              [enable_ligo=yes])

if test $enable_ligo = "no"
then
   AC_MSG_RESULT([disable NeL Ligo])
else
   NEL_SUBDIRS="$NEL_SUBDIRS ligo"
fi

# Memory library
AC_ARG_ENABLE([memory],
              AC_HELP_STRING([--disable-memory],
                             [disable compilation and install of NeL Memory]),
              [],
              [enable_memory=yes])

if test $enable_memory = "no"
then
   AC_MSG_RESULT([disable NeL Memory])
else
   NEL_SUBDIRS="$NEL_SUBDIRS memory"
fi

# NeL libraries that are disabled by default

# Sound library
AC_ARG_ENABLE([sound],
              AC_HELP_STRING([--enable-sound],
                             [enable compilation and install of NeL Sound]),
              [],
              [enable_sound=no])

if test $enable_sound = "yes"
then
   AC_MSG_RESULT([enable NeL Sound])
   NEL_SUBDIRS="$NEL_SUBDIRS sound"
fi

AC_SUBST([enable_net])
AC_SUBST([enable_3d])
AC_SUBST([enable_pacs])
AC_SUBST([enable_sound])
AC_SUBST([enable_georges])
AC_SUBST([enable_ligo])
AC_SUBST([enable_memory])

AC_SUBST([NEL_SUBDIRS])


# ====================================================================
# Checks for programs.
# ====================================================================

# ====================================================================
# Configure Settings
# ====================================================================

# Disable the static linking by default
# AC_DISABLE_STATIC

# Use C++ compiler as a default for the compilation tests.
AC_LANG([C++])


# ====================================================================
# Debug/optimized compilation mode
# ====================================================================

AM_NEL_DEBUG

AC_ARG_WITH([logging],
            AC_HELP_STRING([--without-logging],
                           [be silent on stdout and in no log.log]),
            [],
            [with_logging=yes])

if test "$with_logging" = "yes"
then
	AC_DEFINE([NEL_DEFAULT_DISPLAYER], 1)
	AC_DEFINE([NEL_LOG_IN_FILE], 1)
fi

# ====================================================================
# Checks for typedefs, structures, and compiler characteristics.
# ====================================================================

# Test endianness
AC_C_BIGENDIAN

# Supress GCC "multi-character character constant" warnings.
if test "X$CC" = "Xgcc";
then
    if test "$with_debug" = "yes"
    then
	#
	# When debugging variables are declared for the sole purpose of
	# inspecting their content with a debugger. They are not used
	# in the code itself and this is legitimate, hence the -Wno-unused
	#
        CXXFLAGS="$CXXFLAGS -Wno-unused"
    fi
fi

# Add some common define
if test "X$CC" = "Xgcc";
then
    CFLAGS="$CFLAGS -D_REENTRANT -Wall -ansi -W -Wpointer-arith -Wsign-compare -Wno-deprecated-declarations -Wno-multichar -Wno-long-long -Wno-unused"
    CXXFLAGS="$CXXFLAGS -D_REENTRANT -Wall -ansi -W -Wpointer-arith -Wsign-compare -Wno-deprecated-declarations -Wno-multichar -Wno-long-long -Wno-unused"
#    CFLAGS="$CFLAGS -D_REENTRANT -Wno-multichar -Wno-long-long"
#    CXXFLAGS="$CXXFLAGS -D_REENTRANT -Wno-multichar -Wno-long-long"
fi


# ====================================================================
# Checks for header and lib files.
# ====================================================================

AC_FUNC_ALLOCA
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_HEADER_TIME
AC_CHECK_HEADERS([arpa/inet.h fcntl.h float.h malloc.h netdb.h netinet/in.h stddef.h stdlib.h string.h sys/ioctl.h sys/socket.h unistd.h sys/time.h])
AC_CHECK_LIB([pthread], [pthread_create])
AC_CHECK_LIB([dl], [dlopen])


# ====================================================================
# Checks for typedefs, structures, and compiler characteristics.
# ====================================================================

AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_STRUCT_TM
AC_C_VOLATILE
AC_CHECK_TYPES([ptrdiff_t])


# ====================================================================
# Checks for library functions.
# ====================================================================

AC_FUNC_CLOSEDIR_VOID
AC_FUNC_ERROR_AT_LINE
AC_PROG_GCC_TRADITIONAL
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_REALLOC
AC_FUNC_SELECT_ARGTYPES
AC_TYPE_SIGNAL
AC_FUNC_STAT
AC_FUNC_STRFTIME
AC_FUNC_FORK
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([floor getcwd gethostbyaddr gethostbyname gethostname gettimeofday inet_ntoa memmove memset mkdir pow select socket sqrt strcasecmp strchr strdup strerror strrchr strstr strtoul sys/time.h])


# ====================================================================
# X11

AC_PATH_X

if test ! "$no_x" = "yes"
then
    if test ! X"$x_libraries" = X
    then
        LIBS="$LIBS -L$x_libraries"
    fi

    if test ! X"$x_includes" = X
    then
        CXXFLAGS="$CXXFLAGS -I$x_includes"
    fi
else
    if test "$enable_3d" = "yes"
    then
        AC_MSG_ERROR([X11 must be installed for NeL 3d library, use --disable-3d if you don't need NeL 3d library])
    fi
fi

# ====================================================================
# LibXML

# Use C compiler as a default for the libxml tests.
AC_LANG([C])

AM_PATH_XML2([2.0.0], [], [AC_MSG_ERROR([libxml2 must be installed])])

CFLAGS="$CFLAGS $XML_CFLAGS $XML_CPPFLAGS"
CXXFLAGS="$CXXFLAGS $XML_CFLAGS $XML_CPPFLAGS"

LIBS="$LIBS $XML_LIBS"

# Use C++ compiler as a default for the compilation tests.
AC_LANG([C++])


# ====================================================================
# STLPort

AM_PATH_STLPORT


# ====================================================================
# Checks for libraries.
# ====================================================================

# ====================================================================
# FreeType 2

AM_PATH_FREETYPE($enable_3d)


# ====================================================================
# OpenGL

AM_PATH_OPENGL($enable_3d)


# ====================================================================
# Check for XF86VidMode extension (-lXxf86vm)

AM_PATH_XF86VIDMODE


# ====================================================================
# FMOD

AM_PATH_FMOD($enable_sound)


# ====================================================================
# Arrange for the include directory to be in the search path even when
# build is done outside the source tree
# Put the nelconfig.h define
CFLAGS="$CFLAGS -I\${top_srcdir}/include -DHAVE_NELCONFIG_H"
CXXFLAGS="$CXXFLAGS -I\${top_srcdir}/include -DHAVE_NELCONFIG_H"

# ====================================================================
# Checks for library functions.
# ====================================================================


# ====================================================================
# Output files to generate.
# ====================================================================

AC_CONFIG_FILES([Makefile                                        \
           include/Makefile                                \
           include/nel/Makefile                            \
           include/nel/ligo/Makefile                       \
           include/nel/misc/Makefile                       \
           include/nel/net/Makefile                        \
           include/nel/3d/Makefile                         \
           include/nel/pacs/Makefile                       \
           include/nel/sound/Makefile                      \
           include/nel/memory/Makefile                     \
           include/nel/georges/Makefile                    \
           src/Makefile                                    \
           src/misc/Makefile                               \
           src/misc/config_file/Makefile                   \
           src/net/Makefile                                \
           src/memory/Makefile                             \
           src/3d/Makefile                                 \
           src/3d/driver/Makefile                          \
           src/3d/driver/opengl/Makefile                   \
           src/pacs/Makefile                               \
           src/sound/Makefile                              \
           src/sound/driver/Makefile                       \
           src/sound/driver/fmod/Makefile                  \
           src/georges/Makefile                            \
           src/ligo/Makefile                               \
           tools/Makefile                                  \
           tools/3d/Makefile                               \
           tools/3d/build_coarse_mesh/Makefile             \
           tools/3d/build_far_bank/Makefile                \
           tools/3d/build_smallbank/Makefile               \
           tools/3d/ig_lighter/Makefile                    \
           tools/3d/ig_lighter_lib/Makefile                \
           tools/3d/panoply_maker/Makefile                 \
           tools/3d/zone_dependencies/Makefile             \
           tools/3d/zone_ig_lighter/Makefile               \
           tools/3d/zone_lib/Makefile                      \
           tools/3d/zone_lighter/Makefile                  \
           tools/3d/zone_welder/Makefile                   \
           samples/Makefile                                \
           samples/sound_sources/Makefile                  \
           samples/pacs/Makefile                           \
           samples/georges/Makefile                        \
           samples/3d/Makefile                             \
           samples/3d/font/Makefile                        \
           samples/3d/cluster_viewer/Makefile              \
	   samples/net/Makefile                            \
	   samples/net/chat/Makefile                       \
           nel-config                                      \
])
AC_OUTPUT

# End of configure.in
