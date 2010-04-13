del *.exe
del *.o
gcc -ggdb main.c -o app.exe
gdb app.exe
