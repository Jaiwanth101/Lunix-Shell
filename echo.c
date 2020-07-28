#include<stdio.h>
void echo_com(char store1[100][100],int a)
{
    for (int i = 1; i < a; i++)
    {
        printf("%s ", store1[i]);
    }
    printf("\n");
}