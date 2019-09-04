// 百炼上的题图错了，难受啊
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AND &&
#define OR ||
#define NOT !
#define MOD %

FILE *fp = NULL;
int n_sets=1;

int Compare(const void *p1, const void *p2)
{
    return (strcmp((char *)p1, (char *)p2));
}

int Construct(int depth)
{
    char s_temp[32];
    char Files[32][32];
    int i, j;
    int n = 0; //Number of files

    gets(s_temp);

    if (*s_temp == '#')
        return (0);

    if (depth == 0)
    {
        fprintf(fp, "DATA SET %d:\n", n_sets);
        fputs("ROOT",fp);
        n_sets++;
    }

    memset(Files, 0, sizeof(Files));

    while ((*s_temp != ']') AND(*s_temp != '*'))
    {
        if (*s_temp == 'f')
        {
            strcpy(Files[n], s_temp);
            n++;
        }
        if (*s_temp == 'd')
        {
            for (i = 0; i < depth + 1; i++)
                fprintf(fp,"|     ");
            fprintf(fp,"%s\n", s_temp);
            Construct(depth + 1);
        }
        gets(s_temp);
    }

    if (*s_temp == ']')
    {
        qsort(Files, n, 32 * sizeof(char), Compare);
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < depth; j++)
                fprintf(fp,"|     ");
            fprintf(fp,"%s\n", Files[i]);
        }
    }

    if ((*s_temp == '*') AND(depth == 0))
    {
        qsort(Files, n, 32 * sizeof(char), Compare);
        for (i = 0; i < n; i++)
        {
            fprintf(fp,"%s\n", Files[i]);
        }
        fputc('\n',fp);
        return (1);
    }
    return (1);
}

int main()
{
    fp = fopen("D:/private/Program/Source files/vscode/C/BaiLian_POJ/2775/resort.txt", "w");
    while (Construct(0)!=0)
        ;
    fclose(fp);
    return (0);
}
