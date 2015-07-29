#include<iostream>
#include<string>

using namespace std;

struct Node
{
	int val;
	struct Node * next;
};

struct Adjlist
{
	struct Node * head;
};

struct Graph
{
	int ver;
	struct Adjlist * neighbors;
};

int front = -1;
int rear = -1;
int t = 0;

struct Graph * CreateGraph(int ver)
{
	struct Graph * graph = new struct Graph;
	graph->ver = ver;
	graph->neighbors = new struct Adjlist [ver];
	for(int i = 0; i < ver; i++)
	{
		graph->neighbors[i].head = new struct Node;
		graph->neighbors[i].head->val = i;
		graph->neighbors[i].head->next = NULL;
	}
	return graph;
};

void CreateNode(struct Graph * graph, int src, int dst)
{
	struct Node * node = new struct Node;
	node->val = dst;
	node->next = graph->neighbors[src].head->next;
	graph->neighbors[src].head->next = node;
}

void AddEdge(struct Graph * graph, int x, int y)
{
	CreateNode(graph,x,y);
	CreateNode(graph,y,x);
}

void PrintGraph(struct Graph * graph)
{
	for(int i=0; i < graph->ver; i++)
	{
		struct Node * node = new struct Node;
		node = graph->neighbors[i].head;
		while(node != NULL)
		{
			cout << node->val << "->";
			node = node->next;
		}
		cout << "\n";
	}
}

void DeleteNode(struct Graph ** graph, int src, int dst)
{
	struct Node * node = new struct Node;
	node = (*graph)->neighbors[src].head;
	while(1)
	{
		if(node->next->val == dst)
		{
			struct Node * temp = new struct Node;
			temp = node->next;
			node->next = temp->next;
			delete temp;
			temp = NULL;
			break;
		}
		else
		{
			node = node->next;
		}
	}
}

void DeleteEdge(struct Graph ** graph, int src, int dst)
{
	DeleteNode(graph,src,dst);
	DeleteNode(graph,dst,src);
}

bool EmptyQueue()
{
	if(front == rear)
	{
		return(true);
	}
	return(false);
}

void Push(int * queue, int val)
{
	rear++;
	queue[rear] = val;
}

int Pop(int * queue)
{
	front++;
	return(queue[front]);
}

void BFS(struct Graph * graph, int * visited, int root)
{
	int * queue = new int [graph->ver];
	visited[root] = 1;
	Push(queue,root);
	cout << root << "->";
	while(!EmptyQueue())
	{
		int val = Pop(queue);
		struct Node * node = new struct Node;
		node = graph->neighbors[val].head->next;
		while(node != NULL)
		{
			val = node->val;
			if(visited[val] == 0)
			{
				cout << val << "->";
				visited[val] = 1;
				Push(queue,val);
			}
			node = node->next;
		}
	}
}

void DFS(struct Graph * graph, int * visited, int * arr, int * dep, int root)
{
	visited[root] = 1;
	arr[root] = ++t;
	struct Node * node = new struct Node;
	node = graph->neighbors[root].head->next;
	while(node != NULL)
	{
		int val = node->val;
		if(visited[val] == 0)
		{
			DFS(graph,visited,arr,dep,val);
		}
		node = node->next;
	}
	dep[root] = ++t;
	cout << "Node " << root << " is visited with arrival time " << arr[root] << " and departure time " << dep[root] << "\n";
}
 
int main()
{
	string ch;
	struct Graph * graph = new struct Graph;
	while(1)
	{
		cin >> ch;
		if(ch == "creategraph")
		{
			int ver;
			cin >> ver;
			graph = CreateGraph(ver);
		}
		else if(ch == "addedge")
		{
			int x,y;
			cin >> x >> y;
			AddEdge(graph,x,y);
		}
		else if(ch == "deleteedge")
		{
			int x,y;
			cin >> x >> y;
			DeleteEdge(&graph,x,y);
		}
		else if(ch == "bfs")
		{
			int * visited = new int[graph->ver];
			for(int i=0; i < graph->ver; i++)
			{
				visited[i] = 0;
			}
			cout << "Breadth First Search of the given graph: \n";
			for(int i=0; i < graph->ver; i++)
			{
				if(visited[i] == 0)
				{
					BFS(graph,visited,i);
					cout << "\n";
				}
				front = -1;
				rear = -1;
			}
			cout<<"\n";
		}
		else if(ch == "dfs")
		{
			int * visited = new int[graph->ver];
			int * arr = new int[graph->ver];
			int * dep = new int[graph->ver];
			for(int i=0; i < graph->ver; i++)
			{
				visited[i] = 0;
				arr[i] = 0;
				dep[i] = 0;
			}
			for(int i=0; i < graph->ver; i++)
			{
				if(visited[i] == 0)
				{
					DFS(graph,visited,arr,dep,i);
					cout << "\n";
				}
			}
			t = 0;
		}
		else if(ch == "printgraph")
		{
			cout<<"Printing Adjacency List of the graph: \n";
			PrintGraph(graph);
			cout<<"\n";
		}	
		else if(ch == "exit")
		{
			break;
		}
	}
	return(0);
}
