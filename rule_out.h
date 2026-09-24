/*
    SAP1PT - SAP1 Pure Turing
    Modul:  rule_out.h

    Copyright(C) 2026 by Oberoner
*/


void GenerateRuleOUT(uint16_t rule) {

    // Entrypoint: NP pointer position: I0 of Instruction Register IR
    // Exitpoint : NP pointer position: M0 of Memory Address Register MAR

    // The OUT rule has not yet been implemented. It currently executes the NOP command.

    uint8_t i, j;

    // Seek back to MMB an remark it
    rule = next_RIGHT(rule); 
    SetRule(rule-1, '_', '$', LEFT, rule);
    // Seek to marked register IR and remark it
    rule = next_LEFT(rule);
    SetRule(rule-1, '_', '$', RIGHT, rule);
    // Skip right Instruction Register IR
    rule = next$RIGHT(rule);     
    // Skip right Program counter PC
    rule = next$RIGHT(rule); 
    // Skip right Memory Address Register MAR and go to RULE_FETCH
    rule = next$RIGHT(rule);
    SetRule(rule-1, '$', '$', LEFT, RULE_FETCH); 

    // 5 Rules
}