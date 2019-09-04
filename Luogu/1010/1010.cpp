//ÃÝ´Î·½
#include <cmath>
#include <iostream>

using namespace std;

const int Power2[15] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384};

void Solve(int n)
{
    int b;
    for (int k = 0; (b = (int)(log(n) / log(2))) > 0; n -= Power2[b], k++)
    {
        if (k != 0)
            cout << "+";
        if (b == 1)
            cout << "2";
        else
        {
            cout << "2(";
            Solve(b);
            cout << ')';
        }
    }
    if (n == 1)
        cout << "+2(0)";
    return;
}

int main()
{
    int n;
    cin >> n;
    Solve(n);
    return (0);
}