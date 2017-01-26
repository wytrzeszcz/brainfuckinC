#include <stdio.h>
#include <time.h>
#define NOP 0 /* * */
#define INC 1 /*+*/
#define DEC 2 /*-*/
#define AINC 3 /*>*/
#define ADEC 4 /*<*/
#define IN 5 /*.*/
#define OUT 6 /*,*/
#define LOOPS 7 /*[*/
#define LOOPE 8 /*]*/
#define COPYD 9 /*C Copy  data[DP] into clipboard */
#define COPYC 10 /*c Copy program[DP] into clipboard */
#define PASTED 11 /*P Paste from clipboard into data[DP]*/
#define PASTEC 12 /*p Paste from clipboard into program[DP]*/
#define TRAP 13 /*T Trap mode for debuging LOL*/
#define OK 0 
#define ERRSTACK 100
struct memory //whole machine memory
{
	int PC; //Program Counter
	int SP; //Stack Pointer
	int ACC; //Accumulator
	int CB; //Clipboard
	int DP; //Data Pointer
	char program[256]; //Program Data
	char data[256]; //Data
	char stack[256]; //call stack
}computer_mem;
int clear()
{
	printf("\nRESETING MEMORY");
	fflush(stdout);
	int i;
	computer_mem.PC=0;
	computer_mem.SP=0;
	computer_mem.CB=0;
	computer_mem.DP=0;
	computer_mem.ACC=0;
	for (i=0;i<256;i++)
	{
		printf(".");
		fflush(stdout);
		computer_mem.program[i]=0;
		computer_mem.data[i]=0;
		computer_mem.stack[i]=0;
		usleep(10*1000);
	}
	return 0;
}
int load()
{
	printf("\nLOADING CODE FROM STDIN");
	char loaded_char;
	while((loaded_char=getchar())!=EOF)
	{
		if(loaded_char=='+')
		{
			computer_mem.program[computer_mem.PC]=INC;
			computer_mem.PC++;
			continue;
		}
		if(loaded_char=='-')
		{
			computer_mem.program[computer_mem.PC]=DEC;
			computer_mem.PC++;
			continue;
		}
		if(loaded_char=='>')
		{
			computer_mem.program[computer_mem.PC]=AINC;
			computer_mem.PC++;
			continue;
		}
		if(loaded_char=='<')
		{
			computer_mem.program[computer_mem.PC]=ADEC;
			computer_mem.PC++;
			continue;
		}
		if(loaded_char=='.')
		{
			computer_mem.program[computer_mem.PC]=IN;
			computer_mem.PC++;
			continue;
		}
		if(loaded_char==',')
		{
			computer_mem.program[computer_mem.PC]=OUT;
			computer_mem.PC++;
			continue;
		}
		if(loaded_char=='[')
		{
			computer_mem.program[computer_mem.PC]=LOOPS;
			computer_mem.PC++;
			continue;
		}
		if(loaded_char==']')
		{
			computer_mem.program[computer_mem.PC]=LOOPE;
			computer_mem.PC++;
			continue;
		}
		if(loaded_char=='C')
		{
			computer_mem.program[computer_mem.PC]=COPYD;
			computer_mem.PC++;
			continue;
		}
		if(loaded_char=='c')
		{
			computer_mem.program[computer_mem.PC]=COPYC;
			computer_mem.PC++;
			continue;
		}
		if(loaded_char=='P')
		{
			computer_mem.program[computer_mem.PC]=PASTED;
			computer_mem.PC++;
			continue;
		}
		if(loaded_char=='p')
		{
			computer_mem.program[computer_mem.PC]=PASTEC;
			computer_mem.PC++;
			continue;
		}
		if(loaded_char=='T')
		{
			computer_mem.program[computer_mem.PC]=TRAP;
			computer_mem.PC++;
			continue;
		}
	}
	
 return OK;
}

int reset()
{
	computer_mem.PC=0;
	return 0;
}


int run()
{
	while (1==1)
	{
		usleep(10*1000);
		computer_mem.PC%=255;
		if(computer_mem.program[computer_mem.PC]==NOP)
		{
			computer_mem.PC++;
			continue;
		}
		if(computer_mem.program[computer_mem.PC]==INC)
		{
			computer_mem.ACC=computer_mem.data[computer_mem.DP];
			computer_mem.ACC++;
			computer_mem.data[computer_mem.DP]=computer_mem.ACC;
			computer_mem.PC++;
			continue;
		}		
		if(computer_mem.program[computer_mem.PC]==DEC)
		{
			computer_mem.ACC=computer_mem.data[computer_mem.DP];
			computer_mem.ACC++;
			computer_mem.data[computer_mem.DP]=computer_mem.ACC;
			computer_mem.PC++;
			continue;
		}		
		if(computer_mem.program[computer_mem.PC]==AINC)
		{
			computer_mem.DP++;
			computer_mem.DP%=256;
			computer_mem.PC++;
			continue;
		}		
		if(computer_mem.program[computer_mem.PC]==ADEC)
		{
			if(computer_mem.DP==0)computer_mem.DP=255;
			else computer_mem.DP--;
			computer_mem.PC++;
			continue;
		}		
		if(computer_mem.program[computer_mem.PC]==IN)
		{
			char in=getchar();
			computer_mem.data[computer_mem.DP]=in;
			computer_mem.PC++;
			continue;
		}		
		if(computer_mem.program[computer_mem.PC]==OUT)
		{
			printf("%c",computer_mem.data[computer_mem.DP]);
			fflush(stdout);
			computer_mem.PC++;
			continue;
		}		
		if(computer_mem.program[computer_mem.PC]==LOOPS)
		{
			computer_mem.SP++;
			if(computer_mem.SP>255) return ERRSTACK;
			computer_mem.PC++;
			computer_mem.PC%256;
			computer_mem.stack[computer_mem.SP]=computer_mem.PC;
			continue;
		}		
		if(computer_mem.program[computer_mem.PC]==LOOPE)
		{
			computer_mem.ACC=computer_mem.data[computer_mem.DP];
			if(computer_mem.ACC==0)
			{
				if(computer_mem.SP<1) return ERRSTACK;
				computer_mem.SP--;
				computer_mem.PC++;
			}
			else 
			{
				computer_mem.PC=computer_mem.stack[computer_mem.SP];
			}
			continue;
		}	
		if(computer_mem.program[computer_mem.PC]==COPYD)
		{
			computer_mem.PC++;
			continue;
		}		
		if(computer_mem.program[computer_mem.PC]==COPYC)
		{
			computer_mem.PC++;
			continue;
		}		
		if(computer_mem.program[computer_mem.PC]==PASTED)
		{
			computer_mem.PC++;
			continue;
		}	
		if(computer_mem.program[computer_mem.PC]==PASTEC)
		{
			computer_mem.PC++;
			continue;
		}
		
		if(computer_mem.program[computer_mem.PC]==TRAP)
		{
			computer_mem.PC++;
			continue;
		}
	}
}
int main()
{
	clear();
	if(load()!=OK)
		{
			printf("LOAD ERROR TOO LONG CODE\n");
			return 0;
		}
	reset();
	run();
	return 0;		
}
