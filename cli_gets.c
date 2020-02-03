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

#ifdef USE_STD_OUT
  fprintf(stdout, "PROMPT> " );
#else
  fprintf(stderr, "PROMPT> " );
#endif
  while ( fgets( input, psize, stdin) != NULL )
  {
#ifdef USE_STD_OUT
    fprintf(stdout, "\tRcvd> %s\n\n", input );
    fprintf(stdout, "PROMTPT> ");
#else
    fprintf(stderr, "\tRcvd> %s\n\n", input );
    fprintf(stderr, "PROMTPT> ");
#endif
  }
}
