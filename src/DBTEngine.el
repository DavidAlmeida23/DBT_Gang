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
		i_CurrBBExec s_CurrBBExec
		i_Init s_Init
	references:
		i_Translate r_Translate
		
	
	bind r_Translate to translate.s_Translate
	bind execute.r_CurrBBExec to s_CurrBBExec
	promote reference execute.r_DMem as pr_DMem
	promote reference translate.r_Decode as pr_Decode
	promote reference translate.r_TCache as pr_TransTCache

} 
