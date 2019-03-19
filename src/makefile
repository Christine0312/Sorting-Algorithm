PP = g++

insertionSort : insertionSort.cpp parser.o
	$(PP) insertionSort.cpp parser.o -o ./../insertionSort

mergeSort : mergeSort.cpp parser.o
	$(PP) mergeSort.cpp parser.o -o ./../mergeSort

heapSort : heapSort.cpp parser.o
	$(PP) heapSort.cpp parser.o -o ./../heapSort

quickSort : quickSort.cpp parser.o
	$(PP) quickSort.cpp parser.o -o ./../quickSort

parser.o : parser.cpp
	$(PP) -c parser.cpp

clean : 
	rm *.o
