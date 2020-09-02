#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0

struct edge
{
    int ver;
    int weight;
};

struct HeapItem
{
    public:
        int data;                //actual data that is stored
        float key;              //key value of the data, heap is constructed based on key
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
    HeapItem *A;        //stores heap items, e.g., nodes
    int heapLength;
    int *map;

    MinHeap()
    {
        A = new HeapItem[MAX_HEAP_SIZE];
        map = new int[MAX_HEAP_SIZE];
        heapLength=0;
    }

    ~MinHeap()
    {
        if(map) delete [] map;
        if(A) delete [] A;
        map = 0;                        //set to NULL after deletion
        A = 0;                            //set to NULL after deletion
    }
    //Fills the heap with an array of integers
    //key values do not maintain heap property
    void initialize(int v[], int n)
    {
        heapLength = n;
        for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
        {
            A[i+1].data = v[i];
            A[i+1].key = MAXREAL;
            map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
        }
    }

    void insertItem(int data, float key)
    {
        heapLength++;
        A[heapLength].data=data;
        A[heapLength].key=key;

        map[A[heapLength].data]=heapLength;

        //restore the properties of the heap
        buHeapify(heapLength);
    }

    //this function removes (and returns) the node which contains the minimum key value
    HeapItem removeMin()
    {
        HeapItem temp=A[1];
        A[1]=A[heapLength];

        if(heapLength==0)
        {
            printf("Nothing to delete\n");
            temp.data=-1;temp.key=-1;
            return  temp;
        }

        heapLength--;
        heapify(1);

        return temp;
    }

    //The function updates the key value of an existing data stored in the heap
    void updateKey(int data, float key)
    {
        //search
        int idx=0;
        idx=map[data];

        if(!idx)
        {
            printf("Data not found\n");
            return ;
        }

        //this node should be placed in lower parts of the tree
        if(A[idx].key>key)
        {
            A[idx].key=key;
            buHeapify(idx);
        }

        else
        {
             A[idx].key=key;
             heapify(idx);
        }
    }

    //This function returns the key value of a data stored in heap
    float getKey(int data)
    {
        int i = map[data];
        return A[i].key;
    }

    //this function will restore heap property
    //works only for updating or removing min
    //adding heapify(i+1);heapify(i+2) before "break" of line 147 will make it work for insert() too.
    void heapify(int i)
    {
        int l,r,smallest;
        while(1)
        {
            l=2*i;          //left child index
            r=2*i+1;     //right child index
            smallest=i;

            if(l>heapLength && r>heapLength)
                break; //nothing to do, we are at bottom

            else if(r>heapLength)
                smallest = l;

            else if(l>heapLength)
                smallest = r;

            else if( A[l].key < A[r].key )
                smallest = l;

            else
                smallest = r;

            if(A[i].key <= A[smallest].key)
                break;	//we are done heapifying

            else
            {
                //swap nodes with smallest child, adjust map array accordingly
                HeapItem t;
                t=A[i];
                A[i]=A[smallest];
                map[A[i].data]=i;
                A[smallest]=t;
                map[A[smallest].data]=smallest;
                i=smallest;
            }
        }
    }

    void buHeapify(int i)
    {
        HeapItem temp;
        int parent,child;

        child=i;
        while(child>1)
        {
            if(child%2==0)
                parent=child/2;
            else
                parent=(child-1)/2;

            if(A[parent].key>A[child].key)
            {
                temp=A[child];
                A[child]=A[parent];
                A[parent]=temp;

                map[A[parent].data]=parent;
                map[A[child].data]=child;
            }
            child=parent;
        }
    }

    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1; i<=heapLength; i++)
        {
            printf("(%d,%.2f) ", A[i].data, A[i].key);
        }
        printf("\n");
    }

    bool Empty()
    {
        if(heapLength==0)
            return true;

        else
            return false;
    }
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
	Graph(bool dir = false);
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
    void MST(int root);
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

            if(dist[i] == INFINITY)
                continue;

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

    for(int i = 1; i < nVertices; i++)
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

void Graph::MST(int root)
{
    MinHeap heap;
    HeapItem u;
    edge temp;
    int sum = 0;
    int visit[nVertices + 1];

    for(int i = 1; i <= nVertices; i++)
    {
        heap.insertItem(i, INFINITY);
        parent[i] = NULL_VALUE;
        dist[i] = INFINITY;
        visit[i]=0;
    }

    heap.updateKey(root, 0);
    dist[root] = 0;

    while(!heap.Empty())
    {
        u = heap.removeMin();

        for(int i = 0; i < adjList[u.data].getLength(); i++)
        {
            temp = adjList[u.data].getItem(i);
            if (visit[temp.ver]==0 && temp.weight < dist[temp.ver])
            {
                parent[temp.ver] = u.data;
                dist[temp.ver] = temp.weight;
                heap.updateKey(temp.ver, temp.weight);
            }
        }
        visit[u.data]=1;
    }

    for(int i = 1; i <= nVertices; i++)
    {
        sum = sum + dist[i];
        printf("%d %d %d\n", i, parent[i], dist[i]);
    }

    printf("Weight of MST = %d\n", sum);
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
    //write your destructor here
    if(nVertices > 0)
	{
		delete[]parent;
		delete[]dist;
	}
}

int main()
{
    //freopen("in.txt","r",stdin);

    int nVertex, nEdge, root;;
    int u, v, w;
    Graph g;

    scanf("%d%d",&nVertex,&nEdge);
    g.setnVertices(nVertex);

    for(int i = 0; i < nEdge; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        g.addEdge(u, v, w);
    }

    printf("Graph\n");
    g.printGraph();
    printf("MST\n");
    g.MST(1);

    return 0;
}
