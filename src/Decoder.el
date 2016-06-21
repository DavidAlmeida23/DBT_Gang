import "Languages.el"
import "Interfaces.el"

component Decoder (C)
{
	services:
		i_Decode s_Decode
	references:
		i_ISA r_ISA
		i_Registers r_Registers
		i_PCAccessors r_PCAccessors
		i_Generate r_Generate
		i_CCache r_CCache
}