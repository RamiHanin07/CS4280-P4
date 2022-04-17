//Name: Rami Hanin
//Date: 4/5/2022
//Class: CS4280

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#include "parser.h"
#include "scanner.h"
#include "tokens.h"


int main(int argc, char *argv[]){

    //Variables
    string fileName = "";


    //Extracting command line arguments
    string argument = "";
    if(argv[1]){
        //cout << argv[1] << " arg" << endl;
        argument = string(argv[1]);
    }
    cout << argument << endl;

    //Dealing with command line argument conditionals
    if(argument != ""){
        if(argument != ">"){
            fileName = argument;
        }
        else{
            cout << "Error, unidentified argument" << endl;
        }
    }

    cout << fileName << endl;

    //Call testScanner
    parse(fileName);

    return 0;
}