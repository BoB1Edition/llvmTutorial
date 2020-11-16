#pragma once
#ifndef callAST_h
#define callAST_h

#include "abstract.h"
#include <string>
#include <vector>

class CallExprAST : public ExprAST
{
    std::string Callee;
    std::vector<ExprAST *> Args;

public:
    CallExprAST(const std::string &callee, std::vector<ExprAST *> &args)
        : Callee(callee), Args(args) {}
};

#endif