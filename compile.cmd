@ECHO OFF
gcc main.c game.c egg.c beef.c .\raylib\src\text.c -I "raylib\src" -lraylib -lopengl32 -lgdi32 -lwinmm -std=c99 -mwindows -o demonEgg
ECHO Finished!
PAUSE