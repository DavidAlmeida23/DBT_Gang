import "defines.el"
component Src_gang (C)
{
	subcomponents:
		Decoder dec
		Src_Arch source
		Src_Env env	
	bind env.size to source.memsize
	bind dec.pc to env.pc
	bind dec.op to source.op
	bind dec.reg to source.reg
	bind dec.wordsrc to source.wordsrc
	promote service source.reg as reg
	promote service source.wordsrc as scr_word
	promote service env.mem as mem
	promote service env.s_pc as pc
	promote service dec.decode as decode
	promote reference dec.fetch as fetch
	
}
component Decoder (C)
{
	references:
		inter2 pc
		inter5 op
		inter8 reg
		inter6 wordsrc
		inter13 fetch
	services:
		inter11 decode
}
component Src_Arch (C)
{
	services:
		inter1 memsize
		inter5 op
		inter8 reg
		inter6 wordsrc
}
component Src_Env (C)
{
	subcomponents:
		Data_Mem mem
	promote service mem.pc as pc
	promote service mem.mem as mem
	promote reference mem.size as size
	promote service mem.s_pc as s_pc
}
component Data_Mem (C)
{
	services:
		inter3 mem
		inter2 pc
		inter2_1 s_pc
	references:
		inter1 size
}
interface inter1
{
	xmem_size
	datamem_size
}
interface inter2
{
	getPC
	setPC
}

interface inter5
{
	nbitsopcode
}




