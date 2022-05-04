genCode.o : main.cpp scanner.cpp parser.cpp
	g++ -std=c++11 -g -o genCode main.cpp scanner.cpp parser.cpp