//#include "MSC.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
#include <map>
using namespace std;
#define  M_SIZE 100
int OPmemory[M_SIZE];
void coder(int memory_cell,int command,int operand);
void memory_clear()
{
	for (int i = 0; i < M_SIZE; i++)
		OPmemory[i] = 0;

}
//сохраняет содержимое памяти в файл в бинарном виде
int sc_memorySave(char* filename)
{
	ofstream addressData(filename, ios::out | ios::binary);
    	addressData.write((char *)OPmemory, sizeof(OPmemory));
    	addressData.close();
	return 0;
}
void str_clear(char *str,int n)
{
	for(int i=0;i<n;i++)
		str[i]=' ';
}
void str_print(char *str,int n)
{
	for(int i=0;i<n;i++)
		printf(" %d ",str[i]);
}
/*int cheak_num(char* num,int n)
{
	if(lit>47&&lit<58)
	
}*/
/*int check_space(char lit)
{
	if
}*/
int check_char(char lit)
{
	if(lit==' ')
		return 0;
	else if(lit>='0'&&lit<='9')
		return 1;
	else if(lit=='='||(lit>='A'&&lit<='Z'))
		return 2;
	else if(lit==';')
		return 3;
	else
		return 4;
}
int counter_space(int j,char *str,int n)
{
	while(str[j]==' '&&j<n)
		j++;
	return j;
}
int checkCommand(string str)
{
	map <string,int> Command={
					{"READ",0x10},
					{"WRITE",0x11},
					{"LOAD",0x20},
					{"STORE",0x21},
					{"ADD",0x30},
					{"SUB",0x31},
					{"DIVIDE",0x32},
					{"MUL",0x33},
					{"JUMP",0x40},
					{"JNEG",0x41},
					{"JZ",0x42},
					{"HALT",0x43},
					{"CHL",0x60},
					{"=",0x1},
				  };
	map <string,int>::iterator i=Command.begin();
	
	i=Command.find(str);
	//cout<<i->second<<endl;
	if(i!=Command.end())
		return i->second;
	return -1;
}
int treat (char *str,int n)
{
	int memory_cell;
	char Arr_mc[2];
	str_clear(Arr_mc,2);
	int j=0,i=0;
	j=counter_space(j,str,n);
	//printf("l%d \n",j);
	
	//int result=check_char(str[j]);
	
	while(i<2&&j<n)
	{
		int result=check_char(str[j]);
		if(result==1)
			Arr_mc[i]=str[j];
		j++;
		i++;
	}
	if(Arr_mc[0]==' '||Arr_mc[1]==' ')
			return 1;

			
	memory_cell=(Arr_mc[0]-'0')*10+(Arr_mc[1]-'0');
	j=counter_space(j,str,n);
	
	/////////////////////////////////////////////////
	string str1;
	int result=check_char(str[j]);
	//while(result!=1&&result!=0&&str[j]!=0&&j<n)
	while(result==2&&j<n)
	{
		//printf("l%d \n",str[j]);
		str1.push_back(str[j]);
		j++;
		result=check_char(str[j]);
	}
	int command=checkCommand(str1);
	//printf("%d \n",command);
	if(command==-1)
		return 2;
	j=counter_space(j,str,n);
	///////////////////////////////////////////
	str_clear(Arr_mc,2);
	char stOperand[5];
	str_clear(Arr_mc,5);
	i=0;
	int operand=0;
	
	if(command==0x1)
	{
		if(str[j]=='+'||str[j]=='-')
			stOperand[i]=str[j];
		else
			return 3;
		j++;
		i++;
		while(i<5&&j<n)
		{
			result=check_char(str[j]);
			if(result==1||result==2)
				stOperand[i]=str[j];
			else
				return 3;
			i++;
			j++;
		}
		
	        int dop=16*16*16;
	        for(int k=1;k<5;k++)
	        {
	        	if(check_char(stOperand[k])==1)
	        		stOperand[k]-='0';
	        	else
	        		stOperand[k]-=55;
	        	//printf("llll%d \n",stOperand[k]);
	       	operand+=stOperand[k]*dop;
	       	//printf("%x \n",stOperand[k]*dop);
	        	dop/=16;
	        }
	        
	        if(stOperand[0]=='-')
	        {
	        	operand--;
	        	operand=~operand;
	        }
		
	}
	else
	{
		while(i<2&&j<n)
		{
			result=check_char(str[j]);
			if(result==1)
				Arr_mc[i]=str[j];
			j++;
			i++;
		}
		if(Arr_mc[0]==' '||Arr_mc[1]==' ')
			return 3;
			
		operand=(Arr_mc[0]-'0')*10+(Arr_mc[1]-'0');
	}
	//printf("ll%x \n",operand);
	//str_print(stOperand,5);	
	j=counter_space(j,str,n);
	////////////////////////////////////////
	result=check_char(str[j]);
	if(result!=3&&str[j]!=0&&j<n)
		return 4;
	coder(memory_cell,command,operand);
	//str_print(ComArr,s_ComArr);
	//printf("%d \n",memory_cell);
	
	return 0;
}
void coder(int memory_cell,int command,int operand)
{
	if (command==0x1)
	{
		OPmemory[memory_cell]=operand;
		return;
	}
	int MC=command<<7;
	//printf("%x ",MC);
	MC|=operand;
	//printf("%x ",MC);
	OPmemory[memory_cell]=MC;
}
/*int str_space(char *str,int n)
{
	int k=0;
	for(int i=0;i<n;i++)
	{
		if(str[i]==' ')
			k++;
		else 
			break;
	}
	printf("SS%d %d",n,k);
	printf("!1");
		str_print(str,n);
		printf("\n");
	if(n!=k)
		return 1;
	return 0;
	
}*/
int main()
{
	memory_clear();
	
	/*for(int i=0;i<100;i++)
		OPmemory[i]=0x3;*/
		//sc_memorySet(i,0x1);
	//char fname[128];
		//printf("Input filename\n");
		//scanf("%s",&fname);
		//fgets(fname,128,stdin);
		//for(int i=0;i<128;i++)
			
		//printf("%d %c\n",i,fname[i]);	
	//char fname[128]={'c','a'/*,'.','o'*/};
	//sc_memorySave(fname);
	//sc_memoryLoad(fname);
	//printf("gr");
	//for(int i=0;i<100;i++)
	//printf("%x ",OPmemory2[i]);
	ifstream file("assembler.sa");
	int n=64;
	if(!file)
		printf("hhh");
	char buffer[n];
	str_clear(buffer,n);
	int i=1;
	while(!file.eof())
	{
		str_clear(buffer,n);
		file.getline(buffer,n);
		if(buffer[0]==0)
			break;
		int result=treat (buffer,n);
		if(result>=1&&result<=4)
		{
			printf("number %d\n",i);
			memory_clear();
			if(result==1)
				printf("ERROR memory cell\n");
			else if(result==2)
				printf("ERROR command\n");
			else if(result==3)
				printf("ERROR operand\n");
			else if(result==4)
				printf("ERROR comment\n");
			return 0;
		}
		i++;
	}
	//printf("%c",s[2]);
	file.close();
	char fname[128];
	printf("Input filename\n");	
	fgets(fname,128,stdin);
	sc_memorySave(fname);
	return 0;
}
