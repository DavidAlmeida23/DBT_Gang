/******************** TCACHE ***********************/
/*-------------------------------------------------*/
interface i_Target_TCache // 7
{
	getWordSize
}

interface i_TCache_RunDBT // Atualização - Esta interface ainda nao existia no modelo
{
	addTag
}

interface i_TCache_RunDBT2 // Atualização - Esta interface ainda nao existia no modelo
{
	getTransAddr
}

interface i_TCache_Execute // 4_0
{
	//getcurrBBExecPtr
	getLastTransAddr
}

interface i_TCache_Translate // 4_1
{
	//setcurrBBExecPtr
	getCurrInsAddr
}

interface i_TCache_Generator // 10
{
	cacheCode
}
/*-------------------------------------------------*/


/******************** CCACHE ***********************/
/*-------------------------------------------------*/
interface i_CCache_Decoder // 13
{
	fetch
}

interface i_SrcArch_CCache // 6
{
	getWordSize
}
/*-------------------------------------------------*/


/**************** DATA MEMORY **********************/
/*-------------------------------------------------*/
interface i_DMem_Execute // 3
{
	getDataMem
}

interface i_SrcArch_DMem // 1
{
	MemSize
}

interface i_SrcArch_DMem2 // 1
{
	xMemSize
}
/*-------------------------------------------------*/



interface inter2
{
	getPC
	setPC
}

interface inter5
{
	nbitsopcode
}

interface inter2_1
{
	getPC
}

interface inter8
{
	src_Registers
}

interface inter9
{
	targetRegisters
}

interface inter11
{
	decode
}
interface inter12
{
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
interface inter13
{
	fetch
}

interface inter14
{
	translate
}
interface inter15
{
	execute
}
interface inter16
{
	runDBT
}
interface inter17
{
	
}