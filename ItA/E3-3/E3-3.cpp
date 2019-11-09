// 多重背包
// 1 <= n <= 200
// 1 <= W <= 10000
// 1 <= w_i <= 1000
// 1 <= v_i <= 1000
// 1 <= num_i <= 10000

#include <iostream>
#define N 10000

using namespace std;

struct queue
{
    int number;
    int value;
} PriorityQueue[N + 1];

int F[N + 1]; // F[i]表示剩余i单位空间时的最大价值

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, W;
    cin >> n >> W;
    // F[i] = Max{ F[i - k * w[j]] + k * v[j] } (0 <= k <= num[j], i >= k * w[j])
    for (int i = 0; i < n; i++)
    {
        int w, v, num;
        cin >> w >> v >> num;
        for (int j = 0; j < w; j++)
        {
            int left = 0, right = 0;
            for (int k = 0; j + k * w <= W; k++)
            {
                // 出队较小元素
                while ((left < right) && (F[j + k * w] - k * v > PriorityQueue[right - 1].value))
                    right--;

                // 元素入队
                PriorityQueue[right].number = k;
                PriorityQueue[right].value = F[j + k * w] - k * v;
                right++;

                // 出队
                if (num < k - PriorityQueue[left].number)
                    left++;

                // 状态转移
                F[j + k * w] = PriorityQueue[left].value + k * v;
            }
        }
    }
    cout << F[W];
    return 0;
}