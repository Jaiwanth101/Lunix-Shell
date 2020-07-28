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
char store[100][100];
char store1[100][100];
char initial_path[100];
void breaking_input(char *input, char store1[100][100]);
void pwd1();
void cool_commands(int a, char store1[100][100], char *initial_path);
void pinfo(char store1[100][100]);
void Supporting_ls_tags(char store1[100][100], int a, char *initial_path);
void cd1(char *input, char *initial_path);
void echo_com(char store1[100][100], int a);
void history(char *input,char * initial_path);
void breaking_input_semi(int argc, char **argv)
{
    char *input = NULL;
    ssize_t bufsize = 0;
    getline(&input, &bufsize, stdin);

    int fd2 = open("new.txt", O_WRONLY | O_CREAT, 0777);///storing all the commmands in a file for history.
    lseek(fd2, 0, SEEK_END);
    write(fd2, input, strlen(input)); ////
    
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            store[i][j] = 0;
    int a, b = 0;
    a = 0;
    for (int i = 0; i < strlen(input); i++) //
    {
        int ab = 1;
        while (input[i] == ';')
        {
            ab = 0;
            b = 0;
            i++;
        }
        if (ab == 0)
        {
            a++;
        }
        store[a][b++] = input[i];
    }
    for (int i = 0; i <= a; i++)
    {
        breaking_input(store[i], store1);
    }
    return;
}
void breaking_input(char *input, char store1[100][100])
{
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            store1[i][j] = 0;
    int a, b = 0;
    a = 0;
    for (int i = 0; i < strlen(input); i++) //
    {
        int ab = 1;
        int i_before = i;
        while ((input[i] == ' ' | input[i] == '\t' | input[i] == '\n'))
        {

            ab = 0;
            b = 0;
            i++;
        }
        if (i_before == 0)
            ab = 1;
        if (ab == 0)
        {
            a++;
            // ab = 1;
        }

        store1[a][b++] = input[i];
    }

    if (strcmp(store1[0], "echo") == 0) //ECHO start
    {
        echo_com(store1, a);
    }
    else if (strcmp(store1[0], "\0") == 0)
    {
        return;
    }
    else if (strcmp(store1[0], "exit") == 0)
    {
        exit(0);
    }
    else if (strcmp(store1[0], "cd") == 0) // CHECKING FOR "cd"
    {
        cd1(store1[1], initial_path);
    }
    else if (strcmp(store1[0], "pwd") == 0) // CHECKING FOR "pwd"
    {
        pwd1();
    }
    else if (strcmp(store1[0], "ls") == 0) // CHECKING FOR "ls and all tags"
    {

        Supporting_ls_tags(store1, a, initial_path);

    }                                         //end of ls
    else if (strcmp(store1[0], "pinfo") == 0) // PINFO
    {
        pinfo(store1);
    }
    else if (strcmp(store1[0], "history") == 0)
    {
        history(store1[1],initial_path);
    }
    else ///foreground and background
    {
        cool_commands(a, store1, initial_path);
    }
}

void get_curr_dir(char *initial_path)
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    int i;
    if (strstr(cwd, initial_path) == cwd)
    {
        printf("~");
        for (i = strlen(initial_path); i < strlen(cwd); i++)
        {
            if (cwd[i] != initial_path[i])
            {
                printf("%c", cwd[i]);
            }
        }
    }
    else
    {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("%s", cwd);
    }

    printf(">");
    return;
}
void Display_user_name(char *initial_path)
{
    struct utsname uname_pointer;
    uname(&uname_pointer);
    printf("<%s@%s", uname_pointer.nodename, getenv("USER"));
    get_curr_dir(initial_path);
    return;
}
int main(int argc, char **argv)
{
    char error_input[100];
    int flago = 0, count = 0;
    for (int i = strlen(argv[0]) - 1; i >= 0; i--)
    {
        if (argv[0][i] == '/' && flago == 0)
        {
            flago = 1;
            continue;
        }
        if (flago == 1)
        {
            error_input[count++] = argv[0][i];
        }
    }
    for (int i = 0; i < count / 2; i++)
    {
        char temp;
        temp = error_input[i];
        error_input[i] = error_input[count - i - 1];
        error_input[count - i - 1] = temp;
    }
    error_input[count] = '\0';
    // printf("%d === %s\n",count,error_input);
    getcwd(initial_path, sizeof(initial_path));
    strcat(initial_path, "/");
    strcat(initial_path, error_input);
    // printf("%s\n",initial_path);
    chdir(initial_path);
    getcwd(initial_path, sizeof(initial_path));

    while (1)
    {
        Display_user_name(initial_path);
        breaking_input_semi(argc, argv);
    }
    return 0;
}
