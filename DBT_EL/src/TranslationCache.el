import "Languages.el"
import "Interfaces.el"

component TranslationCache(C)
{
	properties:
		int TCache_Size 
		int numberOfTradutions
	services:
		i_TCache s_TCache
	references:
		i_ISA r_ISA
}

