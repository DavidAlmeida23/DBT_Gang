/** 
* _TranslationCache is a Java class represention of one of the components
* of the Reference Architecture of TOP_LEVEL.
* <p>
* It extends from the class Component like all other elements of TOP_LEVEL because
* this model follows the Composite design patter and SCA (Service Component Architecture)
* <p>
* It also implements the following services:
* <ul>
* <li>_i_TCache</li>
* </ul>
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

public class _TranslationCache extends Component implements _i_TCache
{
	//-------------------------- NO SUBCOMPONENTS -------------------------//
	
	
	//----------------------------- REFERENCES ----------------------------//
	protected _i_ISA _r_ISA;
	
	//----------------------------- PROPERTIES ----------------------------//
	private int _TCache_Size;
	private int _numberOfTradutions;

	public _TranslationCache()
	{
		//There are no subcomponents to be initialized.
		
		
		//There are bindings to be done.
	}
	//---------------------------------------------------------------------//
	//-------------------- PROPERTIES ACCESSOR METHODS --------------------//
	//---------------------------------------------------------------------//
	/**
	* Getter method for _TCache_Size
	*
	* @return _TCache_Size (Property in _TranslationCache)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/			
	public int get_TCache_Size()
	{
		return this._TCache_Size;
	}						
		
	/**
	* Setter method for _TCache_Size taking the restriction associated to _TCache_Size 
	* into account.
	*
	* @param _arg (Value to set _TCache_Size in _TranslationCache)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	protected void set_TCache_Size(int _arg)
	{
		this._TCache_Size = _arg;
	}
	
	/**
	* Setter method for _TCache_Size with no restrictions and no parameters.
	* Asserting the value of _TCache_Size to its default value.
	*
	* @param null 
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	protected void set_TCache_Size()
	{
		ElaborationError.elaborationError("No value to be assigned to _TCache_Size.");
	}
	/**
	* Getter method for _numberOfTradutions
	*
	* @return _numberOfTradutions (Property in _TranslationCache)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/			
	public int get_numberOfTradutions()
	{
		return this._numberOfTradutions;
	}						
		
	/**
	* Setter method for _numberOfTradutions taking the restriction associated to _numberOfTradutions 
	* into account.
	*
	* @param _arg (Value to set _numberOfTradutions in _TranslationCache)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	protected void set_numberOfTradutions(int _arg)
	{
		this._numberOfTradutions = _arg;
	}
	
	/**
	* Setter method for _numberOfTradutions with no restrictions and no parameters.
	* Asserting the value of _numberOfTradutions to its default value.
	*
	* @param null 
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	protected void set_numberOfTradutions()
	{
		ElaborationError.elaborationError("No value to be assigned to _numberOfTradutions.");
	}
	//---------------------------------------------------------------------//
	//----------------- END OF PROPERTIES ACCESSOR METHODS ----------------//
	//---------------------------------------------------------------------//
	
	//---------------------------------------------------------------------//
	//--------------------- REFERENCES ACCESSOR METHODS -------------------//
	//---------------------------------------------------------------------//
	/**
	* Getter method for _r_ISA which type is _i_ISA
	*
	* @return _r_ISA (Reference in _TranslationCache)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	public _i_ISA get_r_ISA()
	{
		return this._r_ISA;
	}
	/**
	* Setter method for _r_ISA which type is _i_ISA
	*
	* @param _arg (Component to set r_ISA in _TranslationCache that implements _i_ISA)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	protected void set_r_ISA(_i_ISA _arg)
	{
		this._r_ISA = _arg;
	}			
	//---------------------------------------------------------------------//
	//----------------- END OF REFERENCES ACCESSOR METHODS ----------------//	
	//---------------------------------------------------------------------//	
	
	//---------------------------------------------------------------------//
	//--------------------- SERVICES ACCESSOR METHODS ---------------------//
	//---------------------------------------------------------------------//
	/**
	* Getter method for the component that implements _i_TCache
	*
	* @return this (Component _TranslationCache)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	public Component get_i_TCache()
	{
		return this;
	}
	
	//---------------------------------------------------------------------//
	//------------------ END OF SERVICES ACCESSOR METHODS -----------------//
	//---------------------------------------------------------------------//
}	
