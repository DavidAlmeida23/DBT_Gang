import "Languages.el"
import "Interfaces.el"
import "Optimizations.el"

component Translate (C)
{
	subcomponents:
		Optimization optimization
	services:
		i_Translate s_Translate
	references:
		i_Decode r_Decode
		i_Optimization r_Optimization
		i_TCache r_TCache
		
	bind r_Optimization to optimization.s_Optimization
}