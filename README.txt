PLZ DONT GIVE COMMANDS BIGGER THAN 100 CHARACTERS

Commands to execute the Shell:
    $make
    $./a.out

# script.c
    ->creating a prompt()
        ->handled the error for execution of shell from different directory
        FUNCTION USED : Display_user_name();
        geting the user_id and the PC name ;
        and getting the cwd and handling '~';
    
    -> breaking the input using ';' as a delimiter;
        FUNCTION USED : breaking_semi_input();
        -> passing each part of the output to be excecuted 
            ->FUNCTION USED:breaking_input();
                ->code for ls,cd,pwd,echo,exit,history,opening bg & fg,pinfo.


#echo.c 
    ->(ONLY ASKED FOR ONE CASE);
    ->handled one case where there are no quotes!

#cd.c
    ->chdir() is used for traversing through directories.
    ->and handled the '~' case also.

#ls.c
    -> '~' case is handled for all the cases!!!;
    ->ls -l , ls -al, ls -a ,ls are the cases handled;
    ->if, else if conditions are used for handling teh above cases;
    ->For ls , ls -a : These are send to print_ls to traverse through the directory mentioned.

    -> for ls -l, ls -la(and substitutes): print_ls_l function is used to get the directories/files and then sent to the function print_permissions()

#fore_back.c
    ->commands(processes) have been excecuted using "execvp";
    ->distinguishing bg and fg process just by letting the parent to wait in fg;
    ->And signal() and waitpid() are used to print if a bg process ENDS!!

#pinfo.c
    ->Considering 2 conditions -> with and without arguement
        ->WITHOUT arguement : finding the pid of current process (./a.out)
            ->all the process info are in "/proc/pid/status" & "/proc/pid/exec"