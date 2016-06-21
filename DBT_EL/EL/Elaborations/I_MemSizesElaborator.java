package EL.Elaborations;
import EL.Elaborations.Elaborator;
import java.util.ArrayList;

	public interface I_MemSizesElaborator extends Elaborator {      	
	    	
		public ArrayList<String> getI_MemSizesElaboratorHeaderlist();
	   public Object getI_MemSizesElaboratorXDataMemSize();
	   public Object getI_MemSizesElaboratorDataMemSize();
	   public Object getI_MemSizesElaboratorMemSize();
	   public Object getI_MemSizesElaboratorHeapSize();
	   public Object getI_MemSizesElaboratorStackSize();
	
	}
