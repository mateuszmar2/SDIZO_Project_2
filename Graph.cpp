#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <sstream> // do stringstreama (wczytywanie)
#include "Colors.h"
#include "Graph.h"

using namespace std;

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

void Graph::fillZeros() // wypełnia macierz zerami - brak krawędzi
{
    for (int i = 0; i < size_nodes; i++)
        for (int j = 0; j < size_nodes; j++)
            this->matrix[i][j] = 0;
}

void Graph::print()
{
    if (size_nodes == 0)
    {
        cout << "Graph is empty" << endl;
        return;
    }
    printMatrix();
    printList();
}

void Graph::printMatrix()
{
    // printowanie macierzy
    cout << endl
         << "Matrix" << endl
         << " ";
    for (int i = 0; i < this->size_nodes; i++)
        cout << "   " << RED << i << RESET; // kolumny
    cout << endl;
    for (int i = 0; i < this->size_nodes; i++)
    {
        cout << RED << i << RESET << "   "; // wiersze
        for (int j = 0; j < this->size_nodes; j++)
        {
            if (this->matrix[i][j] == 0) // nie wypisuj 0 czyli braku krawędzi
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
}

void Graph::printList()
{
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

void Graph::randomStructure(int size, float density, int min, int max, bool directed)
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

    fillZeros(); // wszędzie brak krawędzi

    // tablica indeksów wierzchołków, wypełniona false, będzie true jeśli wierzchołek będzie już połączony
    bool *index_table = new bool[size];
    for (int i = 0; i < size; i++)
        index_table[i] = false;
    // Na początku trzeba utworzyć minimalne drzewo rozpinające
    int random_weight;
    int random_index = 0;
    int index = 0;
    for (int i = 0; i < max_index; i++)
    {
        index_table[index] = true; // wierzchołek do którego wcześniej doszliśmy jest odznaczony
        // wyszukiwanie wierzchołka który jeszcze nie jest podłączony
        do
        {
            random_index = rand() % size;    // losowy index
        } while (index_table[random_index]); // szukamy dopóki nie znajdziemy odpowiedniego
        // wagi krawędzi
        do
        {
            random_weight = rand() % (max - min + 1) + min; // od max to min
        } while (random_weight == 0);                       // waga nie może być równa 0

        //wypełnienie macierzy wagami
        this->matrix[index][random_index] = random_weight;
        if (!directed) // jeśli nieskierowana to dodać połączenie w drugą stronę
            this->matrix[random_index][index] = random_weight;

        index = random_index; // nowy indeks od którego wyjdziemy to ten wyżej wylosowany
    }
    // sprawdzenie czy należy dodać więcej krawędzi
    if (edges_amount != max_index)
    {
        int line, column;
        int if_directed = 2;
        if (!directed)
            if_directed = 1;

        // dodanie reszty krawędzi
        for (int i = max_index; i < edges_amount * if_directed; i++)
        {
            do
            {
                random_weight = rand() % (max - min + 1) + min; // od max to min
            } while (random_weight == 0);                       // waga nie może być równa 0
            while (true)                                        // dopóki nie znajdziemy miejsca w którym nie ma krawędzi
            {
                line = rand() % size;
                column = rand() % size;
                if (this->matrix[line][column] == 0 && line != column)
                    break;
            }
            this->matrix[line][column] = random_weight;
            if (!directed)
                this->matrix[column][line] = random_weight;
        }
    }
    delete[] index_table;
    this->size_edges = edges_amount;
    matrixToList();
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

void Graph::loadGraphFromFile(const char *filename, bool directed)
{
    ifstream file;
    file.open(filename);

    if (!file)
        cout << "File open error" << endl;
    else
    {
        if (this->size_nodes != 0)
            deleteStructure();

        int temp;
        // pierwsze krawędzie
        file >> temp;
        if (temp <= 0)
        {
            cout << "The number of edges is incorrect" << endl;
            deleteStructure();
            return;
        }
        this->size_edges = temp;
        // później wierzchołki
        file >> temp;
        if (temp <= 0)
        {
            cout << "The number of nodes is incorrect" << endl;
            deleteStructure();
            return;
        }
        this->size_nodes = temp;
        // wierzchołek początkowy
        file >> temp;
        if (temp < 0)
        {
            cout << "The start node number is incorrect" << endl;
            deleteStructure();
            return;
        }
        this->start_node = temp;
        // utworzenie macierzy
        this->matrix = new int *[this->size_nodes];

        for (int i = 0; i < this->size_nodes; i++) // utworzenie wierszy
            this->matrix[i] = new int[this->size_nodes];

        fillZeros();

        file >> temp; // wierzchołek końcowy nie jest potrzebny
        int from, to, weight;
        for (int i = 0; i < this->size_edges; i++)
        {
            if (!(file >> from))
            {
                cout << "The size given in the file is not appropriate for the number of elements" << endl;
                deleteStructure();
                return;
            }
            if (!(file >> to))
            {
                cout << "The size given in the file is not appropriate for the number of elements" << endl;
                deleteStructure();
                return;
            }
            if (!(file >> weight))
            {
                cout << "The size given in the file is not appropriate for the number of elements" << endl;
                deleteStructure();
                return;
            }
            cout << from << " " << to << " " << weight << endl;
            // jeśli wszystko poprawnie to dodajemy
            this->matrix[from][to] = weight;
            if (!directed)
                this->matrix[to][from] = weight;
        }
        file.close();
        matrixToList();
        print();
    }
}

void Graph::matrixToList() // przepisanie wartości z macierzy do listy
{
    // for (int i = 0; i < size_nodes; i++)
    //     for (int j = 0; j < size_nodes; j++)
    //         this->matrix[i][j] = 0;
}
