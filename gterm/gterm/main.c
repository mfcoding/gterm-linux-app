#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include "../runtime/runtime.h"


int isDirExists(const char *path);

int main(int argc, char *argv[])
{
    string gterm = new $string; 

    ISNULL_return(gterm);

    write_string(gterm, "/home/");
    struct passwd *uname = getpwuid(getuid());
    append_string(gterm, uname->pw_name);
    append_string(gterm, "/.gterm");


    if (!isDirExists(gterm))
    {
        system("cd ~;"
               "mkdir .gterm");
        if(!isDirExists(gterm))
        {
            printf("%s%s", "Program terminated: Can't create ", gterm);
            delete(gterm);
            return EXIT__FAILURE;
        }
    }

    append_string(gterm, "/configs.txt");

    FILE *gterm_filePtr = fopen(gterm, "r");
    if(gterm_filePtr == NULL)
    {
        gterm_filePtr = fopen(gterm, "w");
        if(gterm_filePtr == NULL)
        {
            printf("%s%s", "Program terminated: Can't create ", gterm);
            delete(gterm);
            return EXIT__FAILURE;
        }
        fprintf(gterm_filePtr, "%s", "gterm.executorMap\n{\n#Example\n\"c\" : \"gcc main.c\"\n\"cpp\" : \"g++ main.cpp\"\n}");
        printf("%s%s\n", "gterm Created ", gterm);
    }

    fdelete(gterm_filePtr);
    gterm_filePtr = NULL;

    if (argc == 1 && !strcmp(argv[0], "gterm"))
    {
        printf("%s\n", "Missing option");
        return EXIT__FAILURE;
    }

    if (argc == 3 && !strcmp(argv[2], "configs"))
    {
        insert_string(gterm, " ", 0);
        insert_string(gterm, argv[1], 0);
        system(gterm);
        return EXIT__SUCCESS;
    }

      
    gterm_filePtr = fopen(gterm, "r");
    if (gterm_filePtr == NULL)
    {
        printf("%s%s\n", "Program terminated: can't read ", gterm);
        delete(gterm);
        return EXIT__FAILURE;
    }

    delete(gterm);

    gterm = new $string;
    ISNULL_return(gterm);
    
    int ch = 0, i = 0, count_wspaces = 0, read = 0, stage = 1, return_state = EXIT__SUCCESS;
    char get__char[2] = {' ', '\0'};


    while (1)
    {
        ch = fgetc(gterm_filePtr);
        if (stage != 3)
        {
            if (ch == '#')
            {
                read = 1;
            }
            else if (ch == '\n' && read == 1)
            {
                read = 0;
            }
            else if(ch == ' ')
            {
            	ch = '\n';
            }
            else if (ch == EOF)
            {
                break;
            }
            if (read == 0 && ch != '\n')
            {
            	get__char[0] = ch;
                append_string(gterm, get__char);
                ++i;
            }
        }
        else
        {
            if (ch == '\"' || ch == '}' || ch == EOF)
            {
                stage = 4;
            }
            else
            {
                ch == '\n' ? ch = ' ' : 0;
                if (ch == ' ')
                {
                    ++count_wspaces;
                }
                else
                {
                    count_wspaces = 0;
                }
                if (count_wspaces < 2)
                {
                    get__char[0] = ch;
                    append_string(gterm, get__char);
                    ++i;
                }
            }
        }

        if (stage == 1 && !strcmp(gterm, "gterm.executorMap{"))
        {
            delete(gterm);
            gterm = new $string;
            ISNULL_break(gterm, return_state);
            i = 0;
            stage = 2;
        }

         /* *** C,C++ *** */

        if (!strcmp(argv[1], "c") || !strcmp(argv[1], "cpp"))
        {
            if (stage == 2)
            {
                if ((!strcmp(argv[1], "c")   && !strcmp(gterm, "\"c\":\"") && i == 5 )     || 
                    (!strcmp(argv[1], "cpp") && !strcmp(gterm, "\"cpp\":\"") && i == 7 ))
                {
                    i = 0;
                    stage = 3;
                    delete(gterm);
                    gterm = new $string;
                    ISNULL_break(gterm, return_state);
                }
                else
                {	
	            if((!strcmp(argv[1], "c") && i == 5) || (!strcmp(argv[1], "cpp") && i == 7))
                    {	
                        i = 0;
                        read = 1;
			delete(gterm);
                    	gterm = new $string;
                    	ISNULL_break(gterm, return_state);
                    }
                }
            }

            if (stage == 4)
            {
                if (argc == 2)
                {
                    printf("%s\n", "Missing option");
                    break;
                }
				
		printf("\033[0;34m%s\033[0m\n", gterm);

                if (argc == 3 && !strcmp(argv[2], "build"))
                {
                    system(gterm);
                }
                else if (argc == 3 && !strcmp(argv[2], "run"))
                {
                    system(gterm);
                    system("gnome-terminal -- gterm0 1a c run");
                }
                else if (argc == 4 && !strcmp(argv[2], "run"))
                {
                    system(gterm);
                    delete(gterm);
                    gterm = new $string;
                    ISNULL_break(gterm, return_state);
                    write_string(gterm, "gnome-terminal -- gterm0 1b c run .//"); 
                    append_string(gterm, argv[3]);
                    system(gterm);
                }
                else
                {
                    printf("%s\n", "Unknown option");
                }
                break;
            }
        }
        else
        {
            printf("%s\n", "Unknown option");
            break;
        }
    } // While loop ends here

    delete(gterm);
    fdelete(gterm_filePtr);

    return return_state;
}

int isDirExists(const char *path)
{
    struct stat stats;
    stat(path, &stats);
    // Check for file existence
    if (S_ISDIR(stats.st_mode))
    {
        return 1;
    }
    return 0;
}

