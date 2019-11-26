#include <algorithm>
#include <iostream>
#include <queue>
#define N 100000

using namespace std;

struct job
{
    int arrival;
    int burst;
    int remain;

    // 重载操作符，比较两个任务剩余时间的多少
    bool operator<(const job that) const
    {
        if (this->remain == that.remain)
            return this->arrival < that.arrival;
        else
            return this->remain < that.remain;
    }
    bool operator>(const job that) const
    {
        if (this->remain == that.remain)
            return this->arrival > that.arrival;
        else
            return this->remain > that.remain;
    }
} Job[N + 1];

/*
    供sort函数调用的比较函数
    比较两个任务到达时间的早晚
*/
int Earlier_Q(const job &x, const job &y)
{
    if (x.arrival == y.arrival)
        return x.remain < y.remain;
    else
        return x.arrival < y.arrival;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> Job[i].arrival >> Job[i].burst;
        Job[i].remain = Job[i].burst;
    }
    sort(Job, Job + n, Earlier_Q);

    int responseTime = 0; // 响应时间
    /*
        已到达但未完成的任务
        队头是剩余时间最短的任务，也即当前执行的任务
    */
    priority_queue<job, vector<job>, greater<job>> JobQueue;
    JobQueue.push(Job[0]);
    for (int i = 1; i < n; i++)
    {
        job current = JobQueue.top(); // 当前执行的任务
        JobQueue.pop();
        int timeInterval = Job[i].arrival - Job[i - 1].arrival; // 两次任务到达时的间隔时间
        while (current.remain <= timeInterval)                  // 在任务到达之前，当前任务就可以完成
        {
            responseTime += Job[i].arrival - timeInterval + current.remain - current.arrival; // Job[i].arrival - timeInterval + current.remain 是当前任务的完成时间
            timeInterval -= current.remain;                                                   // 工作时间
            current.remain = 0;
            if (JobQueue.empty())
                break;
            else
            {
                current = JobQueue.top(); // 当前执行的任务
                JobQueue.pop();
            }
        }
        current.remain -= timeInterval; // 剩余时间减少
        if (current.remain > 0)
            JobQueue.push(current); // 重新入队
        JobQueue.push(Job[i]);      // 到达任务入队
    }
    int time = Job[n - 1].arrival; // 最后一个任务的到达时刻，用于计算队列内剩余任务的响应时间
    while (!JobQueue.empty())
    {
        job current = JobQueue.top(); // 当前执行的任务
        JobQueue.pop();
        responseTime += time + current.remain - current.arrival;
        time += current.remain;
    }
    cout << responseTime;
    return 0;
}