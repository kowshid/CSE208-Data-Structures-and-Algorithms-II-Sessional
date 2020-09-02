//Adjacency List
//1505102

#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999

struct edge
{
    int ver;
    int weight;
};

class ArrayList
{
	edge * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(edge item) ;
    void insertItem(edge item) ;
	void removeItem(edge item) ;
	void removeItemAt(int item);
	edge getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new edge[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(edge newitem)
{
	edge * tempList ;
	if (length == listMaxSize)
	{
		listMaxSize = 2 * listMaxSize ;
		tempList = new edge[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	}

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(edge item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i].ver == item.ver  && list[i].weight == item.weight) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(edge item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


edge ArrayList::getItem(int position)
{
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
        printf("%d %d\n", list[i].ver, list[i].weight);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	int *parent;
	int *dist;

public:
	Graph(bool dir = true);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v,int w);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void Bellman(int n);
    void printGraph();
};

Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ;
	parent = 0;
	dist = 0;
}

void Graph::setnVertices(int n)
{
	this->nVertices = n + 1 ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;
	parent = new int[nVertices];
	dist = new int[nVertices];
	this->nVertices--;
}

void Graph::addEdge(int u, int v, int w)
{
    if(u <= 0 || v <= 0 || u > nVertices || v > nVertices) return;

    this->nEdges++ ;

	edge edge1,edge2;
	edge1.ver = v;
	edge1.weight = w;
	adjList[u].insertItem(edge1);

	if(!directed)
    {
    edge2.ver = u;
	edge2.weight = w;
	adjList[v].insertItem(edge2);
    }
}

int Graph::getDegree(int u)
{
    if(u<=0 || u>nVertices) return NULL_VALUE;

    return adjList[u].getLength();
}

bool Graph::hasCommonAdjacent(int u, int v)
{
	if(u<=0 || v<=0 || u>nVertices || v>nVertices) return false;

	for(int i = 0; i < adjList[v].getLength(); i++)
	{
		if(adjList[u].searchItem(adjList[v].getItem(i)) != NULL_VALUE)
			return true;
	}

	return false;
}

void Graph::Bellman(int root)
{
    bool solution = true;

    for(int i = 1; i <= nVertices; i++)
    {
        dist[i] = INFINITY;
        parent[i] = -1;
    }

    dist[root] = 0;

    for(int v= 1; v < nVertices; v++)
    {
        for(int i = 1; i <= nVertices ; i++)
        {
            for(int j = 0; j < adjList[i].getLength(); j++)
            {
                if(dist[adjList[i].getItem(j).ver] > (dist[i] + adjList[i].getItem(j).weight) )
                {
                   dist[adjList[i].getItem(j).ver] = dist[i] + adjList[i].getItem(j).weight;
                   parent[adjList[i].getItem(j).ver] = i;
                }
            }
        }
    }

    for(int i = 1; i <= nVertices; i++)
    {
        for(int j = 0; j < adjList[i].getLength(); j++)
        {
            if(dist[adjList[i].getItem(j).ver] > dist[i] + adjList[i].getItem(j).weight)
            {
                solution = false;
            }
        }
    }

    if(solution == false)
    {
        printf("NO SOLUTION\n");
        return;
    }

    for(int i = 1; i <= nVertices; i++)
    {
        printf("%d V.d = %d V.parent = %d\n", i, dist[i], parent[i]);
    }
}

void Graph::printGraph()
{
    for(int i = 1; i <= nVertices; i++ )
    {
        for(int j = 0; j < adjList[i].getLength(); j++)
        {
            edge temp = adjList[i].getItem(j);
            printf("%d %d %d\n", i, temp.ver, temp.weight);
        }
    }
}

Graph::~Graph()
{
    if(nVertices > 0)
	{
		delete[]parent;
		delete[]dist;
	}
}

int main()
{
    //freopen("in.txt","r",stdin);

    int nVertex, nEdge, root;
    int u, v, w;
    Graph g;

    scanf("%d %d", &nVertex ,&nEdge);

    g.setnVertices(nVertex);

    for(int i = 0; i < nEdge; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        g.addEdge(u, v, w);
    }

    g.printGraph();

    scanf("%d", &root);

    g.Bellman(root);

    return 0;
}
