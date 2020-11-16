#include <vector>
#include <ctype.h>

#include "CApp.h"
#include "AST/numberAST.h"
#include "AST/variableAST.h"
#include "AST/callAST.h"

CApp::CApp(FILE *input, FILE *output) {
    this->input = input;
    this->output = output;
    BinopPrecedence['<'] = 10;
    BinopPrecedence['='] = 10;
    BinopPrecedence['>'] = 10;
    BinopPrecedence['.'] = 10;
    BinopPrecedence['+'] = 20;
    BinopPrecedence['-'] = 20;
    BinopPrecedence['*'] = 40;
    BinopPrecedence['/'] = 40;
    BinopPrecedence['^'] = 50;
}

CApp::~CApp() {
    fclose(this->input);
    fclose(this->output);
}

char *CApp::LexicalAnalyzer() {
    this->gettok();
    return 0;
}

int CApp::gettok() {
    int LastChar = ' ';
    while (isspace(LastChar))
        LastChar = fgetc(input);
    if (isalpha(LastChar)) {
        this->IdentifierStr = LastChar;
        while (isalnum((LastChar = fgetc(input))))
            IdentifierStr += LastChar;

        if (IdentifierStr == "def")
            return tok_def;
        if (IdentifierStr == "extern")
            return tok_extern;
        return tok_identifier;
    }
    if (isdigit(LastChar) || LastChar == '.') { 
        std::string NumStr;
        do {
            NumStr += LastChar;
            LastChar = fgetc(input);
        } while (isdigit(LastChar) || LastChar == '.');

        NumVal = strtod(NumStr.c_str(), 0);
        return tok_number;
    }
    if (LastChar == '#')
    {
        // Комментарий до конца строки.
        do
            LastChar = fgetc(input);
        while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF)
            return gettok();
    }
    if (LastChar == EOF)
        return tok_eof;

    // В противном случае просто возвращаем символ как значение ASCII
    int ThisChar = LastChar;
    LastChar = fgetc(input);
    return ThisChar;
}

ExprAST *CApp::ParseNumberExpr() {
    ExprAST *Result = new NumberExprAST(NumVal);
    getNextToken(); // получаем число
    return Result;
}

ExprAST *CApp::ParseParenExpr()
{
    getNextToken(); // получаем (.
    ExprAST *V = ParseExpression();
    if (!V)
        return 0;

    if (CurTok != ')')
        return Error("expected ')'");
    getNextToken(); // получаем ).
    return V;
}

ExprAST *CApp::ParseIdentifierExpr()
{
    std::string IdName = IdentifierStr;

    getNextToken(); // получаем идентификатор.

    if (CurTok != '(') // Ссылка на переменную.
        return new VariableExprAST(IdName);

    // Вызов функции.
    getNextToken(); // получаем (
    std::vector<ExprAST *> Args;
    if (CurTok != ')')
    {
        while (1)
        {
            ExprAST *Arg = ParseExpression();
            if (!Arg)
                return 0;
            Args.push_back(Arg);

            if (CurTok == ')')
                break;

            if (CurTok != ',')
                return Error("Expected ')' or ',' in argument list");
            getNextToken();
        }
    }

    // получаем ')'.
    getNextToken();

    return new CallExprAST(IdName, Args);
}

ExprAST *CApp::ParsePrimary()
{
    switch (CurTok)
    {
    default:
        return Error("unknown token when expecting an expression");
    case tok_identifier:
        return ParseIdentifierExpr();
    case tok_number:
        return ParseNumberExpr();
    case '(':
        return ParseParenExpr();
    }
}

int CApp::GetTokPrecedence() {
    if (!isascii(CurTok))
        return -1;

    // Удостоверимся, что это объявленный бинарный оператор.
    int TokPrec = BinopPrecedence[CurTok];
    if (TokPrec <= 0)
        return -1;
    return TokPrec;
}

ExprAST *CApp::ParseExpression()
{
    ExprAST *LHS = ParsePrimary();
    if (!LHS)
        return 0;

    return ParseBinOpRHS(0, LHS);
}

ExprAST *CApp::ParseBinOpRHS(int ExprPrec, ExprAST *LHS)
{
    // Если это бинарный оператор, получаем его приоритет
    while (1)
    {
        int TokPrec = GetTokPrecedence();

        // Если этот бинарный оператор связывает выражения по крайней мере так же,
        // как текущий, то используем его
        if (TokPrec < ExprPrec)
            return LHS;
        int BinOp = CurTok;
        getNextToken(); // получить бинарный оператор

        // Разобрать первичное выражение после бинарного оператора
        ExprAST *RHS = ParsePrimary();
        if (!RHS)
            return 0;
        int NextPrec = GetTokPrecedence();
        if (TokPrec < NextPrec)
        {
        }
        LHS = new BinaryExprAST(BinOp, LHS, RHS);
    }
}