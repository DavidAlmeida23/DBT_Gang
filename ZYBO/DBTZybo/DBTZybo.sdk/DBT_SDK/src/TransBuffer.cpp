//#include "stdafx.h"
#include "TransBuffer.h"
#include "stdio.h"

//extern inline void cacheByte(uint8_t byte);
extern int tInstCount;

CTransBuffer::CTransBuffer(int targCacheSize)
{

  //initialization is done above by initilization list
//	headTag = NULL;
//	workTag = NULL;
//	tailTag = NULL;

	if (targCacheSize > 0)
	{
	  
		static uint8_t targetMem[0x2000];
		pTargetMem_begin = targetMem ;
		
	  	codeInsertPtr = pTargetMem_begin;
  		t_size = targCacheSize;
		avail_size = t_size;

		pTargetMem_end = pTargetMem_begin + t_size;
		
		transSourAddr = ~0;
		
		
		zprintf("TBuffer starts at 0x%x, with a size of %d bytes\n", (int)pTargetMem_begin, t_size );
		zprintf("Buffer end address is 0x%x\n", pTargetMem_end);
	}
	else
	{
	  	pTargetMem_begin = NULL;

		codeInsertPtr = pTargetMem_begin;
  		t_size = 0;
		//size_limit = 0;
		pTargetMem_end = NULL;
		zprintf("Failed to contruct Tcache\n");
	}
	

}


CTransBuffer::~CTransBuffer(void)
{
	if (pTargetMem_begin != NULL) delete[] pTargetMem_begin;

}


uint8_t * CTransBuffer::getCurrInsAddr(void)
{
	return codeInsertPtr;
}


int CTransBuffer::addTag(SOURCE_PC sourAddr)
{ 
	transSourAddr = sourAddr;
	bb_size = 0;
	codeInsertPtr = pTargetMem_begin;
	  
	return 0;	
}


uint8_t * CTransBuffer::getLastTransAddr(void)
{
	return pTargetMem_begin;
}


uint8_t * CTransBuffer::getTransAddr(SOURCE_PC searchAddr)
{
	
	if (transSourAddr == searchAddr)
	{
	  	zprintf("\t\t## 0x%x HIT ##\n", searchAddr );
	 	return pTargetMem_begin;
	}
	else
	{
	  	zprintf("\t\t## 0x%x MISS ##\n", searchAddr );
	 	return NULL;	
	}
  
}

bool CTransBuffer::checkForRoom(int code_size)
{
  	bb_size += code_size;
	if (bb_size > t_size)
	  return EOBB;
	else
	  return NO_EOBB;
}


bool CTransBuffer::cacheCode(uint16_t hWord)
{

   	if ( checkForRoom(2) == NO_EOBB)
	{
  		* (uint16_t *)codeInsertPtr = hWord;
		codeInsertPtr+=2;
		
	
		return NO_EOBB;
	}
	else
	{
	  	printf("ERROR RETURN EOBB in caching\n");
		return EOBB;
	}
}

bool CTransBuffer::cacheCode(uint16_t msb, uint16_t lsb)
{
  	if ( checkForRoom(4) == NO_EOBB)
	{
	   	 * (uint16_t *)codeInsertPtr = msb;
	    	codeInsertPtr+=2;
	   	 * (uint16_t *)codeInsertPtr = lsb;
	   	 codeInsertPtr+=2;
	    
	    	return NO_EOBB;
	}
	else
	{
	  	printf("ERROR RETURN EOBB in caching\n");
		return EOBB;
	}
}

//example:
//		transCache.cacheCode(env.dataMem[SP]);
//		transCache.cacheCode(env.PC);
//		transCache.cacheCode(env.PC, env.PC);
