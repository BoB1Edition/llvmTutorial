#pragma once
#ifndef prototypeAST_h
#define prototypeAST_h

#include "abstract.h"

#include <string>
#include <vector>

class PrototypeAST
{
    std::string Name;
    std::vector<std::string> Args;

public:
    PrototypeAST(const std::string &name, const std::vector<std::string> &args)
        : Name(name), Args(args) {}
    static inline PrototypeAST *ErrorP(const char *Str)
    {
        ExprAST::Error(Str);
        return 0;
    }
};

#endif