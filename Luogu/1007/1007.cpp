//╤юд╬ге
#include <iostream>

using namespace std;

int main()
{
    int l, n;
    cin >> l >> n;
    int soldier;
    int min = 0, max = 0;
    for (int i = 0; i < n;i++)
    {
        cin >> soldier;
        if (soldier>(l-soldier+1))
        {
            if (soldier > max)
                max = soldier;
            if ((l - soldier + 1) > min)
                min = l - soldier + 1;
        }
        else
        {
            if (soldier > min)
                min = soldier;
            if ((l - soldier + 1) > max)
                max = l - soldier + 1;
        }
    }
    cout << min << ' ' << max;
    return (0);
}