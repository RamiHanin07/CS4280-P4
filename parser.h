#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include "tokens.h"

using namespace std;

void parse(string fileName);

void error(Token token, int indents);

void bnfA(vector<Token> &tokens, int indents);

void bnfS(vector<Token> &tokens, int indents);

void bnfR(vector<Token> &tokens, int indents);

bool bnfE(vector<Token> &tokens, int indents);

void bnfB(vector<Token> &tokens, int indents);

void bnfC(vector<Token> &tokens, int indents);

bool bnfD(vector<Token> &tokens, int indents);

bool bnfG(vector<Token> &tokens, int indents);

void bnfT(vector<Token> &tokens, int indents);

bool bnfV(vector<Token> &tokens, int indents);

bool bnfH(vector<Token> &tokens, int indents);

bool bnfJ(vector<Token> &tokens, int indents);

bool bnfK(vector<Token> &tokens, int indents);

bool bnfL(vector<Token> &tokens, int indents);

void bnfZ(vector<Token> &tokens, int indents);

bool bnfF(vector<Token> &tokens, int indents);

void bnfM(vector<Token> &tokens, int indents);

void bnfW(vector<Token> &tokens, int indents);

void bnfN(vector<Token> &tokens, int indents);
void bnfY(vector<Token> &tokens, int indents);


#endif