// 石子合并
// N <= 40000
// 0 < a_i <= 200

#include <algorithm>
#include <iostream>
#include <vector>
#define N 200

using namespace std;
vector<int> Length;

// 基于GarsiaWachs算法计算合并时间
int Merge()
{
    int k = Length.size() - 2; // 如果在0到n - 3之间找不到满足A[k] <= A[k + 2]的k，那么k为n - 2
    for (int i = 0; i < Length.size() - 2; i++)
    {
        if (Length[i] <= Length[i + 2])
        {
            k = i;
            break;
        }
    }
    int mergeTime = Length[k] + Length[k + 1]; // 合并A[k]和A[k + 1]
    Length.erase(Length.begin() + k);
    Length.erase(Length.begin() + k);
    int index;
    for (index = k - 1; index >= 0 && Length[index] <= mergeTime; --index) // 从右往左找第一个比temp小的
        ;
    Length.insert(Length.begin() + index + 1, mergeTime); // 在其后插入
    return mergeTime;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int answer = 0, n;
    cin >> n;
    int length;
    for (int i = 0; i < n; i++)
    {
        cin >> length;
        Length.push_back(length);
    }
    for (int i = 0; i < n - 1; i++) // 进行n - 1次归并
        answer += Merge();
    cout << answer;
    return 0;
}