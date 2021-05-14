#ifndef GRAPH_H_
#define GRAPH_H_

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
    int start_node; // wierzchołek początkowy

public:
    Graph();
    ~Graph();
    void deleteStructure();
    void fillZeros();
    void print();
    void printMatrix();
    void printList();
    void randomStructure(int size, float density, int min, int max, bool directed);
    void loadGraphFromFile(const char *filename, bool directed);
    void matrixToList();
};

#endif /* GRAPH_H_ */
