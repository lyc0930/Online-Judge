//数据库查询v1
//插入语句和查询语句分别不超过10^6条。
//0 <= id, a[id], k <= 10^9

#include <stdio.h>
#include <stdlib.h>

#define HASHSIZE 1000000
#define OK 1
#define NULLKEY -32768

typedef short Status;
typedef struct
{
    int key;   // a_id
    int value; // id
} type;

typedef struct
{
    type *element;
    int count;
} HashTable;

int hashTableLength = 0;

Status Initialize(HashTable *hashTable)
{
    int i;
    hashTableLength = HASHSIZE;
    hashTable->element = (type *)malloc(hashTableLength * sizeof(type));
    hashTable->count = 0;
    for (i = 0; i < hashTableLength; i++)
    {
        hashTable->element[i].key = NULLKEY;
    }
    return OK;
}

int Hash(int key)
{
    return key % hashTableLength;
}

Status Insert(HashTable *hashTable, type data)
{
    int hashAddress = Hash(data.key);

    while (hashTable->element[hashAddress].key != NULLKEY)
    {
        //利用开放定址的线性探测法解决冲突
        hashAddress = (++hashAddress) % hashTableLength;
    }

    hashTable->element[hashAddress] = data;
    hashTable->count++;
    return OK;
}

int Search(HashTable *hashTable, int key) //return the value
{
    int hashAddress = Hash(key);

    while (hashTable->element[hashAddress].key != key)
    {
        hashAddress = (++hashAddress) % hashTableLength;
        if (hashTable->element[hashAddress].key == NULLKEY || hashAddress == Hash(key))
            return -1;
    }

    return hashTable->element[hashAddress].value;
}

int main()
{
    HashTable hashTable;
    char command[7];
    type temp;
    int value;

    if (Initialize(&hashTable) != OK)
        exit(0);

    while (scanf("%s", command) == 1 && command[0] != 'E')
    {
        if (command[0] == 'I') //INSERT
        {
            scanf("%d%d", &temp.value, &temp.key);
            Insert(&hashTable, temp);
        }
        else if (command[0] == 'F') //FIND
        {
            scanf("%d", &value);
            printf("%d\n", Search(&hashTable, value));
        }
        else
            printf("ERROR");
    }

    return 0;
}