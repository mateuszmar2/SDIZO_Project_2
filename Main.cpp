#include <iostream>
#include <limits>

#include "Graph.h"
#include "Bellman_Ford.h"
#include "Prim.h"

using namespace std;

void menuMST()
{
	Graph graph;
	int action;
	int value;
	int min_weight, max_weight;
	char filename[50];
	float density;
	bool directed = false;
	do
	{
		cout << endl
			 << "Which action you want to perform? Type appropriate number " << endl;
		cout << "1 - Display graph " << endl;
		cout << "2 - Make random graph " << endl;
		cout << "3 - Build graph from file " << endl;
		cout << "4 - Prim algorithm " << endl;
		cout << "5 - Kruskal algorithm " << endl;
		cout << "6 - Exit MST mode " << endl;
		cout << "MST> ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> action;
		cout << endl;
		switch (action)
		{
		case 1: // wypisanie
			graph.print();
			break;
		case 2: // utworzenie losowego
			cout << "Enter how many nodes you want to create: ";
			cin >> value;
			if (value <= 0)
			{
				cout << "Invalid number of edges" << endl;
				break;
			}
			cout << "Density must be between 0 and 1" << endl;
			cout << "Enter the density: ";
			cin >> density;
			if (density < 0 || density > 1)
			{
				cout << "Invalid density" << endl;
				break;
			}
			cout << "Enter min weight: ";
			cin >> min_weight;
			cout << "Enter max weight: ";
			cin >> max_weight;
			cout << endl;
			if (min_weight < 0 || max_weight < 0)
			{
				cout << "Weight must be positive" << endl;
				break;
			}
			graph.randomStructure(value, density, min_weight, max_weight, directed);
			break;
		case 3: // utworzenie z pliku
			cout << "Enter file name: ";
			cin >> filename;
			cout << endl;
			graph.loadGraphFromFile(filename, directed);
			break;
		case 4: // Prim
			primMatrix(graph);
			primList(graph);
			break;
		case 5: // Kruskal
			break;
		case 6: // wyjście
			break;
		default:
			cout << "Type appropriate number" << endl;
			break;
		}
	} while (action != 6);
}

void menuPath()
{
	Graph graph;
	int action;
	int value;
	int min_weight, max_weight;
	char filename[50];
	float density;
	bool directed = true;
	do
	{
		cout << endl
			 << "Which action you want to perform? Type appropriate number " << endl;
		cout << "1 - Display graph " << endl;
		cout << "2 - Make random graph " << endl;
		cout << "3 - Build graph from file " << endl;
		cout << "4 - Bellman-Ford algorithm " << endl;
		cout << "5 - Dijkstra algorithm " << endl;
		cout << "6 - Exit shortest path mode " << endl;
		cout << "PATH> ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> action;
		cout << endl;
		switch (action)
		{
		case 1: // wypisanie
			graph.print();
			break;
		case 2: // utworzenie losowego
			cout << "Enter how many nodes you want to create: ";
			cin >> value;
			if (value <= 0)
			{
				cout << "Invalid number of edges" << endl;
				break;
			}
			cout << "Density must be between 0 and 1" << endl;
			cout << "Enter the density: ";
			cin >> density;
			if (density < 0 || density > 1)
			{
				cout << "Invalid density" << endl;
				break;
			}
			cout << "Enter min weight: ";
			cin >> min_weight;
			cout << "Enter max weight: ";
			cin >> max_weight;
			cout << endl;
			graph.randomStructure(value, density, min_weight, max_weight, directed);
			min_weight = max_weight = 0;
			break;
		case 3: // utworzenie z pliku
			cout << "Enter file name: ";
			cin >> filename;
			cout << endl;
			graph.loadGraphFromFile(filename, directed);
			break;
		case 4: // Bellman - Ford
			bellmanFordMatrix(graph);
			break;
		case 5: // Dijkstra
			if (min_weight < 0 || max_weight < 0)
			{
				cout << "Weight must be positive" << endl;
				break;
			}
			break;
		case 6: // wyjście
			break;
		default:
			cout << "Type appropriate number" << endl;
			break;
		}
	} while (action != 6);
}

void menu()
{
	char choice;
	do
	{
		cout << endl
			 << "Which algorithm you want to test? Type appropriate letter " << endl;
		cout << "m - Determining the minimum spanning tree (MST) " << endl;
		cout << "p - Finding the shortest path in the graph " << endl;
		cout << "e - Exit the program " << endl;
		cout << "> ";
		cin >> choice;
		switch (choice)
		{
		case 'm':
			menuMST();
			break;
		case 'p':
			menuPath();
			break;
		case 'e':
			break;
		default:
			cout << "Type appropriate letter" << endl;
			break;
		}
	} while (choice != 'e');
}

int main()
{
	menu();

	return 0;
}
