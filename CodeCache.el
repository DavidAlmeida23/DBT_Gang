import "Interfaces.el"
import "Languages.el"

component CodeCache(C)
{
	properties:
		int CCache_Size 
	services:
		i_CCache_Decoder fetch
	references:
		i_SrcArch_CCache getWordSize
}