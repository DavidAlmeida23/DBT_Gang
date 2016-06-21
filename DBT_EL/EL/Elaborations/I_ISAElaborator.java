package EL.Elaborations;
import EL.Elaborations.Elaborator;
import java.util.ArrayList;

	public interface I_ISAElaborator extends Elaborator {      	
	    	
		public ArrayList<String> getI_ISAElaboratorHeaderlist();
	   public Object getI_ISAElaboratorGetWordSize();
	   public Object getI_ISAElaboratorNBitsOpcode();
	
	}
