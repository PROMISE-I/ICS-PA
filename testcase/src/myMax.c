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

int test_data[] = {1, 7};
int ans[] = {1, 7, 7, 7};

#define NR_DATA (sizeof(test_data) / sizeof(test_data[0]))

int main()
{
	int i, j, ans_idx = 0;
	for (i = 0; i < NR_DATA; i++)
	{
		for (j = 0; j < NR_DATA; j++)
		{
			nemu_assert(max(test_data[i], test_data[j]) == ans[ans_idx++]);
		}
	}

	HIT_GOOD_TRAP;

	return 0;
}