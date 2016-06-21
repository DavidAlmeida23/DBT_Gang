package EL.Elaborations;

import EL.Components.Component;
import EL.Components.*;
import EL.ConfigReader.SpecificConfigReader;
import EL.Loader.SpecificLoader;
import java.util.ArrayList;
import EL.ElaborationError;

public abstract class AbstractSourceEnvElaborator extends AbstractElaborator implements I_PCAccessorsElaborator{
    protected _SourceEnv target = null;
    SpecificLoader speload = new SpecificLoader("");    
    
	public void setComponent(Component comp){
		target = (_SourceEnv) comp;	
	}
    
	// A list of elaborations for each subomponent
	ArrayList<Class<?>> subDataMemList = new ArrayList<Class<?>>(); 
	
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
     * Add elaboration in the list of the DataMem subcomponent
     *
     * @author Pedro Fernandes
     * @param str path to the elaboration
     */
    public void addDataMemListElaborator (String str){
    	Class classe = speload.getElaboratorClass(str);
    	
    	if(AbstractElaborator.class.isAssignableFrom(classe))
    	{
    		subDataMemList.add(classe);
    	}else ElaborationError.elaborationError("The Elaborator classe.getName() doesn't extend AbstractElaborator");
    
    }
    
	/**
	 * Verify if the specific elaboration is contained in the list of the subcomponentDataMem 
	 *
	 * @author Pedro Fernandes
	 * @param class class that will be verified
	 */
	Boolean checkDataMemElaboratorList(Object classe)
	{
		if(subDataMemList.isEmpty())
		{
			return true;
		}else
		{
			for(Class<?> classOfList : subDataMemList )
			{
				if(classOfList.isInstance(classe))
				{
					return true;
				}
			}
		}
		return false;
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
		
		//Verify if there is an Elaborator for this subcomponent
		if(getElaborator(target.get_dataMem()) != null)
		{
			if(checkDataMemElaboratorList(getElaborator(target.get_dataMem())))
			{
				getElaborator(target.get_dataMem()).Elaborate();// Starts Elaborating
			}
			else ElaborationError.elaborationError("The Elaboration dataMem that you specified isn't allowed.");
		
		}else ElaborationError.elaborationError("Missing Elaboration.");	
		
    }	

	public Object getI_PCAccessorsElaboratorGetPC(){
		return null;
	}
	public Object getI_PCAccessorsElaboratorSetPC(){
		return null;
	}
	public ArrayList<String> getI_PCAccessorsElaboratorHeaderlist(){
		ArrayList<String> list = new ArrayList<String>();
		return list;
	}


}
