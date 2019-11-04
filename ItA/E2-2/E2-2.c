// 军训排队
// len(name_i) <= 5
// 0 < k < n <= 10000000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10000000

typedef struct
{
    char name[6];
    int times;
} Type;

char Name[N][6];
Type HashTable[N];

int Hash_BKDR(char *S)
{
    int seed = 31;
    int hash = 0;

    for (; *S != '\0'; S++)
        hash = hash * seed + *S;
    return hash;
}

// 在Hash表中插入字符串S，并返回Hash地址
int HT_Insert(char *S)
{
    int address = Hash_BKDR(S) % N;
    while ((HashTable[address].times != 0) && (strcmp(S, HashTable[address].name) != 0))
    {
        address = (++address) % N;
    }
    strcpy(HashTable[address].name, S);
    HashTable[address].times++;
    return address;
}

// 在Hash表中查找字符串S，返回地址
int HT_Search(char *S)
{
    int address = Hash_BKDR(S) % N;
    while (strcmp(S, HashTable[address].name) != 0)
    {
        address = (++address) % N;
    }
    return address;
}

int main()
{
    int n, k;
    int i;
    int left = 0, right = 0;
    int hashAddress;
    int count = 0; // 统计相异的字符串个数
    int answer = 0, answer_partial = 1;
    scanf("%d%d", &n, &k);
    for (i = 0; i < n; i++)
        scanf("%s", Name[i]);
    for (right = 0; right < n; right++)
    {
        hashAddress = HT_Insert(Name[right]);
        if (HashTable[hashAddress].times == 1) // 首次插入
            count++;
        for (hashAddress = HT_Search(Name[left]);
             count > k || HashTable[hashAddress].times > 1;
             HashTable[hashAddress].times--, hashAddress = HT_Search(Name[++left]))
        {
            if (HashTable[hashAddress].times > 1) // 消除重复
                answer_partial++;
            else // count > k
            {
                answer_partial = 1;
                count--;
            }
        }
        if (count == k)
            answer += answer_partial;
    }
    printf("%d", answer);
    return 0;
}