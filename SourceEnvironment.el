import "Languages.el"
import "Interfaces.el"
import "DataMemory.el"

component SourceEnv (C)
{
	subcomponents:
		DataMemory dataMem
	services:
		i_PCAcessors s_setPC

	promote reference dataMem.r_MemSizes as pr_MemSizes
}