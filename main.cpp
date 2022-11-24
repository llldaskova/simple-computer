#include "MBC.h"
#include "MRK.h"
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include<signal.h>
#include<sys/time.h>
const int cursor=23;
void menu();
void menu_flag();
void key_enter(enum keys key, int count);
void f6(int value);
void I();
int CU(int value,int cell_num);
int count_t=0;
void signalhandler(int signo)
{
	int value;
	sc_regGet(IGNORING_CLOCK_PULSES, &value);
	if(count_t==100)
	{
		count_t=0;
		//alarm(1);	
	}
	if(signo==SIGALRM&&value==0)
	{
		//rk_mytermsave();
		f6(count_t);
		sleep(1);
		int value;
		//sw(int fl_color,int X,int Y,int count)
		sc_memoryGet(count_t, &value);
		int result=CU(value,count_t);
		if(result==1)
		{
			alarm(0);
			sc_regSet(IGNORING_CLOCK_PULSES, 1);// игнорировать 
			menu_flag();
			mt_gotoXY(23,0);
		}
		else
		{
			sc_regSet(IGNORING_CLOCK_PULSES, 0);
			menu();
			if(result!=2)
				count_t++;
		}
		
	}
	else if(signo==SIGUSR1)
	{
		count_t=0;
		sc_regInit();//обнуление флагов
		//I();
		alarm(0);
		menu();
	}
	//menu();
}
void sig()
{
	struct itimerval nval,oval;
	nval.it_interval.tv_sec=1;
	nval.it_interval.tv_usec=0;
	nval.it_value.tv_sec=1;
	nval.it_value.tv_usec=0;
	//alarm(1);
	setitimer(ITIMER_REAL,&nval,&oval);
	//while(1)
		//pause();
	
	
}
int neg(int value)
{
	return ~value+1;
}
void menu_memory()
{
	
	bc_box(1,1,12,62);
	mt_gotoXY(1,27);
	printf("Memory");
	
	int value;
	int size=M_SIZE/10;
	int count=0;
	int j1=0;
	for (int i=0;i<size;i++)
	{
	for(int j=0;j<size;j++)
	{
		mt_gotoXY(i+2,j1+2);
		sc_memoryGet(count, &value);
		if(value&0x80000000)
			printf("-%04x",neg(value));
		else
			printf("+%04x",value);
		count+=10;
		j1+=6;
	}
	j1=0;
	count=i+1;
	}
	printf("\n");
	
	
	
}
int accum=0x0;
void menu_accum()
{
	bc_box(1,64,3,79);
	mt_gotoXY(1,67);
	printf("accumulator");
	mt_gotoXY(2,69);
	if(accum&0x80000000)
		printf("-%04x",neg(accum));
	else
		printf("+%04x",accum);
}
void menu_iC(int value=0)
{
	mt_setbgcolor(Standart);
	bc_box(4,64,6,79);
	mt_gotoXY(4,65);
	printf("instructionCou");
	mt_gotoXY(5,69);
	printf("%+05d",value);
}
void menu_Oper()
{
	bc_box(7,64,9,79);
	mt_gotoXY(7,67);
	printf("Operation");
	mt_gotoXY(8,69);
	printf("+00:00");
}
void menu_flag()
{
	bc_box(10,64,12,79);
	mt_gotoXY(10,67);
	printf("Flags");
	int value;
	int y=69;
	int x=11;
	mt_gotoXY(x,y);
	for(int i=0;i<REG_SIZE;i++)
	{
		sc_regGet(i, &value);
		if(value==1&&i==0)
			printf("p");
		else if(value==1&&i==1)
			printf("0");
		else if(value==1&&i==2)
			printf("m");
		else if(value==1&&i==3)
			printf("t");
		else if(value==1&&i==4)
			printf("e");
		y++;
		mt_gotoXY(x,y);
	}
	
	
}
void menu_key()
{
	bc_box(13,57,21,79);
	int x=14,y=58;
	mt_gotoXY(x,y+2);
	printf("keys:");
	mt_gotoXY(x,y);
	printf("l-load");
	x++;
	mt_gotoXY(x,y);
	printf("s-save");
	x++;
	mt_gotoXY(x,y);
	printf("r-run");
	x++;
	mt_gotoXY(x,y);
	printf("t-step");
	x++;
	mt_gotoXY(x,y);
	printf("i-reset");
	x++;
	mt_gotoXY(x,y);
	printf("F5-accumulator");
	x++;
	mt_gotoXY(x,y);
	printf("F6-instructionCounter");
	x++;
	mt_gotoXY(x,y);
}
void BChar(int value=0x0)
{
	int X=13;
	int Y=1;
	int big[2];
	if(!(value&0x80000000))
	{
		big[0]=BC[16][0];
		big[1]=BC[16][1];
		bc_printbigchar(big,X,Y,Standart,Standart);
	}
	else
	{
		big[0]=BC[17][0];
		big[1]=BC[17][1];
		bc_printbigchar(big,X,Y,Standart,Standart);
		value=neg(value);
	}
	Y+=8*5;
	int rem=0x10;
	for(int i=0;i<4;i++)
	{
		int value0=value%rem;
		value/=0x10;
		switch(value0)
		{
			case 0x0:
				big[0]=BC[0][0];
				big[1]=BC[0][1];
				break;
			case 0x1:
				big[0]=BC[1][0];
				big[1]=BC[1][1];
				break;
			case 0x2:
				big[0]=BC[2][0];
				big[1]=BC[2][1];
				break;
			case 0x3:
				big[0]=BC[3][0];
				big[1]=BC[3][1];
				break;
			case 0x4:
				big[0]=BC[4][0];
				big[1]=BC[4][1];
				break;
			case 0x5:
				big[0]=BC[5][0];
				big[1]=BC[5][1];
				break;
			case 0x6:
				big[0]=BC[6][0];
				big[1]=BC[6][1];
				break;
			case 0x7:
				big[0]=BC[7][0];
				big[1]=BC[7][1];
				break;
			case 0x8:
				big[0]=BC[8][0];
				big[1]=BC[8][1];
				break;
			case 0x9:
				big[0]=BC[9][0];
				big[1]=BC[9][1];
				break;
			case 0xa:
				big[0]=BC[10][0];
				big[1]=BC[10][1];
				break;
			case 0xb:
				big[0]=BC[11][0];
				big[1]=BC[11][1];
				break;
			case 0xc:
				big[0]=BC[12][0];
				big[1]=BC[12][1];
				break;
			case 0xd:
				big[0]=BC[13][0];
				big[1]=BC[13][1];
				break;
			case 0xe:
				big[0]=BC[14][0];
				big[1]=BC[14][1];
				break;
			case 0xf:
				big[0]=BC[15][0];
				big[1]=BC[15][1];
				break;
		}
		bc_printbigchar(big,X,Y,Standart,Standart);
		Y-=8;
	}
}
void sw(int fl_color,int X,int Y,int count)
{
	int value;
	if(fl_color==0)
		mt_setbgcolor(White);
	else
		mt_setbgcolor(Standart);
	mt_gotoXY(X,Y);
	sc_memoryGet(count, &value);
	if(value&0x80000000)
			printf("-%04x",neg(value));
		else
			printf("+%04x",value);
	BChar(value);
}
void memory_p()
{
	int X=2,Y=2;
	int count=0;
	sw(0,X,Y,count);
	keys key;
	mt_gotoXY(23,0);
	rk_readkey(&key);
	while(key==KEY_UP||key==KEY_DOWN||key==KEY_RIGHT||key==KEY_LEFT)
	{
		if(key==KEY_UP)
		{
			if(X-1>1)
			{
				sw(1,X,Y,count);
				X-=1;
				count--;
				sw(0,X,Y,count);
			}	
		}
		else if(key==KEY_DOWN)
		{
			if((X+1)<12)
			{
				sw(1,X,Y,count);
				X+=1;
				count++;
				sw(0,X,Y,count);
			}
		}	
		else if(key==KEY_RIGHT)
		{
			if(Y+6<62)
			{
				sw(1,X,Y,count);
				Y+=6;
				count+=10;
				sw(0,X,Y,count);
			}
		}
		else if(key==KEY_LEFT)
		{
			if(Y-6>0)
			{
				sw(1,X,Y,count);
				Y-=6;
				count-=10;
				sw(0,X,Y,count);
			}
		}
		//keys key;
		menu_iC(count);
		mt_gotoXY(23,0);
		rk_readkey(&key);
		
	}
	key_enter(key,count);
	//menu();
	/*if(key==KEY_ENTER)
	{
		int value;
		scanf("%d",&value);
		//mt_gotoXY(25,0);
		//printf("%d",value);
		if(value>=-9999&&value<=9999)
		{
			sc_memorySet(count,value);
			sw(1,X,Y,count);
		}
		else
		{
			//printf("Invalid input");
			sw(1,X,Y,count);
		}
		menu();
	}*/
	//mt_gotoXY(25,0);
	//menu_memory();
	
}
void I()
{
	sc_memoryInit();
	sc_regInit();
	sc_regSet(IGNORING_CLOCK_PULSES, 1);
	accum=0;
}
void f6(int value)//окраска кнопки без координат
{
	menu();
	if(value>-1&&value<100)
	{
		menu_iC(value);
		int x=value%10+2;
		int y=value/10*6+2;
		sw(0,x,y,value);
		mt_gotoXY(23,0);
	}
}
void inp()
{
	int value;
	sc_regGet(IGNORING_CLOCK_PULSES, &value);
	keys key;
		rk_readkey(&key);
	if(value==0)
	{
		
		//sc_regGet(IGNORING_CLOCK_PULSES, &value);
		//printf("%d",value);
		 //if(key==KEY_R)
		//{
			raise(SIGUSR1);
			sc_regSet(IGNORING_CLOCK_PULSES, 1);
			menu();
		//}
	}
	else
	{
	//keys key;
	//rk_readkey(&key);
	if(key==KEY_UP||key==KEY_DOWN||key==KEY_RIGHT||key==KEY_LEFT)
	{	
		memory_p();
	}
	else if(key==KEY_F6)
	{
		//printf("In");
		//setbuf(stdout,NULL);
		//fflush(stdin);
		int value;
		scanf("%d",&value);
		menu();
		if(value>-1&&value<100)
		{
			menu_iC(value);
			int x=value%10+2;
			int y=value/10*6+2;
			sw(0,x,y,value);
			mt_gotoXY(23,0);
			rk_readkey(&key);
			key_enter(key,value);
		}
	}
	else if(key==KEY_F5)
	{
		//printf("In");
		int value;
		scanf("%x",&value);
		if((value>=0x0&&value<=0xffff)||(value>=0xffff0001&&value<=0xffffffff))
		{
			accum=value;
		}	
	}
	else if(key==KEY_I)
	{
		I();
	}
	else if(key==KEY_S)
	{	
		char fname[128];
		for(int i=0;i<128;i++)
			fname[i]=' ';
		printf("Input filename\n");
		//scanf("%s",&fname);
		fgets(fname,128,stdin);
		sc_memorySave(fname);	
	}
	else if(key==KEY_L)
	{	
		char fname[128];
		for(int i=0;i<128;i++)
			fname[i]=' ';
		printf("Input filename\n");
		//scanf("%s",&fname);
		fgets(fname,128,stdin);
		sc_memoryLoad(fname);	
	}
	else if(key==KEY_R)
	{	
		rk_mytermsave();
		//raise(SIGALRM);
		//sc_regSet(INCORRECT_COMMAND, 0);
		sc_regSet(IGNORING_CLOCK_PULSES, 0);
		sig();
	}
	//rk_mytermrestore();
	//if(value==1)
		//rk_mytermrestore();
	menu();
	}
}
void key_enter(enum keys key, int count)//и т
{
	if(key==KEY_ENTER)
	{
		int value;
		scanf("%x",&value);
		if((value>=0x0&&value<=0xffff)||(value>=0xffff0001&&value<=0xffffffff))
		{
			sc_memorySet(count,value);
		}
		
		//sw(1,X,Y,count);
	}
	else if(key==KEY_T)
	{
		count_t=count;
		menu_iC(count_t);
		rk_mytermsave();
		int memory;
		sc_memoryGet(count, &memory);
		if(CU(memory,count)==1||CU(memory,count)==2)
		{
			menu_flag();
			mt_gotoXY(23,0);
			sleep(1);
			sc_regInit();
			sc_regSet(IGNORING_CLOCK_PULSES, 1);
			menu_flag();
		}
		count_t=0;
		menu_iC(count_t);
	}
	
}
void menu()
{
	mt_clrscr();
	menu_memory();
	menu_accum();
	menu_iC();
	menu_Oper();
	menu_flag();
	menu_key();
	BChar();
	printf("\nInput/Output\n");
	mt_gotoXY(23,0);

}


void decoder(int value,int *number,int *operand)
{
	if(value|0x3fff==0x3fff)
	{
		int num,oper;
		num=value;
		num>>=7;
		*number=num;
		oper=value;
		oper&=0x7F;
		*operand=oper;		
	}
	else
	{
		*number=0;
		*operand=0;	
	}
}
int ALU(int operand,int command)
{
	int result,value;
	sc_memoryGet(operand,&value);
	switch(command)
	{
		case 0x30:
			result=value+accum;
			break;

		case 0x31:
			result=accum-value;
			break;
		case 0x32:
			if(value!=0)
				result=accum/value;
			else
				return 0xffff1;
			break;
		case 0x33:
			result=accum*value;
			break;
		case 0x60:
			result=value<<1;
			break;
		default:
			result=accum;
	}
	if((result>=0x0&&result<=0xffff)||(result>=0xffff0001&&result<=0xffffffff))
				return result;
	else
				return 0xfffff;
	
	
}
int CU(int value_m,int cell_num)
{
	int number,operand;
	decoder(value_m,&number,&operand);
	if(number==0)
	{
		sc_regSet(INCORRECT_COMMAND, 1);//неверная команда 
		return 1;
	}
	sc_regSet(IGNORING_CLOCK_PULSES, 1);
	menu_flag();
	mt_gotoXY(23,0);
	//sleep(1);
	int value;
	if(operand<0||operand>99)
	{
		sc_regSet(OUT_OF_MEMORY, 1);
		return 1;
	}
	if(number==0x30||number==0x31||number==0x32||number==0x33||number==0x60)
	{
			int result=ALU(operand,number);
			if(result==0xfffff)
			{
				sc_regSet(OUT_OF_MEMORY, 1);
				return 1;
			}
			else if(result==0xffff1)
			{
				sc_regSet(DIVISION_ERR_BY_ZERO, 1);
				return 1;
			}
			else
			{
				accum=result;
				menu_accum();
				return 0;
			}
	}
	switch( number)
	{
	case 0x10:
			/*if(operand<0||operand>99)
			{
				sc_regSet(OUT_OF_MEMORY, 1);
				return 1;
			}*/
			//int value;
			mt_gotoXY(23,0);
			printf("input value\n");
			rk_mytermsave2();
			rk_mytermrestore();
			scanf("%x",&value);
			rk_mytermrestore2();
			if((value>=0x0&&value<=0xffff)||(value>=0xffff0001&&value<=0xffffffff))
			{
				sc_memorySet(operand,value);
			}
			else
			{
				sc_regSet(OVERFLOW, 1);
				return 1;
			}
			break;
	case 0x11:
			/*if(operand<0||operand>99)
			{
				sc_regSet(OUT_OF_MEMORY, 1);
				return 1;
			}*/
			//int value;
			mt_gotoXY(cursor,0);
			sc_memoryGet(operand,&value);
			printf("%x",value);
			sleep(2);
			break;
	case 0x20:
			/*if(operand<0||operand>99)
			{
				sc_regSet(OUT_OF_MEMORY, 1);
				return 1;
			}*/
			//int value;
			sc_memoryGet(operand,&value);
			accum=value;
			menu_accum();
			break;
	case 0x21:
			/*if(operand<0||operand>99)
			{
				sc_regSet(OUT_OF_MEMORY, 1);
				return 1;
			}*/
			sc_memorySet(operand,accum);
			menu_memory();
			break;
	case 0x40:
			count_t=operand;
			f6(count_t);
			sleep(1);
			return 2;
	case 0x41:
			if(accum>=0xffff0001&&accum<=0xffffffff)
			{
				count_t=operand;
				f6(count_t);
				sleep(1);
				return 2;
			}
			break;
	case 0x42:
			if(accum==0)
			{
				count_t=operand;
				f6(count_t);
				sleep(1);
				return 2;
			}
			break;
	case 0x43:
			return 1;
	default:
			sc_regSet(INCORRECT_COMMAND, 1);//неверная команда 
			return 1;
	}
	menu();
	//sleep(1);
	return 0;
}
int main ()
{
	sc_memoryInit();
	sc_regInit();
	//sc_regSet(IGNORING_CLOCK_PULSES, 1);
	/*for(int i=0;i<5;i++)
	{
	sc_regSet(i,1);
	}*/
	
	signal(SIGALRM,signalhandler);
	signal(SIGUSR1,signalhandler);
	sc_regSet(IGNORING_CLOCK_PULSES, 1);
	menu();
	setbuf(stdout,NULL);
	while(1)
	{
		//pause();
		inp();
	}
	//mt_gotoXY(22,0);
	
	return 0;
}

