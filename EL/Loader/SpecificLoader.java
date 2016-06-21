package EL.Loader;
import java.io.File;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;

import javax.tools.JavaCompiler;
import javax.tools.ToolProvider;

import EL.ConfigReader.SpecificConfigReader;

public class SpecificLoader {
	String m_Path = "./EL/SpecificElaborations/";

	boolean verbose = false;

	ClassLoader cl = null;
	// Compile source file.
	JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();

	public SpecificLoader(String path) {
		if(verbose) System.out.println("SpecificLoader: new instance");						

		// m_Path = path;// must end with '/', denoting a folder
		String root = null; 		
		try {
			root = SpecificLoader.class.getProtectionDomain().getCodeSource().getLocation().toURI().getPath();
			//System.out.println(root);

		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
		root = root.substring(0, root.lastIndexOf("/") + 1);
		if(verbose) System.out.println("SpecificLoader: Root dir: " + root);
		String strURL = "file:" + root; 
		
		//*		
		URL url = null;
		try {
			url = new URL(strURL);
		} catch (MalformedURLException e) {
			// TODO Auto-generated catch blocklistl
			e.printStackTrace();
		}
		URL[] urls = new URL[] { url };
		/*/
		URL[] urls = getCurrentFolderFoldersURL(m_Path);		 
		//*/

		cl = new URLClassLoader(urls);
	}

	URL[] getCurrentFolderFoldersURL(String path) {
		File file = new File(path); // current folder

		if (!file.isDirectory()) { // if this file object doesn't represent a
			// folder
			System.err.println("SpecificLoader: " + path + " is not a directory!");
			return null;
		}
		
		String[] names = file.list();// get a list of all files and folders
		File tempFile = null;
		int size = names.length;
		URL[] urls = new URL[size];
		for(int i = 0; i < size; i++){
			tempFile = new File(path + File.separator + names[i]);
			if (tempFile.isDirectory()) { // if this file object doesn't represent a
				try {
					urls[i] = tempFile.toURI().toURL();
				} catch (MalformedURLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
		return urls;
	}

	public Class<?> getElaboratorClass(String CompName) {
		String compName = CompName; //Cannot be the same type because of namespace shadowing
		if(verbose) System.out.println("SpecificLoader: Loading: " + "EL.SpecificElaborations." + compName + ".java");
		compName = compName + compName.substring(compName.lastIndexOf("."));
		compiler.run(null, null, null, m_Path + compName.replace(".", File.separator) + ".java");
		Class<?> clss = null;
		try {
			clss = cl.loadClass("EL.SpecificElaborations." + compName);
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return clss;
	}

	public Object LoadElaborator(String CompName) {
		if(verbose) System.out.println("SpecificLoader: Instanciate elaborator: " + CompName);
		Class<?> clss = getElaboratorClass(CompName);

		Object obj = null;
		try {
			obj = clss.newInstance();
		} catch (InstantiationException | IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return obj;
	}

	public void setConfigReader(Object elab, SpecificConfigReader confReadr) {
		Method setCR = null;
		if(verbose) System.out.println("SpecificLoader: Setting config reador on elaborator: " + elab);
		try {
			setCR = elab.getClass().getMethod("setConfigReader", SpecificConfigReader.class);
		} catch (NoSuchMethodException | SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			setCR.invoke(elab, confReadr);
		} catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	// this method is not calling elaborate, it's calling another method just to
	// test
	public void elaborate(Object elab) {
		Method elaborate = null;
		try {
			elaborate = elab.getClass().getMethod("elaborate", (Class<?>[]) null);
		} catch (NoSuchMethodException | SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return;
		}

		try {
			elaborate.invoke(elab, (Object[]) null);
		} catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
