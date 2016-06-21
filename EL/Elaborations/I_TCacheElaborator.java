package EL.Elaborations;
import EL.Elaborations.Elaborator;
import java.util.ArrayList;

	public interface I_TCacheElaborator extends Elaborator {      	
	    	
		public ArrayList<String> getI_TCacheElaboratorHeaderlist();
	   public Object getI_TCacheElaboratorAddTag();
	   public Object getI_TCacheElaboratorGetTransAddr();
	   public Object getI_TCacheElaboratorGetLastTransAddr();
	   public Object getI_TCacheElaboratorGetCurrInsAddr();
	   public Object getI_TCacheElaboratorCacheCode();
	
	}
