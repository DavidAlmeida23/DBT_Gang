import "defines.el"
component Trg_gang (C)
{
	subcomponents:
		Trg_Arch target
		Generator gen
	bind gen.trg_reg to target.reg
	bind gen.trg_word to target.trg_word
	promote service target.trg_word as target_word
	promote reference gen.pc as pc
	promote reference gen.src_reg as src_reg
	promote service gen.gen as generate
	promote reference gen.cache_code as cache_code
}
component Trg_Arch (C)
{
	services:
		inter9 reg
		inter7 trg_word
}
component Generator (C)
{
//	properties:
// 		bool saveIR : false
// 		string genType restrict {"IR","~IR"} : "IR"	
	services:
		inter12 gen	
	references:
		inter2_1 pc
		inter7 trg_word
		inter8 src_reg 
		inter9 trg_reg
		inter10 cache_code
}
interface inter9
{
	targetRegisters
}