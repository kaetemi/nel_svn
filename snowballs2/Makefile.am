#
# $Id: Makefile.am,v 1.4 2002/04/10 07:32:46 lecroart Exp $
#

MAINTAINERCLEANFILES = Makefile.in configure config.guess missing \
                       config.sub ltconfig aclocal.m4 config.h.in \
                       install-sh mkinstalldirs

EXTRA_DIST	     = acconfig.h bootstrap \
		       snowballs2.dsw

DIST_SUBDIRS	     = client server

SUBDIRS              = @SNO_SUBDIRS@

install-data-hook:
	mkdir -p ${DESTDIR}${logdir}
	mkdir -p ${DESTDIR}${pkgsysconfdir}
#
# Do not override existing config file
#
	test -f ${DESTDIR}${pkgsysconfdir}/client.cfg || cp client/client.cfg ${DESTDIR}${pkgsysconfdir}
	for service in frontend chat position ; \
	do \
		test -f ${DESTDIR}${pkgsysconfdir}/$${service}_service.cfg || cp ${srcdir}/server/$${service}/$${service}_service.cfg ${DESTDIR}${pkgsysconfdir} ; \
	done

uninstall-local:
	rm -f ${DESTDIR}${pkgsysconfdir}/client.cfg
	for service in frontend chat position ; \
	do \
		rm -f ${DESTDIR}${pkgsysconfdir}/$${service}_service.cfg ; \
	done

# End of Makefile.am
