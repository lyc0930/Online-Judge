#include <bits/stdc++.h>
#include <iostream>
#define N 1000
#define R 1000
#define P 1000
// 100000 10000000 1000
using namespace std;

stringstream Stream;
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

    int n = rand() % (N - 1) + 1;
    cout << n << endl;
    for (int i = 0; i < n; i++)
    {
        int r = rand() % (R - 1) + 1;
        int p = rand() % (P - 1) + 1;
        cout << r << ' ' << p << endl;
    }
    return 0;
}