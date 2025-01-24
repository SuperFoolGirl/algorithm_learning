#include <stdio.h>

int countBits(int n)
{
    if (!n)
        return 1;
    if (n < 0) // 如果输入负数 也会统计位数 故return一个defalut的值
        return 4;
    int ans = 0;
    while (n)
    {
        n /= 10;
        ans++;
    }
    return ans;
}

void work1(int n)
{
    switch (n)
    {
    case 0:
        printf("zero");
        break;
    case 1:
        printf("one");
        break;
    case 2:
        printf("two");
        break;
    case 3:
        printf("three");
        break;
    case 4:
        printf("four");
        break;
    case 5:
        printf("five");
        break;
    case 6:
        printf("six");
        break;
    case 7:
        printf("seven");
        break;
    case 8:
        printf("eight");
        break;
    case 9:
        printf("nine");
        break;
    default:
        break;
    }
}

int special(int n)
{
    int flag = 0;
    switch (n)
    {
    case 10:
        printf("ten");
        flag = 1;
        break;
    case 11:
        printf("eleven");
        flag = 1;
        break;
    case 12:
        printf("twelve");
        flag = 1;
        break;
    case 13:
        printf("thirteen");
        flag = 1;
        break;
    case 14:
        printf("fourteen");
        flag = 1;
        break;
    case 15:
        printf("fifteen");
        flag = 1;
        break;
    case 16:
        printf("sixteen");
        flag = 1;
        break;
    case 17:
        printf("seventeen");
        flag = 1;
        break;
    case 18:
        printf("eighteen");
        flag = 1;
        break;
    case 19:
        printf("nineteen");
        flag = 1;
        break;
    case 20:
        printf("twenty");
        flag = 1;
        break;
    case 30:
        printf("thirty");
        flag = 1;
        break;
    case 40:
        printf("forty");
        flag = 1;
        break;
    case 50:
        printf("fifty");
        flag = 1;
        break;
    case 60:
        printf("sixty");
        flag = 1;
        break;
    case 70:
        printf("seventy");
        flag = 1;
        break;
    case 80:
        printf("eighty");
        flag = 1;
        break;
    case 90:
        printf("ninety");
        flag = 1;
        break;
    default:
        break;
    }
    return flag;
}

void work2(int n)
{
    if (special(n))
        return;
    special(n - n % 10); // 去零头
    printf("-");
    work1(n % 10);
}

void work3(int n)
{
    work1(n / 100);
    if (n % 100 == 0)
        printf(" hundred");
    else
    {
        printf(" hundred and ");
        // 下面这里 模和除用得很好  模10的n次方，取尾部n个数，除则取 模的情况下 剩余的部分
        if ((n / 10) % 10 == 0) // 如果十位是0
            work1(n % 10);
        else
            work2(n % 100);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int bits = countBits(n);
    switch (bits)
    {
    case 1:
        work1(n);
        break;
    case 2:
        work2(n);
        break;
    case 3:
        work3(n);
        break;
    default:
        printf("ERR");
        break;
    }
    return 0;
}