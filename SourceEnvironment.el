import "Languages.el"
import "Interfaces.el"
import "DataMemory.el"

component SourceEnv (C)
{
	subcomponents:
		DataMemory mem
	services:
		inter2 pc		// Atualizado - Este serviço não é DMem mais sim do SourceEnv
		inter2_1 s_pc 	// Atualizado - Este serviço não é DMem mais sim do SourceEnv
	promote service mem.getDataMem 		as getDataMem
	promote reference mem.getMemSize 	as getMemSize
	promote reference mem.getXMemSize 	as getXMemSize
}