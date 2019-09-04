//µçÓ°½Ú
#include <algorithm>
#include <iostream>
#include <string.h>
#include <vector>
#define AND &&

using namespace std;

typedef struct Movietime
{
    int begin, end;
} MovieTime;

bool Compare_inBeginOrder(MovieTime x, MovieTime y)
{
    return (x.begin < y.begin);
}

/* bool Compare_inEndOrder(MovieTime x, MovieTime y)
{
    return (x.end < y.end);
} */

int main()
{
    int n;
    cin >> n;
    while (n != 0)
    {
        MovieTime Timetable[n], Timetable_iBO[n];
        //Timetable_iEO[n];
        int endtime = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> Timetable[i].begin >> Timetable[i].end;
            if (Timetable[i].end > endtime)
                endtime = Timetable[i].end;
        }
        memcpy(Timetable_iBO, Timetable, n * sizeof(MovieTime));
        // memcpy(Timetable_iEO, Timetable, n * sizeof(MovieTime));
        sort(Timetable_iBO, Timetable_iBO + n, Compare_inBeginOrder);
        // sort(Timetable_iEO, Timetable_iEO + n, Compare_inEndOrder);
        int F[endtime + 1];
        memset(F, 0, sizeof(F));
        for (int i = endtime - 1; i >= Timetable_iBO[0].begin; i--)
        {
            for (int j = i; j < endtime; j++)
            {
                for (int k = 0; (k < n) AND(Timetable_iBO[k].begin <= j); k++)
                {
                    if (Timetable_iBO[k].begin == j)
                    {
                        if ((F[Timetable_iBO[k].end] + 1) > F[i])
                            F[i] = F[Timetable_iBO[k].end] + 1;
                    }
                }
            }
        }
        for (int i = 0; i <= endtime; i++)
            cout << F[i] << ' ';
        cout << endl;
        cout << F[Timetable_iBO[0].begin] << endl;
        cin >> n;
    }
}
