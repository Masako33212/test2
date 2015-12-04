#Makefile
#This creates executables for python cpp and java , to create only one language use #'make cpp' or 'make python' or 'make java'
 
.PHONY: all cpp java python clean
 
all: cpp java python
 
cpp:    add_part_cpp    list_parts_cpp
java:   add_part_java   list_parts_java
python: add_part_python list_parts_python
 
clean:
	rm -f add_part_cpp list_parts_cpp add_part_java list_parts_java add_part_python list_parts_python
	rm -f javac_middleman AddPart*.class ListParts*.class com/example/tutorial/*.class
	rm -f protoc_middleman partbook.pb.cc partbook.pb.h partbook.pb2.py com/example/tutorial/PartBookProtos.java
	rm -f *.pyc
	rmdir com/example/tutorial 2>/dev/null || true
	rmdir com/example 2>/dev/null || true
	rmdir com 2>/dev/null || true
 
protoc_middleman: partbook.proto
	protoc --cpp_out=. --java_out=. --python_out=. partbook.proto
	@touch protoc_middleman
 
add_part_cpp: add_part.cc protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ add_part.cc partbook.pb.cc -o add_part_cpp `pkg-config --cflags --libs protobuf`
 
list_parts_cpp: list_parts.cc protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ list_parts.cc partbook.pb.cc -o list_parts_cpp `pkg-config --cflags --libs protobuf`
 
javac_middleman: AddPart.java ListParts.java protoc_middleman
	javac AddPart.java ListParts.java com/example/tutorial/PartBookProtos.java
	@touch javac_middleman
 
add_part_java: javac_middleman
	@echo "Writing shortcut script add_part_java..."
	@echo '#! /bin/sh' > add_part_java
	@echo 'java -classpath .:$$CLASSPATH AddPart "$$@"' >> add_part_java
	@chmod +x add_part_java
 
list_parts_java: javac_middleman
	@echo "Writing shortcut script list_parts_java..."
	@echo '#! /bin/sh' > list_parts_java
	@echo 'java -classpath .:$$CLASSPATH ListParts "$$@"' >> list_parts_java
	@chmod +x list_parts_java
 
add_part_python: add_part.py protoc_middleman
	@echo "Writing shortcut script add_part_python..."
	@echo '#! /bin/sh' > add_part_python
	@echo './add_part.py "$$@"' >> add_part_python
	@chmod +x add_part_python
 
list_parts_python: list_parts.py protoc_middleman
	@echo "Writing shortcut script list_parts_python..."
	@echo '#! /bin/sh' > list_parts_python
	@echo './list_parts.py "$$@"' >> list_parts_python
	@chmod +x list_parts_python
 