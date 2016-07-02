#ifndef SOURCE_ARCHITECTURE_H
#define SOURCE_ARCHITECTURE_H

//#include "TransTabl.h"
//#include "TransCache.h"
#include "TransBuffer.h"
//#include "CCache.h"
#include "CBuffer.h"
#include "types.h"
#include "TargetArchitecture.h"



class CSourceArchitecture{
  friend class CDBTEngine;

private:
protected:
        int sourceProgSize;	//to verify if the program execution is still inside program space.

	SOURCE_MEM_BASE * pSourceProgMem;	//source program pointer, points to the begin of the loaded program

	CBuffer codeCache;

	uint8_t volatile * currBBExecPtr;		//pointer for the BB under decoding. after EOB engine will jump to its address
							//check how to jump to it in decode.c from arm-x86 DBT

	SourceEnvironment volatile env;		//enviroment is allocated in the stack for faster access. a pointer is used, so a register can be used as base

	//translation support variables
	//bool volatile eoExec;
	bool volatile eoBB;

        uint8_t* xMem;

        CTargetArchitecture *target;

	//int callCount;
	int exit_addr;

public:

  CSourceArchitecture(int Ccache_size, CTargetArchitecture *target);
  ~CSourceArchitecture();

  unsigned int translation_cycles;

  SourceEnvironment volatile * getEnv(){return &env;}
  uint8_t *getxMem(){return xMem;}

  	//static CTranslator * singleton;

	//CTranslator( int Ccache_size, int TcacheSize);	//constructor, receives the size of the source code memory, cache size and data mem size (if different)
//	~CTranslator(void);
	int sourceCodeLoader(void * programStart);	//load source program into the source memory structure returns a source memory pointer or NULL if problem occurs
	int sourceCodeLoader(void);			//verifies if the program has been loaded into the memory already and check its size

//	void pushCodeByte(uint8_t byte);

	//Virtual functions
	//virtual	~CTranslator(void);

	virtual void envReset(void) = 0;		//pure virtual function, must be implemented by the child translator class

	virtual void condCodedHandlerInit(void) = 0;

	virtual void decode() = 0;	//method used to decompose a fetched instruction into a set of micro Ops.




};


#endif
