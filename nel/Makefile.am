#
# $Id: Makefile.am,v 1.11 2005/04/04 11:53:51 cado Exp $
#

MAINTAINERCLEANFILES = Makefile.in configure libtool config.guess \
                       config.sub ltconfig aclocal.m4 config.h.in \
                       install-sh missing mkinstalldirs ltmain.sh \
                       include/nelconfig.h include/nelconfig.h.in \
                       include/nel/nelconfig.h

DISTCLEANFILES       = include/stamp-h include/stamp-h.in 

SUBDIRS              = include src

bin_SCRIPTS          = nel-config

EXTRA_DIST           = acconfig.h nel.dsw bootstrap doc tools

dist-hook:
	find $(distdir) -name CVS -print | xargs rm -fr

# End of Makefile.am

