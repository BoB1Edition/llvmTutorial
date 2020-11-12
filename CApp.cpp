#include "CApp.h"

CApp::CApp(FILE *input, FILE *output) {
    this->input = input;
    this->output = output;
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
    /*if (isalpha(LastChar)) {
        this->IdentifierStr = LastChar;
        while (isalnum((LastChar = getchar())))
            IdentifierStr += LastChar;

        if (IdentifierStr == "def")
            return tok_def;
        if (IdentifierStr == "extern")
            return tok_extern;
        return tok_identifier;
    }*/
    return 0;
}
