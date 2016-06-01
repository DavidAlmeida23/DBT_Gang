import "source.el"
import "defines.el"
import "target.el"
import "cache.el"
import "engine.el"
//compile DBT
component DBT (C)
{
	subcomponents:
		Src_gang source
		Trg_gang target
		CodeCache ccache
		TranslatedCache tcache
		Engine eng
	references:
		inter16 run
	bind run to eng.run
	bind target.src_reg to source.reg
	bind target.pc to source.pc
	bind source.fetch to ccache.fetch
	bind ccache.src_word to source.scr_word
	bind eng.decode to source.decode
	bind eng.mem to source.mem
	bind eng.fetch to ccache.fetch
	bind eng.generate to target.generate
	bind eng.get_ptr to tcache.get_ptr
	bind eng.set_ptr to tcache.set_ptr
	bind target.cache_code to tcache.cache_code
	bind tcache.trg_wrd to target.target_word
}

