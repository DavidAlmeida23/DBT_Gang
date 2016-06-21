import "Languages.el"
import "Interfaces.el"

component Architecture (C)
{
	properties:
		string name
	services:
		i_ISA s_ISA
		i_MemSizes s_MemSizes
		i_Registers s_Registers
}
