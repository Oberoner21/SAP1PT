/*
    SAP1PT - SAP1 Pure Turing
    Modul:  rule_sub.h

    Copyright(C) 2026 by Oberoner
*/

/*
    Instruction rule for SUB
    Entry conditions: IR and current MMB is marked.
    Entry point     : NP pointer position I0 of Instruction Register IR
    Exit point      : NP pointer position M0 of Memory Address Register MAR 
    Rules           : 744 
*/
void GenerateRuleSUB(uint16_t rule) {

    uint8_t i, j;

    // ------------ Save A in Output register ----------------

    // Remark IR
    rule = next_LEFT(rule);
    SetRule(rule-1, '_', '$', LEFT, rule);

    // Mark the Output register
    rule = next$LEFT(rule);
    SetRule(rule-1, '$', '_', LEFT, rule);

    // Mark register A/B
    // Skip left A/B register and mark it
    rule = next$LEFT(rule);
    SetRule(rule-1, '$', '_', RIGHT, rule);

    // Copy interleaved A register into Output register
    rule = CopyAtoMMB(rule);

    // Seek back to Output register and remark it
    rule = next_RIGHT(rule);
    SetRule(rule-1, '_', '$', RIGHT, rule);

    // Skip Output register
    rule = next$RIGHT(rule);

    // Skip IR
    rule = next$RIGHT(rule);

    // Skip PC
    rule = next$RIGHT(rule);
    // Mark MR
    SetRule(rule-1, '$', '_', RIGHT, rule); 

    // Seek to bit7 of the marked memory byte
    rule = next_RIGHT(rule);

    // Copy low nibble of MMB into MAR
    rule = CopyMMBArgToMAR(rule);

    // Seek back to bit3 of MAR
    rule = next_LEFT(rule);

    // ------ Mark the memory byte, addressed by register MAR ------
    rule = MarkMemoryByte(rule);
    // Skip to MMB bit7
    SetRule(rule-1, '_', '_', RIGHT, rule);

    // Copy MMB Value to Register A
    rule = CopyMMBToAB(rule);

    // Negate A
    for(i=0; i<8; i++) {

        SetRule(rule, '0', '1', RIGHT, rule + 1);
        SetRule(rule, '1', '0', RIGHT, rule + 1);
        rule++;

        rule = nextRIGHT(rule);
    }

    // Skip left to B0
    rule = next$LEFT(rule);

    // Set B = 1
    SetRule(rule, '0', '1', LEFT, rule+1);
    rule++;

    // Skip right to B0
    SetRule(rule, '0', '0', RIGHT, rule+2);
    SetRule(rule, '1', '1', RIGHT, rule+2);
    rule++;

    // Add A + B (Twos komplement)
    //----------------- A + B ----------------------

    // 0
    SetRule(rule, '0', '0', LEFT, rule+1);      // SUM = 0
    SetRule(rule, '1', '1', LEFT, rule+1);
    rule++;
    // 1
    SetRule(rule, '0', '0', LEFT, rule-1);      // No Carry
    SetRule(rule, '1', '0', LEFT, rule+1);
    SetRule(rule, '$', '$', LEFT, rule+4);      // End of Add with no carry
    rule++;
    // 2
    SetRule(rule, '0', '1', LEFT, rule-1);      // SUM = 1
    SetRule(rule, '1', '0', LEFT, rule+1);
    rule++;
    // 3
    SetRule(rule, '0', '0', LEFT, rule-1);      // Carry
    SetRule(rule, '1', '0', LEFT, rule+1);
    SetRule(rule, '$', '$', LEFT, rule+2);      // End of Add with carry
    rule++;
    // 4
    SetRule(rule, '0', '0', LEFT, rule-1);      // SUM = 2
    SetRule(rule, '1', '1', LEFT, rule-1);
    rule++;

    // ---------- Copy saved value of A (in Output Register) to Register B ------

    // Mark Register A/B and skip to right
    rule = next$RIGHT(rule);
    SetRule(rule-1, '$', '_', RIGHT, rule);

    // Mark Output register and skip to O7
    rule = next$RIGHT(rule);
    SetRule(rule-1, '$', '_', RIGHT, rule);

    // Copy Output Register to Register B
    rule = CopyMMBToAB(rule, true);

    // Seek to B0
    rule = next$RIGHT(rule, LEFT);
    // Change the rule to new value of next rule -> rule_ALU
    SetRule(rule-1, '$', '$', LEFT, rule_ALU);

}
