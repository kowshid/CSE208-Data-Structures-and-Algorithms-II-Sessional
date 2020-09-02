//Adjacency Matrix
//1505102

#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ; //adjacency matrix to store the graph
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation
	int *color;
	int *parent;
	int *dist;
    int time;
	int *discovery_time;
	int *final_time;

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
	void dfs();
	void dfsVisit(int source);
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
	color = 0;
	parent = 0;
	dist = 0;
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

	color = new int[nVertices];
	parent = new int[nVertices];
	dist = new int[nVertices];
	discovery_time = new int[nVertices];
	final_time = new int[nVertices];
}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;

    this->nEdges++ ;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;

    printGraph();
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    if(matrix[u][v] == 1 && nEdges> 0) nEdges--;
    matrix[u][v] = 0;
    if(!directed) matrix[v][u] = 0;

    printGraph();
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
    {
    	printf("is not Edge\n");
    	return false;
    }
    else if(matrix[u][v] == 1) return true;
    else return false;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    if(u<0 || u>=nVertices) return NULL_VALUE;

    int i, count = 0;

    for(i = 0; i < nVertices; i++)
	{
		if(matrix[u][i] == 1) count++;
	}

	return count;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
	if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;

	int i;
	for(i = 0; i < nVertices; i++)
	{
		if(matrix[u][i] == 1 && matrix[v][i] == 1) return true;
	}

	return false;
}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
    if (source >= nVertices) return;

    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        int d = q.dequeue();
        for (int j = 0; j < nVertices; j++)
		{
			if (matrix[d][j] == 1 && color[j] == WHITE)
			{
				color[j] = GREY;
				dist[j] = dist[d] + 1;
				parent[j] = d;
				q.enqueue(j);
			}
		}
		color[d] = BLACK;
    }
}

void Graph::dfs()
{
    //write this function
	for(int i = 0; i < nVertices; i++)
	{
		color[i] = WHITE;
		parent[i] = 0;
	}

	for(int i = 0; i < nVertices; i++)
	{
		if(color[i] == WHITE) dfsVisit(i);
	}
}

void Graph::dfsVisit(int source)
{
	time++;
	discovery_time[source] = time;
	color[source] = GREY;
	for (int i = 0; i < nVertices; i++)
	{
		if(matrix[source][i] == 1 && color[i] == WHITE)
		{
			parent[i] = source;
			dfsVisit(i);
		}
	}

	color[source] = BLACK;
	time++;
	final_time[source] = time;
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return INFINITY;
    else
	{
		bfs(u);
		return dist[v];
	}
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    if(nVertices > 0)
	{
		delete[]parent;
		delete[]color;
		delete[]dist;
		delete[]discovery_time;
		delete[]final_time;
	}
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("\n1. Add edge. 2. Remove Edge. 3. isEdge. 4. getDegree. 5. Print Graph\n");
        printf("6. hasCommonAdjacent. 7. call BFS. 8. getDist. 9. call DFS. 10. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
			int u, v;
            scanf("%d%d", &u, &v);
            g.removeEdge(u, v);
        }
        else if(ch==3)
        {
			int u, v;
            scanf("%d%d", &u, &v);
            if(g.isEdge(u, v)) printf("is Edge\n");
            else printf("is not Edge\n");
        }
        else if(ch==4)
        {
			int u;
            scanf("%d", &u);
            printf("Number of degree of %d = %d\n", u, g.getDegree(u));
        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(g.hasCommonAdjacent(u, v)) printf("has Common Adjacent\n");
            else printf("does not have Common Adjacent\n");
        }
        else if(ch==7)
        {
        	int u;
            scanf("%d", &u);
			g.bfs(u);
        }
        else if(ch==8)
        {
			int u, v;
            scanf("%d%d", &u, &v);
            printf("Distance between %d and %d is %d\n", u, v, g.getDist(u, v));
        }
        else if(ch==9)
		{
			g.dfs();
		}
        else if(ch==10)
        {
            break;
        }
    }
}
