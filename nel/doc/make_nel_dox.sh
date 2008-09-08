#!/bin/sh

cd ..
CURDIR=$(pwd)
cd doc
rm -rf html/*
doxygen nel.dox -DCURDIR