#include "trap.h"

typedef unsigned char uint8_t;
typedef char bool;

void setbit(void *buf, int offset, bool bit)
{
	int byte = offset >> 3;
	offset &= 7;
	uint8_t mask = 1 << offset;

	uint8_t *p = buf + byte;
	*p = (bit == 0 ? (*p & ~mask) : (*p | mask));
	//bit = bit == 0 ? 1 : 0;
	//nemu_assert(getbit(buf, offset) == bit);
}

int main()
{
	uint8_t buf[2];

	buf[0] = 0xaa;

	setbit(buf, 8, 1);
	nemu_assert(buf[1] == 0x1);
	/*
	setbit(buf, 9, 0);
	nemu_assert(buf[1] == 0x1);
	setbit(buf, 10, 1);
	nemu_assert(buf[1] == 0x5);
	setbit(buf, 11, 0);
	nemu_assert(buf[1] == 0x5);
	setbit(buf, 12, 1);
	nemu_assert(buf[1] == 0x15);
	setbit(buf, 13, 0);
	nemu_assert(buf[1] == 0x15);
	setbit(buf, 14, 1);
	nemu_assert(buf[1] == 0x55);
	setbit(buf, 15, 0);
	nemu_assert(buf[1] == 0x55);
    */
	HIT_GOOD_TRAP;
	return 0;
}