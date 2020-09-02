#include <stdio.h>
#include <stdlib.h>

#define INFINITY 99999999

int result[10001][10001];
int parent[10001][10001];

using namespace std;

int main()
{
    int nVertices, nEdges, a, b, w;

    scanf("%d %d", &nVertices, &nEdges);

 //   int result[nVertices + 1][nVertices + 1];
 //   int parent[nVertices + 1][nVertices + 1];

    for(int i = 1; i <= nVertices; i++)
    {
        for(int j = 1; j <= nVertices; j++)
        {
            parent[i][j] = INFINITY;
            if (i == j) result[i][i] = 0;
            else result[i][j] = INFINITY;
        }
    }

    for(int i = 0; i < nEdges; i++)
    {
        scanf("%d %d %d", &a, &b, &w);
        if (result[a][b] > w)
        {
            result[a][b] = w;
            parent[a][b] = a;
        }
    }

    printf("\n\nInitial Matrix:\n");

    for(int i = 1; i <= nVertices; i++)
    {
        for(int j = 1; j <= nVertices; j++)
        {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    for(int k = 1; k <= nVertices; k++)
    {
        for(int i = 1; i <= nVertices; i++)
        {
            for(int j = 1; j <= nVertices; j++)
            {
                if (result[i][j] > result[i][k] + result[k][j])
                {
                    result[i][j] = result[i][k] + result[k][j];
                    parent[i][j] = parent[k][j];
                }
            }
        }
    }

    printf("\n\nDistance Matrix:\n");

    for(int i = 1; i <= nVertices; i++)
    {
        for(int j = 1; j <= nVertices; j++)
        {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    printf("\n\nParent Matrix:\n");

    for(int i = 1; i <= nVertices; i++)
    {
        for(int j = 1; j <= nVertices; j++)
        {
            printf("%d ", parent[i][j]);
        }
        printf("\n");
    }

//    int root, destination, temp;
//
//    scanf("%d %d", &root, &destination);
//
//    temp = destination;
//
//    printf("\nThe path is reversely %d", destination);
//
//    while (parent[root][temp] != INFINITY)
//    {
//        printf(" %d", parent[root][temp]);
//        temp = parent[root][temp];
//    }

    return 0;
}
