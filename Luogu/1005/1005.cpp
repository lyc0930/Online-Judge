//æÿ’Û»° ˝”Œœ∑
#include <algorithm>
#include <cstdarg>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#define AND &&
#define OR ||
#define NOT !
#define MAX_DIGIT 26
using namespace std;
const string Power2[81] = {"1", "2", "4", "8", "16", "32", "64", "128", "256", "512", "1024", "2048", "4096", "8192", "16384", "32768", "65536", "131072", "262144", "524288", "1048576", "2097152", "4194304", "8388608", "16777216", "33554432", "67108864", "134217728", "268435456", "536870912", "1073741824", "2147483648", "4294967296", "8589934592", "17179869184", "34359738368", "68719476736", "137438953472", "274877906944", "549755813888", "1099511627776", "2199023255552", "4398046511104", "8796093022208", "17592186044416", "35184372088832", "70368744177664", "140737488355328", "281474976710656", "562949953421312", "1125899906842624", "2251799813685248", "4503599627370496", "9007199254740992", "18014398509481984", "36028797018963968", "72057594037927936", "144115188075855872", "288230376151711744", "576460752303423488", "1152921504606846976", "2305843009213693952", "4611686018427387904", "9223372036854775808", "18446744073709551616", "36893488147419103232", "73786976294838206464", "147573952589676412928", "295147905179352825856", "590295810358705651712", "1180591620717411303424", "2361183241434822606848", "4722366482869645213696", "9444732965739290427392", "18889465931478580854784", "37778931862957161709568", "75557863725914323419136", "151115727451828646838272", "302231454903657293676544", "604462909807314587353088", "1208925819614629174706176"};

class wnt
{
    int *number;
    int digit;

  public:
    wnt()
    {
        number = (int *)calloc(MAX_DIGIT, sizeof(int));
    }

    wnt(string s)
    {
        number = (int *)calloc(MAX_DIGIT, sizeof(int));
        s.erase(0, s.find_first_of("123456789"));
        if (s.length() % 4 != 0)
            s.insert(0, 4 - s.length() % 4, '0');
        digit = s.length() / 4;
        for (int i = 0; i < digit; i++)
        {
            sscanf(s.c_str(), "%4d", &number[i]);
            s.erase(0, 4);
        }
    }

    ~wnt()
    {
        free(number);
        digit = 0;
    }

    wnt operator+(const wnt &B) const
    {
        wnt C;
        int a[MAX_DIGIT], b[MAX_DIGIT];
        int c[2 * MAX_DIGIT];
        memset(c, 0, sizeof(c));
        //x.digit is the digit of the wnt_number
        for (int i = 0; i < digit; i++)
            a[i] = number[digit - i - 1];
        for (int i = 0; i < B.digit; i++)
            b[i] = B.number[B.digit - i - 1];

        if (digit > B.digit)
        {
            for (int i = B.digit; i < digit; i++)
                b[i] = 0;
            C.digit = digit;
        }
        else
        {
            for (int i = digit; i < B.digit; i++)
                a[i] = 0;
            C.digit = B.digit;
        }

        //reverse
        for (int i = 0; i < C.digit; i++)
        {
            c[i] += a[i] + b[i];
            if (c[i] >= 10000)
            {
                c[i + 1] += c[i] / 10000;
                c[i] %= 10000;
            }
        }

        for (C.digit += 2; c[C.digit] == 0; C.digit--)
            ;

        if (C.digit >= 0)
        {
            C.digit++;
            for (int i = 0; i < C.digit; i++)
                C.number[i] = c[C.digit - i - 1];
        }
        else
        {
            C.digit = 1;
            C.number[0] = 0;
        }
        return (C);
    }

    wnt operator*(const wnt &B) const
    {
        wnt C;
        int a[MAX_DIGIT], b[MAX_DIGIT];
        int c[2 * MAX_DIGIT];
        memset(c, 0, sizeof(c));
        //x[0] is the digit of the wnt_number
        for (int i = 0; i < digit; i++)
            a[i] = number[digit - i - 1];
        for (int i = 0; i < B.digit; i++)
            b[i] = B.number[B.digit - i - 1];
        //reverse
        for (int i = 0; i < digit; i++)
        {
            for (int j = 0; j < B.digit; j++)
            {
                c[i + j] += a[i] * b[j];
                if (c[i + j] >= 10000) //carry timely
                {
                    c[i + j + 1] += c[i + j] / 10000;
                    c[i + j] %= 10000;
                }
            }
        }

        for (int i = 0; i < digit + B.digit + 2; i++)
            if (c[i] >= 10000)
            {
                c[i + 1] += c[i] / 10000;
                c[i] %= 10000;
            }

        for (C.digit = digit + B.digit + 2; c[C.digit] == 0; C.digit--)
            ;
        if (C.digit >= 0)
        {
            C.digit++;
            for (int i = 0; i < C.digit; i++)
                C.number[i] = c[C.digit - i - 1];
        }
        else
        {
            C.digit = 1;
            C.number[0] = 0;
        }
        return (C);
    }

    wnt operator=(const wnt &B)
    {
        wnt C;
        digit = B.digit;
        C.digit = B.digit;
        memcpy(number, B.number, MAX_DIGIT * sizeof(int));
        memcpy(C.number, B.number, MAX_DIGIT * sizeof(int));
        return (C);
    }

    bool operator>(const wnt &B) const
    {
        if (digit != B.digit)
            return (digit > B.digit);
        else
        {
            for (int i = 0; i < digit; i++)
                if (number[i] > B.number[i])
                    return (true);
            return (false);
        }
    }

    bool operator<(const wnt &B) const
    {
        if (digit != B.digit)
            return (digit < B.digit);
        else
        {
            for (int i = 0; i < digit; i++)
                if (number[i] < B.number[i])
                    return (true);
            return (false);
        }
    }

    bool operator>=(const wnt &B) const
    {
        if (digit != B.digit)
            return (digit > B.digit);
        else
        {
            for (int i = 0; i < digit; i++)
            {
                if (number[i] > B.number[i])
                    return (true);
                if (number[i] < B.number[i])
                    return (false);
            }
            return (true);
        }
    }

    bool operator<=(const wnt &B) const
    {
        if (digit != B.digit)
            return (digit < B.digit);
        else
        {
            for (int i = 0; i < digit; i++)
            {
                if (number[i] < B.number[i])
                    return (true);
                if (number[i] > B.number[i])
                    return (false);
            }
            return (true);
        }
    }

    bool operator==(const wnt &B) const
    {
        if (digit != B.digit)
            return (false);
        else
        {
            for (int i = 0; i < digit; i++)
                if (number[i] != B.number[i])
                    return (false);
            return (true);
        }
    }

    bool operator!=(const wnt &B) const
    {
        if (digit != B.digit)
            return (true);
        else
        {
            for (int i = 0; i < digit; i++)
                if (number[i] != B.number[i])
                    return (true);
            return (true);
        }
    }

    void Output() const
    {
        cout << number[0];
        for (int i = 1; i < digit; i++)
            cout << setw(4) << setfill('0') << number[i];
        return;
    }
};

wnt Max(const wnt &A, const wnt &B)
{
    if (A>=B)
        return (A);
    else
        return (B);
}

int main()
{
    int n, m;
    wnt ans("0");
    string s_temp;
    wnt Column[81];
    wnt F[81][81];
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        wnt T;
        for (int j = 1; j <= m; j++)
        {
            cin >> s_temp;
            Column[j]=wnt(s_temp);
            F[j][j] = Column[j] * Power2[m];
        }
        for (int k = 2; k <= m; k++)
        {
            for (int p = 1; p <= m - k + 1; p++)
            {
                int q = p + k - 1;
                T = wnt(Power2[m - k + 1]);
                F[p][q] = Max(F[p + 1][q] + Column[p] * T, F[p][q - 1] + Column[q] * T);
            }
        }
        ans = ans + F[1][m];
    }
    ans.Output();
    return (0);
}
