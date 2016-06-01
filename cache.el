import "defines.el"
component CodeCache(C)
{
	properties:
		int code_cache_size 
	services:
		inter13 fetch
	references:
		inter6 src_word
}
component TranslatedCache(C)
{
	properties:
		int basic_block_size
	services:
		inter4_0 get_ptr
		inter4_1 set_ptr
		inter10 cache_code
	references:
		inter7 trg_wrd
}