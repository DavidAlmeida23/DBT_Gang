#ifndef TRANSBUFFER_H
#define TRANSBUFFER_H

#include <stdint.h>
#include "types.h"
//#include "uthash.h"


class CTransBuffer
{
private:
  
	SOURCE_PC transSourAddr;	//element used as hash key, has the source code memory address of the BB
//	uint8_t * targAddr;		//address were starts the translated BB code
	
	uint8_t * pTargetMem_begin;	//target architecture code memory pointer
        uint8_t * pTargetMem_end;       // end byte address of the Tcache (outside already)	
	
	int bb_size;	
  
	uint8_t * codeInsertPtr;	

	int t_size;                                             // size of the CCache (in bytes)

	int avail_size;

public:
	CTransBuffer(int targCacheSize = 0);
	~CTransBuffer(void);

//	uint8_t * getCacheAddr(void);			//returns the start address of the cache (cache pointer, pTargetMem_begin)
	uint8_t * getCurrInsAddr(void);			//returns the address of the current insertion place (codeInsertPtr)

//	unsigned int getCodeSize(void);			//returns the cache size in duty (getCurrInsAddr() - getCacheAddr())
	
	int addTag(SOURCE_PC sourAddr);			//adds a new tag entry, marking the begining of a new translated BB
	
//	bool getTag(SOURCE_PC searchAddr);		//search if a code addr is translated and cached
	uint8_t * getLastTransAddr(void);			//return the address of the code of the last searched translation

	uint8_t * getTransAddr(SOURCE_PC searchAddr);			//return the address of the code or NULL if the entry exists or not
	
	bool checkForRoom(int code_size);
	
	bool cacheCode(uint16_t hWord);
	bool cacheCode(uint16_t msb, uint16_t lsb);

};


#endif
