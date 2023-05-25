#include <stdlib.h>
#include "utils.h"

char *strdup(const char *src)
{
    char *str;
    char *p;
    int len = 0;

    while (src[len])
        len++;
    str = malloc(len + 1);
    p = str;
    while (*src)
        *p++ = *src++;
    *p = '\0';
    return str;
}

int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

int power(int a, int b)
{
    int ans = 1;
    while (b)
    {
        if (b & 1)
            ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}
