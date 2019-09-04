//ÂòÇ¦±Ê
#include  <iostream>
#include <cmath>

using namespace std;

struct Pencil
{
    int number, price, money;
} Pencils[3];

int main()
{
    int n;
    int min = 100000000;
    cin >> n;
    for (int i = 0; i < 3;i++)
    {
        cin >> Pencils[i].number >> Pencils[i].price;
        if (int(ceil((1.0*n)/Pencils[i].number)*Pencils[i].price)
            < min)
        {
            min = int(ceil((1.0 * n) / Pencils[i].number) * Pencils[i].price);
        }
        cout << min<<endl;
    }
    cout << min;
    return (0);
}