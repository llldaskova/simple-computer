#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include<termios.h>
enum colors {Black, Red, Green, Yellow, Blue, Dark, Cyan, White, Standart = 9};
int mt_clrscr();
int mt_gotoXY(int X, int Y);
int mt_getscreensize(int *rows, int *cols);
int mt_setfgcolor(enum colors color);
int mt_setbgcolor(enum colors color);
