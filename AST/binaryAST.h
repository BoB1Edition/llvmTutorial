#pragma once
#ifndef binaryAST_h
#define binaryAST_h

#include "abstract.h"

class BinaryExprAST : public ExprAST
{
    char Op;
    ExprAST *LHS, *RHS;

public:
    BinaryExprAST(char op, ExprAST *lhs, ExprAST *rhs)
        : Op(op), LHS(lhs), RHS(rhs) {}
};

#endif