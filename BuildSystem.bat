javac ./EL/Components/*.java ./EL/Elaborations/*.java ./EL/ConfigReader/*.java ./EL/Loader/*.java ./EL/*.java
jar cvfe Elaborator.jar EL.ELMain ./EL/Components/*.class ./EL/Elaborations/*.class ./EL/ConfigReader/*.class ./EL/Loader/*.class ./EL/*.class
