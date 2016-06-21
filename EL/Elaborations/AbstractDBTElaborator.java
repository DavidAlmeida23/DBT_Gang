package EL.Elaborations;

import EL.Components.Component;
import EL.Components.*;
import EL.ConfigReader.SpecificConfigReader;
import EL.Loader.SpecificLoader;
import java.util.ArrayList;
import EL.ElaborationError;

public abstract class AbstractDBTElaborator extends AbstractElaborator {
    protected _DBT target = null;
    SpecificLoader speload = new SpecificLoader("");    
    
	public void setComponent(Component comp){
		target = (_DBT) comp;	
	}
    
	// A list of elaborations for each subomponent
	ArrayList<Class<?>> subTrgClusterList = new ArrayList<Class<?>>(); 
	ArrayList<Class<?>> subSrcClusterList = new ArrayList<Class<?>>(); 
	ArrayList<Class<?>> subTCacheList = new ArrayList<Class<?>>(); 
	ArrayList<Class<?>> subDbtEngineList = new ArrayList<Class<?>>(); 
	ArrayList<Class<?>> subCCacheList = new ArrayList<Class<?>>(); 
	
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
     * Add elaboration in the list of the TrgCluster subcomponent
     *
     * @author Pedro Fernandes
     * @param str path to the elaboration
     */
    public void addTrgClusterListElaborator (String str){
    	Class classe = speload.getElaboratorClass(str);
    	
    	if(AbstractElaborator.class.isAssignableFrom(classe))
    	{
    		subTrgClusterList.add(classe);
    	}else ElaborationError.elaborationError("The Elaborator classe.getName() doesn't extend AbstractElaborator");
    
    }
    
    /**
     * Add elaboration in the list of the SrcCluster subcomponent
     *
     * @author Pedro Fernandes
     * @param str path to the elaboration
     */
    public void addSrcClusterListElaborator (String str){
    	Class classe = speload.getElaboratorClass(str);
    	
    	if(AbstractElaborator.class.isAssignableFrom(classe))
    	{
    		subSrcClusterList.add(classe);
    	}else ElaborationError.elaborationError("The Elaborator classe.getName() doesn't extend AbstractElaborator");
    
    }
    
    /**
     * Add elaboration in the list of the TCache subcomponent
     *
     * @author Pedro Fernandes
     * @param str path to the elaboration
     */
    public void addTCacheListElaborator (String str){
    	Class classe = speload.getElaboratorClass(str);
    	
    	if(AbstractElaborator.class.isAssignableFrom(classe))
    	{
    		subTCacheList.add(classe);
    	}else ElaborationError.elaborationError("The Elaborator classe.getName() doesn't extend AbstractElaborator");
    
    }
    
    /**
     * Add elaboration in the list of the DbtEngine subcomponent
     *
     * @author Pedro Fernandes
     * @param str path to the elaboration
     */
    public void addDbtEngineListElaborator (String str){
    	Class classe = speload.getElaboratorClass(str);
    	
    	if(AbstractElaborator.class.isAssignableFrom(classe))
    	{
    		subDbtEngineList.add(classe);
    	}else ElaborationError.elaborationError("The Elaborator classe.getName() doesn't extend AbstractElaborator");
    
    }
    
    /**
     * Add elaboration in the list of the CCache subcomponent
     *
     * @author Pedro Fernandes
     * @param str path to the elaboration
     */
    public void addCCacheListElaborator (String str){
    	Class classe = speload.getElaboratorClass(str);
    	
    	if(AbstractElaborator.class.isAssignableFrom(classe))
    	{
    		subCCacheList.add(classe);
    	}else ElaborationError.elaborationError("The Elaborator classe.getName() doesn't extend AbstractElaborator");
    
    }
    
	/**
	 * Verify if the specific elaboration is contained in the list of the subcomponentTrgCluster 
	 *
	 * @author Pedro Fernandes
	 * @param class class that will be verified
	 */
	Boolean checkTrgClusterElaboratorList(Object classe)
	{
		if(subTrgClusterList.isEmpty())
		{
			return true;
		}else
		{
			for(Class<?> classOfList : subTrgClusterList )
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
	 * Verify if the specific elaboration is contained in the list of the subcomponentSrcCluster 
	 *
	 * @author Pedro Fernandes
	 * @param class class that will be verified
	 */
	Boolean checkSrcClusterElaboratorList(Object classe)
	{
		if(subSrcClusterList.isEmpty())
		{
			return true;
		}else
		{
			for(Class<?> classOfList : subSrcClusterList )
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
	 * Verify if the specific elaboration is contained in the list of the subcomponentTCache 
	 *
	 * @author Pedro Fernandes
	 * @param class class that will be verified
	 */
	Boolean checkTCacheElaboratorList(Object classe)
	{
		if(subTCacheList.isEmpty())
		{
			return true;
		}else
		{
			for(Class<?> classOfList : subTCacheList )
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
	 * Verify if the specific elaboration is contained in the list of the subcomponentDbtEngine 
	 *
	 * @author Pedro Fernandes
	 * @param class class that will be verified
	 */
	Boolean checkDbtEngineElaboratorList(Object classe)
	{
		if(subDbtEngineList.isEmpty())
		{
			return true;
		}else
		{
			for(Class<?> classOfList : subDbtEngineList )
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
	 * Verify if the specific elaboration is contained in the list of the subcomponentCCache 
	 *
	 * @author Pedro Fernandes
	 * @param class class that will be verified
	 */
	Boolean checkCCacheElaboratorList(Object classe)
	{
		if(subCCacheList.isEmpty())
		{
			return true;
		}else
		{
			for(Class<?> classOfList : subCCacheList )
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
		if(getElaborator(target.get_trgCluster()) != null)
		{
			if(checkTrgClusterElaboratorList(getElaborator(target.get_trgCluster())))
			{
				getElaborator(target.get_trgCluster()).Elaborate();// Starts Elaborating
			}
			else ElaborationError.elaborationError("The Elaboration trgCluster that you specified isn't allowed.");
		
		}else ElaborationError.elaborationError("Missing Elaboration.");	
		
		//Verify if there is an Elaborator for this subcomponent
		if(getElaborator(target.get_srcCluster()) != null)
		{
			if(checkSrcClusterElaboratorList(getElaborator(target.get_srcCluster())))
			{
				getElaborator(target.get_srcCluster()).Elaborate();// Starts Elaborating
			}
			else ElaborationError.elaborationError("The Elaboration srcCluster that you specified isn't allowed.");
		
		}else ElaborationError.elaborationError("Missing Elaboration.");	
		
		//Verify if there is an Elaborator for this subcomponent
		if(getElaborator(target.get_tCache()) != null)
		{
			if(checkTCacheElaboratorList(getElaborator(target.get_tCache())))
			{
				getElaborator(target.get_tCache()).Elaborate();// Starts Elaborating
			}
			else ElaborationError.elaborationError("The Elaboration tCache that you specified isn't allowed.");
		
		}else ElaborationError.elaborationError("Missing Elaboration.");	
		
		//Verify if there is an Elaborator for this subcomponent
		if(getElaborator(target.get_dbtEngine()) != null)
		{
			if(checkDbtEngineElaboratorList(getElaborator(target.get_dbtEngine())))
			{
				getElaborator(target.get_dbtEngine()).Elaborate();// Starts Elaborating
			}
			else ElaborationError.elaborationError("The Elaboration dbtEngine that you specified isn't allowed.");
		
		}else ElaborationError.elaborationError("Missing Elaboration.");	
		
		//Verify if there is an Elaborator for this subcomponent
		if(getElaborator(target.get_cCache()) != null)
		{
			if(checkCCacheElaboratorList(getElaborator(target.get_cCache())))
			{
				getElaborator(target.get_cCache()).Elaborate();// Starts Elaborating
			}
			else ElaborationError.elaborationError("The Elaboration cCache that you specified isn't allowed.");
		
		}else ElaborationError.elaborationError("Missing Elaboration.");	
		
		//The root component must trigger the final files generation after all of the elaborators are processed
		generateFinalFiles();
    }	



}
