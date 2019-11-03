#include <algorithm>
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <windows.h>
#define N 2000000
using namespace std;

enum Command
{
    I,
    D,
    K
};

int main()
{
    int n, k;
    int i;
    enum Command command;
    vector<int> A;
    srand((int)time(0));
    n = rand() % N;
    printf("%d\n", n);
    for (i = 0; i < n; i++)
    {
        command = (enum Command)(rand() % 3);
        if (command == I)
        {
            k = rand() % N;
            A.push_back(k);
            cout << "I " << k << endl;
        }
        else if (command == D)
        {
            if (A.size() == 0)
                continue;
            int pos = rand() % (A.size());
            k = A[pos];
            vector<int>::iterator iter = A.begin() + pos;
            A.erase(iter);
            cout << "D " << k << endl;
        }
        else if (command == K)
        {
            if (A.size() == 0)
            {
                i--;
                continue;
            }
            k = rand() % (A.size()) + 1;
            cout << "K " << k << endl;
        }
    }
}