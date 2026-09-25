/*
    SAP1PT - SAP1 Pure Turing
    Modul:  rule_reset.h

    Copyright(C) 2026 by Oberoner
*/

void GenerateRuleRESET(uint16_t rule) {

    // Entrypoint: NP pointer position: 0
    // Exitpoint : NP pointer position: M0 (MAR bit 0)

    // ------------ Skip to position MAR0 -------------

    rule = next$RIGHT(rule);                        // Skip first $
    rule = next$RIGHT(rule);                        // Skip second $
    rule = next$RIGHT(rule);                        // Skip the flags
    rule = next$RIGHT(rule);                        // Skip the A/B Register
    rule = next$RIGHT(rule);                        // Skip the Output Register
    rule = next$RIGHT(rule);                        // Skip the Instruction Register
    rule = next$RIGHT(rule);                        // Skip the Program counter

    rule = next$RIGHT(rule);                        // Skip the MAR and go to rule FETCH
    SetRule(rule-1, '$', '$', LEFT, RULE_FETCH);
}