#include "SourceArchitecture.h"

/*CTranslator::CTranslator( int Ccache_size, int TcacheSize)	//constructor, receives the size of the source code memory, cache size and data mem size (if different)
	: codeCache(Ccache_size), transCache(TcacheSize) //call constructors if the transcache and transtable were instantiated inside stack
{
//not unser use because env is a member of the class
//	env = new SourceEnvironment;
//	envPtr = &env;

  	//singleton = NULL;

	eoExec = false;
	eoBB = false;

	//to controll the end of the program
	//finish when returning from main
	//callCount = 0;

//replaced with the Ccache!!!
//	pSourceProgMem = (sourCodeSize != 0)	?	(SOURCE_MEM_BASE *) new uint8_t[sourCodeSize]	:
//											NULL											;


	//only used if source arch has a data memory, otherwise data registers are handled  in the child class
//	pSourceDataMem = (dataMemSize != 0)	?	(SOURCE_MEM_BASE *) new uint8_t[dataMemSize]	:
//											NULL											;
}   */

CSourceArchitecture::CSourceArchitecture(int Ccache_size,CTargetArchitecture *target)
  : codeCache(Ccache_size), target(target)
{

	eoBB = false;
}

CSourceArchitecture::~CSourceArchitecture(void)
{
//	delete env;

//	if (pSourceProgMem != NULL) delete[] pSourceProgMem;
//	if (pSourceDataMem != NULL) delete[] pSourceDataMem;
}


int CSourceArchitecture::sourceCodeLoader(void)
{
//  	#pragma section = "S_CODE_SEC"
//	sourceProgSize = __section_size("S_CODE_SEC");
//	pSourceProgMem = (SOURCE_MEM_BASE *)&S_CODE_SYM;

  	if (sourceProgSize <= 0)
	{
		//then problem on the memory loaded code
	  	return 1;
	}

	//cache preload

	//else regular return
	return 0;

}


