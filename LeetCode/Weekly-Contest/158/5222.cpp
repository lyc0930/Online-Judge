#include <iostream>
#include <stack>
using namespace std;

class Solution
{
public:
    int balancedStringSplit(string s)
    {
        stack<char> sub;
        char flag = 'L';
        int answer = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (sub.empty())
            {
                flag = s[i];
                sub.push(s[i]);
            }
            else
            {
                if (sub.top() == 'R' && s[i] == 'L')
                    sub.pop();
                else if (sub.top() == 'L' && s[i] == 'R')
                    sub.pop();
                else
                    sub.push(s[i]);
                if (sub.empty())
                    answer++;
            }
        }
        return answer;
    }
};