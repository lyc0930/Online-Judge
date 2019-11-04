//最短前缀
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000
#define AND &&
#define OR ||
#define NOT !
#define MOD %

void Initialize(char hashtable[N + 1][22])
{
    int i;
    for (i = 0; i < N; i++)
    {
        strcpy(hashtable[i], "");
    }
    return;
}

int Hash(char *data)
{
    int resort = 0;
    while (*data)
    {
        resort = (65599 * resort + (*data++)) MOD N;
    }
    return (resort MOD N);
}

void Insert(char hashtable[N + 1][22], char *data)
{
    int hashaddress = Hash(data);
    while (*hashtable[hashaddress] != '\0')
    {
        hashaddress = (++hashaddress)MOD N;
    }
    strcpy(hashtable[hashaddress], data);
}

int Search(char hashtable[N + 1][22], char *data)
{
    int hashaddress = Hash(data);
    while (strcmp(hashtable[hashaddress], data) != 0)
    {
        hashaddress = (++hashaddress)MOD N;
        if ((*hashtable[hashaddress] == '\0') OR(hashaddress == Hash(data)))
            return -1;
    }
    return hashaddress;
}

int StringCompare(char *a, char *b)
{
    return (strcmp(a, b) < 0);
}

void QSort(char array[][22], int left, int right)
{
    int i = left;
    int j = right;
    char key[22];
    strcpy(key, array[left]);
    if (left >= right)
        return;
    while (i < j)
    {
        while ((i < j) AND StringCompare(key, array[j]))
            j--;
        strcpy(array[i], array[j]);
        while ((i < j) AND StringCompare(array[i], key))
            i++;
        strcpy(array[j], array[i]);
    }
    strcpy(array[i], key);
    QSort(array, left, i - 1);
    QSort(array, i + 1, right);
    return;
}

int main()
{
    int size = 0;
    char Word[N + 1][22];
    char Word_Hash[N + 1][22];
    char Word_Sorted[N + 1][22];
    int PrefixLength[N + 1];
    int i, j = 0;
    int length = 0, subscript = 0;

    Initialize(Word_Hash);

    while (scanf("%s", Word[size]) != EOF)
    {
        Insert(Word_Hash, Word[size]);
        size++;
    }

    memset(PrefixLength, 0, sizeof(PrefixLength));

    memcpy(Word_Sorted, Word, sizeof(Word));
    QSort(Word_Sorted, 0, size - 1);

    for (i = 0; i < size; i++)
    {
        j = 0;
        length = strlen(Word_Sorted[i]);
        subscript = Search(Word_Hash, Word_Sorted[i]);
        while ((j < PrefixLength[subscript]) AND(Word_Sorted[i][j] == Word_Sorted[i + 1][j]))
        {
            PrefixLength[Search(Word_Hash, Word_Sorted[i + 1])]++;
            j++;
        }
        while ((j < length) AND(Word_Sorted[i][j] == Word_Sorted[i + 1][j]))
        {
            PrefixLength[subscript]++;
            PrefixLength[Search(Word_Hash, Word_Sorted[i + 1])]++;
            j++;
        }
        if (PrefixLength[subscript] + 1 > length)
            PrefixLength[subscript] = length - 1;
    }

    for (i = 0; i < size; i++)
    {
        printf("%s ", Word_Sorted[i]);
        for (j = 0; j <= PrefixLength[Search(Word_Hash, Word_Sorted[i])]; j++)
            putchar(Word_Sorted[i][j]);
        putchar('\n');
    }
    putchar('\n');
    for (i = 0; i < size; i++)
    {
        printf("%s ", Word[i]);
        for (j = 0; j <= PrefixLength[Search(Word_Hash, Word[i])]; j++)
            putchar(Word[i][j]);
        putchar('\n');
    }

    getchar();
    getchar();
    return (0);
}