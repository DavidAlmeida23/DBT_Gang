import "Languages.el"
import "Interfaces.el"

component TargetArch (C)
{
	services:
		i_ISA s_ISA
		i_MemSizes s_MemSizes
		i_Registers s_Registers
}

component SourceArch (C)
{
	services:
		i_ISA s_ISA
		i_MemSizes s_MemSizes
		i_Registers s_Registers
}
