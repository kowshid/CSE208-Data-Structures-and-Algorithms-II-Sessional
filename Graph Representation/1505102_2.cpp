//Adjacency List
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

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
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
	void dfs(); //will run dfs in the graph
	void dfsVisit(int source);
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
	color = 0;
	parent = 0;
	dist = 0;
	time = 0;
	discovery_time = 0;
	final_time = 0;
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;

	color = new int[nVertices];
	parent = new int[nVertices];
	dist = new int[nVertices];
	discovery_time = new int[nVertices];
	final_time = new int[nVertices];
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range

    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	if(!directed) adjList[v].insertItem(u) ;

	printGraph();
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range

    if(adjList[u].searchItem(v) != NULL_VALUE && nEdges > 0) nEdges--;
	adjList[u].removeItem(v) ;
	if(!directed) adjList[v].removeItem(u);

	printGraph();
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;
    else if (adjList[u].searchItem(v) != NULL_VALUE) return true;
    else return false;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
   if(u<0 || u>=nVertices) return NULL_VALUE;

//   int count = adjList[u].getLength();
//
//   for(i = 0; i < nVertices; i++)
//   {
//		if (adjList[u].searchItem(v) != NULL_VALUE)  count++;
//   }
//
//   return count;

	return adjList[u].getLength();
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
	if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;
	for(int i = 0; i < adjList[v].getLength(); i++)
	{
		if(adjList[u].searchItem(adjList[v].getItem(i)) != NULL_VALUE)
			return true;
	}

	return false;
}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
    if(source >= nVertices) return;

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
        for (int j = 0; j < adjList[d].getLength(); j++)
		{
			if (color[adjList[d].getItem(j)] == WHITE)
			{
				color[adjList[d].getItem(j)] = GREY;
				dist[adjList[d].getItem(j)] = dist[d] + 1;
				parent[adjList[d].getItem(j)] = d;
				q.enqueue(adjList[d].getItem(j));
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
	for (int i = 0; i < adjList[source].getLength(); i++)
	{
		if(color[i] == WHITE)
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
    return INFINITY ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
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
        printf("\n1. Add edge. 2. Remove Edge. 3. isEdge. 4. getDegree. 5. Print Graph.\n");
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
