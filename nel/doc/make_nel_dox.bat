@echo off
cd ..
set CURDIR=%CD%
cd doc
del html\*.* /Q
doxygen nel.dox -DCURDIR
S:\bin\hhc html\index.hhp
copy html\index.chm nel.chm
pause
