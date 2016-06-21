package EL.Components;

import java.io.IOException;
import EL.ConfigReader.*;
import EL.Loader.SpecificLoader;
import EL.Components.*;
import EL.Elaborations.*;
import EL.ElaborationError;
import javax.xml.parsers.ParserConfigurationException;
import java.util.ArrayList; //TODO import it only when needed

import org.xml.sax.SAXException;
	
public class ELGenerator
{
	private ConfigReader proc;
	private SpecificLoader SpecLoad;
	
	public ELGenerator(){
		Object obj, objElab;
		String ElabName;
		SpecLoad = new SpecificLoader("");
		
		//Open XML parser object
		try {
			proc = new ConfigReader("","");
		} catch (ParserConfigurationException e) {
			// TODO Auto-generated catch block
			System.err.println(e.getMessage());
			return;
		}
		//Initialize top level component
		_DBT __DBT = new _DBT();
		
		//================== DEPENDENCIES GRAPH ==================
		//Non-dependent properties
		obj = proc.getProperty("DBT.trgCluster.gen","optmizations");
		if(obj==null) __DBT._trgCluster._gen.set_optmizations(); //Set default or throw error
		else __DBT._trgCluster._gen.set_optmizations((boolean) obj);
		obj = proc.getProperty("DBT.cCache","CCache_Size");
		if(obj==null) __DBT._cCache.set_CCache_Size(); //Set default or throw error
		else __DBT._cCache.set_CCache_Size((int) obj);
		obj = proc.getProperty("DBT.tCache","TCache_Size");
		if(obj==null) __DBT._tCache.set_TCache_Size(); //Set default or throw error
		else __DBT._tCache.set_TCache_Size((int) obj);
		obj = proc.getProperty("DBT.tCache","numberOfTradutions");
		if(obj==null) __DBT._tCache.set_numberOfTradutions(); //Set default or throw error
		else __DBT._tCache.set_numberOfTradutions((int) obj);
		

		Object topElab;
		//Generate Elaborators Table
		topElab = SpecLoad.LoadElaborator(proc.getElabName("DBT"));
		((AbstractElaborator)topElab).setComponent(__DBT);
		((AbstractElaborator)topElab).setSpecificReader(proc.getSpecificConfigReader("DBT"));
		
		int size = 0;
		
		if(topElab instanceof AbstractElaborator && topElab instanceof AbstractDBTElaborator){
			//If everything ok with the Top Level Elaboration
			((AbstractElaborator)topElab).addCompElab(__DBT, (AbstractElaborator)topElab);
			topElab = AddToElabCompTable((AbstractElaborator)topElab, "DBT.srcCluster", "SourceCluster", __DBT._srcCluster, AbstractSourceClusterElaborator.class);
			topElab = AddToElabCompTable((AbstractElaborator)topElab, "DBT.srcCluster.decoder", "Decoder", __DBT._srcCluster._decoder, AbstractDecoderElaborator.class);
			topElab = AddToElabCompTable((AbstractElaborator)topElab, "DBT.srcCluster.srcArch", "Architecture", __DBT._srcCluster._srcArch, AbstractArchitectureElaborator.class);
			topElab = AddToElabCompTable((AbstractElaborator)topElab, "DBT.srcCluster.srcEnv", "SourceEnv", __DBT._srcCluster._srcEnv, AbstractSourceEnvElaborator.class);
			topElab = AddToElabCompTable((AbstractElaborator)topElab, "DBT.srcCluster.srcEnv.dataMem", "DataMemory", __DBT._srcCluster._srcEnv._dataMem, AbstractDataMemoryElaborator.class);
			topElab = AddToElabCompTable((AbstractElaborator)topElab, "DBT.trgCluster", "TargetCluster", __DBT._trgCluster, AbstractTargetClusterElaborator.class);
			topElab = AddToElabCompTable((AbstractElaborator)topElab, "DBT.trgCluster.target", "Architecture", __DBT._trgCluster._target, AbstractArchitectureElaborator.class);
			topElab = AddToElabCompTable((AbstractElaborator)topElab, "DBT.trgCluster.gen", "Generator", __DBT._trgCluster._gen, AbstractGeneratorElaborator.class);
			topElab = AddToElabCompTable((AbstractElaborator)topElab, "DBT.cCache", "CodeCache", __DBT._cCache, AbstractCodeCacheElaborator.class);
			topElab = AddToElabCompTable((AbstractElaborator)topElab, "DBT.tCache", "TranslationCache", __DBT._tCache, AbstractTranslationCacheElaborator.class);
			topElab = AddToElabCompTable((AbstractElaborator)topElab, "DBT.dbtEngine", "DBTEngine", __DBT._dbtEngine, AbstractDBTEngineElaborator.class);
			topElab = AddToElabCompTable((AbstractElaborator)topElab, "DBT.dbtEngine.translate", "Translate", __DBT._dbtEngine._translate, AbstractTranslateElaborator.class);
			topElab = AddToElabCompTable((AbstractElaborator)topElab, "DBT.dbtEngine.execute", "Execute", __DBT._dbtEngine._execute, AbstractExecuteElaborator.class);
		}
		else { 
			ElaborationError.elaborationError("The elaboration specified for the component DBT is not valid!");
		}
		((AbstractElaborator)topElab).Elaborate();
	}
	
	private Object AddToElabCompTable(AbstractElaborator top, String xmlUrl, String pathUrl, Component comp, Class absElabCompType){
		Object tempObj;
		
		tempObj = SpecLoad.LoadElaborator(proc.getElabName(xmlUrl));
		((AbstractElaborator)tempObj).setComponent(comp);
		((AbstractElaborator)tempObj).setSpecificReader(proc.getSpecificConfigReader(xmlUrl));
		if(!(tempObj instanceof AbstractElaborator && absElabCompType.isInstance(tempObj))) ElaborationError.elaborationError("The elaboration specified for the component" + xmlUrl + " is not valid!");
		top.addCompElab(comp, (AbstractElaborator)tempObj);
		
		return top;
	}
}
