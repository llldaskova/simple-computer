#include "MRK.h"
struct termios buff;
struct termios buff2;
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
	if ((regime!=0&&regime!=1)||(vtime!=0&&vtime!=1)||(vmin!=0&&vmin!=1)||(echo!=0&&echo!=1)||(sigint!=0&&sigint!=1))
		return -1;
	struct termios ws;
	tcgetattr(0,&ws);//текущие настройки
	
	if(regime)
		ws.c_lflag|=ICANON;
	else
	{
		ws.c_lflag&=~ICANON;
		ws.c_cc[VMIN]=vmin;
		ws.c_cc[VTIME]=vtime;
	}
	if(echo)//символы выводятся в консоли
		ws.c_lflag|=ECHO;
	else
		ws.c_lflag&=~ECHO;
	if(sigint)
		ws.c_lflag|=ISIG;
	else
		ws.c_lflag&=~ISIG;
	tcsetattr(0,TCSANOW,&ws);
	return 0;
}
int rk_mytermsave()
{
	tcgetattr(0,&buff);
	return 0;
}
int rk_mytermrestore()
{
	tcsetattr(0,TCSANOW,&buff);
	return 0;
}
int rk_mytermsave2()
{
	tcgetattr(0,&buff2);
	return 0;
}
int rk_mytermrestore2()
{
	tcsetattr(0,TCSANOW,&buff2);
	return 0;
}
int rk_readkey(enum keys* key)
{
	char temp[8];
	rk_mytermsave();
	//printf("1");
	rk_mytermregime(0,0,1,0,1);
	read(0,&temp,8);
	switch(temp[0])
	{
		case 'e':
			*key=KEY_ENTER;
			break;
		case 'l':
			*key=KEY_L;
			break;
		case 's':
			*key=KEY_S;
			break;
		case 'r':
			*key=KEY_R;
			break;
		case 't':
			*key=KEY_T;
			break;
		case 'i':
			*key=KEY_I;
			break;
		case '\E':
			//read(0,&temp,1);
			//read(0,&temp,1);
			switch((int)temp[2])
			{
				case 65:
					*key=KEY_UP;
					break;
				case 66:
					*key=KEY_DOWN;
					break;
				case 67:
					*key=KEY_RIGHT;
					break;
				case 68:
					*key=KEY_LEFT;
					break;
				case 49:
					//read(0,&temp,1);
					switch((int)temp[3])
					{
						case 53:
							*key=KEY_F5;
							break;
						case 55:
							*key=KEY_F6;
							break;
						default:
							*key=ERROR;
							break;
					}
					break;

				default:
					*key=ERROR;
					break;
			}
			break;
		default:

			*key=ERROR;
	}
	/*for(int i=1;i<4;i++)
		printf(" %d %d",i,temp[i]);*/
	rk_mytermrestore();
	return 0;
}
/*int main()
{
	
	setbuf(stdout,NULL);
	//rk_readkey(&key);
	for(int i=1;i>0;i++)
	{
	printf("n");
	printf("n");
	printf("n");
	keys key;
	rk_readkey(&key);
	if(key==KEY_ENTER)
		printf("enter");
	else if(key==KEY_F5)
		printf("f5");
	else if(key==KEY_F6)
		printf("f6");
	else if(key==KEY_UP)
		printf("up");
	else if(key==KEY_DOWN)
		printf("down");
	else if(key==KEY_LEFT)
		printf("left");
	else if(key==KEY_RIGHT)
		printf("right");
	else if(key==KEY_R)
		printf("r");
	else if(key==ERROR)
		printf("er");
	}

/*	printf("1");
	//rk_mytermsave();
	printf("1");
	rk_mytermregime(0,0,1,0,1);
	int temp[4];
	read(0,&temp,4);
	printf("er");
	for(int i=0;i<4;i++)
		printf("%d %d ",i,temp[i]);
	//rk_mytermrestore();
*//*
	return 0;
}*/
