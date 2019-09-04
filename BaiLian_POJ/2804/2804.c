//´Êµä
#include<stdio.h>
#include<string.h>
#define AND &&
#define OR ||
#define NOT !
#define MOD %

int number, flag, resort;
char c_temp;
char word[12];

typedef struct SDictionary
{
    char English[12];
    char Foreign[12];
} Dictionary;

Dictionary dictionary[100001];

int ForeignCompare(Dictionary a,Dictionary b)
{
    return (strcmp(a.Foreign,b.Foreign)<0);
}


void DictionaryQSort(Dictionary array[], int left, int right)
{
	int i=left;
	int j=right;
	Dictionary key;
    key = array[left];
    if (left>=right) return;
	while (i<j)
	{
		while ((i<j) AND ForeignCompare(key,array[j])) j--;
		array[i]=array[j];
		while ((i<j) AND ForeignCompare(array[i],key)) i++;
		array[j]=array[i];
	}
	array[i] = key;
	DictionaryQSort(array,left,i-1);
	DictionaryQSort(array,i+1,right);
}

int Find(int left,int right,char* dest)
{
    int mid = (left+right)/2;
    if (left <= right)
    {
        if (strcmp(dictionary[mid].Foreign,dest) < 0)
        {
            return (Find(mid+1,right,dest));
        }
        else if(strcmp(dictionary[mid].Foreign,dest) > 0)
        {
            return (Find(left,mid-1,dest));
        }
        else
        {
            flag = 1;
            resort = mid;
            return (resort);
        }
    }
    return (resort);
}

int main()
{
    while((c_temp=getchar()) != '\n')
    {
        dictionary[number].English[0] = c_temp;
        scanf("%s%s",dictionary[number].English+1,dictionary[number].Foreign);
        number++;
        getchar();
    }

    DictionaryQSort(dictionary,0,number-1);
    while (scanf("%s", word) != EOF)
    {
        flag = 0;
        Find(0, number - 1, word);
        if (flag == 0)
        {
            printf("eh\n");
        }
        else
        {
            printf("%s\n", dictionary[resort].English);
        }
    }
    return (0);
}