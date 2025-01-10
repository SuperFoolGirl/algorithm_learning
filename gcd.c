#include <stdio.h>

int gcd(int x, int y)
{
    return y ? gcd(y, x % y) : x;
}

int lcm(int x, int y)
{
    return x / gcd(x, y) * y;
}

int main()
{
    int n;
    scanf("%d", &n);
    int x, y;
    scanf("%d", &x);
    for (int i = 0; i < n - 1; i++)
    {
        scanf("%d", &y);
        x = lcm(x, y);
    }
    printf("%d", x);
}