#ifndef TOKENS_H
#define TOKENS_H

#include <string>
using namespace std;

const string alpha = "alphaTK";
const string digit = "digitTK";
const string keyword = "keywordTK";
const string identifier = "identifierTK";
const string oper = "operatorTK";
const string comment = "commentTK";
const string eof = "eofTK";

const int TOTALKEYWORDS = 13;
const int TOTALOPERATORS = 9;
const string keywordArray[TOTALKEYWORDS] = {"Again","If","Assign","Move","Show","Flip","Name","Home","Do","Spot","Place","Here","There"};
const char operatorArray[TOTALOPERATORS] = {'&', '+', '/', '%', '.','{','}','<', '-'};

struct Token{
    string tokenID;
    string tokenInstance;
    int lineNum;

    Token(string id, string instance, int num){
        tokenID = id;
        tokenInstance = instance;
        lineNum = num;
    };
};




#endif