#!/bin/bash
gcc shell.c -I./libshell -L./libshell -lshell -o shell
gnome-terminal -- ./shell
