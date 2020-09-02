#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define INFINITY 9999999
#define NULL_VALUE -1

using namespace std;

//void printGraph(int **graph, int nVertices);

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

void bfs(int source, int **graph, int nVertices, int *parent, int *visited)
{
    for(int i = 1; i <= nVertices; i++)
    {
        parent[i] = -1 ;
        visited[i] = 0;
    }

    parent[source] = 0;

    Queue q;

    q.enqueue(source);

    while(!q.empty())
    {
        int d = q.dequeue();

        for(int i = 1; i <= nVertices; i++)
        {
            if(graph[d][i] != INFINITY && visited[i] == 0)
            {
                parent[i] = d;
                q.enqueue(i);
            }
        }

         visited[d] = 1;
    }
}

void makeResidual(int **graph, int **flow, int **residual, int nVertices)
{
    for(int i = 1; i <= nVertices; i++)
    {
        for(int j = 1; j <= nVertices; j++)
        {
            if(graph[i][j] != INFINITY)
            {
                residual[i][j] = graph[i][j] - flow[i][j];

                if(graph[j][i] == INFINITY and flow[i][j]!=0)
                {
                    residual[j][i] = flow[i][j];
                }

                else
                {
                    residual[j][i] = graph[j][i] + flow[i][j];
                }
            }

            if(residual[i][j] == 0) residual[i][j] = INFINITY;
        }
    }
}

bool isExistPath(int source, int sink, int *parent)
{
    while(1)
    {
        if(sink == source) return true;

        else if (sink == -1) return false;

        else
        {
            sink = parent[sink];
        }
    }
}

int maxFlow(int source, int sink, int *parent, int **graph)
{
    int f = INFINITY;

   while(1)
    {
        if(sink == source) break;

        if(f > graph[parent[sink]][sink])
        {
            f = graph[parent[sink]][sink];
        }

        sink = parent[sink];
   }

    return f;
}

void makeFlow(int source, int sink, int *parent, int **flow, int **graph, int f)
{
    if(isExistPath(source, sink, parent))
    {
        while(sink != source)
        {
            if(graph[parent[sink]][sink] != INFINITY) flow[parent[sink]][sink] = f + flow[parent[sink]][sink];

            else flow[parent[sink]][sink] = flow[parent[sink]][sink] - f;
            sink = parent[sink];
        }
    }
}

void dfsVisit(int source, int nVertices, int **graph, int *visited)
{
    visited[source] = 1;

    for(int i = 1; i <= nVertices; i++)
    {
        if(graph[source][i] != INFINITY && visited[i] == 0)
        {
            dfsVisit(i, nVertices, graph, visited);
        }
    }
}

void dfs(int source, int nVertices, int **graph, int *visited)
{
    for(int i = 1; i <= nVertices; i++)
    {
        visited[i] = 0;
    }

    dfsVisit(source, nVertices, graph, visited);
}

void FordFulkerson(int source, int sink, int nVertices, int **graph, int **flow, int **residual)
{
    int *parent, *visited;

    parent = new int [nVertices + 1];
    visited = new int [nVertices + 1];

    for(int i = 1; i <= nVertices; i++)
    {
        parent[i] = -1;
        visited[i] = 0;
    }

    makeResidual(graph, flow, residual, nVertices);
    bfs(source, residual, nVertices, parent, visited);

    int count = 0;

    int x = 0;

    while(isExistPath(source, sink, parent))
    {
        x = maxFlow(source, sink, parent, graph);
        count = count + x;

        makeFlow(source, sink, parent, flow, graph, x);
        makeResidual(graph, flow, residual, nVertices);

        bfs(source, residual, nVertices, parent, visited);
    }

    printf("\nmax flow: \n%d", count);

    printf("\nmin cut:\n");

    dfs(source, nVertices, residual, visited);

    for(int i = 1; i <= nVertices; i++)
    {
        for(int j = 1; j <= nVertices; j++)
        {
            if(visited[i] == 1 && visited[j] == 0 && graph[i][j] != INFINITY)
            {
                printf("%d -> %d\n", i, j);
            }
        }
    }
}

void printGraph(int **graph, int nVertices)
{
    printf("\n");

    for(int i = 1; i <= nVertices; i++)
    {
        printf("\n");

        for(int j = 1; j <= nVertices; j++)
        {
            if(graph[i][j] == INFINITY) printf("i ");
            else printf("%d ", graph[i][j]);
        }
    }

    printf("\n");
}

int main()
{
    int nVertices, nEdges, source, sink;

    scanf("%d %d", &nVertices, &nEdges);

    int **graph;
    int **residual;
    int **flow;

    graph = new int*[nVertices + 1];
    residual = new int*[nVertices + 1];
    flow  = new int*[nVertices + 1];

    for(int i = 0; i <= nVertices; i++)
    {
        graph[i] = new int[nVertices + 1];
        residual[i] = new int[nVertices + 1];
        flow[i]  = new int[nVertices + 1];
    }

    for(int i = 1; i <= nVertices; i++)
    {
        for(int j = 1; j <= nVertices; j++)
        {
            graph[i][j] = INFINITY;
            residual[i][j] = INFINITY;
            flow[i][j] = 0;
        }
    }

    int a, b, c;

    for(int i = 0; i < nEdges; i++)
    {
        scanf("%d %d %d", &a, &b, &c);
        graph[a][b] = c;
    }

    printf("\n");
    printGraph(graph, nVertices);

//    makeResidual(graph, flow, residual, nVertices);
//    printf("\n");
//    printGraph(residual, nVertices);

    scanf("%d %d", &source, &sink);

    FordFulkerson(source, sink, nVertices, graph, flow, residual);

    printf("\n");
//    printGraph(flow, nVertices);

    for(int i = 1; i <= nVertices; i++)
    {
        for(int j = 1; j <=nVertices; j++)
        {
            if(graph[i][j] != INFINITY)
            {
                printf("%d - %d : %d\n", i, j, flow[i][j]);
            }
        }
    }
}
