// 简单概括下进制转换的核心
// 对于一个10进制数n，想要转成b进制，只需要不断地对n除以b，每次取余数即可

// 如果反过来 转为十进制其实更容易 直接套定义就行
#include <stdio.h>

void transform(long long n, int b)
{
    if (!n)
        return;
    int ans = n % b;
    n /= b;
    transform(n, b);
    ans < 10 ? printf("%d", ans) : printf("%c", 'A' + ans - 10);
}

int main()
{
    long long n;
    int b;
    scanf("%lld %d", &n, &b);

    if (n)
        transform(n, b);
    else
        printf("0");
    return 0;
}