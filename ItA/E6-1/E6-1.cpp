#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define SIZE_P 10000
#define SIZE_S 1000000

vector<int> KMP;

// 获得前缀函数对应数组
void ComputePrefixFunction(string P)
{
    KMP.clear();
    KMP.resize(P.length() + 1);
    KMP[0] = KMP[1] = 0;
    int k = 0;
    for (int i = 1; i < P.length(); i++) // 模式串自己匹配自己
    {
        while (k > 0 && P[k] != P[i])
            k = KMP[k];
        if (P[k] == P[i])
            k++;
        KMP[i + 1] = k;
    }
    return;
}

// KMP匹配，统计模式串P在文本S中的出现次数
int KMP_Matcher(string S, string P)
{
    int answer = 0;
    int q = 0;                           // 匹配的字符数
    for (int i = 0; i < S.length(); i++)
    {
        while (q > 0 && P[q] != S[i])
            q = KMP[q];
        if (P[q] == S[i])
            q++;
        if (q == P.length())
        {
            answer++;
            q = KMP[q];
        }
    }
    return answer;
}

int main()
{
    int t;
    string s, p;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        cin >> p >> s;
        ComputePrefixFunction(p);
        cout << KMP_Matcher(s, p) << endl;
    }
    return 0;
}