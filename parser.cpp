
#include <iostream>
#include <fstream>
#include <sstream>

#include "parser.h"
#include "scanner.h"
#include "tokens.h"
#include <vector>
#include <string>

const char SPACES = ' ';

void parse(string fileName){
    cout << "parser()" << endl;
    ifstream file(fileName);
    string line;
    string word;
    vector<Token> tokens;
    
    

    //Parse all tokens of the file into a single vector in order.
    int lineNum = 0;
    while(getline(file,line)){
        istringstream stream(line);
        while(stream >> word){
            Token currentToken = scanner(word, lineNum);
            tokens.push_back(currentToken);
        }
        lineNum++;
    }
    tokens.push_back(Token("eofTK","eof",lineNum));

    for(int i = 0; i < tokens.size(); i++){
        cout << tokens[i].tokenID << " : " << tokens[i].tokenInstance << " : " << tokens[i].lineNum << endl;
    }

    cout << endl;
    cout << endl;

    //Start actually dealing with the grammar.
    bnfS(tokens, 2);

}
void error(Token token, int indents){
    const char SPACES = ' ';
    cout << string(indents, SPACES) << "SCANNER ERROR: Token: " << token.tokenID << " Instance: " << token.tokenInstance << " Line Number: " << token.lineNum << endl;
} 

void bnfA(vector <Token> &tokens, int indents){
    cout << string(indents-2, SPACES) << "A" << endl;
    if(tokens[0].tokenID == "keywordTK"){
        if(tokens[0].tokenInstance == "Name"){
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
        }
        else{
            error(tokens[0], indents);
            return;
            //cout << string(indents, SPACES) << "SCANNER ERROR: Token: " << tokens[0].tokenID << " Instance: " << tokens[0].tokenInstance << " Line Number: " << tokens[0].lineNum << endl;
        }
    }
    else{
        error(tokens[0], indents);
        return;
        //cout << string(indents, SPACES) << "SCANNER ERROR: Token: " << tokens[0].tokenID << " Instance: " << tokens[0].tokenInstance << " Line Number: " << tokens[0].lineNum << endl;
    }
    if(tokens[0].tokenID == "alphaTK"){
        cout << string(indents, SPACES) << "Identifier " << tokens[0].tokenInstance << endl;
        tokens.erase(tokens.begin());
    }
    else{
        error(tokens[0], indents);
        return;
        //cout << string(indents, SPACES) << "SCANNER ERROR: Token: " << tokens[0].tokenID << " Instance: " << tokens[0].tokenInstance << " Line Number: " << tokens[0].lineNum << endl;
    }
    indents = indents-2;
    return;
}
void bnfM(vector <Token> &tokens, int indents){
    cout << string(indents-2, SPACES) << "M" << endl;
    if(tokens[0].tokenID == "keywordTK"){
        if(tokens[0].tokenInstance == "If"){
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
            if(tokens[0].tokenID == "alphaTK"){
                cout << string(indents, SPACES) << "Identifier " << tokens[0].tokenInstance << endl;
                tokens.erase(tokens.begin());
                indents+2;
                bnfT(tokens, indents);
                bnfW(tokens, indents);
                bool dResult = bnfD(tokens, indents);
                if(dResult == false){
                    error(tokens[0], indents);
                    return;
                }
                indents-2;
                if(tokens[0].tokenID == "operatorTK"){
                    if(tokens[0].tokenInstance == "}"){
                        cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
                        tokens.erase(tokens.begin());
                    }
                    else{
                        error(tokens[0], indents);
                        return;
                    }
                }
                else{
                    error(tokens[0], indents);
                    return;
                }
            }
            else{
                error(tokens[0], indents);
                return;
            }
            
        }
        else if(tokens[0].tokenInstance == "Do"){
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
            if(tokens[0].tokenID == "keywordTK"){
                if(tokens[0].tokenInstance == "Again"){
                    cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
                    tokens.erase(tokens.begin());

                    indents+2;
                    //bnfD(tokens,indents);
                    //bnfT(tokens, indents);
                    //bnfW(tokens, indents);
                    indents-2;
                    if(tokens[0].tokenID == "operatorTK"){
                        if(tokens[0].tokenInstance == "}"){
                            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
                            tokens.erase(tokens.begin());
                        }
                        else{
                            error(tokens[0], indents);
                            return;
                        }
                    }
                    else{
                        error(tokens[0], indents);
                    }

                }
                else{
                    error(tokens[0], indents);
                    return;
                }
            }
            else{
                error(tokens[0], indents);
                return;
            }
        }
        else{
            error(tokens[0],indents);
            return;
        }
    }
    else{
        error(tokens[0], indents);
        return;
        //cout << string(indents, SPACES) << "SCANNER ERROR: Token: " << tokens[0].tokenID << " Instance: " << tokens[0].tokenInstance << " Line Number: " << tokens[0].lineNum << endl;
    }
}
bool bnfF(vector <Token> &tokens, int indents){
    bool worked = false;
    if(tokens[0].tokenID == "operatorTK"){
        if(tokens[0].tokenInstance == "{"){
            cout << string(indents-2, SPACES) << "F" << endl;
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
            worked = true;
            indents+2;
            bnfM(tokens, indents);
        }
        else{
            worked = false;
        }
    }
    return worked;
}

bool bnfG(vector <Token> &tokens, int indents){
    bool worked = false;
    cout << string(indents-2, SPACES) << "F" << endl;
    if(tokens[0].tokenID == "keywordTK"){
        if(tokens[0].tokenInstance == "Here"){
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
            worked = true;
        }
        else{
            //error(tokens[0], indents);
            worked = false;
            return worked;
        }
    }else{
        //error(tokens[0], indents);
        worked = false;
        return false;
    }
    if(tokens[0].tokenID == "digitTK"){
        cout << string(indents, SPACES) << "Number " << tokens[0].tokenInstance << endl;
        tokens.erase(tokens.begin());
    }
    else{
        error(tokens[0], indents);
        return false;
    }
    if(tokens[0].tokenID == "keywordTK"){
        if(tokens[0].tokenInstance == "There"){
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
        }
        else{
            error(tokens[0], indents);
            return false;
        }
    }
    else{
        error(tokens[0], indents);
        return false;
    }
    return worked;
}
void bnfC(vector < Token> &tokens, int indents){
    cout << string(indents-2, SPACES) << "C" << endl;
    bool cResult = bnfF(tokens, indents);
    bool gResult = false;
    if(cResult == true){
        //awesome it was in there
    }
    else{
        gResult = bnfG(tokens, indents);
        if(gResult == false)
            error(tokens[0], indents);
    }
    return;
}

bool bnfH(vector <Token> &tokens, int indents){
    bool worked = false;
    cout << string(indents-2, SPACES) << "H" << endl;
    if(tokens[0].tokenID == "operatorTK"){
        if(tokens[0].tokenInstance == "/"){
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
            worked = true;
            indents+2;
            bnfZ(tokens, indents);
        }
    }
    return worked;
}

bool bnfJ(vector <Token> &tokens, int indents){
    bool worked = false;
    if(tokens[0].tokenID == "keywordTK"){
        if(tokens[0].tokenInstance == "Assign"){
            cout << string(indents-2, SPACES) << "J" << endl;
            worked = true;
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
        }
        else{
            return worked;
        }
    }else{
        return worked;
    }

    if(tokens[0].tokenID == "alphaTK"){
        cout << string(indents, SPACES) << "Identifier " << tokens[0].tokenInstance << endl;
        tokens.erase(tokens.begin());
    }
    else{
        error(tokens[0], indents);
        return worked;
    }
    indents+2;
    bool dResult = bnfD(tokens, indents);
    if(dResult == false){
        error(tokens[0], indents);
        return worked;
    }


}

bool bnfK(vector <Token> &tokens, int indents){
    bool worked = false;
    if(tokens[0].tokenID == "keywordTK"){
        if(tokens[0].tokenInstance == "Spot"){
            cout << string(indents-2, SPACES) << "K" << endl;
            worked = true;
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
            if(tokens[0].tokenID == "digitTK"){
                cout << string(indents, SPACES) << "Number " << tokens[0].tokenInstance << endl;
                tokens.erase(tokens.begin());
                if(tokens[0].tokenID == "keywordTK"){
                    if(tokens[0].tokenInstance == "Show"){
                        cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
                        tokens.erase(tokens.begin());
                        if(tokens[0].tokenID == "digitTK"){
                            cout << string(indents, SPACES) << "Number " << tokens[0].tokenInstance << endl;
                            tokens.erase(tokens.begin());
                        }
                        else{
                            error(tokens[0], indents);
                        }
                    }
                    else{
                        error(tokens[0], indents);
                    }
                }
                else{
                    error(tokens[0], indents);
                }
            }
            else{
                error(tokens[0], indents);
                return worked;
            }
        }
        else if(tokens[0].tokenInstance == "Move"){
            cout << string(indents-2, SPACES) << "K" << endl;
            worked = true;
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
            if(tokens[0].tokenID == "alphaTK"){
                cout << string(indents, SPACES) << "Identifier " << tokens[0].tokenInstance << endl;
                tokens.erase(tokens.begin());
                if(tokens[0].tokenID == "keywordTK"){
                    if(tokens[0].tokenInstance == "Show"){
                        cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
                        tokens.erase(tokens.begin());
                        if(tokens[0].tokenID == "alphaTK"){
                            cout << string(indents, SPACES) << "Identifier " << tokens[0].tokenInstance << endl;
                            tokens.erase(tokens.begin());
                        }
                        else{
                            error(tokens[0], indents);
                            return worked;
                        }
                    }
                    else{
                        error(tokens[0], indents);
                        return worked;
                    }
                }
                else{
                    error(tokens[0], indents);
                    return worked;
                }
            }
        }
        else{
            worked = false;
            return worked;
        }
    }
    else{
        worked = false;
        return worked;
    }

    return worked;
}

bool bnfL(vector <Token> &tokens, int indents){
    
    bool worked = false;
    if(tokens[0].tokenID == "keywordTK"){
        if(tokens[0].tokenInstance == "Flip"){
            cout << string(indents-2, SPACES) << "L" << endl;
            worked = true;
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
            if(tokens[0].tokenID == "alphaTK"){
                cout << string(indents, SPACES) << "Identifier " << tokens[0].tokenInstance << endl;
                tokens.erase(tokens.begin());
            }
            else{
                error(tokens[0], indents);
                return worked;
            }
        }
        else{
            worked = false;
            return worked;
        }
    }
    else{
        worked = false;
        return worked;
    }

    return worked;
}


bool bnfE(vector <Token> &tokens, int indents){
    bool worked = true;
    if(tokens[0].tokenID == "keywordTK"){
        if(tokens[0].tokenInstance == "Show"){
            cout << string(indents-2, SPACES) << "E" << endl;
            worked = true;
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
        }
        else{
            worked = false;
            return worked;
            //cout << string(indents, SPACES) << "SCANNER ERROR: Token: " << tokens[0].tokenID << " Instance: " << tokens[0].tokenInstance << " Line Number: " << tokens[0].lineNum << endl;
        }
    }
    else{
        worked = false;
        return worked;
        //cout << string(indents, SPACES) << "SCANNER ERROR: Token: " << tokens[0].tokenID << " Instance: " << tokens[0].tokenInstance << " Line Number: " << tokens[0].lineNum << endl;
    }
    if(tokens[0].tokenID == "alphaTK"){
        cout << string(indents, SPACES) << "Identifier " << tokens[0].tokenInstance << endl;
        tokens.erase(tokens.begin());
    }
    else{
        error(tokens[0], indents);
        return worked;
        //cout << string(indents, SPACES) << "SCANNER ERROR: Token: " << tokens[0].tokenID << " Instance: " << tokens[0].tokenInstance << " Line Number: " << tokens[0].lineNum << endl;
    }
    indents = indents-2;
    return worked;
}

bool bnfD(vector <Token> &tokens, int indents){
    cout << string(indents-2, SPACES) << "D" << endl;
    bool worked = false;
    bool hResult;
    bool jResult;
    bool kResult;
    bool lResult;
    bool eResult;
    bool fResult;
    indents+2;
    hResult = bnfH(tokens, indents);
    //cout << string(indents-2, SPACES) << "hResult:" << hResult << endl;
    if(hResult == false){
        jResult = bnfJ(tokens, indents);
        if(jResult == false){
            kResult = bnfK(tokens, indents);
            if(kResult == false){
                lResult = bnfL(tokens, indents);
                if(lResult == false){
                    eResult = bnfE(tokens, indents);
                    if(eResult == false){
                        fResult = bnfF(tokens, indents);
                        if(fResult == false){
                            //error(tokens[0], indents);
                        }
                        else{
                            worked = true;
                        }
                    }
                    else{
                        worked = true;
                    }
                }
                else{
                    worked = true;
                }
            }
            else{
                worked = true;
            }
        }
        else{
            worked = true;
        }
    }
    else{
        worked = true;
    }

    return worked;
}

void bnfB(vector <Token> &tokens, int indents){
    cout << string(indents-2, SPACES) << "B" << endl;
    bool dResult = false;
    if((tokens[0].tokenID == "operatorTK") && (tokens[0].tokenInstance == ".")){
        //cout << string(indents-2, SPACES) << "Enter Op 1" << endl;
        if(tokens[0].tokenInstance == "."){
            //cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
        }
        else{
            cout << string(indents-2, SPACES) << "ReADING /" << endl;
            error(tokens[0], indents);
            return;
            //cout << string(indents, SPACES) << "SCANNER ERROR: Token: " << tokens[0].tokenID << " Instance: " << tokens[0].tokenInstance << " Line Number: " << tokens[0].lineNum << endl;
        }
        indents+2;
        bnfC(tokens, indents);
        if(tokens[0].tokenID == "operatorTK"){
            //cout << string(indents-2, SPACES) << "Enter Op 2" << endl;
            if(tokens[0].tokenInstance == "."){
                cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
                tokens.erase(tokens.begin());
            }
            else{
                error(tokens[0], indents);
                return;
                //cout << string(indents, SPACES) << "SCANNER ERROR: Token: " << tokens[0].tokenID << " Instance: " << tokens[0].tokenInstance << " Line Number: " << tokens[0].lineNum << endl;
            }
        }
        else{
            //cout << string(indents-2, SPACES) << "Outside Error" << endl;
            error(tokens[0], indents);
            return;
            //cout << string(indents, SPACES) << "SCANNER ERROR: Token: " << tokens[0].tokenID << " Instance: " << tokens[0].tokenInstance << " Line Number: " << tokens[0].lineNum << endl;
        }

        indents+2;
        bnfB(tokens,indents);
    }
    else{
        indents+2;
        cout << string(indents, SPACES) << "inside bnfD check" << endl;
        Token emptyCheck = Token(tokens[0].tokenID, tokens[0].tokenInstance, tokens[0].lineNum);
        dResult = bnfD(tokens, indents);
        if(dResult == false){
            //cout << string(indents-2, SPACES) << "None Worked" << endl;
            //cout << string(indents-2, SPACES) << "emptyCheck tokenID: " << emptyCheck.tokenID << " , tokenInstance: " << emptyCheck.tokenInstance << " ; lineNum: " << emptyCheck.lineNum << endl;
            //cout << string(indents-2, SPACES) << "tokens[0].tokenID: " << tokens[0].tokenID << " , tokenInstance: " << tokens[0].tokenInstance << " ; lineNum: " << tokens[0].lineNum << endl;
            if(tokens[0].tokenID == emptyCheck.tokenID){
                //cout << string(indents-2, SPACES) << "ID Match" << endl;
                if(tokens[0].tokenInstance == emptyCheck.tokenInstance){
                    //cout << string(indents-2, SPACES) << "Instance Match" << endl;
                    if(tokens[0].lineNum == emptyCheck.lineNum){
                        //cout << string(indents-2, SPACES) << "Line Match" << endl;
                        cout << string(indents, SPACES) << "Empty" << endl;
                    }
                }
            }
        }
        else{
            //cout << "returning" << endl;
        }
    indents = indents-2;
    return;
    }
}

void bnfR(vector <Token> &tokens, int indents){
    cout << string(indents-2, SPACES) << "R" << endl;
    if(tokens[0].tokenID == "keywordTK"){
        if(tokens[0].tokenInstance == "Place"){
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
        }
        else{
            error(tokens[0], indents);
            return;
            //cout << string(indents, SPACES) << "SCANNER ERROR: Token: " << tokens[0].tokenID << " Instance: " << tokens[0].tokenInstance << " Line Number: " << tokens[0].lineNum << endl;
        }
    }
    else{
        error(tokens[0], indents);
        return;
        //cout << string(indents, SPACES) << "SCANNER ERROR: Token: " << tokens[0].tokenID << " Instance: " << tokens[0].tokenInstance << " Line Number: " << tokens[0].lineNum << endl;
    }
    indents = indents+2;
    bnfA(tokens, indents);
    bnfB(tokens, indents);
    indents = indents-2;
    if(tokens[0].tokenID == "keywordTK"){
        if(tokens[0].tokenInstance == "Home"){
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
        }
        else{
            error(tokens[0], indents);
            return;
            //cout << string(indents, SPACES) << "SCANNER ERROR: Token: " << tokens[0].tokenID << " Instance: " << tokens[0].tokenInstance << " Line Number: " << tokens[0].lineNum << endl;
        }
    }
    else{
        error(tokens[0], indents);
        return;
        //cout << string(indents, SPACES) << "SCANNER ERROR: Token: " << tokens[0].tokenID << " Instance: " << tokens[0].tokenInstance << " Line Number: " << tokens[0].lineNum << endl;
    }

    indents = indents-2;
    return;
}

void bnfS(vector <Token> &tokens, int indents){
    cout << "S" << endl;
    if(tokens[0].tokenID == "keywordTK"){
        if(tokens[0].tokenInstance == "Name"){
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
        }
        else{
            error(tokens[0], indents);
            return;
            //cout << string(indents, SPACES) << "SCANNER ERROR: Token: " << tokens[0].tokenID << " Instance: " << tokens[0].tokenInstance << " Line Number: " << tokens[0].lineNum << endl;
        }
    }
    else{
        error(tokens[0], indents);
        return;
        //cout << string(indents, SPACES) << "SCANNER ERROR: Token: " << tokens[0].tokenID << " Instance: " << tokens[0].tokenInstance << " Line Number: " << tokens[0].lineNum << endl;
    }

    if(tokens[0].tokenID == "alphaTK"){
        cout << string(indents, SPACES) << "Identifier " << tokens[0].tokenInstance << endl;
        tokens.erase(tokens.begin());
    }
    else{
        error(tokens[0], indents);
        return;
        //cout << string(indents, SPACES) << "SCANNER ERROR: Token: " << tokens[0].tokenID << " Instance: " << tokens[0].tokenInstance << " Line Number: " << tokens[0].lineNum << endl;
    }

    if(tokens[0].tokenID == "keywordTK"){
        if(tokens[0].tokenInstance == "Spot"){
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
        }
        else{
            error(tokens[0], indents);
        }

    }
    else{
        error(tokens[0], indents);
    }

    if(tokens[0].tokenID == "alphaTK"){
        cout << string(indents, SPACES) << "Identifier " << tokens[0].tokenInstance << endl;
        tokens.erase(tokens.begin());
    }
    else{
        error(tokens[0], indents);
    }

    indents = indents+2;
    bnfR(tokens, indents);
    //cout << string(indents, SPACES) << "calling E" << endl;
    bnfE(tokens, indents);
    bnfY(tokens, indents);
    return;
}

void bnfY(vector <Token> &tokens, int indents){
    if(tokens[0].tokenID == "eofTK"){
        cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
        tokens.erase(tokens.begin());
    }
    else{
        error(tokens[0], indents);
    }
    return;
}
void bnfT(vector <Token> &tokens, int indents){
    cout << string(indents-2, SPACES) << "T" << endl;
    if(tokens[0].tokenID == "operatorTK"){
        if(tokens[0].tokenInstance == "<<"){
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
        }
        else if(tokens[0].tokenInstance == "<-"){
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
        }
        else{
            error(tokens[0], indents);
        }
    }
    else{
        error(tokens[0], indents);
        return;
    }
}

bool bnfV(vector <Token> &tokens, int indents){
    bool worked = false;
    if(tokens[0].tokenID == "operatorTK"){
        if(tokens[0].tokenInstance == "+"){
            cout << string(indents-2, SPACES) << "V" << endl;
            worked = true;
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
        }
        else if(tokens[0].tokenInstance == "%"){
            cout << string(indents-2, SPACES) << "V" << endl;
            worked = true;
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
        }
        else if(tokens[0].tokenInstance == "&"){
            cout << string(indents-2, SPACES) << "V" << endl;
            worked = true;
            cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
        }
        else{
            worked = false;
            return worked;
        }
    }
    else{
        worked = false;
        return worked;
    }
    return worked;
}
void bnfN(vector <Token> &tokens, int indents){
    bool vResult = bnfV(tokens, indents);
    if(vResult == true){
        if(tokens[0].tokenID == "digitTK"){
            cout << string(indents-2, SPACES) << "N" << endl;
            cout << string(indents, SPACES) << "Number " << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
        }
        else{
            error(tokens[0], indents);
            return;
        }
    }
    else{
        if(tokens[0].tokenID == "operatorTK"){
            if(tokens[0].tokenInstance == "."){
                cout << string(indents-2, SPACES) << "N" << endl;
                cout << string(indents, SPACES) << tokens[0].tokenInstance << endl;
                tokens.erase(tokens.begin());
            }
            else{
                error(tokens[0], indents);
                return;
            }
        }
        else{
            error(tokens[0], indents);
            return;
        }
    }

    return;
}
void bnfW(vector <Token> &tokens, int indents){
    cout << string(indents-2, SPACES) << "W" << endl;
    if(tokens[0].tokenID == "digitTK"){
        cout << string(indents, SPACES) << "Number " << tokens[0].tokenInstance << endl;
        tokens.erase(tokens.begin());
    }
    else{
        error(tokens[0], indents);
    }
    indents+2;
    bnfN(tokens, indents);
}

void bnfZ(vector <Token> &tokens, int indents){
        cout << string(indents-2, SPACES) << "Z" << endl;
        if(tokens[0].tokenID == "alphaTK"){
            cout << string(indents, SPACES) << "Identifier " << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
        }
        else if(tokens[0].tokenID == "digitTK"){
            cout << string(indents, SPACES) << "Number " << tokens[0].tokenInstance << endl;
            tokens.erase(tokens.begin());
        }
        else{
            error(tokens[0], indents);
            return;
        }
}






