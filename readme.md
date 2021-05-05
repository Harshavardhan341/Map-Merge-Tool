## **Map Merge Tool**

#### Instructions to Run:
	g++ -c mapmerge.cpp
	g++ main.cpp mapmerge.o `pkg-config opencv --cflags --libs`
	./a.out input1.pgm input2.pgm output.pgm
