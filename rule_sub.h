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
    for(i=0; i<8; i++){

        for(j=0; j<i; j++){

            // Skip register bit and constant bit
            rule = nextRIGHT(rule);
            rule = nextRIGHT(rule);         
        }

        // Read current bit in A and branch
        SetRule(rule, '0', '0', RIGHT, rule+3+i);
        SetRule(rule, '1', '1', RIGHT, rule+1);
        rule++;

        // Readed bit was a 1
        // Seek to bit7 of the marked Output register
        rule = next_RIGHT(rule); 

        for(j=0; j<i; j++){

            // Skip jx bit in marked Output register
            rule = nextRIGHT(rule);  
        }

        // Write a 1 into current bit of marked Output register
        SetRule(rule, '0', '1', RIGHT, rule+3+i);
        SetRule(rule, '1', '1', RIGHT, rule+3+i);  
        rule++;

        // Readed bit was a 0
        // Seek to bit7 of the marked Output register
        rule = next_RIGHT(rule); 

        for(j=0; j<i; j++){

            // Skip jx bit in marked Output register
            rule = nextRIGHT(rule);  
        }

        // Write a 0 into current bit of marked Output register
        SetRule(rule, '0', '0', RIGHT, rule+1);
        SetRule(rule, '1', '0', RIGHT, rule+1);  
        rule++;

        // Skip left marked Output register
        rule = next_LEFT(rule);
        SetRule(rule-1, '_', '_', LEFT, rule);

        // Jump back to A7 of register A/B
        rule = next_LEFT(rule);
    }

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
    SetRule(rule, '0', '_', LEFT, rule-1);      // No Carry
    SetRule(rule, '1', '_', LEFT, rule+1);
    SetRule(rule, '$', '$', LEFT, rule+4);     // End of Add with no carry
    rule++;
    // 2
    SetRule(rule, '0', '1', LEFT, rule-1);      // SUM = 1
    SetRule(rule, '1', '0', LEFT, rule+1);
    rule++;
    // 3
    SetRule(rule, '0', '_', LEFT, rule-1);      // Carry
    SetRule(rule, '1', '_', LEFT, rule+1);
    SetRule(rule, '$', '$', LEFT, rule+2);      // End of Add with carry
    rule++;
    // 4
    SetRule(rule, '0', '0', LEFT, rule-1);      // SUM = 2
    SetRule(rule, '1', '1', LEFT, rule-1);
    rule++;

    // ---------- Copy saved value of A (in Output Register) to Register B ------

    // Skip 2x to right to A7
    rule = nextRIGHT(rule); 
    rule = nextRIGHT(rule);

    // Skip A/B to O7
    rule = next$RIGHT(rule);

    // Copy the Value
    for(i=0; i<8; i++) {

        for(j=0; j<i; j++) {

            // Skip Output register bit right
            rule = nextRIGHT(rule);
        }

        // 0 - Read current bit in the Output Register
        SetRule(rule, '0', '0', LEFT, rule+1);
        SetRule(rule, '1', '1', LEFT, rule+5+i*2);
        rule++;

        // 1 - Seek left to A7
        rule = next$LEFT(rule);
        rule = next$LEFT(rule);
        SetRule(rule-1, '$', '$', RIGHT, rule);
        rule = nextRIGHT(rule);

        for(j=0; j<i; j++) {

            // Skip bit pos of A/B 2xi to left
            rule = nextRIGHT(rule);
            rule = nextRIGHT(rule);
        }

        // 2 - Write 0 into current bit B
        SetRule(rule, '_', '0', LEFT, rule+5+i*2);
        rule++;

        // 1 - Seek left to A7
        rule = next$LEFT(rule);
        rule = next$LEFT(rule);
        SetRule(rule-1, '$', '$', RIGHT, rule);
        rule = nextRIGHT(rule);
    
        for(j=0; j<i; j++) {

            // Skip bit pos of A/B 2xi to left
            rule = nextRIGHT(rule);
            rule = nextRIGHT(rule);
        }

        // 4 - Write 1 into current bit B
        SetRule(rule, '_', '1', LEFT, rule+1);
        rule++;

        // 5 - Seek back to O7
        rule = next$RIGHT(rule); 
    }

    // Seek to B0
    rule = next$LEFT(rule, LEFT);
    // Change the rule to new value of next rule -> rule_ALU
    SetRule(rule-1, '$', '$', LEFT, rule_ALU);

}
