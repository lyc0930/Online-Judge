//รินฌ
#include <stdio.h>
#include <string.h>
#define AND &&
#define OR ||
#define NOT !
#define MOD %
#define N 100

int Movements[4][2] =
    {
    //   R,  C
        {-1, 0}, //0 up
        {0, +1}, //1 right
        {+1, 0}, //2 down
        {0, -1}  //3 left
    };

int Judge(int n, char Map[][N+1],int A_Row,int A_Column,int B_Row,int B_Column)
{
    int i;
    //int flag = 0;

    if (((A_Row<0) OR (A_Row>=n)) OR ((A_Column<0) OR (A_Column>=n)) OR ((B_Row<0) OR (B_Row>=n)) OR ((B_Row<0) OR (B_Row>=n)))
        return (0);//out of the map
    if ((Map[A_Row][A_Column] == '#') OR (Map[B_Row][B_Column] == '#'))
        return (0);//Encountered an obstacle
    if ((A_Row == B_Row) AND (A_Column == B_Column))
    {
        return (1);
    }
    else
    {
        Map[A_Row][A_Column] = '#';//already walked on it
        for (i = 0; i < 4;i++)//loop for up,right,down,left
        {
            if (Judge(n, Map, A_Row + Movements[i][0], A_Column + Movements[i][1], B_Row, B_Column)==1)
                return (1);
        }
    }



    return (0);
}

int main()
{
    int k, n;//k for the number of groups of data, n for the size of the maze
    int i, j;
    int A_Row, A_Column, B_Row, B_Column;
    char Maze[101][101];

    scanf("%d", &k);
    for (; k > 0;k--)
    {
        scanf("%d", &n);
        getchar();
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                scanf("%c",&Maze[i][j]);
            }
            getchar();
        }
        /*for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                printf("%c", Maze[i][j]);
            }
            putchar('\n');
        }*/
        scanf("%d%d%d%d", &A_Row, &A_Column, &B_Row, &B_Column);
        if (Judge(n,Maze,A_Row,A_Column,B_Row,B_Column) == 1)
        {
            puts("YES");
        }
        else
        {
            puts("NO");
        }

    }
    return (0);
}
