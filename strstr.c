#include <stdio.h>
#include <string.h>

int main()
{
    char a[200] = {0};
    char b[200] = {0};
    gets(a);
    gets(b);
    char *ret = strstr(a, b); // 先源，再子
    if (ret)
        printf("%d", ret - a);
    else
        printf("-1");
    return 0;
}