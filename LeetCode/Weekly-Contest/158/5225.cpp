#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int maxEqualFreq(vector<int> &nums)
    {
        int answer;
        int Times[100001] = {0};
        Times[nums[0]]++;
        for (int i = 1; i < nums.size(); i++)
        {
            cin >> nums[i];
            bool flag_plus = false, flag_1 = false, end_plus = false, end_1 = false;
            Times[nums[i]]++;
            int t = Times[nums[0]];
            for (int j = 1; j <= i; j++)
            {
                if (Times[nums[j]] == t + 1 && flag_plus == false)
                {
                    flag_plus = true;
                    cout << "1_flag_plus = true;";
                }
                else if (Times[nums[j]] == t - 1 && flag_plus == false)
                {
                    t = Times[nums[j]];
                    flag_plus = true;
                    cout << "t = " << t << "2_flag_plus = true;";
                }
                else if (Times[nums[j]] == t)
                    end_plus = false;
                else
                    end_plus = true;
            }
            cout << end_plus;
            for (int j = 1; j <= i; j++)
            {
                if (Times[nums[j]] == t)
                    end_1 = false;
                else if (Times[nums[j]] == 1 && flag_1 == false)
                    flag_1 = true;
                else
                    end_1 = true;
            }
            cout << end_1;
            if (end_plus && end_1)
            {
                int answer = i;
                break;
            }
        }
        cout << answer;
        return answer;
    }
};