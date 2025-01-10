#include <stdio.h>

int main()
{
    char stack[200] = {0};
    int top = 0;
    char ch = getchar();
    int flag = 0;
    int ans = 0;
    while (ch != '#')
    {
        switch (ch)
        {
        case '{':
            // 注意顺序 交换的话就越界了 意思是在不空栈的情况下 栈顶如果是圆方括号————
            if (top && (stack[top - 1] == '(' || stack[top - 1] == '[')) // 注意top-1(使用后置++操作后要-1查询刚刚的那个 其实我觉得这里应该用前置++ 这样判断空栈更好理解 当然后置也可以)
                flag = 1;
            else
                stack[top++] = ch;
            break;
        case '[':
            if (top && stack[top - 1] == '(')
                flag = 1;
            else
                stack[top++] = ch;
            break;
        case '(':
            stack[top++] = ch;
            break;
        case '}':
            if (top && stack[top - 1] == '{') // 交换会越界 top意思是不空栈
            {
                ans++;
                top--;
            }
            else
                flag = 1;
            break;
        case ']':
            if (top && stack[top - 1] == '[')
            {
                ans++;
                top--;
            }
            else
                flag = 1;
            break;
        case ')':
            if (top && stack[top - 1] == '(')
            {
                ans++;
                top--;
            }
            else
                flag = 1;
            break;
        default:
            break;
        }
        if (flag)
        {
            printf("ERR %d", ans);
            return 0;
        }
        ch = getchar();
    }
    printf("MATCHED %d", ans);
    return 0;
}