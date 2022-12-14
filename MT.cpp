#include "MT.h"

int mt_clrscr()
{
    printf("\E[H\E[2J");
    return 0;
}

int mt_gotoXY(int X, int Y)
{
    printf("\E[%d;%dH",X,Y);
    return 0;
}

int mt_getscreensize(int *rows, int *cols)
{
    struct winsize ws;
    if(!ioctl(1, TIOCGWINSZ, &ws))
    {
        (*rows) = ws.ws_row;
        (*cols) = ws.ws_col;
        return 0;
    }
    else
        return -1;
}

int mt_setfgcolor(enum colors color)
{
    printf("\E[3%dm",color);
    return 0;
}

int mt_setbgcolor(enum colors color)
{
    printf("\E[4%dm",color);
    return 0;
}

