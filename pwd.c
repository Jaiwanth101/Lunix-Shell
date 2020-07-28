#include<stdio.h>
#include<string.h>
#include<unistd.h>
void pwd1()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
}