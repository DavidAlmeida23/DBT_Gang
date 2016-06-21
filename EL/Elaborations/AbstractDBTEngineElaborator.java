package EL.Elaborations;

import EL.Components.Component;
import EL.Components.*;
import EL.ConfigReader.SpecificConfigReader;
import EL.Loader.SpecificLoader;
import java.util.ArrayList;
import EL.ElaborationError;

public abstract class AbstractDBTEngineElaborator extends AbstractElaborator implements I_RunDBTElaborator, I_CurrBBExecElaborator, I_InitElaborator{
    protected _DBTEngine target = null;
    SpecificLoader speload = new SpecificLoader("");    
    
	public void setComponent(Component comp){
		target = (_DBTEngine) comp;	
	}
    
	// A list of elaborations for each subomponent
	ArrayList<Class<?>> subTranslateList = new ArrayList<Class<?>>(); 
	ArrayList<Class<?>> subExecuteList = new ArrayList<Class<?>>(); 
	
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
     * Add elaboration in the list of the Translate subcomponent
     *
     * @author Pedro Fernandes
     * @param str path to the elaboration
     */
    public void addTranslateListElaborator (String str){
    	Class classe = speload.getElaboratorClass(str);
    	
    	if(AbstractElaborator.class.isAssignableFrom(classe))
    	{
    		subTranslateList.add(classe);
    	}else ElaborationError.elaborationError("The Elaborator classe.getName() doesn't extend AbstractElaborator");
    
    }
    
    /**
     * Add elaboration in the list of the Execute subcomponent
     *
     * @author Pedro Fernandes
     * @param str path to the elaboration
     */
    public void addExecuteListElaborator (String str){
    	Class classe = speload.getElaboratorClass(str);
    	
    	if(AbstractElaborator.class.isAssignableFrom(classe))
    	{
    		subExecuteList.add(classe);
    	}else ElaborationError.elaborationError("The Elaborator classe.getName() doesn't extend AbstractElaborator");
    
    }
    
	/**
	 * Verify if the specific elaboration is contained in the list of the subcomponentTranslate 
	 *
	 * @author Pedro Fernandes
	 * @param class class that will be verified
	 */
	Boolean checkTranslateElaboratorList(Object classe)
	{
		if(subTranslateList.isEmpty())
		{
			return true;
		}else
		{
			for(Class<?> classOfList : subTranslateList )
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
	 * Verify if the specific elaboration is contained in the list of the subcomponentExecute 
	 *
	 * @author Pedro Fernandes
	 * @param class class that will be verified
	 */
	Boolean checkExecuteElaboratorList(Object classe)
	{
		if(subExecuteList.isEmpty())
		{
			return true;
		}else
		{
			for(Class<?> classOfList : subExecuteList )
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
		if(getElaborator(target.get_translate()) != null)
		{
			if(checkTranslateElaboratorList(getElaborator(target.get_translate())))
			{
				getElaborator(target.get_translate()).Elaborate();// Starts Elaborating
			}
			else ElaborationError.elaborationError("The Elaboration translate that you specified isn't allowed.");
		
		}else ElaborationError.elaborationError("Missing Elaboration.");	
		
		//Verify if there is an Elaborator for this subcomponent
		if(getElaborator(target.get_execute()) != null)
		{
			if(checkExecuteElaboratorList(getElaborator(target.get_execute())))
			{
				getElaborator(target.get_execute()).Elaborate();// Starts Elaborating
			}
			else ElaborationError.elaborationError("The Elaboration execute that you specified isn't allowed.");
		
		}else ElaborationError.elaborationError("Missing Elaboration.");	
		
    }	

	public Object getI_RunDBTElaboratorRun(){
		return null;
	}
	public ArrayList<String> getI_RunDBTElaboratorHeaderlist(){
		ArrayList<String> list = new ArrayList<String>();
		return list;
	}
	public Object getI_CurrBBExecElaboratorCurrBBExecPtr(){
		return null;
	}
	public ArrayList<String> getI_CurrBBExecElaboratorHeaderlist(){
		ArrayList<String> list = new ArrayList<String>();
		return list;
	}
	public Object getI_InitElaboratorInitTranslator(){
		return null;
	}
	public Object getI_InitElaboratorRunDBT(){
		return null;
	}
	public ArrayList<String> getI_InitElaboratorHeaderlist(){
		ArrayList<String> list = new ArrayList<String>();
		return list;
	}


}
