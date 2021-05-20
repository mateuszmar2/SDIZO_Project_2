all: run valgrind valgrindleak

run:
	clear
	g++ -o Main Main.cpp Graph.cpp Bellman_Ford.cpp Prim.cpp Dijkstra.cpp
	./Main

valgrind:
	clear
	g++ -g -o Main Main.cpp Graph.cpp Bellman_Ford.cpp Prim.cpp Dijkstra.cpp -Wall
	valgrind --track-origins=yes ./Main

valgrindleak:
	clear
	g++ -g -o Main Main.cpp Graph.cpp Bellman_Ford.cpp Prim.cpp Dijkstra.cpp -Wall
	valgrind --leak-check=full ./Main
