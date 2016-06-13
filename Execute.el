import "Languages.el"
import "Interfaces.el"

component Execute (C)
{
	services:
		inter15 exec
	references:
		i_TCache_Execute get_ptr
		i_DMem_Execute data_mem
}