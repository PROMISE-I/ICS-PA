#include "memory/mmu/cache.h"
#include <stdlib.h>

#ifdef CACHE_ENABLED
uint32_t hw_mem_read(paddr_t paddr, size_t len);
void hw_mem_write(paddr_t paddr, size_t len, uint32_t data);

//cache object
CacheLine cache[1024];

// init the cache
void init_cache()
{
	// implement me in PA 3-1
	int line_number = 0;
	for (; line_number < LINE_NUMBER; line_number++){
	    cache[line_number].valid_bit = 0;
	}
}

// write data to cache
void cache_write(paddr_t paddr, size_t len, uint32_t data)
{
	// implement me in PA 3-1
	uint32_t block_offset;
	uint32_t block_num;
	uint32_t set_num;
	uint32_t tag;
	
	//write cache every byte per time
	for (;len > 0; len--)
	{
	    uint32_t line_offset = 0;
	    uint32_t the_byte = (data & 0xFF);
	    
	    data = data >> 8;
	    
	    block_offset = (paddr & 0x3F);
	    block_num = ((paddr >> 6) & (0xFFFFFFFF >> 6));
	    set_num = block_num & 0x7;
	    tag = ((block_num >> 3) & (0xFFFFFFFF >> 9));
	    
	    for (line_offset = 0; line_offset < 8; line_offset++)
	    {
	        CacheLine *line = &cache[set_num * 8 + line_offset];
	        
	        //hit the cache for this byte
	        if ((line->valid_bit == 1) && (tag == line->tag))
	        {
	            line->data[block_offset] = (uint8_t)the_byte;
	            break;
	        }//end write for this byte
	    }// end for search
	    
	    hw_mem_write(paddr, 1, the_byte);
	    //paddr add a byte
	    paddr += 1;
	    
	}//end write per byte
	
}


static void load_from_memory(CacheLine *line, uint32_t tag, uint32_t block_num)
{
    uint32_t data_offset = 0;
    line->valid_bit = 1;
    line->tag = tag;

    for (data_offset = 0; data_offset < 64; data_offset++)
    {
        paddr_t paddr_data = (block_num << 6) + data_offset;
        line->data[data_offset] = (uint8_t)hw_mem_read(paddr_data, 1);
    }
}


// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len)
{
	// implement me in PA 3-1
	uint32_t res = 0;
	uint32_t time = 0;
	
	uint32_t block_offset;
	uint32_t block_num;
	uint32_t set_num;
	uint32_t tag;
	
	//read cache every byte per time
	for (time = 0;time < len; time++)
	{
	    uint32_t line_offset = 0;
	    uint32_t is_hit = 0;
	    
	    block_offset = (paddr & 0x3F);
	    block_num = ((paddr >> 6) & (0xFFFFFFFF >> 6));
	    set_num = block_num & 0x7;
	    tag = ((block_num >> 3) & (0xFFFFFFFF >> 9));
	    
	    for (line_offset = 0; line_offset < 8; line_offset++)
	    {
	        CacheLine *line = &cache[set_num * 8 + line_offset];
	        
	        //hit the cache for this byte
	        if (line->valid_bit && tag == line->tag)
	        {
	            res = res + (line->data[block_offset] << (time * 8));
	            //paddr add a byte
	            paddr += 1;
	            is_hit = 1;
	            break;
	        }
	    }//end for hit situation
	    
	    //miss
	    if (is_hit == 0)
	    {
	        uint32_t is_free = 0;
	        
	        //there is any free areas?
	        for (line_offset = 0; line_offset < 8; line_offset++)
	        {
	            CacheLine *line = &cache[set_num * 8 + line_offset];
	           
	            if (line->valid_bit == 0)
	            {
	                //printf("ENTER THE IS_FREE SITUATION AT LINE OFFSET %x.\n", line_offset);
	                
	                //we have found a free area 
	                is_free = 1;
	                
	                //load byte from memory
	                load_from_memory(line, tag, block_num);
	                
	                res = res + (line->data[block_offset] << (time * 8));
	                paddr += 1;
	                break;
	            }
	        }
	        
	        //there is no free area, so we need to replace a random line
	        if (is_free == 0)
	        {
	            //printf("ENTER THE REPLACE SITUATION.");
	            
	            line_offset = rand() % 8;
	            CacheLine *line = &cache[set_num * 8 + line_offset];
	            
	            //load byte from memory
	            load_from_memory(line, tag, block_num);
                
                res = res + (line->data[block_offset] << (time * 8));
                paddr += 1;
	        }
	    }//end miss
	    
	}//end read per byte
	
	return res;
}

#endif