//矩阵取数游戏万进制处理
#include <algorithm>
#include <cstdarg>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stdio.h>

#define MAX_DIGIT (100 / 4 + 1)

using namespace std;
int Power2[81][MAX_DIGIT] = {{1, 1}, {1, 2}, {1, 4}, {1, 8}, {1, 16}, {1, 32}, {1, 64}, {1, 128}, {1, 256}, {1, 512}, {1, 1024}, {1, 2048}, {1, 4096}, {1, 8192}, {2, 1, 6384}, {2, 3, 2768}, {2, 6, 5536}, {2, 13, 1072}, {2, 26, 2144}, {2, 52, 4288}, {2, 104, 8576}, {2, 209, 7152}, {2, 419, 4304}, {2, 838, 8608}, {2, 1677, 7216}, {2, 3355, 4432}, {2, 6710, 8864}, {3, 1, 3421, 7728}, {3, 2, 6843, 5456}, {3, 5, 3687, 912}, {3, 10, 7374, 1824}, {3, 21, 4748, 3648}, {3, 42, 9496, 7296}, {3, 85, 8993, 4592}, {3, 171, 7986, 9184}, {3, 343, 5973, 8368}, {3, 687, 1947, 6736}, {3, 1374, 3895, 3472}, {3, 2748, 7790, 6944}, {3, 5497, 5581, 3888}, {4, 1, 995, 1162, 7776}, {4, 2, 1990, 2325, 5552}, {4, 4, 3980, 4651, 1104}, {4, 8, 7960, 9302, 2208}, {4, 17, 5921, 8604, 4416}, {4, 35, 1843, 7208, 8832}, {4, 70, 3687, 4417, 7664}, {4, 140, 7374, 8835, 5328}, {4, 281, 4749, 7671, 656}, {4, 562, 9499, 5342, 1312}, {4, 1125, 8999, 684, 2624}, {4, 2251, 7998, 1368, 5248}, {4, 4503, 5996, 2737, 496}, {4, 9007, 1992, 5474, 992}, {5, 1, 8014, 3985, 948, 1984}, {5, 3, 6028, 7970, 1896, 3968}, {5, 7, 2057, 5940, 3792, 7936}, {5, 14, 4115, 1880, 7585, 5872}, {5, 28, 8230, 3761, 5171, 1744}, {5, 57, 6460, 7523, 342, 3488}, {5, 115, 2921, 5046, 684, 6976}, {5, 230, 5843, 92, 1369, 3952}, {5, 461, 1686, 184, 2738, 7904}, {5, 922, 3372, 368, 5477, 5808}, {5, 1844, 6744, 737, 955, 1616}, {5, 3689, 3488, 1474, 1910, 3232}, {5, 7378, 6976, 2948, 3820, 6464}, {6, 1, 4757, 3952, 5896, 7641, 2928}, {6, 2, 9514, 7905, 1793, 5282, 5856}, {6, 5, 9029, 5810, 3587, 565, 1712}, {6, 11, 8059, 1620, 7174, 1130, 3424}, {6, 23, 6118, 3241, 4348, 2260, 6848}, {6, 47, 2236, 6482, 8696, 4521, 3696}, {6, 94, 4473, 2965, 7392, 9042, 7392}, {6, 188, 8946, 5931, 4785, 8085, 4784}, {6, 377, 7893, 1862, 9571, 6170, 9568}, {6, 755, 5786, 3725, 9143, 2341, 9136}, {6, 1511, 1572, 7451, 8286, 4683, 8272}, {6, 3022, 3145, 4903, 6572, 9367, 6544}, {6, 6044, 6290, 9807, 3145, 8735, 3088}, {7, 1, 2089, 2581, 9614, 6291, 7470, 6176}};

void WNT_Input(int num, ...)
{
    va_list point;
    va_start(point, num);
    string s;
    int *WNT_Number;
    for (int i = 0; i < num; i++)
    {
        WNT_Number = va_arg(point, int *);
        cin >> s;
        s.erase(0, s.find_first_of("123456789"));
        if (s.length() % 4 != 0)
            s.insert(0, 4 - s.length() % 4, '0');
        WNT_Number[0] = s.length() / 4;
        for (int i = 1; i <= WNT_Number[0]; i++)
        {
            sscanf(s.c_str(), "%4d", &WNT_Number[i]);
            s.erase(0, 4);
        }
    }
    va_end(point);
    return;
}

int *WNT_StoW(string s, int WNT_Number[])
{
    s.erase(0, s.find_first_of("123456789"));
    if (s.length() % 4 != 0)
        s.insert(0, 4 - s.length() % 4, '0');
    WNT_Number[0] = s.length() / 4;
    for (int i = 1; i <= WNT_Number[0]; i++)
    {
        sscanf(s.c_str(), "%4d", &WNT_Number[i]);
        s.erase(0, 4);
    }
    return (WNT_Number);
}

void WNT_Output(int WNT_Number[])
{
    cout << WNT_Number[1];
    for (int i = 2; i <= WNT_Number[0]; i++)
        cout << setw(4) << setfill('0') << WNT_Number[i];
    return;
}

int *WNT_Times(int _A[], int _B[])
{
    int A[MAX_DIGIT], B[MAX_DIGIT];
    int c[2 * MAX_DIGIT] = {0};
    int static C[2 * MAX_DIGIT];
    memset(C, 0, sizeof(C));
    int digit_A = *_A, digit_B = *_B;
    //x[0] is the digit of the wnt_number
    for (int i = 0; i < digit_A; i++)
        A[i] = _A[digit_A - i];
    for (int i = 0; i < digit_B; i++)
        B[i] = _B[digit_B - i];
    //reverse
    for (int i = 0; i < digit_A; i++)
    {
        for (int j = 0; j < digit_B; j++)
        {
            c[i + j] += A[i] * B[j];
            if (c[i + j] >= 10000) //carry timely
            {
                c[i + j + 1] += c[i + j] / 10000;
                c[i + j] %= 10000;
            }
        }
    }

    for (int i = 0; i < digit_A + digit_B + 2; i++)
        if (c[i] >= 10000)
        {
            c[i + 1] += c[i] / 10000;
            c[i] %= 10000;
        }

    for (C[0] = digit_A + digit_B + 2; c[C[0]] == 0; C[0]--)
        ;

    if (C[0] >= 0)
    {
        C[0]++;
        for (int i = 1; i <= C[0]; i++)
            C[i] = c[C[0] - i];
    }
    else
    {
        C[0] = 1;
        C[1] = 0;
    }
    return (C);
}

int *WNT_Plus(int _A[], int _B[])
{
    int A[MAX_DIGIT], B[MAX_DIGIT];
    int c[2 * MAX_DIGIT] = {0};
    int static C[2 * MAX_DIGIT];
    memset(C, 0, sizeof(C));
    int digit_A = *_A, digit_B = *_B;
    //x[0] is the digit of the wnt_number
    for (int i = 0; i < digit_A; i++)
        A[i] = _A[digit_A - i];
    for (int i = 0; i < digit_B; i++)
        B[i] = _B[digit_B - i];

    if (digit_A > digit_B)
    {
        for (int i = digit_B; i < digit_A; i++)
            B[i] = 0;
        C[0] = digit_A;
    }
    else
    {
        for (int i = digit_A; i < digit_B; i++)
            A[i] = 0;
        C[0] = digit_B;
    }

    //reverse
    for (int i = 0; i < C[0]; i++)
    {
        c[i] += A[i] + B[i];
        if (c[i] >= 10000)
        {
            c[i + 1] += c[i] / 10000;
            c[i] %= 10000;
        }
    }

    for (C[0] = C[0] + 2; c[C[0]] == 0; C[0]--)
        ;

    if (C[0] >= 0)
    {
        C[0]++;
        for (int i = 1; i <= C[0]; i++)
            C[i] = c[C[0] - i];
    }
    else
    {
        C[0] = 1;
        C[1] = 0;
    }
    return (C);
}

int *Max(int A[], int B[])
{
    int i = 0;
    for (i = 0; A[i] == B[i]; i++)
        ;
    if (A[i] >= B[i])
        return (A);
    else
        return (B);
}

int main()
{
    int n, m;
    cin >> n >> m;
    int *Column[m+1];
    int *Ans;
    int *F[m+1][m+1];
    Ans = (int *)calloc(MAX_DIGIT, sizeof(int));
    int *temp1 = (int *)calloc(MAX_DIGIT, sizeof(int));
    int *temp2 = (int *)calloc(MAX_DIGIT, sizeof(int));
    int *temp3 = (int *)calloc(MAX_DIGIT, sizeof(int));
    for (int i = 1; i <= m; i++)
    {
        Column[i] = (int *)calloc(MAX_DIGIT, sizeof(int));
        for (int j = 1; j <= m; j++)
            F[i][j] = (int *)calloc(MAX_DIGIT, sizeof(int));
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            {
                WNT_Input(1, Column[j]);
                memcpy(F[j][j], WNT_Times(Column[j], Power2[m]), MAX_DIGIT * sizeof(int));
            }
        for (int k = 2; k <= m; k++)
        {
            for (int p = 1; p <= m - k + 1; p++)
            {
                int q = p + k - 1;
                memcpy(temp1, WNT_Plus(F[p + 1][q], WNT_Times(Column[p], Power2[m - k + 1])), MAX_DIGIT * sizeof(int));
                memcpy(temp2, WNT_Plus(F[p][q - 1], WNT_Times(Column[q], Power2[m - k + 1])), MAX_DIGIT * sizeof(int));
                memcpy(F[p][q], Max(temp1, temp2), MAX_DIGIT * sizeof(int));
                // cout << p << ',' << q << endl;
                // WNT_Output(F[p + 1][q]);
                // cout << '+';
                // WNT_Output(Column[p]);
                // cout << '*';
                // WNT_Output(Power2[m - k + 1]);
                // cout << '=';
                // WNT_Output(temp1);
                // cout << endl;
                // WNT_Output(F[p][q-1]);
                // cout << '+';
                // WNT_Output(Column[q]);
                // cout << '*';
                // WNT_Output(Power2[m - k + 1]);
                // cout << '=';
                // WNT_Output(temp2);
                // cout << endl;
                // WNT_Output(F[p][q]);
                // cout << endl;
            }
        }
        // WNT_Output(F[1][m]);
        // cout << endl;
        memcpy(temp3, WNT_Plus(Ans, F[1][m]), MAX_DIGIT * sizeof(int));
        memcpy(Ans, temp3, MAX_DIGIT * sizeof(int));
    }
    WNT_Output(Ans);
    for (int i = 1; i <= m; i++)
    {
        free(Column[i]);
        for (int j = 1; j <= m; j++)
            free(F[i][j]);
    }
    return (0);
}