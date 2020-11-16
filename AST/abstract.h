#pragma once
#ifndef abstract_h
#define abstract_h

#include <cstdio>

class ExprAST
{
public:
    virtual ~ExprAST() {}
    inline static ExprAST *Error(const char *Str)
    {
        fprintf(stderr, "Error: %s\n", Str);
        return 0;
    }
};

#endif