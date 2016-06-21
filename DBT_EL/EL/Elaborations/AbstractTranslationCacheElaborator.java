package EL.Elaborations;

import EL.Components.Component;
import EL.Components.*;
import EL.ConfigReader.SpecificConfigReader;
import EL.Loader.SpecificLoader;
import java.util.ArrayList;
import EL.ElaborationError;

public abstract class AbstractTranslationCacheElaborator extends AbstractElaborator implements I_TCacheElaborator{
    protected _TranslationCache target = null;
    SpecificLoader speload = new SpecificLoader("");    
    
	public void setComponent(Component comp){
		target = (_TranslationCache) comp;	
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

	public Object getI_TCacheElaboratorAddTag(){
		return null;
	}
	public Object getI_TCacheElaboratorGetTransAddr(){
		return null;
	}
	public Object getI_TCacheElaboratorGetLastTransAddr(){
		return null;
	}
	public Object getI_TCacheElaboratorGetCurrInsAddr(){
		return null;
	}
	public Object getI_TCacheElaboratorCacheCode(){
		return null;
	}
	public ArrayList<String> getI_TCacheElaboratorHeaderlist(){
		ArrayList<String> list = new ArrayList<String>();
		return list;
	}


}
