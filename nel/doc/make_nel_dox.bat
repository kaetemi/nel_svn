@echo off
R:
cd \code\nel\doc
del html\*.* /Q
s:\bin\doxygen nel.dox
S:\bin\hhc html\index.hhp
copy html\index.chm s:\doc\nel.chm
