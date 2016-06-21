import "Languages.el"
import "Interfaces.el"

component Translate (C)
{
	services:
		i_Translate s_Translate
	references:
		i_Decode r_Decode  
		i_Optimization r_Optimization
		i_TCache r_TCache
} 
