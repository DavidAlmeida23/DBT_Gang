import "Languages.el"
import "Interfaces.el"
import "Translate.el"
import "Execute.el"

component DBTEngine (C)
{
	subcomponents:
		Translate translate
		Execute execute
	services:
		i_RunDBT s_RunDBT
	references:
		i_Translate r_Translate
		i_Execute r_Execute
	
	bind r_Translate to translate.s_Translate
	bind r_Execute to execute.s_Execute
	promote reference execute.r_DMem as pr_DMem
	promote reference translate.r_Decode as pr_Decode
	promote reference translate.r_TCache as pr_TransTCache
	promote reference execute.r_TCache as pr_ExeTCache
} 