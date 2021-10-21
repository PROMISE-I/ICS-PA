#include "trap.h"

int A[10];
int b;
char C[10];
int main()
{
	C[1] = 0x80;
	A[0] = (int)C[1];
	nemu_assert(A[0] == 0xffffff80);

	HIT_GOOD_TRAP;

	return 0;
}