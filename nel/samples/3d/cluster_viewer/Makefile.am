#
# $Id: Makefile.am,v 1.1 2005/04/04 09:45:06 cado Exp $
#

MAINTAINERCLEANFILES      = Makefile.in

bin_PROGRAMS              = cluster_viewer

cluster_viewer_SOURCES = main.cpp

AM_CXXFLAGS               = -I$(top_srcdir)/src 

cluster_viewer_LDADD   = ../../../src/misc/libnelmisc.la \
                         ../../../src/3d/libnel3d.la


# End of Makefile.am

