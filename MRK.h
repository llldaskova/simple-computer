#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <string.h>
enum keys
{
	KEY_I,
	KEY_L,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_F5,
	KEY_F6,
	KEY_UP,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_ENTER,
	ERROR
};
extern struct termios buff;
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
int rk_mytermsave();
int rk_mytermrestore();
int rk_mytermsave2();
int rk_mytermrestore2();
int rk_readkey(enum keys* key);
