import "Languages.el"
import "Interfaces.el"

/*** Source and Target Architectures ***/
import "Architectures.el"
/*-----------------------*/

/*** Source Group ***/
/*-----------------------*/
import "SourceCluster.el"
/*-----------------------*/

/*** Target Group ***/
/*-----------------------*/
import "TargetCluster.el"
/*-----------------------*/

/*** DBT Engine ***/
/*-----------------------*/
import "DBTEngine.el"
/*-----------------------*/

/*** Memory Structures ***/
/*-----------------------*/
import "CodeCache.el"
import "TranslationCache.el"
import "DataMemory.el"
/*-----------------------*/

compile DBT
component DBT (C)
{
	subcomponents:
		SourceCluster srcCluster
		TargetCluster trgCluster
		CodeCache cCache
		TranslationCache tCache
		DBTEngine dbtEngine
	references:
		i_RunDBT r_RunDBT
		
	bind cCache.r_ISA to srcCluster.ps_ISA
	bind trgCluster.pr_SrcRegisters to srcCluster.ps_Registers
	bind trgCluster.pr_PCAccessors to srcCluster.ps_PCAccessors
	bind dbtEngine.pr_DMem to srcCluster.pps_DMem
	bind dbtEngine.pr_Decode to srcCluster.ps_Decode
	bind tCache.r_ISA to trgCluster.ps_ISA
	bind srcCluster.pr_Generate to trgCluster.ps_Generate
	bind trgCluster.pr_TCache to tCache.s_TCache
	bind srcCluster.pr_CCache to cCache.s_CCache
	bind r_RunDBT to dbtEngine.s_RunDBT
	bind dbtEngine.pr_TransTCache to tCache.s_TCache
	bind dbtEngine.pr_ExeTCache to tCache.s_TCache
}


