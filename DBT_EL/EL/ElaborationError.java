package EL;

import  java.lang.Runtime;
import  java.util.ArrayList;

/**
 * Write a description of class ElaborationError here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class ElaborationError
{
    private static ArrayList<Runnable> exitlist = new ArrayList<Runnable>(); 
    
    final private static void abortElaboration(){
        
       for(Runnable r : exitlist)
            r.run();
              
        Runtime.getRuntime().exit(-1);
    }
    
    final public static void elaborationError(String message){
        System.err.println("Elaboration error: " + message);
        abortElaboration();
    }
    
    final public static void elaborationWarning(String message){
        System.err.println("Elaboration warning: " + message);
    }
    
    final public static void registerAtExit(Runnable atexit){
        //Runtime.getRuntime().addShutdownHook(new Thread(atexit));
        exitlist.add(atexit);
    }
   
}   
