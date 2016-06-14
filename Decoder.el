import "Languages.el"
import "Interfaces.el"

component Decoder (C)
{
	services:
		i_Decode s_decode
	references:
		i_ISA r_ISA
		i_Registers r_Registers
//	references:
//		inter2 pc
//		inter5 op
//		inter8 reg
//		i_SrcArch getWordSize
//		i_CCache fetch
}