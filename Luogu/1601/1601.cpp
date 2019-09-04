//A+B Problem
#include <algorithm>
#include <cstdarg>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stdio.h>

using namespace std;

class wnt
{
    int *number;
    int digit;
    int MAX_DIGIT;

  public:
    wnt()
    {
        MAX_DIGIT = 26;
        digit = 0;
        number = (int *)calloc(MAX_DIGIT, sizeof(int));
    }

    wnt(string s)
    {
        MAX_DIGIT = 26;
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
        int a[C.MAX_DIGIT], b[C.MAX_DIGIT];
        int c[2 * C.MAX_DIGIT];
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
        int a[C.MAX_DIGIT], b[C.MAX_DIGIT];
        int c[2 * C.MAX_DIGIT];
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

int main()
{
    string A, B;
    wnt C, D;
    cin >> A >> B;
    C = wnt(A);
    D = wnt(B);
    (C + D).Output();
    return (0);
}