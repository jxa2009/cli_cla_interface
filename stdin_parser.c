#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

#include "stdin_parser.h"

#define USE_STD_OUT 1

void stdin_get(char* argument)
{
    #ifdef USE_STD_OUT
        fprintf(stdout,"Filename: %s\n",argument);
    #else
        fprintf(stderr,"Filename: %s\n",argument);
    #endif
}

void stdin_put(char* argument)
{
    #ifdef USE_STD_OUT
        fprintf(stdout,"Filename: %s\n",argument);
    #else
        fprintf(stderr,"Filename: %s\n",argument);
    #endif
}

void stdin_ascii(void)
{
    #ifdef USE_STD_OUT
        fprintf(stdout,"Ascii mode now activated\n");
    #else
        fprintf(stderr,"Ascii mode now activated\n");
    #endif
    
}

void stdin_bin(void)
{
    #ifdef USE_STD_OUT
        fprintf(stdout,"Bin mode now activated\n");
    #else
        fprintf(stderr,"Bin mode now activated\n");
    #endif
    
}

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
#else
        fprintf(stderr, "\tRcvd> %s\n\n", input );
#endif
        
        token = strtok(input,commandSep);
        for(int i = 0 ; i < NUM_PARSER_FUNCTIONS;i++)
        {
            if (strncmp(token, ParserFunctions[i].function_name,strlen(token)) == 0 )
            {
                if( ParserFunctions[i].has_arg)
                {
                    token = strtok(NULL,commandSep);
                    ParserFunctions[i].respective_function(token);
                }
                else
                {
                    ParserFunctions[i].respective_function(NULL);
                }
                break;
            }
        }
    }
#ifdef USE_STD_OUT
    fprintf(stdout, "PROMPT> ");
#else
    fprintf(stderr, "PROMPT> ");
#endif
}

