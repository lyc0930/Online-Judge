//上机
#include <iostream>
#include <algorithm>

using namespace std;

struct Condition
{
    int before;//先于右侧元素放入
    int after;//后于右侧元素放入
};

int main()
{
    int n;
    cin >> n;
    int a[n], //neither
        b[n], //either
        c[n]; //both
    struct Condition F[n];

    for (int i = 0; i < n;i++)
        cin >> a[i];
    for (int i = 0; i < n;i++)
        cin >> b[i];
    for (int i = 0; i < n;i++)
        cin >> c[i];
    F[0].before = a[0];
    F[0].after = b[0];
    for (int i = 1; i < n;i++)
    {
        F[i].before = max(F[i - 1].before + b[i], F[i - 1].after + a[i]);
        F[i].after = max(F[i - 1].before + c[i], F[i - 1].after + b[i]);
    }
    cout << F[n - 1].before;
    return (0);
}