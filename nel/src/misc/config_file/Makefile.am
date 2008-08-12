#
# $Id: Makefile.am,v 1.4 2005/04/04 09:45:06 cado Exp $
#

MAINTAINERCLEANFILES    = Makefile.in

noinst_LTLIBRARIES      = libconfig.la

AM_YFLAGS = --defines=cf_gramatical.h -p cf

AM_LFLAGS = -f -8 -Pcf -olex.yy.c

EXTRA_DIST = cf_gramatical.h

libconfig_la_SOURCES    = cf_lexical.lxx             \
                          cf_gramatical.yxx          \
                          config_file.cpp 

# End of Makefile.am
