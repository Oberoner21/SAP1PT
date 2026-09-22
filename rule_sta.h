/*
    SAP1PT - SAP1 Pure Turing
    Modul:  rule_ldi.h

    Copyright(C) 2026 by Oberoner
*/


void GenerateRuleSTA(uint16_t rule) {

    // Entrypoint: NP pointer position: I0 of Instruction Register IR
    // Exitpoint : NP pointer position: M0 of Memory Address Register MAR

    SetRule(rule, '0', '0', RIGHT, RULE_END);
}