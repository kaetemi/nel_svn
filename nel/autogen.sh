#!/bin/sh -

set -x

WANT_AUTOMAKE="1.6"

aclocal \
&& libtoolize --force \
&& autoheader \
&& automake --gnu --add-missing \
&& autoconf
#&& ./configure \
#&& make
