@ECHO OFF
ECHO Compiling...
windres resouce.rc -O coff -o resouce.res
ECHO Finished!
PAUSE