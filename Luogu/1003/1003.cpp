//ÆÌµØÌº
#include <iostream>
#define N 10000
#define AND &&
using namespace std;



int main()
{
    int n, x, y;
    int number=-1;
    struct Carpet
    {
        int a, b, length, height;
    } Carpets[N + 1];
    cin >> n;
    for (int i = 1; i <= n;i++)
    {
        cin >> Carpets[i].a >> Carpets[i].b >> Carpets[i].length >> Carpets[i].height;
    }
    cin >> x >> y;
    for (int i = 1; i <= n;i++)
    {
        if (((Carpets[i].a<=x) AND (Carpets[i].a + Carpets[i].length>=x)) AND (Carpets[i].b<=y) AND (Carpets[i].b + Carpets[i].height>=y))
            number = i;
    }
    cout << number;
    return (0);
}