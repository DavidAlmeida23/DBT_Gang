#ifndef DBTENGINE_H
#define DBTENGINE_H


#include "SourceArch_8051.h"
#include "TargetArch_CortexM3.h"
#include "types.h"

#define FETCH *(codeCache.baseBufferAddr + (env.PC++))
#define SWITCH_TO_EXEC(x)		((void (*)(void))x)()

class CDBTEngine
{
  CCortexM3 target;
  C8051Arch source;



public:

  unsigned int translation_cycles;

   CDBTEngine(int Tcache_size, int Ccache_size);

   int initTranslator(void * sourCodeAddr , int sourCodeSize ,int exit_address);

   int runDBT(void);	//method that actualy runs DBT procedure

   int runTranslationOnly(void);

   uint8_t * translate(void);

   void target_wrapper_call_helper_CC_lazyEv_SNIFFER_BACKDOOR()
      { return target.helper_CC_lazyEv_SNIFFER_BACKDOOR(); }


void target_wrapper_call_helper_debug(/*CCortexM3* transPtr,*/ int soft_brkp_addr)
    {return target.helper_debug(soft_brkp_addr);}

};


#endif
