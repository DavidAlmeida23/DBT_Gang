package EL.Elaborations;
import EL.Elaborations.Elaborator;
import java.util.ArrayList;

	public interface I_GenerateElaborator extends Elaborator {      	
	    	
		public ArrayList<String> getI_GenerateElaboratorHeaderlist();
	   public Object getI_GenerateElaboratorGen_helper();
	   public Object getI_GenerateElaboratorGen_brkp();
	   public Object getI_GenerateElaboratorGen_blx();
	   public Object getI_GenerateElaboratorGen_PUSH();
	   public Object getI_GenerateElaboratorGen_POP();
	   public Object getI_GenerateElaboratorGen_cmp();
	   public Object getI_GenerateElaboratorGen_cmpi();
	   public Object getI_GenerateElaboratorGen_it();
	   public Object getI_GenerateElaboratorGen_cje();
	   public Object getI_GenerateElaboratorGen_cjne();
	   public Object getI_GenerateElaboratorGen_cjei();
	   public Object getI_GenerateElaboratorGen_cjnei();
	   public Object getI_GenerateElaboratorGen_writePC();
	   public Object getI_GenerateElaboratorGen_writePCreg();
	   public Object getI_GenerateElaboratorGen_mov();
	   public Object getI_GenerateElaboratorGen_movi();
	   public Object getI_GenerateElaboratorGen_ld8();
	   public Object getI_GenerateElaboratorGen_ld16();
	   public Object getI_GenerateElaboratorGen_ldi8();
	   public Object getI_GenerateElaboratorGen_st8();
	   public Object getI_GenerateElaboratorGen_st16();
	   public Object getI_GenerateElaboratorGen_sti8();
	   public Object getI_GenerateElaboratorGen_ld_bit();
	   public Object getI_GenerateElaboratorGen_st_bit();
	   public Object getI_GenerateElaboratorGen_add();
	   public Object getI_GenerateElaboratorGen_addi();
	   public Object getI_GenerateElaboratorGen_sub();
	   public Object getI_GenerateElaboratorGen_subi();
	   public Object getI_GenerateElaboratorGen_div();
	   public Object getI_GenerateElaboratorGen_mul();
	   public Object getI_GenerateElaboratorGen_not();
	   public Object getI_GenerateElaboratorGen_or();
	   public Object getI_GenerateElaboratorGen_ori();
	   public Object getI_GenerateElaboratorGen_and();
	   public Object getI_GenerateElaboratorGen_andi();
	   public Object getI_GenerateElaboratorGen_xor();
	   public Object getI_GenerateElaboratorGen_shri();
	   public Object getI_GenerateElaboratorGen_shli();
	   public Object getI_GenerateElaboratorGen_orShl();
	
	}
