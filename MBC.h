#include "MSC.h"
#include "MT.h"
#include <stdlib.h>
#include <stdio.h>

const int BC[18][2]=
{
	{0x5050507,0x7050505},//0
	{0x1010101,0x1010101},//1
	{0x1050507,0x7040402},//2
	{0x3010507,0x7050101},//3
	{0x7050505,0x1010101},//4
	{0x7040407,0x7050101},//5
	{0x7040507,0x7050505},//6
	{0x1010107,0x1010101},//7
	{0x7050507,0x7050507},//8
	{0x7050507,0x7050101},//9
	{0x7010507,0x7050505},//a
	{0x6050507,0x7050505},//b
	{0x4040507,0x7050504},//c
	{0x5050506,0x6050505},//d
	{0x7040407,0x7040404},//e
	{0x4070407,0x4040404},//f
	{0x7020000,0x2},//+
	{0x3000000,0x0}//-
};

int bc_printA(char *str);
int bc_box(int x1,int y1,int x2,int y2);
int bc_printbigchar(int *big,int x,int y, enum colors tC,enum colors bgC);
int bc_getbigcharpos(int *big,int x,int y, int *value);
int bc_setbigcharpos(int *big,int x,int y, int value);

