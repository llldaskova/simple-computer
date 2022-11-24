#include"MSC.h"
unsigned char regFLAGS;
int OPmemory[M_SIZE];
//инициализирует оп
int sc_memoryInit()
{
	for (int i = 0; i < M_SIZE; i++)
	{
		OPmemory[i] = 0;
	}
	return 0;
}
//задает значение ячейки или ставит флаг 1
int sc_memorySet(int address, int value)
{
	if (address < M_SIZE && address >= 0)
	{
		OPmemory[address] = value;
	}
	else
	{
		sc_regSet(OUT_OF_MEMORY, 1);
		printf("Error OUT_OF_MEMORY");
		return -1;
	}
	return 0;
}
//возвращает значение ячейки или ставит флаг 1
int sc_memoryGet(int address, int* value)
{
	if (address < M_SIZE && address >= 0)
	{
		*value = OPmemory[address];
		return 0;
	}
	else
	{
		sc_regSet(OUT_OF_MEMORY, 1);
		printf("Error OUT_OF_MEMORY");
		return -1;
	}
}
//сохраняет содержимое памяти в файл в бинарном виде
int sc_memorySave(char* filename)
{
	ofstream addressData(filename, ios::out | ios::binary);
    	addressData.write((char *)OPmemory, sizeof(OPmemory));
    	addressData.close();
	return 0;
}
//загружает содержимое памяти из файла
int sc_memoryLoad(char* filename)
{
	 ifstream addressData(filename, ios::in | ios::binary);
    	addressData.read((char *)&OPmemory, sizeof(OPmemory));
	return 0;
}
//инициализирует регистр флагов 
int sc_regInit()
{
	regFLAGS = 0;
	return 0;
}
// устанавливает значение указанного регистра флагов
int sc_regSet(int reg, int value)
{
	if (reg >= 0 && reg < REG_SIZE)
	{
		if (value == 0)
		{
			regFLAGS = regFLAGS & (~(1 << (reg)));
		}
		else if (value == 1)
		{
			regFLAGS = regFLAGS | (1 << (reg));
		}
		else
		{
			printf("Error incorrect value");
			return -1;
		}
	}
	else
	{
		printf("Error incorrect registr");
		return -1;
	}
	return 0;
}
//возвращает значение указанного регистра флагов
int sc_regGet(int reg, int* value)
{
	if (reg >= 0 && reg < REG_SIZE)
		*value = (regFLAGS >> (reg )) & 0x1;
	else
	{
		printf("Error incorrect registr");
		return -1;
	}
	return 0;
}
//кодирует команду с указанным номером и операндом и помещает результат в value 
int sc_commandEncode(int command, int operand, int* value)
{
	if (command < 10 || (command > 11 && command < 20) || (command > 21 && command < 30) ||
		(command > 33 && command < 40) || (command > 43 && command < 51) || command > 76)
	{
		printf("Error incorrect command");
		return -1;
	}
	if (operand < 0 || operand >127)
	{
		printf("Error incorrect operand");
		return -1;
	}
	*value = operand;
	*value |= command << 7;
	return 0;
}
int sc_commandDecode(int value, int* command, int* operand)
{
	int command1, operand1;
	int i = 0;
	if ((value & 0x4000) == 1)
	{
		sc_regSet(INCORRECT_COMMAND, 1);
		printf("Error INCORRECT_COMMAND");
		return -1;
	}
	operand1 = value & 0x7F;
	command1 = (value >> 7) & 0x7F;

	if ((command1 < 10 || (command1 > 11 && command1 < 20) || (command1 > 21 && command1 < 30) ||
		(command1 > 33 && command1 < 40) || (command1 > 43 && command1 < 51) || command1 > 76) ||
		(operand1 < 0 || operand1 >127))

	{
		sc_regSet(INCORRECT_COMMAND, 1);
		printf("Error INCORRECT_COMMAND");
		return -1;
	}
	else
	{
		*operand = operand1;
		*command = command1;
		return 0;
	}
}

