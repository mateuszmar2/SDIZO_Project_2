#define RESET "\033[0m"
#define RED "\033[31m"

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <sstream> // do stringstreama (wczytywanie)
// #include <climits> // do INT_MAX

#include "Graph.h"

using namespace std;

// Node::Node()
// {
// }

Graph::Graph()
{
    this->matrix = NULL;
    // this->list = NULL;
    this->size_edges = 0;
    this->size_nodes = 0;
    this->start_node = 0;
}

Graph::~Graph()
{
    deleteStructure();
}

void Graph::deleteStructure()
{
    // Node *to_delete; // TODO czy nie da się tego łatwiej usunąć tylko przez usuwanie elementów list?
    // Node *temp;      // TODO czy takie usuwanie macierzy jest dobre
    for (int i = 0; i < this->size_nodes; i++)
    {
        delete[] this->matrix[i];
        // temp = list[i];
        // while (temp != NULL)
        // {
        //     to_delete = temp;
        //     temp = temp->next;
        //     delete to_delete;
        // }
    }
    delete[] this->matrix;
    // delete[] this->list;
    this->size_edges = 0;
    this->size_nodes = 0;
}

void Graph::fillZeros()
{
    for (int i = 0; i < size_nodes; i++)
        for (int j = 0; j < size_nodes; j++)
            this->matrix[i][j] = 0;
}

void Graph::print()
{
    printMatrix();
}

void Graph::printMatrix()
{
    // printowanie macierzy
    cout << endl
         << "Matrix" << endl
         << " ";
    for (int i = 0; i < this->size_nodes; i++)
        cout << "   " << RED << i << RESET;
    cout << endl;
    for (int i = 0; i < this->size_nodes; i++)
    {
        cout << RED << i << RESET << "   ";
        for (int j = 0; j < this->size_nodes; j++)
        {
            if (this->matrix[i][j] == 0)
            {
                cout << " "
                     << "   ";
            }
            else
            {
                cout << this->matrix[i][j] << "   ";
            }
        }
        cout << endl;
    }
    // // Printowanie listy sąsiedztwa
    // cout << endl
    //      << "List";
    // Node *p;
    // for (int i = 0; i < size_nodes; i++)
    // {
    //     cout << endl
    //          << RED << i << RESET << " =  ";
    //     p = list[i];
    //     while (p != NULL)
    //     {
    //         cout << "   " << p->value << "[" << p->weight << "]";
    //         p = p->next;
    //     }
    // }
}

void Graph::randomStructure(int size, float density) // TODO min max directed
{
    int max_index = size - 1;
    if (this->size_nodes != 0)
        deleteStructure();
    this->size_nodes = size;
    srand(time(NULL));
    int edges_amount = (size * (size - 1)) / 2 * density; // wyliczamy ilość krawędzi
    if (edges_amount < max_index)                         // jeśli krawędzi jest mniej niż wierzchołków
        edges_amount = max_index;                         // to zwiększamy tak aby połączyć wszystkie

    this->matrix = new int *[size];

    for (int i = 0; i < size; i++) // utworzenie wierszy
        this->matrix[i] = new int[size];

    fillZeros();

    // tablica indeksów wierzchołków
    int *index_table = new int[size];

    int temp, random_index;
    for (int i = 0; i < size; i++)
        index_table[i] = i; // przypisanie wierzchołków

    //mieszanie kolejności w tablicy w celu utworzenia losowych połączeń
    for (int i = 0; i < size; i++)
    {
        random_index = rand() % max_index;
        temp = index_table[i];
        index_table[i] = index_table[random_index];
        index_table[random_index] = temp;
    }

    // Na początku trzeba utworzyć minimalne drzewo rozpinające
    int random_weight;
    for (int i = 0; i < max_index; i++)
    {
        // wagi krawędzi
        random_weight = rand() % 9 + 1; // od 1-9
        //wypełnienie macierzy wagami
        this->matrix[index_table[i]][index_table[i + 1]] = random_weight; // TODO if directed
    }
    // sprawdzenie czy należy dodać więcej krawędzi
    if (density != 0)
    {
        int line, column;
        // dodanie reszty krawędzi
        for (int i = max_index; i < edges_amount * 2; i++)
        {
            random_weight = rand() % 9 + 1; // od 1-9
            while (true)                    // dopóki nie znajdziemy miejsca w którym nie ma krawędzi
            {
                line = rand() % size;
                column = rand() % size;
                if (this->matrix[line][column] == 0 && line != column)
                    break;
            }
            this->matrix[line][column] = random_weight; // TODO if directed
        }
    }
    delete[] index_table;
    this->size_edges = edges_amount;
    // matrixToList();
    print();
}

int *getNumbersFromLine(string line)
{
    stringstream strstr;
    strstr << line;
    string temp;
    int *tab = new int[3];
    int found;
    int i = 0;
    while (!strstr.eof())
    {
        strstr >> temp;
        if (stringstream(temp) >> found)
        {
            tab[i] = found;
            i++;
        }
        temp = "";
    }
    return tab;
}

void Graph::loadGraphFromFile(const char *filename)
{
    string line;
    ifstream file;
    file.open(filename);

    if (!file)
        cout << "File open error" << endl;
    else
    {
        if (this->size_nodes != 0)
            deleteStructure();
        getline(file, line);
        int *line_split = getNumbersFromLine(line);
        this->size_edges = line_split[0];
        this->size_nodes = line_split[1];
        this->start_node = line_split[2];
        delete[] line_split;

        this->matrix = new int *[this->size_nodes];
        for (int i = 0; i < this->size_nodes; i++) // utworzenie wierszy
            this->matrix[i] = new int[this->size_nodes];
        fillZeros();

        int i = 0;
        while (getline(file, line) && i < this->size_edges)
        {
            int *line_split = getNumbersFromLine(line);
            this->matrix[line_split[0]][line_split[1]] = line_split[2]; // TODO if directed
            delete[] line_split;
            i++;
        }
        file.close();
        // matrixToList();
        print();
    }
}

// int Graph::getStartNode()
// {
//     return this->start_node;
// }

void Graph::matrixToList()
{
    for (int i = 0; i < size_nodes; i++)
        for (int j = 0; j < size_nodes; j++)
            this->matrix[i][j] = 0;
}

// void Graph::ford_Bellman()
// {
//     // wagi ujemne
//     int *distance = new int[this->size_nodes]; // tablica na koszt dojścia do elementu
//     int *prev = new int[this->size_nodes];     // tablica na poprzedniki

//     for (int i = 0; i < this->size_nodes; i++)
//     {
//         distance[i] = INT_MAX; // maksymalne wartości
//         prev[i] = -1;          // -1 oznacza brak poprzednika
//     }
//     distance[start_node] = 0; //koszt dojścia do wierzchołka startowego
//     bool change = false;      // zmienna przechowująca informacje o zmianach
//     // pętla główna
//     for (int i = 1; i < this->size_nodes; i++)
//     {
//         change = true;
//         for (int j = 0; j < size_nodes; j++)
//         {
//             for (int k = 0; k < this->size_nodes; k++) // dla każdego sąsiada wierzchołka j
//             {
//                 if (this->matrix[j][k] != 0 && distance[j] != INT_MAX)
//                 {
//                     if (distance[k] > distance[j] + matrix[j][k]) // warunek relaksacji krawędzi
//                     {
//                         change = false;                           // zapamiętanie zmiany
//                         distance[k] = distance[j] + matrix[j][k]; // relaksacja
//                         prev[k] = j;                              // zmiana poprzednika
//                     }
//                 }
//             }
//         }
//         if (change)
//             break;
//     }
//     // sprawdzenie czy nie wystąpił cykl ujemny
//     for (int i = 0; i < this->size_nodes; i++)
//     {
//         for (int j = 0; j < this->size_nodes; j++)
//         {
//             if (matrix[i][j] != 0)
//             {
//                 if (distance[j] > distance[i] + matrix[i][j])
//                     change = false;
//             }
//         }
//     }
//     if (!change)
//     {
//         cout << "Cykl ujemny" << endl;
//         delete[] distance;
//         delete[] prev;
//         return;
//     }
//     // wyświetlenie macierzy
//     printMatrix();
//     // wyświetlany jest numer węzła, długość drogi do niego oraz droga w postaci sekwencji wierzchołków
//     cout << endl
//          << "Wynik Ford-Bellman Macierz: " << endl;
//     cout << "numer wezla : dlugosc -> droga" << endl;

//     for (int i = 0; i < this->size_nodes; i++)
//     {
//         cout << i << ": " << distance[i] << " -> ";
//         for (int j = i; j != -1; j = prev[j])
//         {
//             cout << j << " ";
//         }
//         cout << endl;
//     }
//     delete[] distance;
//     delete[] prev;
// }