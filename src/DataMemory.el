import "Languages.el"
import "Interfaces.el"

component DataMemory(C)
{ 
	services:
		i_DMem s_DMem
	references:
		i_MemSizes r_MemSizes	// DataMem & xDataMem
}