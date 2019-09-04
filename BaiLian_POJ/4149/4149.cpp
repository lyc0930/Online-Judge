//课程大作业
#include <iostream>

using namespace std;

struct Course
{
    string name;
    int ddl;
    int cost;
};

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t;i++)
    {
        int n;
        cin >> n;
        struct Course Courses[n];
        for (int j = 0; j < n;j++)
        {
            cin >> Courses[j].name >> Courses[j].ddl >> Courses[j].cost;
        }
    }
}