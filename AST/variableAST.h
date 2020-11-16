#pragma once
#ifndef variableAST_h
#define variableAST_h

#include "string"
#include "abstract.h"

class VariableExprAST : public ExprAST
{
    std::string Name;
public:
    VariableExprAST(const std::string &name) : Name(name) {}
};

#endif