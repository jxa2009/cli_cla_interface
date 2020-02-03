#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

#define USE_STD_OUT 1

int main(int argc, char *argv[]) {
    int rc = 0;
    long psize = sysconf(_SC_PAGESIZE);
    
    char input[psize];

    char commandSep[] = " ";
    char *token;
#ifdef USE_STD_OUT
    fprintf(stdout, "PROMPT> " );
#else
    fprintf(stderr, "PROMPT> " );
#endif
    // fgets is being used because it checks for array bound
    while ( fgets( input, psize, stdin) != NULL )
    {
#ifdef USE_STD_OUT
        fprintf(stdout, "\tRcvd> %s\n\n", input );
        fprintf(stdout, "PROMTPT> ");
#else
        fprintf(stderr, "\tRcvd> %s\n\n", input );
        fprintf(stderr, "PROMTPT> ");
#endif

        token = strtok(input,commandSep);
        printf("token: \"%s\"",token);
        if (strncmp(token,"get",sizeof(token)) == 0)
        {
            fprintf(stdout, "received get\n");
        }
        else
        {
            fprintf(stdout,"not get\n");
        }
        

    }
}
