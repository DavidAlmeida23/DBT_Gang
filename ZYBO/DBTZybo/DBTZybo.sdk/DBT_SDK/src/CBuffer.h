#ifndef CBUFFER_H
#define CBUFFER_H

#include <stdlib.h>
#include <string.h>
#include "types.h"


//extern int S_CODE_SYM;

class CBuffer
{
   public:
   
        int c_size;                                             // size of the CBuffer (in bytes)
        SOURCE_MEM_BASE* baseBufferAddr;                        // first PC in Cbuffer
        SOURCE_MEM_BASE* lastBufferAddr;                        // last PC in Cbuffer
	
   public:
     CBuffer(int c_cache_size = 0);
     ~CBuffer(void);
     
     uint8_t load(const void* source_code, int source_code_size, int start_pc);
};


#endif