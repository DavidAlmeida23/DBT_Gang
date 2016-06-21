import "Languages.el"
import "Interfaces.el"
import "Generator.el"
import "Architectures.el"

component TargetCluster (C)
{
	subcomponents:
		Architecture target
		Generator gen 
		
	bind gen.r_ISA to target.s_ISA
	bind gen.r_TrgRegisters to target.s_Registers
	
	promote reference gen.r_SrcRegisters as pr_SrcRegisters
	promote reference gen.r_PCAccessors  as pr_PCAccessors
	promote reference gen.r_TCache 		 as pr_TCache
	
	promote service target.s_ISA as ps_ISA
	promote service gen.s_Generate as ps_Generate
}