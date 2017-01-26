#include <stdio.h>
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
rtruct memory //whole machine memory
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

int load()
{
	char loaded_char;
	computer_mem.PC=0;
	while((loaded_char=getchar())!=EOF)
	{
		if(loaded_char=='+')
		{
						
		}
	}

}


int main()
{
	load();
	reset();
	run();
	return 0;		
}
