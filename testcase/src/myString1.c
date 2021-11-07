#include "trap.h"
#include <string.h>

char *s[] = {
	"a",
	"b",
	};

int main()
{
	nemu_assert(strcmp(s[0], s[1]) == -1);

	HIT_GOOD_TRAP;
	return 0;
}