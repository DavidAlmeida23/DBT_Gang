package EL.Elaborations;

import EL.Components.Component;
import EL.Components.*;
import EL.ConfigReader.SpecificConfigReader;
import EL.Loader.SpecificLoader;
import java.util.ArrayList;
import EL.ElaborationError;

public abstract class AbstractSourceClusterElaborator extends AbstractElaborator {
    protected _SourceCluster target = null;
    SpecificLoader speload = new SpecificLoader("");    
    
	public void setComponent(Component comp){
		target = (_SourceCluster) comp;	
	}
    
	// A list of elaborations for each subomponent
	ArrayList<Class<?>> subSrcArchList = new ArrayList<Class<?>>(); 
	ArrayList<Class<?>> subSrcEnvList = new ArrayList<Class<?>>(); 
	ArrayList<Class<?>> subDecoderList = new ArrayList<Class<?>>(); 
	
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
     * Add elaboration in the list of the SrcArch subcomponent
     *
     * @author Pedro Fernandes
     * @param str path to the elaboration
     */
    public void addSrcArchListElaborator (String str){
    	Class classe = speload.getElaboratorClass(str);
    	
    	if(AbstractElaborator.class.isAssignableFrom(classe))
    	{
    		subSrcArchList.add(classe);
    	}else ElaborationError.elaborationError("The Elaborator classe.getName() doesn't extend AbstractElaborator");
    
    }
    
    /**
     * Add elaboration in the list of the SrcEnv subcomponent
     *
     * @author Pedro Fernandes
     * @param str path to the elaboration
     */
    public void addSrcEnvListElaborator (String str){
    	Class classe = speload.getElaboratorClass(str);
    	
    	if(AbstractElaborator.class.isAssignableFrom(classe))
    	{
    		subSrcEnvList.add(classe);
    	}else ElaborationError.elaborationError("The Elaborator classe.getName() doesn't extend AbstractElaborator");
    
    }
    
    /**
     * Add elaboration in the list of the Decoder subcomponent
     *
     * @author Pedro Fernandes
     * @param str path to the elaboration
     */
    public void addDecoderListElaborator (String str){
    	Class classe = speload.getElaboratorClass(str);
    	
    	if(AbstractElaborator.class.isAssignableFrom(classe))
    	{
    		subDecoderList.add(classe);
    	}else ElaborationError.elaborationError("The Elaborator classe.getName() doesn't extend AbstractElaborator");
    
    }
    
	/**
	 * Verify if the specific elaboration is contained in the list of the subcomponentSrcArch 
	 *
	 * @author Pedro Fernandes
	 * @param class class that will be verified
	 */
	Boolean checkSrcArchElaboratorList(Object classe)
	{
		if(subSrcArchList.isEmpty())
		{
			return true;
		}else
		{
			for(Class<?> classOfList : subSrcArchList )
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
	 * Verify if the specific elaboration is contained in the list of the subcomponentSrcEnv 
	 *
	 * @author Pedro Fernandes
	 * @param class class that will be verified
	 */
	Boolean checkSrcEnvElaboratorList(Object classe)
	{
		if(subSrcEnvList.isEmpty())
		{
			return true;
		}else
		{
			for(Class<?> classOfList : subSrcEnvList )
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
	 * Verify if the specific elaboration is contained in the list of the subcomponentDecoder 
	 *
	 * @author Pedro Fernandes
	 * @param class class that will be verified
	 */
	Boolean checkDecoderElaboratorList(Object classe)
	{
		if(subDecoderList.isEmpty())
		{
			return true;
		}else
		{
			for(Class<?> classOfList : subDecoderList )
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
		if(getElaborator(target.get_srcArch()) != null)
		{
			if(checkSrcArchElaboratorList(getElaborator(target.get_srcArch())))
			{
				getElaborator(target.get_srcArch()).Elaborate();// Starts Elaborating
			}
			else ElaborationError.elaborationError("The Elaboration srcArch that you specified isn't allowed.");
		
		}else ElaborationError.elaborationError("Missing Elaboration.");	
		
		//Verify if there is an Elaborator for this subcomponent
		if(getElaborator(target.get_srcEnv()) != null)
		{
			if(checkSrcEnvElaboratorList(getElaborator(target.get_srcEnv())))
			{
				getElaborator(target.get_srcEnv()).Elaborate();// Starts Elaborating
			}
			else ElaborationError.elaborationError("The Elaboration srcEnv that you specified isn't allowed.");
		
		}else ElaborationError.elaborationError("Missing Elaboration.");	
		
		//Verify if there is an Elaborator for this subcomponent
		if(getElaborator(target.get_decoder()) != null)
		{
			if(checkDecoderElaboratorList(getElaborator(target.get_decoder())))
			{
				getElaborator(target.get_decoder()).Elaborate();// Starts Elaborating
			}
			else ElaborationError.elaborationError("The Elaboration decoder that you specified isn't allowed.");
		
		}else ElaborationError.elaborationError("Missing Elaboration.");	
		
    }	



}
