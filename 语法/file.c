#include <stdio.h>
#include <string.h>

// 只读，文件必须存在
void fileRead()
{
    FILE *fp = fopen("test1.txt", "r"); // txt文件位于可执行文件的目录
    // 读取失败
    if (fp == NULL)
    {
        perror("open file failed");
        return;
    }

    // 读取文件
    while (1)
    {
        char ch = fgetc(fp); // 读取字符
        if (feof(fp))
            break;
        printf("%c", ch);
    }

    fclose(fp);
}

// 只写，文件不存在则创建，文件存在则清空
void fileWrite()
{
    FILE *fp = fopen("test2.txt", "w"); // w模式下 txt文件可以自己创建
    if (fp == NULL)
    {
        perror("open file failed");
        return;
    }
    rewind(fp); // 文件指针移动到文件开头
    char str[] = "hello world";
    for (int i = 0; i < strlen(str); i++)
    {
        char ch = fputc(str[i], fp); // 写入字符
        printf("%c", ch);
    }

    fclose(fp);
}

// 读写，文件存在则清空，文件不存在则创建
void fileReadWrite()
{
    FILE *fp = fopen("test3.txt", "w+");
    if (fp == NULL)
    {
        perror("open file failed");
        return;
    }
    fputs("hello world", fp); // 写入字符串

    rewind(fp); // 文件指针移动到文件开头。在前面的写入操作后，文件指针已经到了文件末尾

    char buf[1024] = {0};
    char *ret = fgets(buf, sizeof buf, fp); // 读取字符串。只能读一行，多行需要循环读取
    printf("%s", ret);
}

// 格式化读
void fileFormatRead()
{
    FILE *fp = fopen("test4.txt", "r");

    if (fp == NULL)
    {
        perror("open file failed");
        return;
    }

    char buf[2][20] = {0};
    

    fclose(fp);
}

int main()
{
    //fileRead();
    //fileWrite();
    //fileReadWrite();
    fileFormatRead();
    return 0;
}