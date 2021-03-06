/** 
* _Execute is a Java class represention of one of the components
* of the Reference Architecture of TOP_LEVEL.
* <p>
* It extends from the class Component like all other elements of TOP_LEVEL because
* this model follows the Composite design patter and SCA (Service Component Architecture)
* <p>
* In addendum, this class also encapsulates all the configurable properties of the 
* component it represent, as well as all the accessor methods to change its values
*
* <b>NOTE:</b> Code autmatically generated by Elaboration Language
*
* @author ESRG (Embedded Systems Research Group) class of 2015/2016
* @version 1.0 
* @since 02/05/2016
*/

package EL.Components;

import java.util.ArrayList;
import java.util.Arrays;
import EL.ElaborationError;

public class _Execute extends Component 
{
	//-------------------------- NO SUBCOMPONENTS -------------------------//
	
	
	//----------------------------- REFERENCES ----------------------------//
	protected _i_CurrBBExec _r_CurrBBExec;
	protected _i_DMem _r_DMem;
	
	//--------------------------- NO PROPERTIES ---------------------------//


	public _Execute()
	{
		//There are no subcomponents to be initialized.
		
		
		//There are bindings to be done.
	}
	//---------------------------------------------------------------------//
	//--------------------- REFERENCES ACCESSOR METHODS -------------------//
	//---------------------------------------------------------------------//
	/**
	* Getter method for _r_CurrBBExec which type is _i_CurrBBExec
	*
	* @return _r_CurrBBExec (Reference in _Execute)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	public _i_CurrBBExec get_r_CurrBBExec()
	{
		return this._r_CurrBBExec;
	}
	/**
	* Setter method for _r_CurrBBExec which type is _i_CurrBBExec
	*
	* @param _arg (Component to set r_CurrBBExec in _Execute that implements _i_CurrBBExec)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	protected void set_r_CurrBBExec(_i_CurrBBExec _arg)
	{
		this._r_CurrBBExec = _arg;
	}			
	/**
	* Getter method for _r_DMem which type is _i_DMem
	*
	* @return _r_DMem (Reference in _Execute)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	public _i_DMem get_r_DMem()
	{
		return this._r_DMem;
	}
	/**
	* Setter method for _r_DMem which type is _i_DMem
	*
	* @param _arg (Component to set r_DMem in _Execute that implements _i_DMem)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	protected void set_r_DMem(_i_DMem _arg)
	{
		this._r_DMem = _arg;
	}			
	//---------------------------------------------------------------------//
	//----------------- END OF REFERENCES ACCESSOR METHODS ----------------//	
	//---------------------------------------------------------------------//	
	
}	
