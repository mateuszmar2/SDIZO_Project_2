all: run valgrind valgrindleak

run:
	clear
	g++ -o Main Main.cpp Graph.cpp
	./Main

valgrind:
	clear
	g++ -o Main Main.cpp Graph.cpp -Wall
	valgrind --track-origins=yes ./Main

valgrindleak:
	clear
	g++ -o Main Main.cpp Graph.cpp -Wall
	valgrind --leak-check=full ./Main

