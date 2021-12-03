#ifndef __CACHE_H__
#define __CACHE_H__

#include "nemu.h"

#ifdef CACHE_ENABLED
#define LINE_NUMBER 1024

//struct of CacheLine
typedef struct
{
    uint32_t valid_bit : 1;
    uint32_t tag : 23;
    uint8_t data[64];
} CacheLine;


// init the cache
void init_cache();

// write data to cache
void cache_write(paddr_t paddr, size_t len, uint32_t data);

// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len);

#endif

#endif
