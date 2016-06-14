import "Languages.el"
import "Interfaces.el"
import "Decoder.el"
import "Architectures.el"
import "SourceEnvironment.el"

component SourceCluster (C)
{
	subcomponents:
		Decoder decoder
		SourceArch srcArch
		SourceEnv srcEnv	
	
	bind decoder.r_ISA 			to srcArch.s_ISA
	bind srcEnv.pr_MemSizes 	to srcArch.s_MemSizes
	bind decoder.r_Registers 	to srcArch.s_Registers
	
	promote service srcArch.s_ISA 		as ps_ISA
	promote service srcArch.s_Registers as ps_Registers 
	
//	bind srcEnv.getXMemSize to srcArch.i_srcArch
//	bind decode.pc 			to srcEnv.pc
//	bind decode.op 			to srcArch.op
//	bind decode.reg 		to srcArch.reg
//	bind decode.getWordSize to srcArch.i_srcArch
//	
//	promote service srcArch.reg 		as reg
//	promote service srcArch.setWordSize as setWordSize
//	promote service srcEnv.getDataMem 	as getDataMem  // Atualizado - Não é necessário fazer promote (Ver SourceEnv)
//	promote service srcEnv.s_pc 		as pc
//	promote service decode.decode 		as decode
//	promote reference decode.fetch 		as fetch
}