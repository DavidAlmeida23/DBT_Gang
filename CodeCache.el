import "Interfaces.el"
import "Languages.el"

component CodeCache(C)
{
	properties:
		int CCache_Size 
	services:
		i_CCache s_CCache
	references:
		i_ISA r_ISA
}