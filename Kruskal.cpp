#include <iostream>
#include <queue>
#include <vector>

#include "Kruskal.h"
#include "Graph.h"

using namespace std;

void makeSet(int size, int *parent, int *tree_height)
{
    for (int i = 0; i < size; i++)
    {
        parent[i] = i;
        tree_height[i] = 0;
    }
}

int findSet(int x, int *parent)
{
    if (parent[x] != x)
        parent[x] = findSet(parent[x], parent);
    return parent[x];
}

void unionSets(int x, int y, int *parent, int *tree_height)
{
    int a = findSet(x, parent);
    int b = findSet(y, parent);
    if (tree_height[a] < tree_height[b])
        parent[a] = b;
    else
        parent[b] = a;

    if (tree_height[a] == tree_height[b])
        tree_height[a]++;
}

void kruskalMatrix(Graph &graph)
{
    Graph graph_mst; // graf na wynik
    int weight;
    int minimum_cost = 0;
    Edge e;
    int *parent = new int[graph.size_nodes]; // tablica której indeksem jest numer wierzchołka
    int *tree_height = new int[graph.size_nodes];
    graph_mst.makeGraph(graph.size_nodes);
    // kolejka priorytetowa z typem Edge z vectorem jako typem sekwencji bazowej, EdgeComparator jako funkcja do porównywania
    priority_queue<Edge, vector<Edge>, EdgeComparator> Q;
    makeSet(graph.size_nodes, parent, tree_height);
    for (int i = 0; i < graph.size_nodes; i++) // dodanie wszystkich krawędzi do kolejki
    {
        for (int j = 0; j < graph.size_nodes; j++) // dla każdego sąsiada wierzchołka i
        {
            weight = graph.matrix[i][j];
            if (weight != 0)            // jezeli krawędź istnieje
                Q.push({weight, i, j}); // krawędź do kolejki
        }
    }
    while (!Q.empty()) // główna pętla algorytmu
    {
        e = Q.top();
        Q.pop();                                              // pobieraj nową krawędź z kolejki
        if (findSet(e.from, parent) != findSet(e.to, parent)) // jeżeli ta krawędź połączy dwa różne zbiory
        {
            minimum_cost += e.weight;                     // dodaj wagę do sumy kosztu
            unionSets(e.from, e.to, parent, tree_height); // połącz zbiory
            graph_mst.matrix[e.from][e.to] = e.weight;    // utwórz krawędź nieskierowaną w grafie na wynik
            graph_mst.matrix[e.to][e.from] = e.weight;
        }
    }
    delete[] parent;
    delete[] tree_height;
    graph_mst.printMatrix();
    cout << endl
         << "Sum of weights (Kruskal): " << minimum_cost << endl;
}

void kruskalList(Graph &graph)
{
    Graph graph_mst; // graf na wynik
    int minimum_cost = 0;
    Edge e;
    Node *p;
    Node *node;
    int *parent = new int[graph.size_nodes]; // tablica której indeksem jest numer wierzchołka
    int *tree_height = new int[graph.size_nodes];
    graph_mst.makeGraph(graph.size_nodes);
    // kolejka priorytetowa z typem Edge z vectorem jako typem sekwencji bazowej, EdgeComparator jako funkcja do porównywania
    priority_queue<Edge, vector<Edge>, EdgeComparator> Q;
    makeSet(graph.size_nodes, parent, tree_height);
    for (int i = 1; i < graph.size_nodes; i++) // dodanie wszystkich krawędzi do kolejki
    {
        for (p = graph.list[i]; p != NULL; p = p->next)
        {
            Q.push({p->weight, i, p->value}); // krawędź do kolejki
        }
    }
    while (!Q.empty()) // główna pętla algorytmu
    {
        e = Q.top();
        Q.pop();                                              // pobieraj nową krawędź z kolejki
        if (findSet(e.from, parent) != findSet(e.to, parent)) // jeżeli ta krawędź połączy dwa różne zbiory
        {
            minimum_cost += e.weight;                     // dodaj wagę do sumy kosztu
            unionSets(e.from, e.to, parent, tree_height); // połącz zbiory
            // utwórz wierzchołek i dodaj do listy
            node = new Node();
            node->weight = e.weight;
            node->value = e.to;
            node->next = graph_mst.list[e.from];
            graph_mst.list[e.from] = node;
            // nie jest skierowana więc dwa razy
            node = new Node();
            node->weight = e.weight;
            node->value = e.from;
            node->next = graph_mst.list[e.to];
            graph_mst.list[e.to] = node;
        }
    }
    delete[] parent;
    delete[] tree_height;
    graph_mst.printList();
    cout << endl
         << "Sum of weights (Kruskal): " << minimum_cost << endl;
}
