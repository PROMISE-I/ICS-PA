#include "trap.h"

int max(int x, int y)
{
	int z;
	if (x > y)
	{
		z = x;
	}
	else
	{
		z = y;
	}
	return z;
}

int test_data[] = {1, 6};
int ans[] = {1, 6, 6, 6};

#define NR_DATA (sizeof(test_data) / sizeof(test_data[0]))

int main()
{
	//nemu_assert(max(test_data[0], test_data[0]) == ans[0]);
	//nemu_assert(max(test_data[0], test_data[1]) == ans[1]);
	nemu_assert(max(test_data[1], test_data[0]) == ans[2]);
	//nemu_assert(max(test_data[1], test_data[1]) == ans[3]);
	
	HIT_GOOD_TRAP;

	return 0;
}