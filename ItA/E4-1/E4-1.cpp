#include <algorithm>
#include <iostream>
#define N 100000
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, r, X[N + 1];
    cin >> n >> r;
    for (int i = 0; i < n; i++)
        cin >> X[i];
    sort(X, X + n);             // 从小到大排序
    int number = 0;             // 基站数目
    int farthestPoint = -r - 1; // 最远基站
    int theUncovered = X[0];    // 最近未被覆盖
    // for (int i = 0; i < n; i++) // Debug Output
        // cout << X[i] << ' ';    // Debug Output
    // cout << endl;               // Debug Output
    for (int i = 1; i < n; i++)
    {
        for (; (theUncovered >= X[i] - r) && i < n; i++) // 确定最远基站
            ;
        number++;
        farthestPoint = X[i - 1];
        // cout << X[i - 1] << endl; // Debug Output
        for (; (X[i] <= farthestPoint + r) && i < n; i++) // 村庄已被覆盖
            ;
        theUncovered = X[i];
    }
    if (X[n - 1] > farthestPoint + r) // 最后一个村庄未被覆盖
        number++;
    cout << number;
    return 0;
}