#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h> 
#include "../runtime/runtime.h"


char *fcontent(const char *fpath);
void run(const char *cmd, const char *fpath);

// ## main ##
int main(int argc, char *argv[])
{
    system("echo \"\033]0;gterm\a\"; printf \"\033[1A\"");
    
    string gterm0 = new $string; 

    if(gterm0 == NULL)
    {
        ____MALLOC_Err_msg;
        return EXIT__FAILURE;
    }
    
    write_string(gterm0, "/home/");
    struct passwd *uname = getpwuid(getuid());
    append_string(gterm0, uname->pw_name);
    append_string(gterm0, "/.gterm");
    append_string(gterm0, "/user_Exstat.txt"); 


    if(argc == 4 && !strcmp(argv[0], "gterm0") && !strcmp(argv[1], "1a") &&
                    !strcmp(argv[2], "c") && !strcmp(argv[3], "run"))
    {
        insert_string(gterm0, "./a.out; echo $? > ", 0);
        run(gterm0, gterm0+19);
    }
    else if(argc == 5 && !strcmp(argv[0], "gterm0") && !strcmp(argv[1], "1b") &&
                         !strcmp(argv[2], "c") && !strcmp(argv[3], "run"))
    {
        insert_string(gterm0, " echo $? > ", 0);
        insert_string(gterm0, ";", 0);
        insert_string(gterm0, argv[4], 0);
        run(gterm0, gterm0+strlen(argv[4])+12);
    }

    delete(gterm0);

    return EXIT__SUCCESS;
}


char *fcontent(const char *fpath)
{
    char *nProc = NULL;
    FILE *file = fopen(fpath, "r");
    if(file != NULL)
    {
        int c = 0;
        int ch = 0;
        do
        {
            ch = fgetc(file);
            c++;
        }while(ch != EOF);

        nProc = (char*)malloc((c+2) * sizeof(char));
        if(nProc != NULL)
        {
            rewind(file);
            fscanf(file, "%[^\n]%*c", nProc);
        }
        fclose(file);
    }
    return nProc;
}

void run(const char *cmd, const char *fpath)
{
    struct timespec start_t, end_t;
    double time_spent = 0.0;
    //Get current time
    clock_gettime (CLOCK_REALTIME, &start_t);


    system(cmd);


    //Get current time again
    clock_gettime (CLOCK_REALTIME, &end_t);
    //Calculate the delta between two timestamps (time spent)
    time_spent =1000000000*(end_t.tv_sec - start_t.tv_sec)+(end_t.tv_nsec - start_t.tv_nsec);
    //print time spent per second

    string fcontnt = fcontent(fpath);

    if(fcontnt != NULL)
    {
        printf("\n\nProcess returned (%s)      Execution time : %.3lf s\n\033[1;33mPress ENTER to continue.\n\033[0m", fcontnt, time_spent / 1000000000);
        delete(fcontnt);
    }
    else
    {
        printf("\n\nProcess returned (%c)      Execution time : %.3lf s\n\033[1;33mPress ENTER to continue.\n\033[0m", '-', time_spent / 1000000000);
    }

    while(getchar() != '\n');
}
