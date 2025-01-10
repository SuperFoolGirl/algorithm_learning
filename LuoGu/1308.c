// 这道题还是应该前后加空格 为了防止开头和结尾，特判一些
// 自己写得很麻烦 而且不知道为啥没过

#include <stdio.h>
#include <string.h>
#define maxn (int)1e6 + 10

int main()
{
    char word[12] = {0};
    char passage[maxn] = {0};
    gets(word);
    gets(passage);
    int flag = 0;
    int first = 0, val = 0, ans = 0;
    int len = strlen(passage);
    int wordLen = strlen(word);
    if (len < wordLen)
    {
        printf("-1");
        return 0;
    }

    for (int i = 0; i < len; i++)
    {
        if (flag)
        {
            if (passage[i] == ' ' && passage[i + 1] != ' ') // 防止连续空格
                flag = 0;
        }
        else
        {
            int failed = 0;
            for (int j = 0; j < wordLen; j++)
            {
                if (word[j] >= 'a' && word[j] <= 'z')
                {
                    if (passage[i + j] != word[j] && passage[i + j] != word[j] - ('a' - 'A'))
                    {
                        flag = 1;
                        failed = 1;
                        break;
                    }
                }
                else
                {
                    if (passage[i + j] != word[j] && passage[i + j] != word[j] + ('a' - 'A'))
                    {
                        flag = 1;
                        failed = 1;
                        break;
                    }
                }
            }
            // 防止passage中的长单词完全包含了目标word，需要检测后面的空格
            if (passage[i + wordLen] == ' ')
            {
                if (!failed)
                {
                    if (!first)
                    {
                        val = i;
                        first = 1;
                    }
                    i += wordLen; // 单词匹配上了 说明长度相等 可以直接跳到下一个单词首了
                    ans++;
                }
            }
            else
            {
                flag = 1;
                i += wordLen;
            }
        }
    }
    ans ? printf("%d %d", ans, val) : printf("-1");
    return 0;
}