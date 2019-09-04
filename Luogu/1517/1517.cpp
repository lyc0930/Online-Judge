//高精度处理正浮点数
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>

#define DIGIT 200
#define AND &&
#define OR ||
#define NOT !

using namespace std;

string HAA_Times(string A, string B)
{
    int i, j;
    string C(A.length() + B.length() + 2, 0);
    int length_decimal_A = 0;
    int length_decimal_B = 0;

    if (A.find('.') != A.npos)
    {
        length_decimal_A = (A.substr(A.find('.') + 1)).length();
        A = A.erase(A.find('.'), 1);
    }
    if (B.find('.') != B.npos)
    {
        length_decimal_B = (B.substr(B.find('.') + 1)).length();
        B = B.erase(B.find('.'), 1);
    }

    reverse(A.begin(), A.end());
    for (int i = 0; i < A.length(); i++) //倒置，并字符转数
        A[i] -= '0';
    reverse(B.begin(), B.end());
    for (int i = 0; i < B.length(); i++) //倒置，并字符转数
        B[i] -= '0';

    for (i = 0; i < B.length(); i++) //循环相乘
    {
        for (j = 0; j < A.length(); j++)
        {
            C[i + j] += B[i] * A[j];
            if (C[i + j] >= 10) //及时进位
            {
                C[i + j + 1] += C[i + j] / 10;
                C[i + j] %= 10;
            }
        }
    }

    for (i = 0; i < A.length() + B.length() + 2; i++) //进位,数转串
    {
        if (C[i] >= 10)
        {
            C[i + 1] += C[i] / 10;
            C[i] %= 10;
        }
        C[i] += '0';
    }

    if (C.find_first_of("123456789") == C.npos)
    {
        C = "0";
        return (C);
    }

    C.insert(C.begin() + length_decimal_A + length_decimal_B, '.');
    C = C.substr(C.find_first_of("123456789."), C.find_last_of("123456789.") - C.find_first_of("123456789.") + 1);
    if (C[0] == '.')
        C.erase(0, 1);
    if (C[C.length() - 1] == '.')
        C.insert(C.begin() + C.length(), '0');
    reverse(C.begin(), C.end());

    return (C);
}

string HAA_Power(string A, int n)
{
    string S = "1";
    for (int i = 0; i < n; i++)
    {
        S = HAA_Times(S, A);
    }
    return (S);
}

int main()
{
    string s,temp;
    int n;
    while(cin>>s>>n)
    {
        temp = HAA_Power(s, n);
        if ((temp[0]=='0')&&(temp[1]=='.'))
            temp.erase(0, 1);
        cout << temp << endl;
    }
    return (0);
}
