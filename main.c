#include <stdio.h>
#include <time.h>
#define NOP 0 /* * */
#define INC 1 /*+*/
#define DEC 2 /*-*/
#define AINC 3 /*>*/
#define ADEC 4 /*<*/
#define IN 5 /*,*/
#define OUT 6 /*.*/
#define LOOPS 7 /*[*/
#define LOOPE 8 /*]*/
#define COPYD 9 /*C Copy  data[DP] into clipboard */
#define COPYC 10 /*c Copy program[DP] into clipboard */
#define PASTED 11 /*P Paste from clipboard into data[DP]*/
#define PASTEC 12 /*p Paste from clipboard into program[DP]*/
#define TRAP 13 /*T Trap mode for debuging LOL*/
#define HALT 24 /*H stop executing, and end program*/
#define OK 0
#define ERRSTACK 100
typedef enum { false, true } bool;

struct memory //whole machine memory
{
	int PC; //Program Counter
	int SP; //Stack Pointer
	int ACC; //Accumulator
	int CB; //Clipboard
	int DP; //Data Pointer
	bool TF; //Trap Flag
	char program[256]; //Program Data
	char data[256]; //Data
	char stack[256]; //call stack
}computer_mem;
char *deassembly(int opcode)
{
	static char mnemonic[10];
	
	switch(opcode)
	{
			case NOP:
				strcpy(mnemonic,"\tNOP_ ");
				break;
			case INC:
				strcpy(mnemonic,"\tINC_+");
				break;				
			case DEC:
				strcpy(mnemonic,"\tDEC_-");
				break;
			case AINC:
				strcpy(mnemonic,"\tAINC_>");
				break;				
			case ADEC:
				strcpy(mnemonic,"\tADEC_<");
				break;
			case IN:
				strcpy(mnemonic,"\tIN_,");
				break;				
			case OUT:
				strcpy(mnemonic,"\tOUT_.");
				break;
			case LOOPS:
				strcpy(mnemonic,"\tLOOPS_[");
				break;				
			case LOOPE:
				strcpy(mnemonic,"\tLOOPE_]");
				break;
	
			case COPYD:
				strcpy(mnemonic,"\tCOPYD_C");
				break;				
			case COPYC:
				strcpy(mnemonic,"\tCOPYC_c");
				break;
			case PASTED:
				strcpy(mnemonic,"PASTED_P");
				break;				
			case PASTEC:
				strcpy(mnemonic,"PASTEC_p");
				break;
			
			case TRAP:
				strcpy(mnemonic,"\tTRAP_T");
				break;				
			case HALT:
				strcpy(mnemonic,"\tHALT_H");
				break;
			default :
				strcpy(mnemonic,"\tERROR!!!");
				break;
			
			
	}

	return mnemonic;
}
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
		switch(loaded_char)
		{
			case '+':
			
				computer_mem.program[computer_mem.PC]=INC;
				computer_mem.PC++;
				break;
			
			case '-':
			
				computer_mem.program[computer_mem.PC]=DEC;
				computer_mem.PC++;
				break;
			
			case '>':
			
				computer_mem.program[computer_mem.PC]=AINC;
				computer_mem.PC++;
				break;
			
			case '<':
			
				computer_mem.program[computer_mem.PC]=ADEC;
				computer_mem.PC++;
				break;
			
			case ',':
			
				computer_mem.program[computer_mem.PC]=IN;
				computer_mem.PC++;
				break;
			
			case '.':
			
				computer_mem.program[computer_mem.PC]=OUT;
				computer_mem.PC++;
				break;
			
			case '[':
			
				computer_mem.program[computer_mem.PC]=LOOPS;
				computer_mem.PC++;
				break;
			
			case ']':
			
				computer_mem.program[computer_mem.PC]=LOOPE;
				computer_mem.PC++;
				break;
			
			case 'C':
			
				computer_mem.program[computer_mem.PC]=COPYD;
				computer_mem.PC++;
				break;
			
			case 'c':
			
				computer_mem.program[computer_mem.PC]=COPYC;
				computer_mem.PC++;
				break;
			
			case 'P':
			
				computer_mem.program[computer_mem.PC]=PASTED;
				computer_mem.PC++;
				break;
			
			case 'p':
			
				computer_mem.program[computer_mem.PC]=PASTEC;
				computer_mem.PC++;
				break;
			
			case 'T':
			
				computer_mem.program[computer_mem.PC]=TRAP;
				computer_mem.PC++;
				break;
			case 'H':
				computer_mem.program[computer_mem.PC]=HALT;
				computer_mem.PC++;
				break;
			default:
				break;
			
		}
	}
 return OK;
}

int reset()
{
	computer_mem.TF=false;
	computer_mem.PC=0;
	return 0;
}


int run()
{
	while (1==1)
	{

		usleep(10*1000);
		computer_mem.PC%=255;
		if(computer_mem.TF)
		{
			printf("REGISTERS:\n");
			printf("DP:%d\t",computer_mem.DP);
			printf("PC:%d\t",computer_mem.PC);
			printf("SP:%d\t",computer_mem.SP);
			printf("ACC:%d\t",computer_mem.ACC);
			printf("CB:%c\n",computer_mem.CB);
			int i=-4;
			
			printf("DATA\t|\tCODE\t|\tSTACK\n");
			for(i;i<5;i++)
			{
				int tmp=computer_mem.data[(computer_mem.DP+i)%256];
				printf("%d %c\t%c\t",tmp,(tmp<' '||tmp>127)?'.':tmp,(i==0)?'<':'|');
				printf("%s\t%c",deassembly(computer_mem.program[(computer_mem.PC+i)%256]),(i==0)?'<':'|');
				printf("%d\t%c\n",computer_mem.stack[(computer_mem.SP+i)%256],(i==0)?'<':'|');
			}
			
			printf("Continue Debuging?(Y/n):");
			char ans=getchar();
			if(ans=='n'||ans=='N') computer_mem.TF=false;
		}
		switch(computer_mem.program[computer_mem.PC])
		{
			case NOP:
		
				computer_mem.PC++;
				break;
		
			case INC:
			
				computer_mem.ACC=computer_mem.data[computer_mem.DP];
				computer_mem.ACC++;
				computer_mem.data[computer_mem.DP]=computer_mem.ACC;
				computer_mem.PC++;
				break;
				
			case DEC:
			
				computer_mem.ACC=computer_mem.data[computer_mem.DP];
				computer_mem.ACC--;
				computer_mem.data[computer_mem.DP]=computer_mem.ACC;
				computer_mem.PC++;
				break;
				
			case AINC:
		
				computer_mem.DP++;
				computer_mem.DP%=256;
				computer_mem.PC++;
				break;
				
			case ADEC:
			
				if(computer_mem.DP==0)computer_mem.DP=255;
				else computer_mem.DP--;
				computer_mem.PC++;
				break;
				
			case IN:
		
				
				computer_mem.data[computer_mem.DP]=getchar();
				computer_mem.PC++;
				break;
				
			case OUT:
		
				printf("%c",computer_mem.data[computer_mem.DP]);
				fflush(stdout);
				computer_mem.PC++;
				break;
				
			case LOOPS:
			
				computer_mem.SP++;
				if(computer_mem.SP>255) return ERRSTACK;
				computer_mem.PC++;
				computer_mem.PC%256;
				computer_mem.stack[computer_mem.SP]=computer_mem.PC;
				break;
					
			case LOOPE:
			
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
				break;
			
			case COPYD:
		
				computer_mem.CB=computer_mem.data[computer_mem.DP];
				computer_mem.PC++;
				break;
				
			case COPYC:
				computer_mem.CB=computer_mem.program[computer_mem.PC];
				computer_mem.PC++;
				break;
					
			case PASTED:
			
				computer_mem.data[computer_mem.DP]=computer_mem.CB;
				computer_mem.PC++;
				break;
			
			case PASTEC:
			
				computer_mem.program[computer_mem.PC]=computer_mem.CB;
				computer_mem.PC++;
				break;
			
		
			case TRAP:
		
				computer_mem.TF=true;
				computer_mem.PC++;
				break;
			case HALT:
				return 0; // to end
				break;
			default:
				printf("ERROR:WRONG OPCODE!!!\n");
				return -1;
				break;
		
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
