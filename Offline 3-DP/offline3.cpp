#include <stdio.h>
#include <stdlib.h>

#define INFINITY 99999999

using namespace std;

int coins[101];
int multi[101];
int count[101][100011];
int result[101][100011];

int main()
{
    int value, types, temp;

    scanf("%d %d", &value, &types);

//    int coins[types + 1];
//    int multi[types + 1];
//    int count[types + 1][value + 1] = {0};
//    int result[types + 1][value + 1];

    for(int i = 1; i <= types; i++)
    {
        scanf("%d", &coins[i]);
    }

    for(int i = 1; i <= types; i++)
    {
        scanf("%d", &multi[i]);
    }

    for(int i = 1; i <= types; i++)
    {
        printf("\n%d %d", coins[i], multi[i]);
    }

    for(int i = 0; i <= types; i++)
    {
        for(int j = 0; j <= value; j++)
        {
            result[i][j] = INFINITY;
        }
    }

    result[0][0] = 0;

    for(int i = 1; i <= types; i++)
    {
        for(int j = 0; j <= value; j++)
        {
            for(int k = 0; k <= j/coins[i] && k <= multi[i]; k++)
            {
                temp = k + result[i - 1][j - k*coins[i]];

                if(result[i][j] > temp)
                {
                    result[i][j] = temp;
                    count[i][j] = k;
                }
            }
        }
    }

//    for(int i = 1; i <= types; i++)
//    {
//        printf("\n");
//        for(int j = 0; j <= value; j++)
//        {
//            printf("%d ", result[i][j] );
//        }
//    }
//    printf("\n");
//    printf("\n");
//    for(int i = 1; i <= types; i++)
//    {
//        printf("\n");
//        for(int j = 0; j <= value; j++)
//        {
//            printf("%d ", count[i][j] );
//        }
//    }


    if(result[types][value] < INFINITY)
    {
        printf("\n\n%d", result[types][value]);

        int i = types;
        //while(1);

        while (value > 0)
        {
            if(count[i][value]*coins[i] <= value && count[i][value]*coins[i] != 0)
            {
                printf("\n%d coin used %d times", coins[i], count[i][value]);
                value = value - count[i][value]*coins[i];
            }

            i--;
        }
    }

    else printf("\nNOT POSSIBLE TO CHANGE\n");

    return 0;
}
