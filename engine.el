import "defines.el"
component Engine (C)
{
	subcomponents:
		Translate trans
		Execute exe
	services:
		inter16 run
	references:
		inter14 translate
		inter15 exec
	bind translate to trans.translate
	bind exec to exe.exec
	promote reference trans.set_ptr as set_ptr
	promote reference trans.fetch as fetch
	promote reference trans.decode as decode
	promote reference trans.gen as generate
	promote reference exe.get_ptr as get_ptr
	promote reference exe.data_mem as mem
}
component Translate (C)
{
	subcomponents:
		Optimization optimize
	services:
		inter14 translate
	references:
		inter13 fetch
		inter11 decode
		inter12 gen
		inter17 optm
	bind optm to optimize.optm
	promote reference optimize.set_ptr as set_ptr
}
component Optimization(C)
{
	services:
	 	inter17 optm
	 references:
	 	inter4_1 set_ptr
}
component Execute (C)
{
	services:
		inter15 exec
	references:
		inter4_0 get_ptr
		inter3 data_mem
}