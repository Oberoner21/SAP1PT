/*
    SAP1PT - SAP1 Pure Turing
    Modul:  rulebook.h

    Copyright(C) 2026 by Oberoner
*/

#include "utils.h"

#define     LEFT            -1
#define     RIGHT           1
#define     RULES           0x1000
#define     SYMBOLS         4

#define     RULE_RESET      0
#define     RULE_FETCH      10
#define     RULE_DECODE     200
#define     RULE_NOP        250
#define     RULE_LDA        300
#define     RULE_ADD        800
#define     RULE_SUB        1300
#define     RULE_STA        1800
#define     RULE_LDI        2300
#define     RULE_JMP        2800
#define     RULE_JC         3000
#define     RULE_JZ         3050
#define     RULE_OUT        3100
#define     RULE_HLT        3200

#define     RULE_END        4094
#define     RULE_ERROR      4095


struct rule {
    int next;
    int direction;
    int writeSymbol;
} ruleBook[RULES][SYMBOLS];


void SetRule(int rule, unsigned char readSymbol, unsigned char writeSymbol, int direction, int nextRule){

    uint8_t numReadSymbol = symbol2num(readSymbol);

    ruleBook[rule][numReadSymbol].writeSymbol = symbol2num(writeSymbol);
    ruleBook[rule][numReadSymbol].direction = direction;
    ruleBook[rule][numReadSymbol].next = nextRule;
}

uint16_t nextLEFT(uint16_t rule){

    SetRule(rule, '0', '0', LEFT, rule+1);
    SetRule(rule, '1', '1', LEFT, rule+1);
    SetRule(rule, '_', '_', LEFT, rule+1);
    SetRule(rule, '$', '$', LEFT, rule+1);

    return rule+1;
}

uint16_t nextRIGHT(uint16_t rule){

    SetRule(rule, '0', '0', RIGHT, rule+1);
    SetRule(rule, '1', '1', RIGHT, rule+1);
    SetRule(rule, '_', '_', RIGHT, rule+1);
    SetRule(rule, '$', '$', RIGHT, rule+1);

    return rule+1;
}

uint16_t next$RIGHT(uint16_t rule, int endDirection = RIGHT) {

    SetRule(rule, '0', '0', RIGHT, rule);
    SetRule(rule, '1', '1', RIGHT, rule);
    SetRule(rule, '_', '_', RIGHT, rule);
    SetRule(rule, '$', '$', endDirection, rule+1);
    
    return rule+1;
}

uint16_t next$LEFT(uint16_t rule, int endDirection = LEFT) {

    SetRule(rule, '0', '0', LEFT, rule);
    SetRule(rule, '1', '1', LEFT, rule);
    SetRule(rule, '_', '_', LEFT, rule);
    SetRule(rule, '$', '$', endDirection, rule+1);
    
    return rule+1;
}

uint16_t next_LEFT(uint16_t rule, int endDirection = RIGHT){

    SetRule(rule, '0', '0', LEFT, rule);        
    SetRule(rule, '1', '1', LEFT, rule);
    SetRule(rule, '$', '$', LEFT, rule);
    SetRule(rule, '_', '_', endDirection, rule+1);

    return rule+1;
}

uint16_t next_RIGHT(uint16_t rule, int endDirection = RIGHT){

    SetRule(rule, '0', '0', RIGHT, rule);        
    SetRule(rule, '1', '1', RIGHT, rule);
    SetRule(rule, '$', '$', RIGHT, rule);
    SetRule(rule, '_', '_', endDirection, rule+1);

    return rule+1;
}

#include "rule_markMemByte.h"
#include "rule_cpyMMBArgToPC.h"
#include "rule_cpyMMBArgToMAR.h"
#include "rule_cpyMMBToAB.h"

#include "rule_reset.h"
#include "rule_fetch.h"
#include "rule_decode.h"
#include "rule_ldi.h"
#include "rule_sta.h"
#include "rule_add.h"
#include "rule_jc.h"
#include "rule_out.h"
#include "rule_lda.h"
#include "rule_jmp.h"
#include "rule_hlt.h"


void generateRuleBook()
{
    uint16_t rule = 0;

    // Initialize all rules as Error State
    while(rule < RULES){

        SetRule(rule, '_', '_', RIGHT, RULE_ERROR);
        SetRule(rule, '0', '0', RIGHT, RULE_ERROR);  
        SetRule(rule, '1', '1', RIGHT, RULE_ERROR);
        SetRule(rule, '$', '$', RIGHT, RULE_ERROR);
        rule++;
    }

    GenerateRuleRESET(RULE_RESET);
    GenerateRuleFETCH(RULE_FETCH);
    GenerateRuleDECODE(RULE_DECODE);
    GenerateRuleLDI(RULE_LDI);
    GenerateRuleSTA(RULE_STA);
    GenerateRuleADD(RULE_ADD);
    GenerateRuleJC(RULE_JC);
    GenerateRuleOUT(RULE_OUT);
    GenerateRuleLDA(RULE_LDA);
    GenerateRuleJMP(RULE_JMP);
    GenerateRuleHLT(RULE_HLT);
}