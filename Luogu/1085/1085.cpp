//不高兴的津津
#include <iostream>

using namespace std;

int main()
{
    int Time[8];
    int a, b;
    int max = 0;
    int maxdate = 0;
    for (int i = 1; i <= 7;i++)
    {
        cin >> a >> b;
        Time[i] = a + b;
        if ((Time[i]>8)&&(Time[i]>max))
        {
            max = Time[i];
            maxdate = i;
        }
    }
    cout << maxdate;
    return (0);
}