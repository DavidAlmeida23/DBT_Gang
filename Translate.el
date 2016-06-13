import "Languages.el"
import "Interfaces.el"
import "Optimizations.el"

component Translate (C)
{
	subcomponents:
		Optimization optimize
	services:
		inter14 translate
	references:
		i_CCache_Decoder fetch
		inter11 decode
		inter12 gen
		inter17 optm
	bind optm to optimize.optm
	promote reference optimize.set_ptr as set_ptr
}