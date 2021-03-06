/** 
* _Translate is a Java class represention of one of the components
* of the Reference Architecture of TOP_LEVEL.
* <p>
* It extends from the class Component like all other elements of TOP_LEVEL because
* this model follows the Composite design patter and SCA (Service Component Architecture)
* <p>
* It also implements the following services:
* <ul>
* <li>_i_Translate</li>
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

public class _Translate extends Component implements _i_Translate
{
	//-------------------------- NO SUBCOMPONENTS -------------------------//
	
	
	//----------------------------- REFERENCES ----------------------------//
	protected _i_Decode _r_Decode;
	protected _i_TCache _r_TCache;
	
	//--------------------------- NO PROPERTIES ---------------------------//


	public _Translate()
	{
		//There are no subcomponents to be initialized.
		
		
		//There are bindings to be done.
	}
	//---------------------------------------------------------------------//
	//--------------------- REFERENCES ACCESSOR METHODS -------------------//
	//---------------------------------------------------------------------//
	/**
	* Getter method for _r_Decode which type is _i_Decode
	*
	* @return _r_Decode (Reference in _Translate)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	public _i_Decode get_r_Decode()
	{
		return this._r_Decode;
	}
	/**
	* Setter method for _r_Decode which type is _i_Decode
	*
	* @param _arg (Component to set r_Decode in _Translate that implements _i_Decode)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	protected void set_r_Decode(_i_Decode _arg)
	{
		this._r_Decode = _arg;
	}			
	/**
	* Getter method for _r_TCache which type is _i_TCache
	*
	* @return _r_TCache (Reference in _Translate)
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
	* @param _arg (Component to set r_TCache in _Translate that implements _i_TCache)
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
	* Getter method for the component that implements _i_Translate
	*
	* @return this (Component _Translate)
	*
	* <b>NOTE:</b> Code autmatically generated by Elaboration Language
	*/
	public Component get_i_Translate()
	{
		return this;
	}
	
	//---------------------------------------------------------------------//
	//------------------ END OF SERVICES ACCESSOR METHODS -----------------//
	//---------------------------------------------------------------------//
}	
