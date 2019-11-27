#include <algorithm>
#include <iostream>

#define N 200000
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    int X[N + 1];

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> X[i];

    sort(X, X + n);

    int left = 0, right = X[n - 1] - X[0];

    while (left <= right)
    {
        int mid = (left + right) / 2; // 二分查找确定最大的 d
        int lastClothes = X[0];       // 上一件晾到衣架上的衣服
        int number = 1;               // 已在衣架上的衣服数，第一件衣服已晾

        for (int i = 1; i < n; i++)
        {
            if (X[i] >= lastClothes + mid) // 间距不小于 d
            {
                number++;
                lastClothes = X[i];
            }
        }

        if (number >= n - m)
            left = mid + 1; // 满足最优解条件，可能会更大
        else
            right = mid - 1; // 不满足最优解条件，向小查找
    }

    cout << right;

    return 0;
}