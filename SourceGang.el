import "Languages.el"
import "Interfaces.el"
import "Decoder.el"
import "SourceArchitecture.el"
import "SourceEnvironment.el"

component SourceGang (C)
{
	subcomponents:
		Decoder decode
		SourceArch srcArch
		SourceEnv srcEnv	
		
	bind srcEnv.getMemSize 	to srcArch.memSize
	bind srcEnv.getXMemSize to srcArch.xMemSize
	bind decode.pc 			to srcEnv.pc
	bind decode.op 			to srcArch.op
	bind decode.reg 		to srcArch.reg
	bind decode.getWordSize to srcArch.setWordSize
	
	promote service srcArch.reg 		as reg
	promote service srcArch.setWordSize as scr_word
	promote service srcEnv.getDataMem 	as mem  // Atualizado - Não é necessário fazer promote (Ver SourceEnv)
	promote service srcEnv.s_pc 		as pc
	promote service decode.decode 		as decode
	promote reference decode.fetch 		as fetch
}