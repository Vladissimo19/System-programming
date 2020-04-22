#include <stdio.h>
#include <stdlib.h>

int mass(int8_t** A, const int8_t size)
{
	__asm__(
		"movb $0,%%cl\n\t"
		"movb $0, %%ch\n\t"
		"loop_start:\n\t"
			"cmp %%ch, %%bl\n\t"
			"je loop_exit\n\t"
			"movl (%%esi), %%eax\n\t"	
		"in_loop_start:\n\t"
			"cmp %%cl, %%bl\n\t"
			"je in_loop_exit\n\t"
			"cmp %%cl, %%ch\n\t"
			"jne nequ\n\t"			
		"equ:\n\t"
			"movb $1, (%%eax)\n\t"
			"jmp in_inc\n\t" 	
		"nequ:\n\t"
			"mov %%bl, %%bh\n\t"
			"sub %%ch, %%bh\n\t"
			"sub $1, %%bh\n\t"
			"cmp %%cl, %%bh\n\t"
			"je equ\n\t"
			"movb $0, (%%eax)\n\t"
		"in_inc:\n\t"	
			"incb %%cl\n\t"
			"add $1, %%eax\n\t"
			"jmp in_loop_start\n\t"
		"in_loop_exit:\n\t"
			"movb $0, %%cl\n\t"
			"incb %%ch\n\t"
			"addl $4, %%esi\n\t"
			"jmp loop_start\n\t"		
		"loop_exit:\n\t"
		: 
		: "S"(A), "b"(size)
		: 		
	);
	return 0;
}
int main()
{
	int8_t size = 45;
	int8_t** A = (int8_t**)malloc(size*sizeof(int8_t*));
	for(int8_t i=0;i<size;i++)
	{
		A[i] = (int8_t*)malloc(size*sizeof(int8_t));
	}
	mass(A, size);
	for(int8_t i=0; i < size; i++)
	{
		for(int8_t j=0; j < size; j++)
		{
			printf("[%d]", A[i][j]);
		}
		printf("\n");
	}

	return 0;
}
