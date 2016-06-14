import "Languages.el"
import "Interfaces.el"

component Generator (C)
{
	services:
		i_Generate s_gen	
	references:
		i_Registers r_Registers
}