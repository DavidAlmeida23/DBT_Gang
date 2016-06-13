import "Languages.el"
import "Interfaces.el"
import "Translate.el"
import "Execute.el"

component Engine (C)
{
	subcomponents:
		Translate translate
		Execute execute
	services:
		inter16 run
	references:
		i_TCache_RunDBT addTag
		i_TCache_RunDBT2 getTransAddr
		inter14 trans
		inter15 exec
		
	// Subcomponent Translate providing a service to the Engine Component
	bind trans to translate.translate
	
	// Subcomponent Execute providing a service to the Engine Component
	bind exec to execute.exec
	
	// Promoting References from the Translate Component
	promote reference translate.set_ptr as set_ptr
	promote reference translate.fetch 	as fetch
	promote reference translate.decode 	as decode
	promote reference translate.gen 	as generate
	
	// Promoting References from the Execute Component
	promote reference execute.get_ptr 	as get_ptr
	promote reference execute.data_mem 	as mem
}