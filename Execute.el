import "Languages.el"
import "Interfaces.el"

component Execute (C)
{
	services:
		i_Execute s_Execute
	references:
		i_DMem r_DMem
		i_TCache r_TCache
		
}