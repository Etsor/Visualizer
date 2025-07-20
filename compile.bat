@echo off

gcc -o visualizer src/*c -I include -L lib -lraylib -lgdi32 -lwinmm 
