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

//compile DBT
component DBT (C)
{
	subcomponents:
		SourceCluster srcCluster
		TargetCluster trgCluster
		CodeCache cCache
//		TranslationCache tCache
//		DBTEngine engine
		
	bind cCache.r_ISA to srcCluster.ps_ISA
	bind trgCluster.pr_Registers to srcCluster.ps_Registers
}

