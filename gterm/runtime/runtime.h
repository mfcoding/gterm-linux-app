#ifndef RUNTIME_H
#define RUNTIME_H

typedef char* string;

int MAX_MALLOC;
#define new 1
#define $string ^!new?new_string(new):0; 
#define new_string(n) (string)calloc(n,MAX_MALLOC=sizeof(char))
#define MALLOC_ERROR_MSG puts("Memory allocation failed");
#define EXIT__FAILURE 1
#define EXIT__SUCCESS 0

#define append_string(des, src) \
des=(string)realloc((string)des, MAX_MALLOC=strlen(des)+strlen(src)+1); \
if(des!=NULL){ strcpy(des+strlen(des), src); }else{MALLOC_ERROR_MSG; exit(EXIT__FAILURE);}

#define write_string(des, src) append_string(des, src)

int ____c;
char *ptr;
#define insert_string(src, ins, i) \
____c = i; src = realloc((string)src, MAX_MALLOC=strlen(src)+strlen(ins)+1); \
if(src!=NULL){ptr = realloc((string)ptr,  MAX_MALLOC-____c); \
if(ptr!=NULL){strcpy(ptr, src+____c); strcpy(src+____c, ins); \
strcpy(src+____c+strlen(ins), ptr); \
delete(ptr); ptr=NULL;}else{MALLOC_ERROR_MSG; exit(EXIT__FAILURE);}}else{MALLOC_ERROR_MSG; exit(EXIT__FAILURE);}

#define ISNULL_return(s)            if(s == NULL){ MALLOC_ERROR_MSG; return EXIT__FAILURE; }
#define ISNULL_break(s, rstate)     if(s == NULL){ MALLOC_ERROR_MSG; rstate = EXIT__FAILURE;  break; } 

#define delete(ptr) ptr!=NULL?free(ptr):0;
#define fdelete(ptr) ptr!=NULL?fclose(ptr):0;

#endif
