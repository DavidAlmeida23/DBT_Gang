package EL.Elaborations;
import EL.Components.Component;

import EL.ConfigReader.*;

import EL.ElaborationError;

import java.nio.file.*;
import java.nio.charset.*;

import java.util.Hashtable;
import java.util.HashMap;

import java.util.Iterator;
import java.util.Set;
import java.util.ArrayList;
import java.util.Iterator;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.File;
import java.io.InputStream;
import java.io.FileInputStream;
import java.io.OutputStream;
import java.io.FileOutputStream;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

import java.io.*;


public abstract class AbstractElaborator implements Elaborator
{
    static String targetpath = "EL" + String.valueOf(File.separator) + "FinalFiles" + String.valueOf(File.separator);
    String anotatedpath = "";
    static String sharedpath = "";
    static Hashtable<Component, AbstractElaborator> compElabTable = new Hashtable<Component, AbstractElaborator>();
    static Hashtable<String,FileDefs> hFileNameAnnotation = new Hashtable<String,FileDefs>();
    static Hashtable<String,String> binaryFiles = new Hashtable<String,String>();
    ArrayList<File> SourceFileList = new ArrayList<File>();
    
    SpecificConfigReader specReader = null;
        
    /**
     * Class that contains all file definitions related to the annotated source file (e.g. annotations).
     * @author Nicolas Almeida
     */
    private class FileDefs
    {
        int hashCode;
        String targetpath;
        String targetname;
        String delimiter;
        HashMap<String,ArrayList<String>> annotationMap;
    }
	
	/**
	 * AbstractElaborator constructor.
	 * @author Nicolas Almeida
	 */
    public AbstractElaborator()
    {
        String temp = getClass().getCanonicalName(); 
		temp = temp.substring(0, temp.lastIndexOf("."));
 		temp = temp.replace(".", String.valueOf(File.separator))+String.valueOf(File.separator);
 		setAnotatedPath(temp);
 		setSharedAnotatedPath("SpecificElaborations" + String.valueOf(File.separator) + "SharedSources" + String.valueOf(File.separator));
    }
    
    public void setSpecificReader(SpecificConfigReader specificReader)
    {
    	specReader = specificReader;
    }
    
    public SpecificConfigReader getSpecificReader()
    {
    	return specReader;
    }
    
    /**
     * Create an association between the reference component and the specific elaborator, creating a pair
     * 
     * @author José Martins 
     * @param component Reference to a component that will be "paired".
     * @param elaborator An elaborator that will be bound to a component.
     */
    public static void addCompElab(Component component, AbstractElaborator elaborator){
        compElabTable.put(component, elaborator);
    }
    
    /**
     * Returns the elaborator associated to a component
     * 
     * @author José Martins 
     * @param component Reference to a component in order to get the associated elaborator.
     */
    public static AbstractElaborator getElaborator(Component component){
        return compElabTable.get(component);
    }

    /**
     * Cast the Component object to the specific component
     *
     * @author José Martins
     * @param comp component object to be casted.
     */
    abstract public void setComponent(Component comp);

    /**
     * Abstract method to be implemented by the derived classes that 
     * generates the component's elaboration and it's subcomponents, recursivelly 
     *
     * @author José Martins
     */
    abstract public void generate();
    
    /**
     * Set path of the target source file
     * 
     * @author José Martins 
     * @param path Tells where the target file is placed.
     */
    public static void setTargetPath(String path){
        targetpath = targetpath + path;
    }
    
    /**
     * Set path of the annotated source file
     * 
     * @author José Martins 
     * @param path Tells where the target file is placed.
     */
    private void setAnotatedPath(String path){
        anotatedpath = path;
    }
    
    /**
     * Set path of the annotated source file
     * 
     * @author Nicolas Almeida
     * @param path Tells where the target file is placed.
     */
    public static void setSharedAnotatedPath(String path){
        sharedpath = "EL" + String.valueOf(File.separator) + path;
    }
    
    /**
     * Get the separator specified by the Language class, within the model.
     * 
     * @author Nicolas Almeida 
     */
    public String getSeparator()
    { 
        return "@";
    }
    
    /**
     * Utility class that copy from one directory to another
     * the directory source contents.
     * 
     * @author Nicolas Almeida
     */
     
    public static void copyFolder(File src, File dest) throws IOException
    {
		if(src.isDirectory())
		{ 
			if(!dest.exists())
			{
				dest.mkdir();
				System.out.println("Directory copied from " + src + "  to " + dest);
			}

			String files[] = src.list();

			for (String file : files) 
			{
			   //construct the src and dest file structure
			   File srcFile = new File(src, file);
			   File destFile = new File(dest, file);
			   //recursive copy
			   copyFolder(srcFile,destFile);
			}

		}
		else
		{
			InputStream in = new FileInputStream(src);
		    OutputStream out = new FileOutputStream(dest); 
		                 
		    byte[] buffer = new byte[1024];

			int length;
			
			while ((length = in.read(buffer)) > 0){
			   out.write(buffer, 0, length);
			}
	
		    in.close();
		    out.close();
		    System.out.println("File copied from " + src + " to " + dest);
		}
	}
    
    /**
     * Open source file annotated and initialize its definitions.
     * 
     * @author Nicolas Almeida 
     * @param source_path Annotated source file path.
     */
    public void openAnnotatedSource(String source_path)
    {
        String line = null;
        FileDefs fileDefs = new FileDefs();
        String filePath = null;
        
        File file = new File(source_path);

		if(file.isAbsolute())
			filePath = source_path;
		else
			filePath = anotatedpath + source_path;
        
        try{
            File fr = new File(filePath); 
            
            if(fr.exists())
            {
                if(hFileNameAnnotation.containsKey(filePath))
                {
                    SourceFileList.add(fr);
                }
                else{
                    SourceFileList.add(fr); 
                    fileDefs.targetpath = null;
                    fileDefs.targetname = fr.getName();
                    fileDefs.hashCode = fr.hashCode();
                    fileDefs.delimiter = getSeparator();
                    fileDefs.annotationMap = new HashMap<String,ArrayList<String>>();
                    hFileNameAnnotation.put(fr.getAbsolutePath(), fileDefs);
                }
            }
            else 
                ElaborationError.elaborationError("File '"+filePath+"' doesn't exist.");
            
        } catch(Exception e) {
            System.err.println("Error opening annotated source!");
        }
    }
    
    /**
     * Open source file annotated, initialize its definitions and associate a target 
     * folder where the final file will be generated.
     *
     * @author Nicolas Almeida 
     * @param source_path Annotated source file path.
     * @param targetPath Path where final file will be generated
     */
    public void openAnnotatedSource(String source_path, String targetPath)
    {
        String line = null;
        FileDefs fileDefs = new FileDefs();
        String filePath = null;
        		        
        File file = new File(source_path);

		if(file.isAbsolute())
			filePath = source_path;
		else
			filePath = anotatedpath + source_path;
        
        try{
            File fr = new File(filePath); 
            
            if(fr.exists())
            {
                if(hFileNameAnnotation.containsKey(filePath))
                {
                    SourceFileList.add(fr);
                }
                else{
                    SourceFileList.add(fr); 
                    fileDefs.targetpath = targetPath;
                    fileDefs.targetname = fr.getName();
                    fileDefs.hashCode = fr.hashCode();
                    fileDefs.delimiter = getSeparator();
                    fileDefs.annotationMap = new HashMap<String,ArrayList<String>>();
                    hFileNameAnnotation.put(fr.getAbsolutePath(), fileDefs);
                }
            }
            else 
                ElaborationError.elaborationError("File '"+filePath+"' doesn't exist.");
            
        } catch(Exception e) {
            System.err.println("Error opening annotated source!");
        }
    }
  
    public void openAnnotatedSource(String source_path, String targetPath, String new_name)
    {
        String line = null;
        FileDefs fileDefs = new FileDefs();
        String filePath = null;
        		        
        File file = new File(source_path);

		if(file.isAbsolute())
			filePath = source_path;
		else
			filePath = anotatedpath + source_path;
        
        try{
            File fr = new File(filePath); 
            
            if(fr.exists())
            {
                if(hFileNameAnnotation.containsKey(filePath))
                {
                    SourceFileList.add(fr);
                }
                else{
                    SourceFileList.add(fr); 
                    fileDefs.targetpath = targetPath;
                    fileDefs.targetname = new_name;
                    fileDefs.hashCode = fr.hashCode();
                    fileDefs.delimiter = getSeparator();
                    fileDefs.annotationMap = new HashMap<String,ArrayList<String>>();
                    hFileNameAnnotation.put(fr.getAbsolutePath(), fileDefs);
                }
            }
            else 
                ElaborationError.elaborationError("File '"+filePath+"' doesn't exist.");
            
        } catch(Exception e) {
            System.err.println("Error opening annotated source!");
        }
    }
    
    /**
     * Open shared source file annotated and initialize its definitions.
     * 
     * @author Nicolas Almeida 
     * @param source_path Annotated shared source file path.
     */
    public void openAnnotatedSharedSource(String source_path)
    {
        String line = null;
        FileDefs fileDefs = new FileDefs();
        String filePath = sharedpath + source_path;
        
        try{
            File fr = new File(filePath); 
            
            if(fr.exists())
            {
                if(hFileNameAnnotation.containsKey(fr.getAbsolutePath()))
                {
                    SourceFileList.add(fr);
                }
                else{
                    SourceFileList.add(fr); 
                    fileDefs.targetpath = null;
                    fileDefs.targetname = fr.getName();
                    fileDefs.hashCode = fr.hashCode();
                    fileDefs.delimiter = getSeparator();
                    fileDefs.annotationMap = new HashMap<String,ArrayList<String>>();
                    hFileNameAnnotation.put(fr.getAbsolutePath(), fileDefs);
                }
            }
            else 
                ElaborationError.elaborationError("File '"+filePath+"' doesn't exist.");
        } catch(Exception e) {
            System.err.println("Error opening annotated source!");
        }
    }
    
    
    
    public void openAnnotatedSharedSource(String source_path, String target_path)
        {
            String line = null;
            FileDefs fileDefs = new FileDefs();
            String filePath = sharedpath + source_path;
            
            try{
                File fr = new File(filePath); 
                
                if(fr.exists())
                {
                    if(hFileNameAnnotation.containsKey(fr.getAbsolutePath()))
                    {
                        SourceFileList.add(fr);
                    }
                    else{
                        SourceFileList.add(fr); 
                        fileDefs.targetpath = target_path;
                        fileDefs.targetname = fr.getName();
                        fileDefs.hashCode = fr.hashCode();
                        fileDefs.delimiter = getSeparator();
                        fileDefs.annotationMap = new HashMap<String,ArrayList<String>>();
                        hFileNameAnnotation.put(fr.getAbsolutePath(), fileDefs);
                    }
                }
                else 
                    ElaborationError.elaborationError("File '"+filePath+"' doesn't exist.");
            } catch(Exception e) {
                System.err.println("Error opening annotated source!");
            }
        }

    public void openAnnotatedSharedSource(String source_path, String target_path, String new_name)
        {
            String line = null;
            FileDefs fileDefs = new FileDefs();
            String filePath = sharedpath + source_path;
            
            try{
                File fr = new File(filePath); 
                
                if(fr.exists())
                {
                    if(hFileNameAnnotation.containsKey(fr.getAbsolutePath()))
                    {
                        SourceFileList.add(fr);
                    }
                    else{
                        SourceFileList.add(fr); 
                        fileDefs.targetpath = target_path;
                        fileDefs.targetname = new_name;
                        fileDefs.hashCode = fr.hashCode();
                        fileDefs.delimiter = getSeparator();
                        fileDefs.annotationMap = new HashMap<String,ArrayList<String>>();
                        hFileNameAnnotation.put(fr.getAbsolutePath(), fileDefs);
                    }
                }
                else 
                    ElaborationError.elaborationError("File '"+filePath+"' doesn't exist.");
            } catch(Exception e) {
                System.err.println("Error opening annotated source!");
            }
        }

    public void createFolder(String path){
    	(new File(targetpath + String.valueOf(File.separator) + path)).mkdirs();		    		    	
    }
    
	public void copyBinaryFile(String source_path){
		binaryFiles.put(anotatedpath +  String.valueOf(File.separator) + source_path, targetpath + String.valueOf(File.separator) + source_path);
	}

	public void copyBinaryFile(String source_path, String target_path){
		binaryFiles.put(anotatedpath +  String.valueOf(File.separator) + source_path, targetpath + String.valueOf(File.separator) + target_path);	    	
	}
    
    /**
     * Add to an HashMap a specific annotation paired with the desired replacement string.
     * 
     * @author Nicolas Almeida 
     * @param anotation String that indentify a specific anotation that must be replaced.
     * @param config String that will replace the annotation in the source file.
     * @param fileName Identifies the replaceable source file whithin the list of annotated source files.
     */
    public void replaceAnotation(String annotation, String config, String fileName){
        
       String line = null;
       FileDefs fileDefs = null; 
       
       if(annotation == null || config == null || fileName == null)
            ElaborationError.elaborationError("Null arguments for annotation.");
        
        try {
            HashMap<String,ArrayList<String>> Hmap = null;
            ArrayList<String> list;
            try{
                if(SourceFileList.contains((new File(anotatedpath+fileName)).getCanonicalPath()))
                {
                    if((fileDefs = hFileNameAnnotation.get(anotatedpath+fileName))!=null)
                    {
                        Hmap = fileDefs.annotationMap;
                        
                        if(Hmap.containsKey(annotation))
                            list = Hmap.get(annotation);
                        else{
                            list = new ArrayList<String>();
                            Hmap.put(annotation,list);
                        }
                        list.add(config);
                    }
                    else
                        ElaborationError.elaborationError("Empty value in hashtable for annotation '"+annotation+"' related to "+anotatedpath+fileName+" file.");
                } 
                else
                     ElaborationError.elaborationError("No file named " + anotatedpath+fileName + ".");
            }
            catch(Exception e){System.err.println("Error replacing annotation: empty value in Hashtable!");}
       }
       catch(NullPointerException e) {
            System.err.println("Error replacing annotation: empty value in Hashtable!");
       }
    }
    
    /**
     * Add to an HashMap a specific annotation paired with the desired replacement string.
     * 
     * @author Nicolas Almeida 
     * @param anotation String that indentify a specific anotation that must be replaced.
     * @param config String that will replace the annotation in the source file.
     */
    public void replaceAnotation(String annotation, String config){
        
       String line = null;
       FileDefs fileDefs = null; 
       
       if(annotation == null || config == null)
            ElaborationError.elaborationError("Null arguments for annotation.");
            
       try {
            HashMap<String,ArrayList<String>> Hmap = null;
            ArrayList<String> list;
            
            for(int i=0; i < SourceFileList.size(); i++)
            {
                try{
                    if((fileDefs = hFileNameAnnotation.get(SourceFileList.get(i).getCanonicalPath()))!=null)
                    {
                        Hmap = fileDefs.annotationMap;
                        if(Hmap.containsKey(annotation)){
                            list = Hmap.get(annotation);
                        }
                        else{
                            list = new ArrayList<String>();
                            Hmap.put(annotation,list);
                        }
                        list.add(config);
                    }
                    else
                        ElaborationError.elaborationError("Empty value in hashtable for annotation '"+annotation+"' related to "+SourceFileList.get(i).getCanonicalPath()+" file.");
                }
                catch(Exception e) {e.printStackTrace();}
            }
       } 
       catch(NullPointerException e) {
            System.err.println("Error replacing annotation: value in Hashtable empty!"); 
       }
    }
    
    /**
     * Add to an HashMap a specific annotation paired with the desired replacement string.
     * 
     * @author Nicolas Almeida 
     * @param anotation String that indentify a specific anotation that must be replaced.
     * @param config Integer that will replace the annotation in the source file.
     * @param fileName Identifies the replaceable source file whithin the list of annotated source files.
     */
    public void replaceAnotation(String annotation, int config, String fileName){        
       replaceAnotation(annotation, String.valueOf(config), fileName);
    }
    
        /**
     * Add to an HashMap a specific annotation paired with the desired replacement string.
     * 
     * @author Nicolas Almeida and Ricardo Teixeira
     * @param anotation String that indentify a specific anotation that must be replaced.
     * @param config Integer that will replace the annotation in the source file.
     */
    public void replaceAnotation(String annotation, int config){
       replaceAnotation(annotation, String.valueOf(config));
    }
    
    /**
     * Generate final files with all annotations replaced and verifies if there are annotations to replace.
     * @author Nicolas Almeida
     */
    public static void generateFinalFiles()
    { 
        String line = null;
        
        try{
            FileDefs fileDefs = null;
            
            Set<String> set = hFileNameAnnotation.keySet();
            Iterator<String> iterator = set.iterator();
            boolean errorFile = false;
            ArrayList<File> generatedFiles = new ArrayList<File>();
            
            while (iterator.hasNext()) {
                String fileName = iterator.next();
                File file = new File(fileName);
                FileReader fr = new FileReader(file);
                BufferedReader br1 = new BufferedReader(fr);
                String targetPath = "";
                String targetDirectory = "";
                String delimiter = null;
                String delimiter_aux = null;
                String listdelimiter = "#";
                String listdelimiter_aux = null;
                
                HashMap<String,ArrayList<String>> aMap = null;
                if((fileDefs = hFileNameAnnotation.get(fileName))==null)
                    ElaborationError.elaborationError("Unable to get annotations related to file '"+targetpath+file.getName()+"'.");
                
                aMap = fileDefs.annotationMap;
                delimiter = fileDefs.delimiter;
                
                // Decompose Delimiter in order to create a Pattern for regex
                delimiter_aux = "";
				for(int i=0; i < (delimiter.length()) ; i++)
				{
					delimiter_aux = delimiter_aux + "[" + delimiter.charAt(i) + "]";
				}		                
                
                // Decompose LIST Delimiter in order to create a Pattern for regex
                listdelimiter_aux = "";
                for(int i=0; i < (listdelimiter.length()) ; i++)
                {
	               	listdelimiter_aux = listdelimiter_aux + "[" + listdelimiter.charAt(i) + "]";
                }
                
                if(fileDefs.targetpath!=null){
                    targetDirectory = targetpath+fileDefs.targetpath+String.valueOf(File.separator);
                    targetPath = targetpath+fileDefs.targetpath+String.valueOf(File.separator)+fileDefs.targetname;
                }
                else {
                    targetDirectory = targetpath;
                    targetPath = targetpath+fileDefs.targetname;
                }
                
                File fileChecker = new File(targetDirectory);
                if(!fileChecker.exists()){
                    fileChecker.mkdirs();
                }
                
                FileOutputStream fos = new FileOutputStream(targetPath);
                
                String aux= null;
                String aux2 = null;
                String pattern = null;
                String patternArray = null;
                String separator = null;
                String pattern_aux_Separator = null;
                String pattern_aux_Initial = null;
                String pattern_aux_Final = null;
                String pattern_aux_Annot = null;
                
                // Regex auxiliar variables 
                String initialChar 		= null;		// Inicial character
                String separatorChar 	= null;		// Separator character
                String finalChar 		= null; 	// Final character
                // Inicial
	                String regexGroup2 		= null; 	// Group which represents the Inicial character
	                String regexGroup3 		= null; 	// Regex Inicial character
                // Separator
	                String regexGroup8 		= null; 	// Group which represents the Separator character
	                String regexGroup10		= null; 	// Regex Separator character
	            // Final
	                String regexGroup11 	= null; 	// Group which represents the Final character
	                String regexGroup13 	= null; 	// Regex Final character
                
               
                //Replace loop
                while ((line = br1.readLine()) != null) {
                    for(HashMap.Entry<String, ArrayList<String>> entry : aMap.entrySet())
                    {
                        pattern = "";
                        
                        // Pattern and Mather for the ArrayList - Multiple Annotation
                        pattern_aux_Initial = "(.*?)" + "("+listdelimiter+")";
                        pattern_aux_Separator = "("+listdelimiter+")" + "(.*?)";
                        pattern_aux_Final = "("+listdelimiter+")" + "(.*?)";
                        pattern_aux_Annot = "("+entry.getKey()+")";
                        		                        
                        // Pattern and Mather for the ArrayList - Multiple Annotation
                        patternArray = "("+delimiter_aux+")" + 
                        					"(" + pattern_aux_Initial + ")?" +
                        					"([ ])*" + 
                        					pattern_aux_Annot +
                        					"([ ])*" +
	                        				"(" + pattern_aux_Separator + ")" +
	                        				"(" + pattern_aux_Final + ")?" +
                        				"("+delimiter_aux+")";		                        
                        
                        Pattern pArray = Pattern.compile(patternArray);
                        Matcher mArray = pArray.matcher(line);
                        
                        if(mArray.find())
                        {
                            if (line.contains(entry.getKey()))
                            {
	                          	regexGroup2 = mArray.group(2);
	                           	regexGroup3 = mArray.group(3);
	                           	regexGroup8 = mArray.group(8);
	                           	regexGroup10 = mArray.group(10);
	                           	regexGroup11 = mArray.group(11);
	                           	regexGroup13 = mArray.group(13);	
	                           	                            	
	                           	// Verify if Initial character exists
	                           	if(regexGroup2 != null && regexGroup3 != null) 
	                           	{
	                           		if (regexGroup3.length() == 0) initialChar = "";
	                           		else initialChar = regexGroup3;
	                           	}
		                        else { initialChar = ""; }
		                            
	                           	// Verify if Separator character exists
	                           	if(regexGroup8 != null && regexGroup10 != null) 
	                           	{
	                           		if (regexGroup10.length() == 0) separatorChar = "\n";
	                           		else separatorChar = regexGroup10;
	                           	}
		                        else { separatorChar = "\n"; }
		                        
	                           	// Verify if Final character exists
	                           	if(regexGroup11 != null && regexGroup13 != null) 
	                           	{
	                           		if (regexGroup13.length() == 0) finalChar = "\n";
	                           		else finalChar = regexGroup13;
	                           	}
		                        else { finalChar = "\n"; }				                        				                            
                            	
                                ArrayList<String> list = entry.getValue();     
                                aux = "";
                                for(int i=0;i<list.size();i++)
                                {
		                            aux2 = list.get(i);
		                            if (i == 0) aux += initialChar + aux2;
		                            else if(i == (list.size() - 1) ) aux += separatorChar + aux2 + finalChar;
		                            else if(i != (list.size() - 1) && i != 0) aux += separatorChar + aux2;
		                            
                                }
                                line = mArray.replaceAll(aux);
                            }
                        }
                        else if(line.contains(entry.getKey()))
                        {
                        	// Pattern and Mather for the Array - Single Annotation
                            pattern = "(" + delimiter_aux + ")" + "([ ])*" + "(" + entry.getKey() + ")" + "([ ])*" + "(" + delimiter_aux + ")";
                            ArrayList<String> list = entry.getValue();
                            Pattern pttern = Pattern.compile(pattern);
                            Matcher match = pttern.matcher(line);
                            line = match.replaceAll(list.get(0));
                        } 
                    }
                    line+="\n";
                    fos.write(line.getBytes());
                }
                br1.close();
                fr.close();
                fos.close();
                
                //Verification loop
                File fileVerification = new File(targetPath);
                generatedFiles.add(fileVerification);
                FileReader frVerification = new FileReader(fileVerification);
                BufferedReader brVerification = new BufferedReader(frVerification);
                String errorLine=null;
                
                int lineNumber=0;
                
                String rewriteText = "";
                boolean rewriteFile = false;
                line = null;
                
                while (((line = brVerification.readLine()) != null)&& errorFile!=true) {
                    for(HashMap.Entry<String, ArrayList<String>> entry2 : aMap.entrySet())
                    {
                        if(line.contains(delimiter) && !entry2.getKey().contains(listdelimiter))
                        {
                            errorFile = true;
                            errorLine = line;
                            break;
                        }
                        else if(line.contains(entry2.getKey()) && entry2.getKey().contains(listdelimiter))
                        {
                            rewriteFile=true;
                            line = line.replace(entry2.getKey(),"");                          
                        }
                    }
                    rewriteText = rewriteText + line + "\n";
                    lineNumber++;
                } 
                
                if(rewriteFile){
                    brVerification.close();
                    frVerification.close();
                    FileOutputStream fosVerification = new FileOutputStream(targetPath);
                    fosVerification.write(rewriteText.getBytes());
                    fosVerification.close();
                    rewriteFile = false;
                }   
                else{
                    brVerification.close();
                    frVerification.close();
                }
                
                if(errorFile)
                {
                    brVerification.close();
                    frVerification.close();
                    
                    for(int i=0; i<generatedFiles.size(); i++){
                       generatedFiles.get(i).delete();
                    }
                       
                    ElaborationError.elaborationError("Fail to generate final files. File "+fileName+" with error at line "+String.valueOf(lineNumber)+":'"+errorLine+"'. All files deleted!");
                    return;
                }
            }
            if(!errorFile)
               System.out.println("All final files successfully generated!");

        }
        catch (Exception e) {
        	e.printStackTrace();
            ElaborationError.elaborationError("Error generating final file: Unresolved annotations!");		            
        }
        
        FileInputStream fis = null;
        FileOutputStream fos = null;
        
		for(String sourceFile : binaryFiles.keySet()){

			String destFile = binaryFiles.get(sourceFile);
			
			File inputfile = new File(sourceFile);
			File outputfile = new File(destFile);
			outputfile.mkdirs();
			outputfile = new File(outputfile.getAbsolutePath() +  String.valueOf(File.separator) + inputfile.getName());
        	
		try {
				fis = new FileInputStream(inputfile);
				fos = new FileOutputStream(outputfile);
		
				byte[]buffer = new byte[1024];
				int noOfBytes = 0;
		
				while ((noOfBytes = fis.read(buffer)) != -1) {
					fos.write(buffer, 0, noOfBytes);
				}
			} catch (FileNotFoundException e) {
					ElaborationError.elaborationError("File not found: " + e);
				} catch (IOException ioe) {
					ElaborationError.elaborationError("Exception while copying file " + ioe);
				} finally {
					// close the streams using close method
					try {
						if (fis != null) {
							fis.close();
						}
						if (fos != null) {
							fos.close();
						}
			} catch (IOException ioe) {
				ElaborationError.elaborationError("Error while closing stream: " + ioe);
			}
		}
		}
        
    }
}
