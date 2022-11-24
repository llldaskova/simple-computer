#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<fstream>
using namespace std;

#define OVERFLOW 0 
#define DIVISION_ERR_BY_ZERO 1 
#define OUT_OF_MEMORY 2 
#define IGNORING_CLOCK_PULSES 3 
#define INCORRECT_COMMAND 4 

#define REG_SIZE 5
#define  M_SIZE 100

int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int* value);
int sc_memorySave(char* filename);
int sc_memoryLoad(char* filename);
int sc_regInit();
int sc_regSet(int reg, int value);
int sc_regGet(int reg, int* value);
int sc_commandEncode(int command, int operand, int* value);
int sc_commandDecode(int value, int* command, int* operand);
