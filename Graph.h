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
public:
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
    void loadGraphFromFile(const char *filename);
    void print();
    void printMatrix();
    void printList();
    void randomStructure(int size, float density);
    void matrixToList();
    // int getStartNode();
};

#endif /* GRAPH_H_ */
