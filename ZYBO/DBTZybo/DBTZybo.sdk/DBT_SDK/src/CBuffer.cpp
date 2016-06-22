#include "CBuffer.h"


/*********************************************************************
******** CBuffer
**********************************************************************
Arguments:
----------------------------------------------------------------------
int size -> size of the CBuffer
______________________________________________________________________
Return:
----------------------------------------------------------------------
______________________________________________________________________
Description:
----------------------------------------------------------------------
- Constructor of the CBuffer class.
**********************************************************************/



CBuffer::CBuffer(int c_cache_size) : baseBufferAddr(0), lastBufferAddr(0)
{
	zprintf("cache size %d NOT BEING USED. CODE BUFFER IN USE\n", c_cache_size );
}


CBuffer::~CBuffer(void)
{
}


uint8_t CBuffer::load(const void* source_code, int source_code_size, int start_pc)
{
		
	  baseBufferAddr = (SOURCE_MEM_BASE*)source_code;
	  c_size = source_code_size;
	  							  
	  lastBufferAddr = baseBufferAddr + source_code_size;
	  
	  return 0;
}

