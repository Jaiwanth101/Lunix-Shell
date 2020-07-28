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
// int flagand[100];
// void Display_user_name(char *);
char a[100];
int back_names[100][100];
int pids_storing[100];
int coca_cola = 0;
    int pid = 0;
 pid_t podrick;
char *global;
void Display_user_name(char *initial_path);
void olaola(int cola)
{
    pid_t podrick1;
    podrick1 = waitpid(-1, &pid, WNOHANG);
    // printf("podrick=%d\n", podrick1);
    for (int i = 0; i < coca_cola; i++)
    {
        if (pids_storing[i] == podrick1 && podrick1!=0)
        {
            // pids_storing[i] = -10;
            fprintf(stderr,"%s with ", back_names[i]);
            fprintf(stderr,"pid %d ", podrick1);
            if (WIFEXITED(pid))
                fprintf(stderr,"exited noramlly\n");
            else
            {
                fprintf(stderr,"exited forcefully\n");
            }
            Display_user_name(global);
            fflush(stdout);
        }
    }
}
void cool_commands(int a, char store1[100][100], char *initial_path) //execvp , backgrund nd foreground
{
    global = (char *)malloc(100);
    strcpy(global, initial_path);
    int stato = 0;
    char **temp = (char **)malloc(sizeof(char *) * (a + 2));
    for (int i = 0; i < (a + 1); i++)
    {
        temp[i] = (char *)malloc(100);
        strcpy(temp[i], store1[i]);
    }
    if (strcmp(temp[a - 1], "&") != 0)
    {
        // pid_t podrick1;
        temp[a] = NULL;
        if ((podrick = fork()) < 0)
        {
            perror("");
            return;
        }
        else if (podrick== 0)
        {
            if (execvp(temp[0], temp) != 0)
            {
                printf("Command not found\n");
                return;
            }
        }
        else
        {
            while(waitpid(-1, &stato, 0)!=podrick);
            // printf("podrick1=%d\n", podrick);
        }
    }
    else
    {
        // printf("\nbgm\n");
        // pid_t podrick;
        temp[a - 1] = NULL;
        if ((podrick = fork()) < 0)
        {
            perror("");
            return;
        }
        if (podrick == 0)
        {
            if (execvp(temp[0], temp) < 0)
            {
                printf("Command not found\n");
                return;
            }
        }
        else
        {
            
            pids_storing[coca_cola] = podrick;
            strcpy(back_names[coca_cola++], store1[0]);
            // flagand[coca_cola++] = 1;
            // printf("pids=%d\n",pids_storing[coca_cola])
        }
        signal(SIGCHLD, olaola);
    }
}