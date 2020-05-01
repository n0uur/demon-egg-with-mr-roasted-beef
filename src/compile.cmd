@ECHO OFF
ECHO Compiling...
gcc main.c game.c egg.c beef.c .\external\raylib\src\text.c -I "external\raylib\src" -lraylib -lopengl32 -lgdi32 -lwinmm -std=c99 -mwindows -o ..\bin\demonEgg
ECHO Finished!
PAUSE