package EL.Elaborations;

import EL.Components.Component;
import EL.Components.*;
import EL.ConfigReader.SpecificConfigReader;
import EL.Loader.SpecificLoader;
import java.util.ArrayList;
import EL.ElaborationError;

public abstract class AbstractTargetClusterElaborator extends AbstractElaborator {
    protected _TargetCluster target = null;
    SpecificLoader speload = new SpecificLoader("");    
    
	public void setComponent(Component comp){
		target = (_TargetCluster) comp;	
	}
    
	// A list of elaborations for each subomponent
	ArrayList<Class<?>> subTargetList = new ArrayList<Class<?>>(); 
	ArrayList<Class<?>> subGenList = new ArrayList<Class<?>>(); 
	
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
     * Add elaboration in the list of the Target subcomponent
     *
     * @author Pedro Fernandes
     * @param str path to the elaboration
     */
    public void addTargetListElaborator (String str){
    	Class classe = speload.getElaboratorClass(str);
    	
    	if(AbstractElaborator.class.isAssignableFrom(classe))
    	{
    		subTargetList.add(classe);
    	}else ElaborationError.elaborationError("The Elaborator classe.getName() doesn't extend AbstractElaborator");
    
    }
    
    /**
     * Add elaboration in the list of the Gen subcomponent
     *
     * @author Pedro Fernandes
     * @param str path to the elaboration
     */
    public void addGenListElaborator (String str){
    	Class classe = speload.getElaboratorClass(str);
    	
    	if(AbstractElaborator.class.isAssignableFrom(classe))
    	{
    		subGenList.add(classe);
    	}else ElaborationError.elaborationError("The Elaborator classe.getName() doesn't extend AbstractElaborator");
    
    }
    
	/**
	 * Verify if the specific elaboration is contained in the list of the subcomponentTarget 
	 *
	 * @author Pedro Fernandes
	 * @param class class that will be verified
	 */
	Boolean checkTargetElaboratorList(Object classe)
	{
		if(subTargetList.isEmpty())
		{
			return true;
		}else
		{
			for(Class<?> classOfList : subTargetList )
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
	 * Verify if the specific elaboration is contained in the list of the subcomponentGen 
	 *
	 * @author Pedro Fernandes
	 * @param class class that will be verified
	 */
	Boolean checkGenElaboratorList(Object classe)
	{
		if(subGenList.isEmpty())
		{
			return true;
		}else
		{
			for(Class<?> classOfList : subGenList )
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
		if(getElaborator(target.get_target()) != null)
		{
			if(checkTargetElaboratorList(getElaborator(target.get_target())))
			{
				getElaborator(target.get_target()).Elaborate();// Starts Elaborating
			}
			else ElaborationError.elaborationError("The Elaboration target that you specified isn't allowed.");
		
		}else ElaborationError.elaborationError("Missing Elaboration.");	
		
		//Verify if there is an Elaborator for this subcomponent
		if(getElaborator(target.get_gen()) != null)
		{
			if(checkGenElaboratorList(getElaborator(target.get_gen())))
			{
				getElaborator(target.get_gen()).Elaborate();// Starts Elaborating
			}
			else ElaborationError.elaborationError("The Elaboration gen that you specified isn't allowed.");
		
		}else ElaborationError.elaborationError("Missing Elaboration.");	
		
    }	



}
