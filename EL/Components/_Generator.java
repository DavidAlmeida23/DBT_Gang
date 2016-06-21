/** 
* _Generator is a Java class represention of one of the components
* of the Reference Architecture of TOP_LEVEL.
* <p>
* It extends from the class Component like all other elements of TOP_LEVEL because
* this model follows the Composite design patter and SCA (Service Component Architecture)
* <p>
* It also implements the following services:
* <ul>
* <li>_i_Generate</li>
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

public class _Generator extends Component implements _i_Generate
{
	//-------------------------- NO SUBCOMPONENTS -------------------------//
	
	
	//----------------------------- REFERENCES ----------------------------//
	protected _i_Registers _r_SrcRegisters;
	protected _i_Registers _r_TrgRegisters;
	protected _i_PCAccessors _r_PCAccessors;
	protected _i_ISA _r_ISA;
	protected _i_TCache _r_TCache;
	
	//----------------------------- PROPERTIES ----------------------------//
	private boolean _optmizations;

	public _Generator()
	{
		//There are no subcomponents to be initialized.
		
		
		//There are bindings to be done.
	}
	//---------------------------------------------------------------------//
	//-------------------- PROPERTIES ACCESSOR METHODS --------------------//
	//---------------------------------------------------------------------//
	/**
	* Getter method for _optmizations
	*
	* @return _optmizations (Property in _Generator)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/			
	public boolean get_optmizations()
	{
		return this._optmizations;
	}						
		
	/**
	* Setter method for _optmizations taking the restriction associated to _optmizations 
	* into account.
	*
	* @param _arg (Value to set _optmizations in _Generator)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	protected void set_optmizations(boolean _arg)
	{
		this._optmizations = _arg;
	}
	
	/**
	* Setter method for _optmizations with no restrictions and no parameters.
	* Asserting the value of _optmizations to its default value.
	*
	* @param null 
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	protected void set_optmizations()
	{
		this._optmizations = false;
		ElaborationError.elaborationWarning("Assigning to _optmizations its default value.");
	}
	//---------------------------------------------------------------------//
	//----------------- END OF PROPERTIES ACCESSOR METHODS ----------------//
	//---------------------------------------------------------------------//
	
	//---------------------------------------------------------------------//
	//--------------------- REFERENCES ACCESSOR METHODS -------------------//
	//---------------------------------------------------------------------//
	/**
	* Getter method for _r_SrcRegisters which type is _i_Registers
	*
	* @return _r_SrcRegisters (Reference in _Generator)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	public _i_Registers get_r_SrcRegisters()
	{
		return this._r_SrcRegisters;
	}
	/**
	* Setter method for _r_SrcRegisters which type is _i_Registers
	*
	* @param _arg (Component to set r_SrcRegisters in _Generator that implements _i_Registers)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	protected void set_r_SrcRegisters(_i_Registers _arg)
	{
		this._r_SrcRegisters = _arg;
	}			
	/**
	* Getter method for _r_TrgRegisters which type is _i_Registers
	*
	* @return _r_TrgRegisters (Reference in _Generator)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	public _i_Registers get_r_TrgRegisters()
	{
		return this._r_TrgRegisters;
	}
	/**
	* Setter method for _r_TrgRegisters which type is _i_Registers
	*
	* @param _arg (Component to set r_TrgRegisters in _Generator that implements _i_Registers)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	protected void set_r_TrgRegisters(_i_Registers _arg)
	{
		this._r_TrgRegisters = _arg;
	}			
	/**
	* Getter method for _r_PCAccessors which type is _i_PCAccessors
	*
	* @return _r_PCAccessors (Reference in _Generator)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	public _i_PCAccessors get_r_PCAccessors()
	{
		return this._r_PCAccessors;
	}
	/**
	* Setter method for _r_PCAccessors which type is _i_PCAccessors
	*
	* @param _arg (Component to set r_PCAccessors in _Generator that implements _i_PCAccessors)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	protected void set_r_PCAccessors(_i_PCAccessors _arg)
	{
		this._r_PCAccessors = _arg;
	}			
	/**
	* Getter method for _r_ISA which type is _i_ISA
	*
	* @return _r_ISA (Reference in _Generator)
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
	* @param _arg (Component to set r_ISA in _Generator that implements _i_ISA)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	protected void set_r_ISA(_i_ISA _arg)
	{
		this._r_ISA = _arg;
	}			
	/**
	* Getter method for _r_TCache which type is _i_TCache
	*
	* @return _r_TCache (Reference in _Generator)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	public _i_TCache get_r_TCache()
	{
		return this._r_TCache;
	}
	/**
	* Setter method for _r_TCache which type is _i_TCache
	*
	* @param _arg (Component to set r_TCache in _Generator that implements _i_TCache)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	protected void set_r_TCache(_i_TCache _arg)
	{
		this._r_TCache = _arg;
	}			
	//---------------------------------------------------------------------//
	//----------------- END OF REFERENCES ACCESSOR METHODS ----------------//	
	//---------------------------------------------------------------------//	
	
	//---------------------------------------------------------------------//
	//--------------------- SERVICES ACCESSOR METHODS ---------------------//
	//---------------------------------------------------------------------//
	/**
	* Getter method for the component that implements _i_Generate
	*
	* @return this (Component _Generator)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	public Component get_i_Generate()
	{
		return this;
	}
	
	//---------------------------------------------------------------------//
	//------------------ END OF SERVICES ACCESSOR METHODS -----------------//
	//---------------------------------------------------------------------//
}	
