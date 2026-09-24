#include <iostream>
#include "rulebook.h"
#include "notepad.h"

const char cSymbols[] = ("_01$");

int notePadPointer = 0;
int rule = 0;

bool halt = false;

int main() {

    generateRuleBook();
    copyNPItems();

    int cykles = 0, outCount = 0;
    notePadPointer = 0;
    rule = 0;

    while(!halt){
        char symbol = notePad[notePadPointer];
        int nextRule = ruleBook[rule][symbol].next;
        notePad[notePadPointer] = ruleBook[rule][symbol].writeSymbol;
        notePadPointer += ruleBook[rule][symbol].direction;
        rule = nextRule;

        cykles++;

        if(rule == RULE_OUT) {

            // Display the current value of A register
            makeOutStr();
            std::cout << outBuffer; 
            std::cout << "\n";
        }


        if(rule == RULE_END) {
            std::cout << "END state in cykle: " << cykles << std::endl;
            std::cout << "Notepad Pointer: " << notePadPointer << std::endl; 
            std::cout << "Readsymbol: " << cSymbols[notePad[notePadPointer]] << std::endl; 

            for(int j=0; j<npSize; j++) std::cout << cSymbols[notePad[j]];
            std::cout << "\n";
            std::cout << "\n";
            std::cout << "\n";

            halt = true;
        }

        if(rule == RULE_ERROR) {
            std::cout << "Go to error state in cykle: " << cykles << std::endl; 
            std::cout << "Notepad Pointer: " << notePadPointer << std::endl;
            std::cout << "Readsymbol: " << cSymbols[notePad[notePadPointer]] << std::endl; 

            for(int j=0; j<npSize; j++) std::cout << cSymbols[notePad[j]];
            std::cout << "\n";
            std::cout << "\n";
            std::cout << "\n";

            halt = true;
        }
    }

    return 0;
}