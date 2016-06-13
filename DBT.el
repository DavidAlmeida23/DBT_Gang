import "Languages.el"
import "Interfaces.el"
import "SourceArchitecture.el"
import "TargetArchitecture.el"
import "Engine.el"
import "SourceGang.el"
import "TargetGang.el"
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
		SourceGang srcGang
		TargetGang trgGang
		CodeCache ccache
		TranslationCache tcache
		Engine eng
		
	references:
		inter16 run
		
	bind run 				to eng.run
	bind trgGang.src_reg 	to srcGang.reg
	bind trgGang.pc 		to srcGang.pc
	bind srcGang.fetch 		to ccache.fetch
	bind ccache.getWordSize to srcGang.scr_word
	bind eng.decode 		to srcGang.decode
	bind eng.mem 			to srcGang.mem
	bind eng.fetch 			to ccache.fetch
	bind eng.generate 		to trgGang.generate
	bind eng.get_ptr 		to tcache.getLastTransAddr
	bind eng.set_ptr 		to tcache.getCurrInsAddr
	bind trgGang.cache_code	to tcache.cacheCode
	bind tcache.getWordSize to trgGang.target_word
	bind eng.addTag			to tcache.addTag
	bind eng.getTransAddr	to tcache.getTransAddr
}

