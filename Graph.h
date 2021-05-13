#ifndef GRAPH_H_
#define GRAPH_H_

// struct Edge
// {
//     int to;
//     int weight; // dla skierowanych krawedzi
// };

// class Node
// {
// public:
//     Node *next;
//     Edge edge;
//     Node();
// };

class Graph
{
private:
    int **matrix;
    // Node **list;
    int size_edges; // ilość krawędzi
    int size_nodes; // ilość wierzchołków
    int start_node;

public:
    Graph();
    ~Graph();
    void deleteStructure();
    void fillZeros();
    void Kruskal();
    void Prim();
    void Dijkstra(int start_node);
    void FordBellman(int start_node);
    void FordFulkerson(int start_node, int end_node);
    void loadGraphFromFile(const char *filename);
    void print();
    void print(int **matrixToPrint, int sizeOfNodematrixToPrint);
    void randomStructure(int size, float density);
    void matrixToList();
    int getStartNode();
    void ford_Bellman();
};

#endif /* GRAPH_H_ */
