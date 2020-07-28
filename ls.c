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
void print_permissions(char *filename)
{
    struct stat itemStats;
    stat(filename, &itemStats);
    mode_t mode = itemStats.st_mode;
    printf((S_ISDIR(itemStats.st_mode)) ? "d" : "");
    printf((S_ISREG(itemStats.st_mode)) ? "-" : "");
    printf((S_ISLNK(itemStats.st_mode)) ? "l" : "");
    // directory permissions
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    //RWE permissions
    int a1 = itemStats.st_nlink;
    int a2 = itemStats.st_size;
    char *b1 = (char *)malloc(100);
    b1 = getpwuid(itemStats.st_uid)->pw_name;
    char *b2 = (char *)malloc(100);
    b2 = getgrgid(itemStats.st_gid)->gr_name;
    printf("\t%d", a1);
    printf("\t%s", b1);
    printf("\t%s", b2);
    printf("\t%d ", a2);
    char buffer[90];
    struct tm *timeinfo;
    time_t timeStamp = itemStats.st_atime;
    timeinfo = localtime(&timeStamp);
    char tempo[100];
    for (int i = 4; i <= 15; i++)
    {
        tempo[i - 4] = ctime(&itemStats.st_mtime)[i];
    }
    printf("\t%s\t", tempo);
}
void print_ls(char *dirc, int some,char *initial_path)
{
    char temp[100];

    strcpy(temp, initial_path);
    if (dirc[0] == '~')
    {
        memmove(dirc, dirc + 1, strlen(dirc));
        strcat(temp, dirc);
        strcpy(dirc, temp);
    }
    printf("%s:\n", dirc);
    DIR *p;
    struct dirent *d;
    p = opendir(dirc);
    if (p == NULL)
    {
        perror("");
        return;
    }
    while (d = readdir(p))
    {
        if (some == 1 && d->d_name[0] != '.')
        {
            printf("%s\t", d->d_name);
        }
        else if (some == 0)
        {
            printf("%s\t", d->d_name);
        }
    }
    printf("\n");
}
void print_ls_l(char *dirc, int some,char * initial_path)
{
    char temp[100];
    strcpy(temp, initial_path);
    if (dirc[0] == '~')
    {
        memmove(dirc, dirc + 1, strlen(dirc));
        strcat(temp, dirc);
        strcpy(dirc, temp);
    }
    DIR *p;
    struct dirent *d;
    p = opendir(dirc);
    if (p == NULL)
    {
        perror("");
        return;
    }
    printf("%s:\n", dirc);
    while (d = readdir(p))
    {
        if (some == 1 && d->d_name[0] != '.') //
        {
            char *temp1 = (char *)malloc(100);
            strcpy(temp1, dirc);
            if (dirc[strlen(dirc) - 1] != '/')
                strcat(temp1, "/");
            strcat(temp1, d->d_name);
            // printf("temp=%s\n",temp1);
            print_permissions(temp1);
            printf("%s", d->d_name);
            printf("\n");
        }
        else if (some == 0) //with -a
        {
            char *temp1 = (char *)malloc(100);
            strcpy(temp1, dirc);
            if (dirc[strlen(dirc) - 1] != '/')
                strcat(temp1, "/");
            strcat(temp1, d->d_name);
            print_permissions(temp1);
            printf("%s", d->d_name);
            printf("\n");
        }
    }
    printf("\n");
}
void Supporting_ls_tags(char store1[100][100], int a,char *initial_path)
{

    int some = -1; //checking for ls -al and substitutes
    if ((strcmp(store1[1], "-al") == 0) || (strcmp(store1[1], "-la") == 0) || ((strcmp(store1[1], "-l") == 0) && (strcmp(store1[2], "-a") == 0)) || ((strcmp(store1[2], "-l") == 0) && (strcmp(store1[1], "-a") == 0)))
    {
        some = 0;
        if ((strcmp(store1[1], "-la") == 0) | (strcmp(store1[1], "-al") == 0))
        {
            if (a == 2)
            {
                char cwd[1024];
                getcwd(cwd, sizeof(cwd));
                print_ls_l(cwd, some,initial_path);
            }
            else
            {
                for (int i = 2; i < a; i++)
                {
                    print_ls_l(store1[i], some,initial_path);
                }
            }
        }
        else if (((strcmp(store1[1], "-l") == 0) && (strcmp(store1[2], "-a") == 0)) | ((strcmp(store1[2], "-l") == 0) && (strcmp(store1[1], "-a") == 0)))
        {
            if (a == 3)
            {
                char cwd[1024];
                getcwd(cwd, sizeof(cwd));
                print_ls_l(cwd, some,initial_path);
            }
            else
            {
                for (int i = 3; i < a; i++)
                {
                    print_ls_l(store1[i], some,initial_path);
                }
            }
        }
    }
    else if (strcmp(store1[1], "\0") != 0)
    {
        if (strcmp(store1[1], "-a") == 0) //checking for "ls -a"
        {
            some = 0;
            if (a == 2)
            {
                char cwd[1024];
                getcwd(cwd, sizeof(cwd));
                print_ls(cwd, some,initial_path);
            }
            for (int i = 2; i < a; i++)
            {
                print_ls(store1[i], some,initial_path);
            }
        }
        else if (strcmp(store1[1], "-l") == 0) //checking for "ls -l"
        {

            some = 1;
            if (a == 2)
            {
                char cwd[1024];
                getcwd(cwd, sizeof(cwd));
                print_ls_l(cwd, some,initial_path);
            }
            else
            {
                for (int i = 2; i < a; i++)
                {
                    // printf("%s:\n", store1[i]);
                    print_ls_l(store1[i], some,initial_path);
                }
            }
        }

        else //checking for "ls with files"
        {
            some = 1;
            for (int i = 1; i < a; i++)
            {
                print_ls(store1[i], some,initial_path);
                printf("\n");
            }
        }
    }
    else if (strcmp(store1[1], "\0") == 0) // checking for only "ls"
    {
        some = 1;
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        print_ls(cwd, some,initial_path);
    }
} //end of ls
