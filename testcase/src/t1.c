#include "trap.h"

int A[10];
int b;
char C[10];
int main()
{
	A[0] = 0;
	A[1] = 1;
	A[2] = 2;
	A[3] = 3;
	A[4] = 4;

	b = A[3];
	A[5] = b;
	C[0] = 'a';
	C[1] = C[0];
	A[0] = (int)C[0];
	C[1] = 0x80;
	A[0] = (int)C[1];
	nemu_assert(C[1] == 0xffffff80);
	nemu_assert(A[0] == 0xffffff80);

	HIT_GOOD_TRAP;

	return 0;
}