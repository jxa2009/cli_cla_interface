#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>


#define TRUE (1)
#define FALSE (0)

#define MAX_STRING_LENGTH (255)

//EXIT CODES
#define IP_FAIL (-1)
/*
    Description: Determines if a string consists of just numbers
    Params: numString [in] : A string that SHOULD consists of numbers
    Returns: 1 if the string consists of just numbers or 0 if it contains non-numbers
*/
int isDigit(char* numString)
{
    for (int i = 0; strlen(numString); i++)
    {
        if (*numString >= '0' && *numString <= '9')
        {
            numString++;
        }
        else
        {
            return FALSE;
        }
    }
    return TRUE;
}

/*
    Description: Parses a string that should be formatted like an ip address: [0-255].[0-255].[0-255].[0-255]
    Params: ipString [in] : A string that should be formatted like an ip address
    Returns: 1 if successfully parsed, 0 if failure
*/
unsigned int ipParser(char* ipString)
{
    unsigned int ipAddress = 0;
    int subAddress = 0;

    char* separator = ".";

    char* ipPtr = strtok(ipString, separator);
    
    int ipSize = 0;
    // Should exit while loop when ipPtr points to NULL
    while (ipPtr)
    {
        

        if (!isDigit(ipPtr))
        {
            fprintf(stderr,"Exiting due to invalid IP address input.");
            exit(IP_FAIL);
        }

        subAddress = atoi(ipPtr);

        if (subAddress > 255 || subAddress < 0)
        {
            fprintf(stderr,"Exiting due to invalid IP address input.");
            exit(IP_FAIL);
        }
        else
        {
            ipAddress = ipAddress | subAddress;
            ipSize++;
            if (ipSize < 4)
            {
                ipAddress = ipAddress << 8;            
            }
            ipPtr = strtok(NULL, separator);
        }
        
    }

    return ipAddress;
}

int main(int argc, char *argv[])
{
    int rc = 0;
    int i = 0;
    
    /* getopt_long stores the option index here. */
    int option_index = 0;

    char *getoptOptions = "hi:p:u:w:";

    /* This contains the long command line parameter list, it should mostly match the short list */
    struct option long_options[] =
    {
        {"ip",       required_argument,    0, 'i'},
        {"port",     required_argument,    0, 'p'},
        {"username", required_argument,    0, 'u'},
        {"user",     required_argument,    0, 'u'},
        {"password", required_argument,    0, 'w'},
        {0,0,0,0}
    };

     long psize = sysconf(_SC_PAGE_SIZE);

    /* Disable STDERR from getopt()*/
    opterr = 0;

    
    /* Exits if maximum amount of arguments is exceeded */
    if (argc > sysconf(_SC_ARG_MAX))
    {
        fprintf(stderr,"too many args\n");
        exit(1);
    }

    /* Verifies that each argument is not too large */
    for (i = 0; i < argc; i++)
    {
        if( strlen(argv[i]) > psize )
        {
            fprintf(stderr, "Arg %d too long \n",i);
        }
    }

    /* Optind is the index of the next element to be processed in argv */
    fprintf(stderr, "Getopt starts at %02X\n", optind);

    char *username;
    char *password;
    unsigned int ip;
    unsigned int port; // max value is 65535 

    while ((rc = getopt_long_only(argc, argv, getoptOptions, long_options, &option_index)) != -1 )
    {
        fprintf(stderr, "Option: %02X is at RC=%02X\n", optind, rc);
        switch(rc)
        {
            /* Help */
            /*case 'h':
                printf("Usage: blahblah");
                break;*/
            case 'i':
                fprintf(stderr,"Inputted ip string was: %s\n",optarg);
                ip = ipParser(optarg);
                printf("Inputted ip stored as: %u.%u.%u.%u\n",(ip >> 24) & 0xFF, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
                break;
            case 'p':

                if ((atol(optarg) > 65535) || (atol(optarg)) < 0  )
                {
                    printf("Inputted port value: %lu\n",atol(optarg));
                    printf("Port number must be any value between 0 and 65535.\n");
                    break;
                }
                else
                {
                    port = (unsigned int) (atol(optarg));
                    printf("Port number is: %d\n",port);
                }
                
                break;
            case 'u':
                printf("Username option, optarg: %s. \n",optarg);
                username = optarg;
                printf("Username is: %s\n",username);
                break;
            case 'w':
                password = optarg;
                printf("Password is: %s",password);
                break;

            case '?':

            default:
                printf("Internal error: undefined option %0xX\n",rc);
                exit(-1); // create defines for this later.
        }
    }
    printf("Next arg[%d]: %s\n",optind, argv[optind]);
    return 0;
}
