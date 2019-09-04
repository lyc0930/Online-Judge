//³µÕ¾
#include <iostream>

using namespace std;

int main()
{
    // int Fibonacci[21] = {0,0, 1};
    // int down_A[21] = {0, 0, 0, 0, 1 , 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597};
    // int down_T[21] = {0, 0, 1, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584};
    int A[21] = {0,1,1,2,2,3,4,6,9,14,22,35,56,90,145,234,378,611,988,1598,2585};
    int T[21] = {0,0,0,1,1,2,4,7,12,20,33,54,88,143,232,376,609,986,1596,2583,4180};
    int a, n, m, x;
    cin >> a >> n >> m >> x;
    int t = (m - (A[n-1]) * a) / (T[n-1]);
    cout << (A[x] * a + T[x] * t);
    // for (int i = 3; i <= 20; i++)
    // {
    //     Fibonacci[i] = Fibonacci[i - 1] + Fibonacci[i - 2];
    //     printf(",%d", Fibonacci[i]);
    // }
    // putchar('\n');
    // for (int i = 4; i <= 20; i++)
    // {
    //     a[i] = Fibonacci[i - 3];
    //     t[i] = Fibonacci[i - 2];
    //     for (int j = 1; j <= i; j++)
    //     {
    //         A[i] += a[j];
    //         T[i] += t[j];
    //     }
    //     cout << A[i] << ' ' << T[i] << endl;
    // }
    // for (int i = 0; i <= 20;i++)
    // {
    //     printf("%d,", T[i]);
    // }
}