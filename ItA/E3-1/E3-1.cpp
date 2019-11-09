// 偏序关系
// 0 < n <= 10000
// 0 < x_i, y_i <= 100000

#include <algorithm>
#include <iostream>
#define N 10000
using namespace std;

// Partially Ordered Set

struct point
{
    int x;
    int y;
    // bool operator==(const point b) const
    // {
    //     return (this->x == b.x) && (this->y == b.y);
    // }
    // bool operator!=(const point b) const
    // {
    //     return (this->x != b.x) || (this->y != b.y);
    // }
    // bool operator<=(const point b) const
    // {
    //     return (this->x <= b.x) && (this->y <= b.y);
    // }
    bool operator<(const point b) const
    {
        return (this->x < b.x) || (this->y < b.y); // || 无法通过OJ
    }
    bool operator>=(const point b) const
    {
        return (this->x >= b.x) && (this->y >= b.y);
    }
    // bool operator>(const point b) const
    // {
    //     return (this->x > b.x) && (this->y > b.y);
    // }
} Point[N + 1], F[N + 1];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        F[i].x = -1;
        F[i].y = -1;
    }
    for (int i = 0; i < n; i++)
    {
        cin >> Point[i].x >> Point[i].y;
        if (Point[i] >= F[index])
            F[++index] = Point[i];
        else
            *lower_bound(F + 1, F + index + 1, Point[i]) = Point[i];
        // for (int i = 0; i <= n; i++)
        //     cout << '(' << F[i].x << ',' << F[i].y << ')' << ' ';
        // cout << endl;
    }
    cout << index;
    return 0;
}

/*
    坏例
    3
    3 3
    1 5
    4 4
*/