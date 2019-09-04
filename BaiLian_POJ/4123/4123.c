//ÌøÂí
#include <stdio.h>
#include <string.h>
#define AND &&
#define OR ||
#define NOT !
#define MOD %

int Jump[8][2] =
    {
        {1, -2},
        {2, -1},
        {2, 1},
        {1, 2},
        {-1, 2},
        {-2, 1},
        {-2, -1},
        {-1, -2}
    };

int Count(char Board[10][10],int n,int m,int x,int y,int steps)
{
    int i;
    int resort = 0;

    if (((x>=n) OR (x<0)) OR ((y>=m) OR (y<0))) //Out of the board
        return (0);
    if (Board[x][y]==1) //Already walked
        return (0);
    if (steps == n * m - 1) //Complete
        return (1);

    Board[x][y] = 1;//flag
    for (i = 0; i < 8;i++)
    {
        resort += Count(Board, n, m, x + Jump[i][0], y + Jump[i][1], steps + 1);
    }
    Board[x][y] = 0;//deflag
    return resort;
}

int main()
{
    int t;
    int n, m, x, y;
    int i;
    char CheckerBoard[10][10];

    scanf("%d", &t);
    for (i = 0; i < t;i++)
    {
        scanf("%d%d%d%d", &n, &m, &x, &y);
        memset(CheckerBoard, 0, sizeof(CheckerBoard));
        printf("%d", Count(CheckerBoard, n, m, x, y, 0));
    }
    getchar();
    getchar();
}
