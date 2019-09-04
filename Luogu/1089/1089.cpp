//½ò½òµÄ´¢Ðî¼Æ»®
#include <iostream>

using namespace std;

int main()
{
    int Budget[13];
    int bank=0;
    int pocket=0;
    for (int i = 1; i <= 12;i++)
    {
        cin >> Budget[i];
        pocket += 300;
        if (pocket<Budget[i])
        {
            cout << '-' << i;
            return(0);
        }
        else
        {
            bank += ((pocket - Budget[i]) / 100) * 100;
            pocket -= ((pocket - Budget[i]) / 100) * 100 + Budget[i];
            // cout << pocket << ',' << bank << endl;
        }
    }
    cout << 1.2 * bank + pocket;
    return (0);
}