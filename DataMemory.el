import "Languages.el"
import "Interfaces.el"

component DataMemory(C)
{ 
	services:
		i_DMem_Execute getDataMem
	references:
		i_SrcArch_DMem getMemSize	// 8051 Internal Memory
		i_SrcArch_DMem2 getXMemSize // 8051 External Memory
}

//component Data_Mem (C)
//{
//	services:
//		i_DMem_Execute mem
//		inter2 pc
//		inter2_1 s_pc
//	references:
//		inter1 size
//}