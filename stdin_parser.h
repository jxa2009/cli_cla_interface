#ifndef STDIN_PARSER_H
#define STDIN_PARSER_H

void stdin_get(char* argument);

void stdin_put(char* argument);

void stdin_ascii(void);

void stdin_bin(void);

void stdin_parse(char *token);

typedef struct ParserFunction_E
{
    char  *function_name;
    void (*respective_function)(char*);
    int     has_arg;

} ParserFunctionE;

const ParserFunctionE ParserFunctions[] =
{
    {"get",&stdin_get,1},
    {"put",&stdin_put,1},
    {"ascii",&stdin_ascii,0},
    {"bin",&stdin_bin,0},
};

const int NUM_PARSER_FUNCTIONS = sizeof(ParserFunctions) / sizeof(ParserFunctionE);
#endif