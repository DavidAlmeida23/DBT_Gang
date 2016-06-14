import "Languages.el"
import "Interfaces.el"
import "Generator.el"
import "Architectures.el"

component TargetCluster (C)
{
	subcomponents:
		TargetArch target
		Generator gen

	promote reference gen.r_Registers as pr_Registers
}