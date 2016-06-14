import "Languages.el"
import "Interfaces.el"
import "SourceArchitecture.el"
import "TargetArchitecture.el"
import "Engine.el"
import "SourceGroup.el"
import "TargetGroup.el"
import "CodeCache.el"
import "TranslationCache.el"

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
		SourceGroup srcGroup
		TargetGroup trgGroup
		CodeCache ccache
		TranslationCache tcache
		Engine engine
		
	references:
		inter16 run
		
	bind run 					to engine.run
	bind engine.generate 		to trgGroup.generate
	
	// Bindings to the SourceGang Services
	bind trgGroup.src_reg 		to srcGroup.reg
	bind trgGroup.pc 			to srcGroup.pc
	bind engine.decode 			to srcGroup.decode
	bind engine.mem 			to srcGroup.getDataMem
	
	
	// DONE 
	// Bindings to the CCache References
	bind ccache.getWordSize 	to srcGroup.setWordSize
	
	// Bindings to the CCache Services
	bind engine.fetch 			to ccache.fetch
	bind srcGroup.fetch 		to ccache.fetch
	
	// Bindings to the TCache References
	bind tcache.getWordSize 	to trgGroup.setWordSize
	
	// Bindings to the TCache Services 
	bind engine.get_ptr 		to tcache.getLastTransAddr 
	bind engine.set_ptr 		to tcache.getCurrInsAddr
	bind engine.addTag			to tcache.addTag
	bind engine.getTransAddr	to tcache.getTransAddr
	bind trgGroup.cacheCode		to tcache.cacheCode
}

