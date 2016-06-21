package EL.Elaborations;

import EL.Components.Component;
import EL.Components.*;
import EL.ConfigReader.SpecificConfigReader;
import EL.Loader.SpecificLoader;
import java.util.ArrayList;
import EL.ElaborationError;

public abstract class AbstractArchitectureElaborator extends AbstractElaborator implements I_ISAElaborator, I_MemSizesElaborator, I_RegistersElaborator{
    protected _Architecture target = null;
    SpecificLoader speload = new SpecificLoader("");    
    
	public void setComponent(Component comp){
		target = (_Architecture) comp;	
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

	public Object getI_ISAElaboratorGetWordSize(){
		return null;
	}
	public Object getI_ISAElaboratorNBitsOpcode(){
		return null;
	}
	public ArrayList<String> getI_ISAElaboratorHeaderlist(){
		ArrayList<String> list = new ArrayList<String>();
		return list;
	}
	public Object getI_MemSizesElaboratorXDataMemSize(){
		return null;
	}
	public Object getI_MemSizesElaboratorDataMemSize(){
		return null;
	}
	public Object getI_MemSizesElaboratorMemSize(){
		return null;
	}
	public Object getI_MemSizesElaboratorHeapSize(){
		return null;
	}
	public Object getI_MemSizesElaboratorStackSize(){
		return null;
	}
	public ArrayList<String> getI_MemSizesElaboratorHeaderlist(){
		ArrayList<String> list = new ArrayList<String>();
		return list;
	}
	public ArrayList<String> getI_RegistersElaboratorHeaderlist(){
		ArrayList<String> list = new ArrayList<String>();
		return list;
	}


}
