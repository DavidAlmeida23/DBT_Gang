import "Languages.el"
import "Interfaces.el"

component Generator (C)
{
	properties:
		bool optmizations : false
	services:
		i_Generate s_Generate	
	references:
		i_Registers r_SrcRegisters
		i_Registers r_TrgRegisters
		i_PCAccessors r_PCAccessors
		i_ISA r_ISA
		i_TCache r_TCache

}
