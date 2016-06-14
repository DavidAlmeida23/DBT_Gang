import "Languages.el"
import "Interfaces.el"
import "DataMemory.el"

component SourceEnv (C)
{
	subcomponents:
		DataMemory dataMem
	services:
		i_PCAccessors s_PCAccessors

	promote reference dataMem.r_MemSizes as pr_MemSizes
	promote service dataMem.s_DMem as ps_DMem
}