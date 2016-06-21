package EL.Elaborations;
import EL.Elaborations.Elaborator;
import java.util.ArrayList;

	public interface I_DMemElaborator extends Elaborator {      	
	    	
		public ArrayList<String> getI_DMemElaboratorHeaderlist();
	   public Object getI_DMemElaboratorReadDataMem();
	   public Object getI_DMemElaboratorWriteDataMem();
	
	}
