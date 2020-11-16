#pragma once
#ifndef CApp_h
#define CApp_h

#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>

#include "AST/abstract.h"


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
    int CurTok;
    int  inline getNextToken() { return CurTok = gettok() ; }
    std::map<char, int> BinopPrecedence;

public:
    CApp(FILE * input, FILE * output);
    char *LexicalAnalyzer();
    ~CApp();
    ExprAST *ParseNumberExpr();
    ExprAST *ParseParenExpr();
    ExprAST *ParseIdentifierExpr();
    ExprAST *ParsePrimary();
    inline ExprAST *Error(const char *Str) { return ExprAST::Error(Str); }
    int GetTokPrecedence();
    ExprAST *ParseExpression();
    ExprAST *ParseBinOpRHS(int ExprPrec, ExprAST *LHS);
};

#endif