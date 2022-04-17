
#include "parser.h"
#include "scanner.h"
#include "tokens.h"
#include <vector>

Token scanner(string word, int lineNum){
    //cout << "scanner()" << endl;
    //cout << word << " ; word ; line num: " << lineNum << endl;

    vector<Token> tokens;
    bool isKeyword = false;

    //conditionals for token creation and assignment

    //Conditional for uppercase first character. (Keyword || Alpha)
    if(isalpha(word[0]) && isupper(word[0])){
        bool isalphaNum = true;
        for(int i = 0; i < word.length(); i++){
            if((isalpha(word[i]) == false) && (isdigit(word[0]) == false)){
                for(int k = 0; k < TOTALOPERATORS; k++){
                    if((operatorArray[k] == word[0]) == true){
                        cout << "SCANNER ERROR: " << word << " line num: " << lineNum << endl;
                        isalphaNum = false;
                        k = TOTALOPERATORS;
                        i = word.length();
                    }
                }
            }
        }
        if(isalphaNum == true){
            //cout << "maybe Keyword" << endl;
            for(int i = 0; i < TOTALKEYWORDS; i++){
                if(word == keywordArray[i]){
                    //cout << "Keyword spotted: " << word << endl;
                    tokens.push_back(Token(keyword,word,lineNum));
                    //cout << tokens[0].tokenID << " : " << tokens[0].tokenInstance << " : " << tokens[0].lineNum << endl;
                    //currentToken.tokenID = tokens[0].tokenID;
                    //currentToken.tokenInstance = tokens[0].tokenInstance;
                    //currentToken.lineNum = tokens[0].lineNum;
                    return tokens[0];
                    isKeyword = true;
                }
            }
            if(isKeyword == false){
                //cout << "just alphabet" << endl;
                tokens.push_back(Token(alpha,word,lineNum));
                //cout << tokens[0].tokenID << " : " << tokens[0].tokenInstance << " : " << tokens[0].lineNum << endl;
                return tokens[0];
            }
        }
    }
    //Conditional for lowercase first letter (Alpha)
    else if(isalpha(word[0]) && islower(word[0])){
        //cout << "alpha spotted" << endl;
        tokens.push_back(Token(alpha,word,lineNum));
        //cout << tokens[0].tokenID << " : " << tokens[0].tokenInstance << " : " << tokens[0].lineNum << endl;
        //currentToken.tokenID = tokens[0].tokenID;
        //currentToken.tokenInstance = tokens[0].tokenInstance;
        //currentToken.lineNum = tokens[0].lineNum;
        return tokens[0];
    }
    //Conditional for numbers (Digit)
    else if(isdigit(word[0])){
        bool isNumber = true;
        for(int i = 0; i < word.length(); i++){
            if(isdigit(word[i]) == false){
                isNumber = false;
            }
        }
        if(isNumber == true){
            //cout << "number spotted" << endl;
            tokens.push_back(Token(digit,word,lineNum));
            //cout << tokens[0].tokenID << " : " << tokens[0].tokenInstance << " : " << tokens[0].lineNum << endl;
            //currentToken.tokenID = tokens[0].tokenID;
            //currentToken.tokenInstance = tokens[0].tokenInstance;
            //currentToken.lineNum = tokens[0].lineNum;
            return tokens[0];
        }
        else{
            cout << "SCANNER ERROR: " << word  << " ; " << lineNum << " only digits in number word" << endl;
        }
    }
    //Conditonals for comments (Comments)
    else if(word[0] == '*'){
        //cout << "Comment spotted" << endl;
        tokens.push_back(Token(comment,word, lineNum));
        //cout << tokens[0].tokenID << " : " << tokens[0].tokenInstance << " : " << tokens[0].lineNum << endl;
        //currentToken.tokenID = tokens[0].tokenID;
        //currentToken.tokenInstance = tokens[0].tokenInstance;
        //currentToken.lineNum = tokens[0].lineNum;
        return tokens[0];
    }
    //Conditionals for Operators (Operator)
    else if((isdigit(word[0]) == false) && (isalpha(word[0]) == false)){
        //cout << "maybe operator" << endl;
        for(int i = 0; i < TOTALOPERATORS; i++){
            if(word[0] == operatorArray[i]){
                //cout << "operator spotted" << endl;
                tokens.push_back(Token(oper,word,lineNum));
                //cout << tokens[0].tokenID << " : " << tokens[0].tokenInstance << " : " << tokens[0].lineNum << endl;
                //currentToken.tokenID = tokens[0].tokenID;
                //currentToken.tokenInstance = tokens[0].tokenInstance;
                //currentToken.lineNum = tokens[0].lineNum;
                return tokens[0];
            }
        }
    }
    else if(word[0] == char_traits<char>::eof()){
        cout << "end of file spotted" << endl;
        tokens.push_back(Token(eof, word, lineNum));
        //cout << tokens[0].tokenID << " : " << tokens[0].tokenInstance << " : " << tokens[0].lineNum << endl;
        //currentToken.tokenID = tokens[0].tokenID;
        //currentToken.tokenInstance = tokens[0].tokenInstance;
        //currentToken.lineNum = tokens[0].lineNum;
        return tokens[0];
        
    }
    

    
    
    return tokens[0];
}
