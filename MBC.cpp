#include "MBC.h"


int bc_printA(char *str)
{
	printf("\E[11m%s\E[10m",str);
	return 0;
}
int bc_box(int x1,int y1,int x2,int y2)
{
	if(x1<0||y1<0||x2<0||y2<0)
		return -1;
	int rows,cols;
	/*mt_getscreensize(&rows,&cols);
	if(rows<x1+x2||cols<y1+y2)
		return -1;*/
	for(int i=x1+1;i<x2;i++)
	{
		mt_gotoXY(i, y1);
		printf("\u2502");
	}
	mt_gotoXY(x2, y1);
	printf("\u2514");
	for(int j=y1+1;j<y2;j++)
	{
		mt_gotoXY(x2, j);
		printf("\u2500");
	}
	mt_gotoXY(x2, y2);
	printf("\u2518");
	for(int i=x2-1;i>x1;i--)
	{
		mt_gotoXY(i, y2);
		printf("\u2502");
	}
	mt_gotoXY(x1, y2);
	printf("\u2510");
	for(int j=y2-1;j>y1;j--)
	{
		mt_gotoXY(x1, j);
		printf("\u2500");
	}
	mt_gotoXY(x1, y1);
	printf("\u250C");
	mt_gotoXY(x2+2, 0);
	return 0;
}
int bc_printbigchar(int *big,int x,int y, enum colors tC,enum colors bgC)
{
	mt_setfgcolor(tC);
	mt_setbgcolor(bgC);
	y+=7;
	mt_gotoXY(x,y);
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(((big[0] >> (i*8+j)) & 0x1)==1)
				printf("\u2588");
			else
				printf(" ");
			y--;
			mt_gotoXY(x, y);
		}
		y+=8;
		x++;
		mt_gotoXY(x, y);
	}
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(((big[1] >> (i*8+j)) & 0x1)==1)
				printf("\u2588");
			else
				printf(" ");
			y--;
			mt_gotoXY(x, y);
		}
		y+=8;
		x++;
		mt_gotoXY(x, y);
	}
	mt_setfgcolor(Standart);
	mt_setbgcolor(Standart);
	return 0;
}
int bc_getbigcharpos(int *big,int x,int y, int *value)
{
	if(x<0||x>8||y<0||y>8)
	{
		return -1;
	}
	else if(y<4)
	{
		*value=((big[0] >> (x*8+7-x)) & 0x1);
	}
	else if(y>=4)
	{
		*value=((big[1] >> (x*8+7-x)) & 0x1);
	}
	return 0;
}
int bc_setbigcharpos(int *big,int x,int y, int value)
{
	if(x<0||x>8||y<0||y>8||(value!=0&&value!=1))
	{
		return -1;
	}
	else if(y<4&&value==0)
	{
		big[0]&=(~(big[0] << (y*8+7-x)));
	}
	else if(y<4&&value==1)
	{
		big[0]|=((big[0] << (y*8+7-x)));
	}
	else if(y>=4&&value==0)
	{
		big[1]&=(~(big[1] << (y*8+7-x)));
	}
	else if(y>=4&&value==1)
	{
		big[1]|=((big[1] << (y*8+7-x)));
	}
	return 0;
}
/*int bc_bigcharwrite(int fd,int *big,int count)
{
	ofstream addressData(fd, ios::out);
	addressData.write((int *)big, sizeof(big)*count);
	for (int i=0;i<count;i++)
	{
		addressData.write((int *)big);
	}
}
int bc_setbigcharpos(int *big,int x,int y, int value)
{
}*/
/*int bc_bigcharwrite(int fd,int* big,int count)
{	
	if(fwrite(fd,&count,sizeof(count))==-1)
	{
		return -1;
	}
	for(int i=0;i<count;i++)
	{
		if(fwrite(fd,big,(sizeof(int))*2)==-1)
		{
			return -1;
		}
	}
	
	return 0;	
}
int bc_bigcharread(int fd,int* big,int need_count,int* count)
{
	int cnt, n, err;
	err=fread(fd,&n,sizeof(n));
	if(err==-1||(err!=sizeof(n)))
	{
	*count=0;
	return -1;
	}
	cnt=fread(fd,big,need_count *sizeof(int)*2);
	if(cnt==-1)
		return -1;
	*count=cnt/(sizeof(int)*2);
	return 0;
}*/
/*int main()
{	
	char A[3]={'a','b','\0'};
	//bc_printA(A);
	//bc_box(5,5,10,10);
	int big[2];
	int X=5;
	int Y=0;
	/*for(int i=0;i<12;i++)
	{
		
		big[0]=BC[i][0];
		big[1]=BC[i][1];
		bc_printbigchar(big,X,Y,Standart,Standart);
		Y+=8;
		if(i==8)
		{
			X+=8;
			Y=0;
		}
	
	}
	
	return 0;
}*/
