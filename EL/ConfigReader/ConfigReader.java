package EL.ConfigReader;
		
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;
		
		public class ConfigReader {
			private static DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
			private static DocumentBuilder builder = null;
		
			// set of info of all components;
			private HashMap<String, ComponentInfo> compInfoMap = null;

			boolean verbose  = false;
		
			String pathDelimeter = "/";
			String componentArchitecturePath = "./EL/Configs/";
			String componenteSpecificConfigPath = "./EL/SpecificElaborations/";
		
			// Initialize Class
			public ConfigReader(String configPath, String specificConfigRootPath) throws ParserConfigurationException {
				if(verbose) System.out.println("ConfigReader: new instance");		
				if (builder == null) { // if there's no builder, build one
					builder = factory.newDocumentBuilder();
				}
		
				compInfoMap = new HashMap<String, ComponentInfo>();

				if(validatePath(configPath)) {
					componentArchitecturePath = configPath;
				}else{
					System.err.println("ConfigReader: Provided configuration root path was invalid. Using " + componentArchitecturePath);
				}
				if(verbose) System.out.println("ConfigReader: Configuration root path is: " + componentArchitecturePath);

				if(validatePath(specificConfigRootPath)){ 
					componenteSpecificConfigPath = specificConfigRootPath;
				}else{
					System.err.println("ConfigReader: Provided specific configuration root path was invalid. Using " + componenteSpecificConfigPath);
				}
				if(verbose) System.out.println("ConfigReader: Specific configuration root path is: " + componenteSpecificConfigPath);
				
				if(verbose) System.out.println("ConfigReader: Reading directory tree");
				readDirectoryTree(componentArchitecturePath, 0);// get current path
			}

			boolean validatePath(String path)
			{
				return path != null && !path.equals("");
			}
		
			// read directory tree so we get all component names, and properties
			private void readDirectoryTree(String configRootPath, int level) {
				File file = new File(configRootPath); // current folder
				File tFile = null; // temporary file to iterate all files
				String filePath = null; // next file path holder

				if (!file.isDirectory()) { // if this file object doesn't represent a
											// folder
					System.err.println("ConfigReader: " + configRootPath + " is not a directory or doesn't exist!");
					return;
				}
		
				String[] names = file.list();// get a list of all files and folders
		
				String compArqName = ""; // hold component architecture name
				String[] folderList; // hold all folders, so we can build the component
										// architecture name: ex Comp.Sub
		
				if (level != 0) {// this folder doesn't represent a component
					folderList = configRootPath.split(pathDelimeter); // split path into
					// folders
					// build component architecture name
					for (int i = level; i > 0; i--) {
						if (i != level) {
							compArqName += '.';
						}
						compArqName += folderList[folderList.length - i];
					}
					try {
						ComponentInfo ci = new ComponentInfo();
						compInfoMap.put(compArqName, ci);
						ci.ArchName = compArqName;
						ci.ElaborationName = null;
						ci.PropertyList = new HashMap<String, Object>();
						if(verbose) System.out.println("ConfigReader: " + compArqName + " - Reading configurations");
						readFields(configRootPath, ci);
						if(verbose) System.out.println("ConfigReader: " + compArqName + " - Properties: " + ci.PropertyList);
						if(verbose) System.out.println("ConfigReader: " + compArqName + " - Specific properties: " + ci.SpecificPropertyList);
						if(verbose) System.out.println("ConfigReader: " + compArqName + " - Done.");
					} catch (SAXException | IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
		
				// iterate over files searching for folders. Folders represent
				// components
				for (String name : names) {
					filePath = configRootPath + name;
		
					tFile = new File(filePath);
					if (tFile.isDirectory()) {
						if(verbose) System.out.println("ConfigReader: Next file path: " + filePath);
						readDirectoryTree(filePath + pathDelimeter, level + 1); // start
																				// the
																				// process
																				// again,
																				// so
																				// increase
																				// level
					}
				}
			}
		
			// read all properties into the table
			// TODO read component properties info based on a component node
			private void readFields(String path, ComponentInfo ci) throws FileNotFoundException, SAXException, IOException {
				String archName = ci.ArchName;
				String compName = getNameFromArchName(archName);
		
				String fileName = path + compName + ".xml";
				if(verbose) System.out.println("ConfigReader: " + ci.ArchName + " - Properties file name: " + fileName);
				File file = new File(fileName); // Open a file
				Document m_Doc = builder.parse(new FileInputStream(file));
		
				// get all elements with tag property
				NodeList comp = m_Doc.getElementsByTagName("component");
				if (comp.getLength() > 1) {
					System.err.println("ConfigReader: " +  ci.ArchName + " - Too many components in configuration file");
					return;
				}
		
				ci.Type = ((Element) comp.item(0)).getAttribute("type");
		
				NodeList fields = comp.item(0).getChildNodes();
		
				Node temp = getNodeOfName(fields, "properties");
				if (temp != null) {
					ci.PropertyList = readProperties(temp.getChildNodes());
				}
				temp = getNodeOfName(fields, "elaboration");
				if (temp != null) {
					Node elab = getNodeOfName(temp.getChildNodes(), "value");
					String elabstr = elab.getTextContent(); 
					if(elabstr != null){
						ci.ElaborationName = elabstr;
					}	
					else {
						elab = getNodeOfName(temp.getChildNodes(), "default");
						ci.ElaborationName = elab.getTextContent(); 
					}
					if(verbose) System.out.println("ConfigReader: " +  ci.ArchName + " - Elaboration name: " + ci.ElaborationName);
				}
		
				//if(verbose) System.out.println("ConfigReader: " +  ci.ArchName + " - Reading specific properties of (type,name) " + ci.Type + "." + ci.getCompName());

				String specificPropFileName = componenteSpecificConfigPath + ci.Type + pathDelimeter + ci.ElaborationName + pathDelimeter + ci.ElaborationName + ".xml";				
				if(verbose) System.out.println("ConfigReader: " +  ci.ArchName + " - Specific properties filename: " + specificPropFileName);			
				
				ci.SpecificPropertyList = readSpecificProperties(specificPropFileName);
			}
		
			private HashMap<String, Object> readSpecificProperties(String fileName) {

				File file = new File(fileName); // Open a file
				Document m_Doc = null;
				if (!file.canRead()) {
					return null;
				}
		
				try {
					m_Doc = builder.parse(new FileInputStream(file));
				} catch (SAXException | IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		
				// get all elements with tag property
				NodeList comp = m_Doc.getElementsByTagName("component");
				if (comp.getLength() > 1) {
					System.err.println("ConfigReader: Too many components");
					return null;
				}
		
				NodeList fields = comp.item(0).getChildNodes();
		
				Node temp = getNodeOfName(fields, "properties");
				if (temp != null) {
					return readProperties(temp.getChildNodes());
				}
		
				return null;
			}
		
			private Node getNodeOfName(NodeList nl, String name) {
				int nNodes = nl.getLength();
				Node n = null;
				for (int i = 0; i < nNodes; i++) { // iterate over all properties
					n = nl.item(i);// current node
					// make sure the node is of type element
					if (n.getNodeType() == Node.ELEMENT_NODE) {
						if (n.getNodeName().equals(name)) {
							return n; // read a property
						}
					}
				}
				return n;
			}
		
			private HashMap<String, Object> readProperties(NodeList props) {
				String name = null; // parameters needed
				Object obj = null; // returned object
				Element prop = null;
				int size = props.getLength();
				HashMap<String, Object> list = new HashMap<String, Object>();
		
				for (int i = 0; i < size; i++) {
					if (props.item(i).getNodeType() == Node.ELEMENT_NODE) {
						prop = (Element) props.item(i);
						// read the necessary fields
						name = prop.getAttribute("name");
						obj = getObjectFromProperty(prop);
						//if(verbose) System.out.println("ConfigReader: Property: " + name + " = " + obj);
						list.put(name, obj); // put property into
												// component
					}
				}
				return list;
			}
		
			private Object getObjectFromProperty(Element prop) {
				String type, subtype = null;
				type = prop.getAttribute("type");
				String defaultValue = prop.getAttribute("default");
				NodeList nl = getNodeOfName((NodeList)prop.getChildNodes(), "value").getChildNodes();

				if (type.equals("array")) {
					if(verbose) System.out.println("ConfigReader: Array!");
					subtype = prop.getAttribute("subtype");
				
					Node n = null;
					int size = nl.getLength();
					ArrayList<Object> list = new ArrayList<Object>();
					for (int i = 0; i < size; i++) {
						n = nl.item(i);
						if (n.getNodeType() == Node.ELEMENT_NODE) {
							// if (elementCounter > maxElements) {
							// System.err.println("Too many elements on array");
							// }
							// System.out.println("Element: " + elementCounter + " - " +
							// n.getTextContent());
							list.add(stringToType(n.getTextContent(), subtype));
							//elementCounter++;
						}
					}
					return list;
				} else {
					Node n = getNodeOfName(nl, "element");
					String value = ((Element)n).getTextContent();
					if(!(value.equals("")))
						return stringToType(value, type);					
					else
						return stringToType(prop.getAttribute("default"), type);
				}
			}
		
			private Node getDefaultValueNode(Element e) {
				NodeList nl = e.getChildNodes();
				int size = nl.getLength();
				Node n = null;
				int i = 0;
				while (i < size) {
					if (nl.item(i).getNodeType() == Node.ELEMENT_NODE) {
						n = (Element) nl.item(i);
						if (n.getNodeName().equals("defaultValue")) {
							return n;
						}
					}
					i++;
				}
				return null;
			}

			Integer getInteger(String str)
			{
				if(str.length() > 1)
				{
					if(str.charAt(0) == '0')
					{
						if(str.charAt(1) == 'x' || str.charAt(1) == 'X'){
							return Integer.valueOf(str.substring(2), 16);
						}
						else{
							return Integer.valueOf(str.substring(1), 8);
						}
					}
					else if(str.charAt(0) == 'b')
					{
						return Integer.valueOf(str.substring(1), 2);
					}
				}
				
				return Integer.valueOf(str);
			}		

			// Cast value to the right type
			private Object stringToType(String val, String type) {
				Object obj = null;
				if (val.equals(""))
					return null;
				switch (type) {
				case "int":
					obj = getInteger(val.trim());
					break;
				case "float":
					obj = Float.valueOf(val.trim());
					break;
				case "string":
					obj = val;
					break;
				case "bool":
					obj = Boolean.valueOf(val.trim());
					break;
				default:
					System.err.println("ConfigReader: Unrecognized type '" + type + "'");
				}
				return obj;
			}
		
			// Create and return the appropriate reader
			public SpecificConfigReader getSpecificConfigReader(String compArchName) {
				ComponentInfo props = compInfoMap.get(compArchName);	
				if(props != null)
					return new SpecificConfigReader(props.SpecificPropertyList);
				else{
					System.err.println("ConfigReader: Error finding specific properties for component '" + compArchName +"' - Component not found");
					return null;
				}
			}
		
			// Get the name of the Elaboration class
			public String getElabName(String archName) {

				if(compInfoMap.get(archName) == null){
					return null;
				}
				//if(verbose) System.out.println("ConfigReader: Get Elab Name returns: " + compInfoMap.get(archName).getFullElabName());		
				return compInfoMap.get(archName).getFullElabName();
			}
		
			// Get a components name based on it's architectural name
			public String getNameFromArchName(String archName) {
				String[] arqNameSplitd = archName.split("\\."); // Match the '.'
																// caracter
				int len = arqNameSplitd.length;
				return arqNameSplitd[len - 1];
			}
		
			public Object getProperty(String compArchName, String property) {
				//if(verbose) System.out.println("ConfigReader: Getting " + stringsPosetion(compArchName) + " " + property + ": " + compInfoMap.get(compArchName).PropertyList.get(property));
				return compInfoMap.get(compArchName).PropertyList.get(property);
			}

			String stringsPosetion(String owner)
			{
				char lastChar = owner.charAt(owner.length() - 1);
				return owner + ((( lastChar == 's' || lastChar == 'S')) ? "'" : "'s");
			}
		
			/* TODO get array size: "compname#" + index */
			public int getArrayListSize(String compArrayArchName) {
				int size = 0;
				
				  if(verbose) System.out.println("ConfigReader: getArrayListSize started"); do{
				  System.out.println("ConfigReader: Checking: " + compArrayArchName + "#" +
				  Integer.valueOf(size)); } //
				 
				while (compInfoMap.containsKey(compArrayArchName + "#" + Integer.valueOf(size++)))
					;
				
				System.out.println("ConfigReader: Component list is of size: " + size); 
				return size - 1;
			}
		}
		
		class ComponentInfo {
			String ArchName; // Component name in the reference architecture
			String Type;
			String ElaborationName; // Elaboration name
			HashMap<String, Object> PropertyList; // List of component properties
			HashMap<String, Object> SpecificPropertyList;
		
			public String getCompName() {
				String str[] = ArchName.split("\\.");
				int len = str.length;
		
				if (len == 1)
					return ArchName;
		
				return str[len - 1];
			}
		
			public String getFullElabName() {
				return Type + "." + ElaborationName;
			}
		}	
