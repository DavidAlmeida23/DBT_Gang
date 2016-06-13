import "Languages.el"
import "Interfaces.el"


component SourceArch (C)
{
	services:
		i_SrcArch_DMem memSize
		i_SrcArch_DMem2 xMemSize
		inter5 op
		inter8 reg
		i_SrcArch_CCache setWordSize
}




