/************** TargetArchitecture *****************/
interface i_TrgArch {
	getWordSize	// 7
	getMemSize	// Update - For verifications 
}

/********* Source & Target Architecture ************/
interface i_ISA {
	getWordSize	// 6
	nBitsOpcode // 5
}
interface i_MemSizes{
	xDataMemSize 	// 1 - 8051 xMemSize 
	DataMemSize 	// 1 - 8051 MemSize 
	MemSize			// Updated - Necessary for algorithms in TCache
	HeapSize		// Updated - Necessary for algorithms in TCache	
	StackSize		// Updated - Necessary for algorithms in TCache
}
interface i_Registers {/*NULL*/} // 8 & 9

/************** SourceEnvironment *****************/
interface i_PCAcessors { // 2
	getPC
	setPC
}

/******************** TCACHE ***********************/
interface i_TCache {
	addTag 				// updated
	getTransAddr		// updated
	getLastTransAddr 	// 4_0
	getCurrInsAddr		// 4_1
	cacheCode			// 10
}

/******************** CCACHE ***********************/
interface i_CCache {
	fetch	// 13
}

/****************** DATA MEMORY *******************/
interface i_DMem {
	readDataMem	 	// 3
	writeDataMem	// Updated - Enable Write Function in the Data Memory
}

/********************* DECODE *********************/
interface i_Decode {
	decode // 11
}

/******************* GENERATOR ********************/
interface i_Generate { // 12
	gen_helper  gen_helper_int  gen_helper_pcArg  gen_helper_r4
  	gen_brkp  gen_blx
	gen_PUSH  gen_POP
	gen_cmp  gen_cmpi
	gen_it  
	gen_cje  gen_cjne gen_cjei  gen_cjnei
	gen_writePC  gen_writePCreg
	gen_mov  gen_movi
	gen_ld8  gen_ld16  gen_ldi8
	gen_st8	 gen_st16  gen_sti8
	gen_ld_bit  gen_st_bit
	gen_add  gen_addi
	gen_sub  gen_subi
	gen_div  gen_mul
	gen_not
	gen_or  gen_ori
	gen_and  gen_andi
	gen_xor
	gen_shri  gen_shli
	gen_orShl
}

/********************* RunDBT *********************/
interface i_RunDBT{
	run // 16
}

/******************* TRANSLATOR *******************/
interface i_Translate{
	translate // 14
}

/******************** EXECUTOR *******************/
interface i_Execute{
	execute	// 15
}

/****************** OPTIMIZATION *****************/
interface i_Optimization{/*NULL*/} // 15