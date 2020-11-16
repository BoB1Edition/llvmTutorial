#pragma once
#ifndef numberAST_h
#define numberAST_h

#include "abstract.h"

class NumberExprAST : public ExprAST
{
    double Val;
public:
    NumberExprAST(double val) : Val(val) {}
};

#endif