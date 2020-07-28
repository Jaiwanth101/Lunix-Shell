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
void history(char *input,char *initial_path)
{
    char * cooler=(char*)malloc(100);
    strcpy(cooler,initial_path);
    strcat (cooler,"/new.txt");
    FILE *fd2 = fopen(cooler, "r");
    int line_count = 0, num_lines, num_rows_to_read;
    while (feof(fd2) == 0)
        if (fgetc(fd2) == '\n')
            num_lines++;

    int number_temp = 0;
    if (input[0] == '\0')
    {
        if (num_lines <= 20)
            num_rows_to_read = num_lines;
        else
            num_rows_to_read = 20;
    }
    else
    {
        int i = 0;
        while (input[i] != '\0')
        {
            number_temp = number_temp * 10 + input[i++] - 48;
        }
        num_rows_to_read = number_temp;
    }
    fseek(fd2, 0, SEEK_SET);
    const int length = 100;
    char line[100];
    while (fgets(line, length, fd2) != NULL)
    {
        if (line_count >= num_lines - num_rows_to_read)
        {
            printf("%s", line);
        }
        line_count++;
    }
}