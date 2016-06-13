import "Languages.el"
import "Interfaces.el"
import "Generator.el"
import "TargetArchitecture.el"

component TargetGang (C)
{
	subcomponents:
		TargetArch target
		Generator gen
	bind gen.trg_reg to target.reg
	bind gen.getWordSize to target.setWordSize
	promote service target.setWordSize as target_word
	promote reference gen.pc as pc
	promote reference gen.src_reg as src_reg
	promote service gen.gen as generate
	promote reference gen.cacheCode as cache_code
}