#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000000

char text[N + 1];

char *strlwr(char *str) // The compiler of Luogu does not support this library function, so it has to be written.
{
    if (str == NULL)
        return NULL;

    char *p = str;
    while (*p != '\0')
    {
        if (*p >= 'A' && *p <= 'Z')
            *p = (*p) + 'a' - 'A';
        p++;
    }
    return (str);
}

int main()
{
    char word[11];
    char *text_word;
    int position = -1, times = 0;

    scanf("%[^\n]%*c", word);
    scanf("%[^\n]%*c", text);
    for (text_word = strtok(text, " "); text_word; text_word = strtok(NULL, " "))
    {

        if (strcmp(strlwr(word), strlwr(text_word)) == 0)
        {
            position = text_word - text;
            break;
        }
    }
    if (position != -1)
    {
        for (times = 1, text_word = strtok(NULL, " "); text_word; text_word = strtok(NULL, " "))
        {
            if (strcmp(strlwr(word), strlwr(text_word)) == 0)
                times++;
        }
        printf("%d %d", times, position);
    }
    else
        printf("-1");
    return (0);
}