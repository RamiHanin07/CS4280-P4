frontEnd.o : main.cpp scanner.cpp parser.cpp
	g++ -std=c++11 -g -o frontEnd main.cpp scanner.cpp parser.cpp