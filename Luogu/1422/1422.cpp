//小玉家的电费
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int e;
    double fee;
    cin >> e;
    if (e<=150)
        fee = e * 0.4463;
    if ((e>150)&&(e<=400))
        fee = 150 * 0.4463 + (e - 150) * 0.4663;
    if (e>400)
        fee = 150 * 0.4463 + 250 * 0.4663 + (e - 400) * 0.5663;
    cout << int(fee*10+0.5)/10.0;
    return (0);
}