#include "trap.h"
#include <string.h>

char *s[] = {
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab",
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
	", World!\n",
	"Hello, World!\n",
	"#####"};

char str1[] = "Hello";
char str[20];

int main()
{
	nemu_assert(strcmp(s[0], s[1]) == -1);

	HIT_GOOD_TRAP;
	return 0;
}