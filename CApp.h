#pragma once
#ifndef CApp_h
#define CApp_h

#include <cstdio>
#include <cstdlib>
#include <string>


class CApp
{
private:
    enum Token
    {
        tok_eof = -1,
        tok_def = -2,
        tok_extern = -3,
        tok_identifier = -4,
        tok_number = -5,
    };
    std::string IdentifierStr;
    double NumVal;
    FILE *input, *output;
    int gettok();
public:
    CApp(FILE * input, FILE * output);
    char *LexicalAnalyzer();
    ~CApp();
};

#endif