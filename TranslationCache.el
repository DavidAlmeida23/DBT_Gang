import "Languages.el"
import "Interfaces.el"

component TranslationCache(C)
{
	properties:
		int TCache_Size
		int numberOfTradutions
	services:
		i_TCache i_tcache
	references:
		i_TrgArch getWordSize
}

