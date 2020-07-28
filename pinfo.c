#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/types.h>
void pinfo(char store1[100][100])
{
    char vor[20] = "", pro[20] = "", vor1[20] = "", vor2[20] = "", pro1[20] = "";
    pid_t process;
    int ola = 0, flag1 = 0;
    if (strcmp(store1[1], "\0") == 0)
    {
        process = getpid();
        flag1 = 1;
    }
    else
    {
        strcpy(vor, store1[1]);
    }
    if (flag1 == 1)
    {
        int process1 = process;
        while (process1 != 0)
        {
            vor[ola++] = (char)((process1 % 10) + 48);
            process1 = process1 / 10;
        }
        for (int i = 0; i < strlen(vor) / 2; i++)
        {
            char temp = vor[i];
            vor[i] = vor[strlen(vor) - 1 - i];
            vor[strlen(vor) - 1 - i] = temp;
        }
    }
    int t = strlen(vor);
    vor[t] = '\0';
    strcat(pro1, "/proc/");
    strcat(vor1, "/status");
    strcat(vor2, "/exe");
    strcat(pro, "/proc/");
    strcat(pro1, vor);
    strcat(pro, vor);
    strcat(pro, vor1);
    strcat(pro1, vor2);
    if (flag1 == 1)
    {
        printf("pid--%d\n", process);
    }
    else
    {
        printf("pid--%s\n", store1[1]);
    }
    FILE *fd1 = fopen(pro, "r");
    char line[250];
    while (fgets(line, sizeof(line), fd1))
    {
        if (strstr(line, "State:") != 0)
        {
            printf("Process Status--- ");
            for (int i = 7; i < strlen(line); i++)
            {
                printf("%c", line[i]);
            }
        }
        else if (strstr(line, "VmSize:") != 0)
        {
            printf("memory--- ");
            int oin = 0;
            while (line[oin]<47 | line[oin]> 57)
            {
                oin++;
            }
            for (int io = oin; io < strlen(line); io++)
            {
                printf("%c", line[io]);
            }
        }
    }
    char buf[1000];
    ssize_t len = readlink(pro1, buf, sizeof(buf));
    buf[len] = '\0';
    printf("Executable path : %s\n", buf);
}
