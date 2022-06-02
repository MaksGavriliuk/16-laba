#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

struct AdjListNode
{
	int dest;
	int weight;
	struct AdjListNode* next;
};

struct AdjList
{
	struct AdjListNode* head;
};

struct Graph
{
	int V;
	struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int, int);
struct Graph* createGraph(int);
void addEdge(struct Graph*, int, int, int);
void printGraph(struct Graph*);
void delEdge(struct Graph*, int);
void delNode(struct Graph*, int);
void printAdjMatrix(struct Graph*);
int printMenu();
void printIncidMatrix(struct Graph*);

int* arrayDelNode;

struct AdjListNode* newAdjListNode(int dest, int weight)
{
	struct AdjListNode* newNode = (AdjListNode*)malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createGraph(int V)
{
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->V = V;
	graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
	int i;
	for (i = 1; i < V; i++)
	{
		graph->array[i].head = NULL;
	}
	arrayDelNode = (int*)malloc(V * sizeof(int));
	memset(arrayDelNode, 0, V * sizeof(int));
	return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight)
{
	struct AdjListNode* newNode = newAdjListNode(dest, weight);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
}

void printGraph(struct Graph* graph)
{
	int v;

	for (v = 1; v < graph->V; ++v)
	{
		struct AdjListNode* pCrawl = graph->array[v].head;

		if (arrayDelNode[v])
			continue;


		cout << "\nСписок смежности из вершины " << v << endl;

		if (!pCrawl)
			cout << "Эта вершина не связана с другими вершинами\n";

		while (pCrawl)
		{
			cout << "Вершина " << v << " соединяется с вершиной " << pCrawl->dest << " ребром с номером " << pCrawl->weight << endl;
			pCrawl = pCrawl->next;
		}

		cout << endl;
	}
}

void delEdge(struct Graph* graph, int nEdge)
{
	struct AdjListNode* del, * prevDel, * tmp;
	int counter = 0;
	for (int i = 1; i < graph->V; i++)
	{
		prevDel = NULL;
		del = graph->array[i].head;
		while (del && del->weight != nEdge)
		{
			prevDel = del;
			del = del->next;
		}
		if (del)
		{
			if (prevDel)
			{
				tmp = del;
				prevDel->next = del->next;
				free(del);
				counter++;
			}
			else
			{
				tmp = del;
				graph->array[i].head = del->next;
				free(del);
				counter++;
			}
		}
	}
	if (counter)
	{
		cout << "\nРёбра " << nEdge << " удалены!\n";
	}
	else
	{
		cout << "\nВ графе нет такого ребра!\n";
	}
}

void delNode(struct Graph* graph, int nNode)
{
	struct AdjListNode* tmp, * del, * prevDel;
	if (nNode >= 0 && nNode < graph->V)
	{
		if (arrayDelNode[nNode])
		{
			cout << "\nВершина уже удалена!\n";
			return;
		}
		if (graph->array[nNode].head)
		{
			del = graph->array[nNode].head;
			while (del)
			{
				tmp = del;
				del = del->next;
				free(tmp);
			}
		}
		arrayDelNode[nNode] = 1;
		for (int i = 1; i < graph->V; i++)
		{
			prevDel = NULL;
			if (arrayDelNode[i])
			{
				continue;
			}
			del = graph->array[i].head;
			while (del && del->dest != nNode)
			{
				prevDel = del;
				del = del->next;
			}
			if (del)
			{
				if (prevDel)
				{
					tmp = del;
					prevDel->next = del->next;
					free(del);
				}
				else
				{
					tmp = del;
					graph->array[i].head = del->next;
					free(del);
				}
			}
		}
		cout << "\nВершина " << nNode << " удалена\n";
	}
	else
	{
		cout << "\nТакой вершины не существует!\n";
	}
}

void printAdjMatrix(struct Graph* graph)
{
	int size = graph->V;
	int** adjMatrix = (int**)malloc(size * sizeof(int));
	for (int i = 1; i < size; i++)
	{
		adjMatrix[i] = (int*)malloc(size * sizeof(int));
	}
	for (int i = 1; i < size; i++)
	{
		memset(adjMatrix[i], 0, size * sizeof(int));
	}
	for (int i = 1; i < size; i++)
	{
		struct AdjListNode* node = graph->array[i].head;
		if (arrayDelNode[i])
		{
			continue;
		}
		while (node)
		{
			adjMatrix[i][node->dest] = node->weight;
			node = node->next;
		}
	}

	cout << "Матрица смежности:\n";
	cout << "  ";

	for (int i = 1; i < size; i++)
	{
		if (arrayDelNode[i])
		{
			continue;
		}
		cout << i << " ";
	}

	cout << endl;

	for (int i = 1; i < size; i++)
	{
		if (arrayDelNode[i])
		{
			continue;
		}
		cout << i << " ";
		for (int j = 1; j < size; j++)
		{
			if (arrayDelNode[j])
			{
				continue;
			}
			cout << adjMatrix[i][j] << " ";
		}
		cout << endl;
	}
}

void printIncidMatrix(struct Graph* graph)
{
	std::vector<int> arrEdges;
	int counter;
	for (int i = 1; i < graph->V; i++)
	{
		counter = 0;
		struct AdjListNode* node = graph->array[i].head;
		if (arrayDelNode[i])
		{
			continue;
		}
		while (node)
		{
			for (int j = 1; j < (signed)arrEdges.size(); j++)
			{
				if (node->weight == arrEdges[j])
				{
					counter++;
				}
			}
			if (!counter)
			{
				arrEdges.insert(arrEdges.end(), node->weight);
			}
			node = node->next;
			counter = 0;
		}
	}
	for (int i = 1; i < arrEdges.size() - 1; i++)
	{
		for (int j = 1; j < arrEdges.size() - 1; j++)
		{
			if (arrEdges[j + 1] < arrEdges[j])
			{
				int tmp = arrEdges[j + 1];
				arrEdges[j + 1] = arrEdges[j];
				arrEdges[j] = tmp;
			}
		}
	}
	int** incidMatrix = (int**)malloc(graph->V * sizeof(int));
	for (int i = 1; i < graph->V; i++)
	{
		incidMatrix[i] = (int*)malloc(arrEdges.size() * sizeof(int));
		memset(incidMatrix[i], 0, arrEdges.size() * sizeof(int));
	}
	for (int i = 1; i < graph->V; i++)
	{
		if (arrayDelNode[i])
		{
			continue;
		}
		for (int j = 1; j < arrEdges.size(); j++)
		{
			struct AdjListNode* node = graph->array[i].head;
			while (node)
			{
				if (node->weight == arrEdges[j])
				{
					incidMatrix[i][j] = 1;
				}
				node = node->next;
			}
		}
	}
	cout << "Матрица инцидентности:\n";
	cout << " ";
	copy(arrEdges.begin(), arrEdges.end(), std::ostream_iterator<int>(std::cout, " "));
	cout << endl;
	for (int i = 1; i < graph->V; i++)
	{
		if (arrayDelNode[i])
		{
			continue;
		}
		cout << i << " ";
		for (int j = 1; j < arrEdges.size(); j++)
		{
			cout << incidMatrix[i][j] << " ";
		}
		cout << endl;
	}
}

int printMenu()
{
	cout << "\nВыберите, что Вы хотите сделать\n"
		"1. Создать граф\n"
		"2. Удалить ребро с введённым номером\n"
		"3. Удалить вершину с введённым номером\n"
		"4. Вывести граф на экран\n"
		"5. Вывести матрицу смежности\n"
		"6. Вывести матрицу инцидентности\n"
		"7. Выход\n";
	int choice;
	cin >> choice;
	return choice;
}

int menuDelete() {
	cout << "\nВведите номер ребра, которое Вы хотите удалить\n";
	cout << "Чтобы выйти, нажмите 0\n";
	int choice;
	cin >> choice;
	return choice;
}

int menuDelete2() {
	cout << "\nВведите номер вершины, которую Вы хотите удалить\n";
	cout << "Чтобы выйти, нажмите 0\n";
	int choice;
	cin >> choice;
	return choice;
}


int main()
{
	
	system("chcp 1251");
	system("cls");
	
	int nNode = 5;
	int nEdge = 1;
	bool flag = true;
	struct Graph* graph = NULL;

	while (1)
	{
		switch (printMenu())
		{
		case 1:
		{
			if (!graph)
			{
				graph = createGraph(7);
				addEdge(graph, 1, 2, 7);
				addEdge(graph, 1, 3, 1);
				addEdge(graph, 2, 4, 4);
				addEdge(graph, 2, 6, 1);
				addEdge(graph, 3, 2, 5);
				addEdge(graph, 3, 5, 2);
				addEdge(graph, 3, 6, 4);
				addEdge(graph, 5, 2, 2);
				addEdge(graph, 5, 4, 5);
				addEdge(graph, 6, 5, 3);
				cout << "\nГраф создан!\n";
			}

			else cout << "\nГраф уже существует!\n\n";

		}
		break;
		case 2:
		{
			if (graph)
			{

				int i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5, i6 = 6, i7 = 7;
				bool a = false;
				while (!a) {
					switch (menuDelete()) {
					case 1: {
						
						if (i1 == 1)
						{
							delEdge(graph, i1);
							i1 = 0;
						}
						else cout << "\nРебро 1 уже удалено!";
					}
						  break;
					case 2: {

						if (i2 == 2)
						{
							delEdge(graph, i2);
							i2 = 0;
						}
						else cout << "\nРебро 2 уже удалено!";
					}
						  break;
					case 3: {

						if (i3 == 3)
						{
							delEdge(graph, i3);
							i3 = 0;
						}
						else cout << "\nРебро 3 уже удалено!";
					}
						  break;
					case 4: {

						if (i4 == 4)
						{
							delEdge(graph, i4);
							i4 = 0;
						}
						else cout << "\nРебро 4 уже удалено!";
					}
						  break;
					case 5: {

						if (i5 == 5)
						{
							delEdge(graph, i5);
							i5 = 0;
						}
						else cout << "\nРебро 5 уже удалено!";
					}
						  break;
					case 6: {

						if (i6 == 6)
						{
							delEdge(graph, i6);
							i6 = 0;
						}
						else cout << "\nРебро 6 уже удалено!";
					}
						  break;
					case 7: {

						if (i7 == 7)
						{
							delEdge(graph, i7);
							i7 = 0;
						}
						else cout << "\nРебро 7 уже удалено!";
					}
						  break;
					case 0: a = true; break;
					default: cout << "\nВ графе нет такого ребра\n";
					}
				}

			}
			else cout << "\nГраф не существует!\n";
		}
		break;
		case 3:
		{
			if (graph)
			{
				int nNode1 = 1, nNode2 = 2, nNode3 = 3, nNode4 = 4, nNode5 = 5, nNode6 = 6;
				bool a = false;
				while (!a) {
					switch (menuDelete2()) {
					case 1: {
						if (nNode1 == 1)
						{
							delNode(graph, nNode1);
							nNode1 = 0;
						}
						else cout << "Вершина 1 уже удалена!";
					}
						  break;
					case 2: {
						if (nNode2 == 2)
						{
							delNode(graph, nNode2);
							nNode2 = 0;
						}
						else cout << "Вершина 2 уже удалена!";
					}
						  break;
					case 3: {
						if (nNode3 == 3)
						{
							delNode(graph, nNode3);
							nNode3 = 0;
						}
						else cout << "Вершина 3 уже удалена!";
					}
						  break;
					case 4: {
						if (nNode4 == 4)
						{
							delNode(graph, nNode4);
							nNode4 = 0;
						}
						else cout << "Вершина 4 уже удалена!";
					}
						  break;
					case 5: {
						if (nNode5 == 5)
						{
							delNode(graph, nNode5);
							nNode5 = 0;
						}
						else cout << "Вершина 5 уже удалена!";
					}
						  break;
					case 6: {
						if (nNode6 == 6)
						{
							delNode(graph, nNode6);
							nNode6 = 0;
						}
						else cout << "Вершина 6 уже удалена!";
					}
						  break;
					case 0: a = true; break;
					default: cout << "\nВ графе нет такой вершины\n";
					}
				}

			}
			else cout << "\nГраф не существует!\n";
		}
		break;

		case 4:
		{
			if (graph)
				printGraph(graph);

			else cout << "\nГраф не существует!\n";
		}
		break;
		case 5:
		{
			if (graph)
				printAdjMatrix(graph);

			else cout << "\nГраф не существует!\n";
		}
		break;
		case 6:
		{
			if (graph)
				printIncidMatrix(graph);

			else cout << "\nГраф не существует!\n";
		}
			break;
		case 7: return 0; break;
		}
	}
}


