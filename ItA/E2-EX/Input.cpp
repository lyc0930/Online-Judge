#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#define N 10
#define M 100
#define K 100
stringstream Stream;

int P[N + 1][N + 1];

int main(int argc, char *argv[])
{
    int seed = time(NULL);
    if (argc > 1)
    {
        Stream.clear();
        Stream << argv[1];
        Stream >> seed;
    }
    srand(seed);

    int n = rand() % N + 1;
    int m = rand() % ((n * n - n) / 2) + 1;
    cout << n << ' ' << m << endl;
    for (int i = 0; i < m; i++)
    {
        int p = rand() % n + 1;
        int q = rand() % n + 1;
        if (P[p][q] != 0)
        {
            i--;
            continue;
        }
        else
        {
            P[p][q] = rand() % K + 1;
            P[q][p] = P[p][q];
            cout << p << ' ' << q << ' ' << P[p][q] << endl;
        }
    }
    return 0;
}