import "Languages.el"
import "Interfaces.el"
import "Decoder.el"
import "Architectures.el"
import "SourceEnvironment.el"

component SourceCluster (C)
{
	subcomponents:
		Decoder decoder
		Architecture srcArch
		SourceEnv srcEnv	
	 
	bind decoder.r_ISA 			to srcArch.s_ISA
	bind srcEnv.pr_MemSizes 	to srcArch.s_MemSizes
	bind decoder.r_Registers 	to srcArch.s_Registers
	bind decoder.r_PCAccessors	to srcEnv.s_PCAccessors
	
	promote service srcArch.s_ISA 		 as ps_ISA
	promote service srcArch.s_Registers  as ps_Registers 
	promote service srcEnv.s_PCAccessors as ps_PCAccessors
	promote service srcEnv.ps_DMem		 as pps_DMem
	promote service decoder.s_Decode	 as ps_Decode
	
	promote reference decoder.r_Generate as pr_Generate
	promote reference decoder.r_CCache   as pr_CCache
}