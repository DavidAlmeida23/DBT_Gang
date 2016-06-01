language C
{
	annotation: "@"
}
interface inter2_1
{
	getPC
}
interface inter3
{
	getDataMem
}
interface inter4_0
{
	getcurrBBExecPtr
}
interface inter4_1
{
	setcurrBBExecPtr
}
interface inter6
{
	src_word
}
interface inter7
{
	trg_word
}
interface inter8
{
	src_Registers
}
interface inter10
{
	cachecode
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

component dummyBOMBASman (C)
{
	properties:
		string queremFazerMelhor : "façam"
		string naoGostamDosNomes : "mudem"
		string queremNumUnicoFicheiro : "metam"
		string queremEmMaisFicheiros : "criem"
		string assinado : "bomberman"
}