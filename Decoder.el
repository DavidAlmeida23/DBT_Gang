import "Languages.el"
import "Interfaces.el"

component Decoder (C)
{
	references:
		inter2 pc
		inter5 op
		inter8 reg
		i_SrcArch_CCache getWordSize
		i_CCache_Decoder fetch
	services:
		inter11 decode
}