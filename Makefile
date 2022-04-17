statSem.o : main.cpp scanner.cpp parser.cpp
	g++ -std=c++11 -g -o statSem main.cpp scanner.cpp parser.cpp