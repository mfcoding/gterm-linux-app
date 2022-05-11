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

    if(gterm == NULL)
    {
        ____MALLOC_Err_msg;
        return EXIT__FAILURE;
    }

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
            printf("%s%s", "Program terminated: Can't create ", gterm_ptr);
            delete(gterm_ptr);
            return EXIT__FAILURE;
        }
        fprintf(gterm_filePtr, "%s", "gterm.executorMap\n{\n#Example\n\"c\" : \"gcc main.c\"\n\"cpp\" : \"g++ main.cpp\"}");
        printf("%s%s", "gterm Created ", gterm_ptr);
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
        insert_string(gterm_ptr, " ", 0);
        insert_string(gterm_ptr, argv[1], 0);
        system(gterm_ptr);
        return EXIT__SUCCESS;
    }

      
    gterm_filePtr = fopen(gterm_ptr, "r");
    if (gterm_filePtr == NULL)
    {
        printf("%s%s\n", "Program terminated: can't read ", gterm_ptr);
        delete(gterm_ptr);
        return EXIT__FAILURE;
    }

    delete(gterm_ptr);

    gterm_ptr = new $string;
    if(gterm_ptr == NULL)
    {
        ____MALLOC_Err_msg;
        return EXIT__FAILURE;
    }

    int ch = 0, i = 0, count_wspaces = 0, read = 0, stage = 1;
    char get__char[2] = {' ', '\0'};


    while (1)
    {
        ch = fgetc(gterm_filePtr);
        if (stage != 3)
        {
            if (ch == ' ' || ch == '#' || ch == '\n' || ch == EOF)
            {
                if (ch == '#')
                {
                    read = 1;
                }
                else if (ch == '\n')
                {
                    if(read == 1)
                    {
                        read = 0;
                    }
                }
                else if (ch == EOF)
                {
                    break;
                }
            }
            else
            {
                if (read == 0 && ch != '\n')
                {
                    get__char[0] = ch;
                    append_string(gterm_ptr, get__char);
                    ++i;
                }
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
                    append_string(gterm_ptr, get__char);
                    ++i;
                }
            }
        }

        if (stage == 1 && !strcmp(gterm_ptr, "gterm.executorMap{"))
        {
            delete(gterm_ptr);
            gterm_ptr = new $string;
            if(gterm_ptr == NULL)
            {
                ____MALLOC_Err_msg;
                return EXIT__FAILURE;
            }
            i = 0;
            stage = 2;
        }

        /* *** Clang *** */

        if (!strcmp(argv[1], "c"))
        {
            if (stage == 2 && i == 5)
            {
                if (!strcmp(gterm_ptr, "\"c\":\""))
                {
                    i = 0;
                    stage = 3;
                    delete(gterm_ptr);
                    gterm_ptr = new $string;
                    if(gterm == NULL)
                    {
                        ____MALLOC_Err_msg;
                        return EXIT__FAILURE;
                    }
                }
                else
                {
                    read = 1;
                    i = 0;
                }
            }

            if (stage == 4)
            {
                if (argc == 2)
                {
                    printf("%s\n", "Missing option");
                    break;
                }

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
                    if(gterm == NULL)
                    {
                        ____MALLOC_Err_msg;
                        return EXIT__FAILURE;
                    }
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

    return EXIT__SUCCESS;
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

