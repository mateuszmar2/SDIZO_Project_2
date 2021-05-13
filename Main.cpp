#include <iostream>
#include <limits>
// #include <cstring>
// #include <stdlib.h>

#include "Graph.h"

using namespace std;

Graph graph;

void menuMST()
{
	int action;
	int value;
	char filename[50];
	float density;
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
			cout << "Enter the density: ";
			cin >> density;
			cout << endl;
			graph.randomStructure(value, density);
			break;
		case 3: // utworzenie z pliku
				/*
            cout << "Enter file name: ";
            cin >> filename;
            cout << endl;
            heap.buildFromFile(filename);
            heap.displayHeap();
		*/
			break;
		case 4: // Prim
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
	int action;
	int value;
	char filename[50];
	float density;
	do
	{
		cout << endl
			 << "Which action you want to perform? Type appropriate number " << endl;
		cout << "1 - Display graph " << endl;
		cout << "2 - Make random graph " << endl;
		cout << "3 - Build graph from file " << endl;
		cout << "4 - Ford-Bellaman algorithm " << endl;
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
			cout << "Enter the density: ";
			cin >> density;
			cout << endl;
			graph.randomStructure(value, density);
			break;
		case 3: // utworzenie z pliku
				/*
            cout << "Enter file name: ";
            cin >> filename;
            cout << endl;
            heap.buildFromFile(filename);
            heap.displayHeap();
		*/
			break;
		case 4: // Ford-Bellaman
			break;
		case 5: // Dijkstra
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
		cout << "m - Wyznaczanie minimalnego drzewa rozpinającego (MST) " << endl;
		cout << "p - Wyznaczanie najkrótszej ścieżki w grafie " << endl;
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
