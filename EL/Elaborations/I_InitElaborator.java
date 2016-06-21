package EL.Elaborations;
import EL.Elaborations.Elaborator;
import java.util.ArrayList;

	public interface I_InitElaborator extends Elaborator {      	
	    	
		public ArrayList<String> getI_InitElaboratorHeaderlist();
	   public Object getI_InitElaboratorInitTranslator();
	   public Object getI_InitElaboratorRunDBT();
	
	}
