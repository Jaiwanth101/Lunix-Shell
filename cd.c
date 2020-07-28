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
void cd1(char *input,char * initial_path )
{
    char temp[100];
    strcpy(temp, initial_path);
    if (strcmp(input, "\0") == 0)
    {
        strcpy(input, initial_path);
        if (chdir(input) != 0)
        {
            perror("");
            return;
        }
    }
    else if (input[0] == '~')
    {

        memmove(input, input + 1, strlen(input));
        strcat(temp, input);

        if (chdir(temp) != 0)
        {
            perror("");
            return;
        }
    }
    else if (chdir(input) != 0)
    {
        perror("");
        return;
    }
}