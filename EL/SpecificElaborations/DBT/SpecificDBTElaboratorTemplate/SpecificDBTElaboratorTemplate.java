
/**
*	This is an automatically generated file by the Elaboration Language
*	framework that serves as a template for a DBT concrete 
*	elaborator in the DBT reference architecture.
*/

package EL.SpecificElaborations.DBT.SpecificDBTElaboratorTemplate;  

import EL.Components._DBT;
import EL.Elaborations.AbstractDBTElaborator;
import EL.ElaborationError;
import java.util.ArrayList;
import EL.ConfigReader.SpecificConfigReader;


public class SpecificDBTElaboratorTemplate extends AbstractDBTElaborator {
	
	/**
	*	This function must be implemented in order to obtain a valid elaborator. In it the annotated source
	*	files shall be identified and respective annotations replaced by getting the configured values from 
	* 	the model component being elaborated and accessible via the target attribute.
	*
	*	You can use the following methods:
	*		public void openAnnotatedSource(String source_path)
	*		public void openAnnotatedSource(String source_path, String targetPath) 
	*		public void openAnnotatedSharedSource(String source_path) 
	*		public void replaceAnotation(String annotation, String config)
	*		public void replaceAnotation(String annotation, String config, String targetfile)
	*		public void replaceAnotation(String annotation, int config)
	*		public void replaceAnotation(String annotation, int config, String targetfile)
	*
	*	In order to specify a target folder where the file opened will be generated to, 
	*	is necessary to call the function openAnnotatedSource(String source_path, String targetPath).
	*
	*	Once a source is opened all annotations replaced will target that source,
	*	unless the target file is specified. If the annotation is not present
	*	in the source, it will be ignored.
	*
	*	The String specified as annotation shall be enclosured by @ specified by the
	*	component language, C . In the source file an annotation shall 
	*	appear as @annot@ and replaced by calling 
	*	replaceAnotation("annot", "replace_value").
	*
	*	If one annotation is to be replaced by several values, or a list of values it shall appear
	* 	in the annotated source file as @annot#@ 
	*	and replaced by calling replaceAnotation("annot", "replace_value").
	*
	*	In the most simplistic way, a list of annotations is composed by: 
	*	- An Initial character (by default an empty string)
	*	- A Separator character (by default \n)
	* 	- A Final character (by default \n)
	*
	*	In order to create a list of annotations, the # for the Separator is obligatory.
	*	The # for the initial and the final character are optional. 
	* 	
	*	The following examples are ilustrative of how this mechanism works:
	*	@ #anot# # @	->  anot anot anot anot 
	*	@(#anot#;#)@ 	-> (anot;anot;anot;anot)
	*	@anot#;#)@ 		-> anot;anot;anot;anot)
	*	@(#anot#;@		-> (anot;anot;anot;anot
	*											
	*	@(#anot##)@		-> (anot
	*					   						anot
	*					   						anot
	*					   						anot)
	*
	*	The Initial, Final and Separator characters cannot be equals to @.
	*
	*	If an annotation is not replaced in an opened source the elaboration will fail
	*	and an error will be thrown.
	*
	*	All the annotated sources must be at the same level or below in the directory hiearchy
	*	of the elaborator java file that is that references, unless it is a shared source, and the´
	*	source_path given shall be relative to this directory.
	*
	*	If two elaborators must configure the same source file, the method openAnnotatedSharedSource
	*	must be used and the source file should be in a the EL/SharedSources directory, accessible by
	*	all elaborators.
	*
	*	Other overloaded methods for replace annotations of other types will be 
	* 	added in the future.
	*
	*	In order to use the utility method that perform the copy of a source directory to a specified 
	*	destination directory, is required to create two File objects with a reference to the directory source path 
	* 	and destination path, respectively.
	*	Example:
	*		File srcDir = new File("Source_Directory");
	*		File destDir = new File("Destination_Directory");
	*		
	*		try{
	*			copyFolder(srcDir, destDir);
	*		} catch(IOException DF) {...}
	*
	*
	*
	*	If in some way it seems that something is wrong with the elaboration, is possible to throw an error 
	*	using the ElaborationError API in order to get more details about it.
	*   Can be used calling ElaborationError.elaborationError("MESSAGE") or ElaborationError.elaborationWarning("MESSAGE").
	*
	*/
	
	/*
	* In order to use the specific config reader you should create a file with the name of the 
	* specific elaborator class. To obtain the specfic properties, you should get the instance of the class 
	* SpecficConfigurationReader, by calling "getSpecificReader" like so: "scr = getSpecificReader();".
	* You may then obtain the configured properties by calling "scr.getProperty("<propertie>")". This method returns
	* a Java Object which must then be casted to type specified by the configuration file. For example, if we intend
	* to retrieve a property named "b" of type int, we may achieve it with: "int b = (Integer)scr.getProperty("b")"
	*
	*/
	SpecificConfigReader scr = null;

	public void generate(){
		System.out.println("This is the DBT template specific elaboration.");
	}


	
	
}
