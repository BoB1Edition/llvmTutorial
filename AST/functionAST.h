#pragma once
#ifndef functionAST_h
#define functionAST_h

#include "abstract.h"
#include "prototypeAST.h"

class FunctionAST
{
    PrototypeAST *Proto;
    ExprAST *Body;

public:
    FunctionAST(PrototypeAST *proto, ExprAST *body)
        : Proto(proto), Body(body) {}
    static inline FunctionAST *ErrorF(const char *Str)
    {
        ExprAST::Error(Str);
        return 0;
    }
};

#endif