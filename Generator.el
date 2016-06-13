import "Languages.el"
import "Interfaces.el"

component Generator (C)
{
//	properties:
// 		bool saveIR : false
// 		string genType restrict {"IR","~IR"} : "IR"	
	services:
		inter12 gen	
	references:
		inter2_1 pc
		i_Target_TCache getWordSize
		inter8 src_reg 
		inter9 trg_reg
		i_TCache_Generator cacheCode
}