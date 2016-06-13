import "Languages.el"
import "Interfaces.el"

component TranslationCache(C)
{
	properties:
		int TCache_Size
		int numberOfTradutions
	services:
		i_TCache_Execute 	getLastTransAddr
		i_TCache_Translate 	getCurrInsAddr
		i_TCache_Generator 	cacheCode
		i_TCache_RunDBT 	addTag
		i_TCache_RunDBT2 	getTransAddr
	references:
		i_Target_TCache getWordSize
}

