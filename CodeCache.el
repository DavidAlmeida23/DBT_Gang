import "Interfaces.el"
import "Languages.el"

component CodeCache(C)
{
	properties:
		int CCache_Size 
	services:
		i_CCache fetch
	references:
		i_ISA r_ISA
}