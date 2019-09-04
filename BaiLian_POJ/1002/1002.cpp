//方便记忆的电话号码
#include <algorithm>
#include <iostream>
#include <string.h>
#define OR ||
#define AND &&
#define NOT !

using namespace std;

//                          A    B    C    D    E    F    G    H    I    J    K    L    M    N    O    P    Q    R    S    T    U    V    W    X    Y    Z
const char Contrast[26] = {'2', '2', '2', '3', '3', '3', '4', '4', '4', '5', '5', '5', '6', '6', '6', '7', '0', '7', '7', '8', '8', '8', '9', '9', '9', '0'};

int main()
{
    int n;
    cin >> n;
    string S[n + 1];
    getchar();
    char c;
    for (int i = 0; i < n; i++)
    {
        while ((c = getchar()) != '\n')
        {
            if (c == '-')
                continue;
            if ((c >= '0') AND(c <= '9'))
                S[i] += c;
            else
            {
                if ((c >= 'A') AND(c <= 'Z'))
                    S[i] += Contrast[c - 'A'];
                if ((c >= 'a') AND(c <= 'z'))
                    S[i] += Contrast[c - 'a'];
            }
            if (S[i].size() == 3)
                S[i] += '-';
        }
    }
    sort(S, S + n);
    S[n] = "";
    // for (int i = 0; i < n; i++)
    //     cout << S[i] << endl;
    string temp = "";
    bool flag = false;
    for (int i = 0, k = 1; i <= n; i++)
    {
        if (temp != S[i])
        {
            if (k > 1)
            {
                cout << temp << ' ' << k << endl;
                flag = true;
            }
            k = 1;
            temp = S[i];
        }
        else
            k++;
    }
    if (NOT(flag))
        cout << "No duplicates." << endl;
    return (0);
}