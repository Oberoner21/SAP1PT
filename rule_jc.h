/*
    SAP1PT - SAP1 Pure Turing
    Modul:  rule_ldi.h

    Copyright(C) 2026 by Oberoner
*/


void GenerateRuleJC(uint16_t rule) {

    // Entrypoint: NP pointer position: I0 of Instruction Register IR
    // Exitpoint : NP pointer position: M0 of Memory Address Register MAR

    // Seek to carry flag
    // If not carry -> END 
    // If carry
    //  - Seek to PC and mark it
    //  - Copy low nibble MMB into interleaved PC
    //  - Remark PC and END
    //  END
    //  - Remark MMB,
    //  - Remark IR
    //  - Seek to MAR0
    //  - Go to RULE_FETCH

    uint8_t i, j;

    // Skip left IR (is yet market) and output register
    rule = next$LEFT(rule);

    // Skip left A/B register
    rule = next$LEFT(rule);

    // Skip one position left to carry
    rule = nextLEFT(rule);

    // Read carry
    SetRule(rule, '0', '0', RIGHT, rule+1);     // Carry not set
    SetRule(rule, '1', '1', RIGHT, rule+2);     // Carry set
    rule++;

    // Skip marked IR
    rule = next_RIGHT(rule);
    SetRule(rule-1, '_', '_', RIGHT, rule+82);     // <-- Jump to END !!!!

    // ++++++++ Carry is set +++++++++++++

    // Seek to IR (the Marker is yet set)
    rule = next_RIGHT(rule);
    // Seek to PC and mark it
    rule = next$RIGHT(rule);
    SetRule(rule-1, '$', '_', RIGHT, rule);
    // Seek to bit7 of MMB
    rule = next_RIGHT(rule);  // 86

    // Copy low nibbel of MMB to interleaved PC
    for(i=0; i<4; i++){

        // Skip to bit 3 of MMB
        rule = nextRIGHT(rule);
        rule = nextRIGHT(rule);
        rule = nextRIGHT(rule);
        rule = nextRIGHT(rule);

        for(j=0; j<i; j++){

            // Skip next left MMB bit
            rule = nextRIGHT(rule);       
        }

        // Read current bit in MMB and branch
        SetRule(rule, '0', '0', RIGHT, rule+4+i*2);
        SetRule(rule, '1', '1', RIGHT, rule+1);
        rule++;

        // Readed bit was a 1
        // Seek to P3 of PC
        rule = next_LEFT(rule, LEFT); 
        rule = next_LEFT(rule);

        for(j=0; j<i; j++){

            // Skip jx bit in PC
            rule = nextRIGHT(rule);  
            rule = nextRIGHT(rule);
        }

        // Write a 1 into current bit of PC
        SetRule(rule, '0', '1', RIGHT, rule+4+i*2);
        SetRule(rule, '1', '1', RIGHT, rule+4+i*2);  
        rule++;

        // Readed bit was a 0
        // Seek to P3 of PC
        rule = next_LEFT(rule, LEFT); 
        rule = next_LEFT(rule);

        for(j=0; j<i; j++){

            // Skip jx bit in PC
            rule = nextRIGHT(rule);  
            rule = nextRIGHT(rule);
        }

        // Write a 0 into current bit of PC
        SetRule(rule, '0', '0', RIGHT, rule+1);
        SetRule(rule, '1', '0', RIGHT, rule+1);  
        rule++;

        // Jump back to bit7 of MMB
        rule = next_RIGHT(rule);
    }

    // Change the last rule
    SetRule(rule-1, '_', '_', LEFT, rule);
    // Remark PC
    rule = next_LEFT(rule);
    SetRule(rule-1, '_', '$', RIGHT, rule);
    
    // ++++++++++++ END ++++++++++++++++++

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

    // 92 Rules
}