/*
    SAP1PT - SAP1 Pure Turing
    Modul:  rule_ldi.h

    Copyright(C) 2026 by Oberoner
*/


void GenerateRuleLDA(uint16_t rule) {

    // Entrypoint: NP pointer position: I0 of Instruction Register IR
    // Exitpoint : NP pointer position: M0 of Memory Address Register MAR

    // Mark register A
    // Remark IR
    // Mark MAR
    // Seek to MMB bit 7

    uint8_t i, j;

    SetRule(rule, '_', '_', LEFT, rule+1);
    SetRule(rule, '0', '0', LEFT, rule+1);
    SetRule(rule, '1', '1', LEFT, rule+1);
    SetRule(rule, '$', '$', LEFT, rule+1);
    rule++;

    // Skip left IR (is yet market) and output register
    rule = next$LEFT(rule);

    // Skip left A/B register and mark it
    rule = next$LEFT(rule);
    SetRule(rule-1, '$', '_', RIGHT, rule);

    // Seek to IR marker and remark the register
    rule = next_RIGHT(rule);
    SetRule(rule-1, '_', '$', RIGHT, rule);

    // Skip IR
    rule = next$RIGHT(rule);

    // Seek right to register MAR and mark it
    rule = next$RIGHT(rule);
    SetRule(rule-1, '$', '_', RIGHT, rule);

    // Seek right to marked memory byte to bit7
    rule = next_RIGHT(rule);
    SetRule(rule-1, '_', '_', RIGHT, rule);


    // ---------- Copy low nibble of MMB into MAR  -----------

    for(i=0; i<4; i++) {

        // Skip 4 byte right to bit3 of the marked memory register
        rule = nextRIGHT(rule);
        rule = nextRIGHT(rule);
        rule = nextRIGHT(rule);
        rule = nextRIGHT(rule);

        for(j=0; j<i; j++){
 
            // Skip jx right in marked memory byte 
            rule = nextRIGHT(rule);     
        }

        // Read current bit of marked memory Byte and branche
        SetRule(rule, '0', '0', RIGHT, rule+1);
        SetRule(rule, '1', '1', RIGHT, rule+4+i);
        rule++;

        // Skip left to the memory byte marker
        rule = next_LEFT(rule, LEFT); 

        // Skip to bit3 of the marked register MAR 
        rule = next_LEFT(rule);

        for(j=0; j<i; j++){
 
            // Skip jx bit right in MAR
            rule = nextRIGHT(rule);     
        }

        // Write a 0 into current bit of MAR
        SetRule(rule, '0', '0', RIGHT, rule+4+i);
        SetRule(rule, '1', '0', RIGHT, rule+4+i);
        rule++;

    
        // Skip to memory byte marker 
        rule = next_LEFT(rule, LEFT);
        // Skip the market destination register MAR 
        rule = next_LEFT(rule);

        for(j=0; j<i; j++){
 
            // Skip jx bit right in MAR
            rule = nextRIGHT(rule);     
        }

        // Write a 1 into current bit of MAR
        SetRule(rule, '0', '1', RIGHT, rule+1);
        SetRule(rule, '1', '1', RIGHT, rule+1);
        rule++;

        // Skip back to Bit7 of the marked byte 
        rule = next_RIGHT(rule);
    }
    // Change last rule
    // Remark the marked memory byte
    SetRule(rule-1, '_', '$', LEFT, rule);

    // Seek back to bit3 of MAR
    rule = next_LEFT(rule);

    // ------ Mark the memory byte, addressed by register MAR ------
    rule = MarkMemoryByte(rule);
    // Change the direction of last rule to RIGHT
    SetRule(rule-1, '_', '_', RIGHT, rule);

    // --------- Copy MMB value into interleaved register A/B ---------------

    for(i=0; i<8; i++) {

        for(j=0; j<i; j++){
 
            // Skip jx right in marked memory byte 
            rule = nextRIGHT(rule);     
        }

        // Read current bit of MMB and branche
        SetRule(rule, '0', '0', RIGHT, rule+1);
        SetRule(rule, '1', '1', RIGHT, rule+4+i*2);
        rule++;

        // Seek left to the memory byte marker
        rule = next_LEFT(rule, LEFT); 

        // Seek to A7 of the marked register A/B 
        rule = next_LEFT(rule);

        for(j=0; j<i; j++){
 
            // Skip jx bit right in A/B
            rule = nextRIGHT(rule); 
            rule = nextRIGHT(rule); 
        }

        // Write a 0 into current bit of B
        SetRule(rule, '0', '0', RIGHT, rule+4+i*2);
        SetRule(rule, '1', '0', RIGHT, rule+4+i*2);
        rule++;

    
        // Seek to memory byte marker 
        rule = next_LEFT(rule, LEFT);
        // Seek to the market destination register A/B
        rule = next_LEFT(rule);

        for(j=0; j<i; j++){
 
            // Skip jx bit right in A/B
            rule = nextRIGHT(rule);    
            rule = nextRIGHT(rule);   
        }

        // Write a 1 into current bit of B
        SetRule(rule, '0', '1', RIGHT, rule+1);
        SetRule(rule, '1', '1', RIGHT, rule+1);
        rule++;
        
        // Seek back to Bit7 of the marked byte 
        rule = next_RIGHT(rule);
    }

    // Change last rule
    // Remark the marked memory byte
    SetRule(rule-1, '_', '$', LEFT, rule);

    // Seek back to marked register A/B and remark it
    rule = next_LEFT(rule);
    SetRule(rule-1, '-', '$', RIGHT, rule);

    // Skip right A/B register
    rule = next$RIGHT(rule); 
    // Skip right Output register
    rule = next$RIGHT(rule); 
    // Skip right Instruction Register IR
    rule = next$RIGHT(rule);     
    // Skip right Program counter PC
    rule = next$RIGHT(rule); 
    // Skip right Memory Address Register MAR and go to RULE_FETCH
    rule = next$RIGHT(rule);
    SetRule(rule-1, '$', '$', LEFT, RULE_FETCH);  

    // 331 Rules
}