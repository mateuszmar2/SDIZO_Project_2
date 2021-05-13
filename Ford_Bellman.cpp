#include <iostream>
#include <climits> // do INT_MAX
#include "Ford_Bellman.h"
#include "Graph.h"

using namespace std;

void fordBellmanMatrix(Graph graph)
{
    // wagi ujemne
    int *distance = new int[graph.size_nodes]; // tablica na koszt dojścia do elementu
    int *prev = new int[graph.size_nodes];     // tablica na poprzedniki

    for (int i = 0; i < graph.size_nodes; i++)
    {
        distance[i] = INT_MAX; // maksymalne wartości
        prev[i] = -1;          // -1 oznacza brak poprzednika
    }
    distance[graph.start_node] = 0; //koszt dojścia do wierzchołka startowego
    bool change = false;            // zmienna przechowująca informacje o zmianach
    // pętla główna
    for (int i = 1; i < graph.size_nodes; i++)
    {
        change = true;
        for (int j = 0; j < graph.size_nodes; j++)
        {
            for (int k = 0; k < graph.size_nodes; k++) // dla każdego sąsiada wierzchołka j
            {
                if (graph.matrix[j][k] != 0 && distance[j] != INT_MAX)
                {
                    if (distance[k] > distance[j] + graph.matrix[j][k]) // warunek relaksacji krawędzi
                    {
                        change = false;                                 // zapamiętanie zmiany
                        distance[k] = distance[j] + graph.matrix[j][k]; // relaksacja
                        prev[k] = j;                                    // zmiana poprzednika
                    }
                }
            }
        }
        if (change)
            break;
    }
    // sprawdzenie czy nie wystąpił cykl ujemny
    for (int i = 0; i < graph.size_nodes; i++)
    {
        for (int j = 0; j < graph.size_nodes; j++)
        {
            if (graph.matrix[i][j] != 0)
            {
                if (distance[j] > distance[i] + graph.matrix[i][j])
                    change = false;
            }
        }
    }
    if (!change)
    {
        cout << "Cykl ujemny" << endl;
        delete[] distance;
        delete[] prev;
        return;
    }
    // wyświetlenie macierzy
    graph.printMatrix();
    // wyświetlany jest numer węzła, długość drogi do niego oraz droga w postaci sekwencji wierzchołków
    cout << endl
         << "Wynik Ford-Bellman Macierz: " << endl;
    cout << "numer wezla : dlugosc -> droga" << endl;

    for (int i = 0; i < graph.size_nodes; i++)
    {
        cout << i << ": " << distance[i] << " -> ";
        for (int j = i; j != -1; j = prev[j])
        {
            cout << j << " ";
        }
        cout << endl;
    }
    delete[] distance;
    delete[] prev;
}

void fordBellmanList(Graph graph)
{
}
