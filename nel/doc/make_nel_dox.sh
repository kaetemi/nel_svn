#!/bin/sh

cd ..
CURDIR=$(pwd)
cd -
rm -rf html
doxygen nel.dox -D$CURDIR
