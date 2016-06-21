package EL.Elaborations;

import EL.Components.Component;
import EL.Components.*;
import EL.ConfigReader.SpecificConfigReader;
import EL.Loader.SpecificLoader;
import java.util.ArrayList;
import EL.ElaborationError;

public abstract class AbstractGeneratorElaborator extends AbstractElaborator implements I_GenerateElaborator{
    protected _Generator target = null;
    SpecificLoader speload = new SpecificLoader("");    
    
	public void setComponent(Component comp){
		target = (_Generator) comp;	
	}
    
	// A list of elaborations for each subomponent
	
	/**
	 * Get the character used for annotations
	 * 
	 * @author Jose Martins
	 * @author Pedro Fernandes
	 */
	 public String getSeparator(){
	 	return "@";
	}
	
    /**
     * Implementation of the abstract method Elaborate
     * generates the component's elaboration and it's subcomponents, recursivelly 
     *
     * @author José Martins
     * @author Pedro Fernandes
     */
    public void Elaborate(){
       generate();
		
    }	

	public Object getI_GenerateElaboratorGen_helper(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_brkp(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_blx(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_PUSH(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_POP(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_cmp(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_cmpi(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_it(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_cje(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_cjne(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_cjei(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_cjnei(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_writePC(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_writePCreg(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_mov(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_movi(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_ld8(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_ld16(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_ldi8(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_st8(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_st16(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_sti8(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_ld_bit(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_st_bit(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_add(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_addi(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_sub(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_subi(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_div(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_mul(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_not(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_or(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_ori(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_and(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_andi(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_xor(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_shri(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_shli(){
		return null;
	}
	public Object getI_GenerateElaboratorGen_orShl(){
		return null;
	}
	public ArrayList<String> getI_GenerateElaboratorHeaderlist(){
		ArrayList<String> list = new ArrayList<String>();
		return list;
	}


}
