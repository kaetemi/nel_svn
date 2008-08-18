#
# $Id: Makefile.am,v 1.1 2005/04/13 12:37:26 cado Exp $
#

MAINTAINERCLEANFILES      = Makefile.in

bin_PROGRAMS              = chatserver chatclient

chatserver_SOURCES = server.cpp

chatclient_SOURCES = client.cpp kbhit.h kbhit.cpp

AM_CXXFLAGS               = -I$(top_srcdir)/src 

chatserver_LDADD   = ../../../src/misc/libnelmisc.la \
                     ../../../src/net/libnelnet.la 

chatclient_LDADD   = ../../../src/misc/libnelmisc.la \
                     ../../../src/net/libnelnet.la 

# End of Makefile.am

