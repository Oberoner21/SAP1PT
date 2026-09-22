
// Kopiert den Wert des Programm counters in das Memory Address Register
uint16_t PCtoMAR(uint16_t rule){

    // Entrypoint: NP pointer position: M0 (MAR bit 0)
    // Exitpoint : NP pointer position: P3 (PC bit 7)

    // ++++++++++++++++++++ Copy Program Counter to MAR +++++++++++++++++++++++++++

    // Notepadpointer auf das $-Zeichen zwischen IR und Programmcounter

    rule = next$LEFT(rule);                     // Skip MAR
    rule = next$LEFT(rule);                     // Skip PC
    SetRule(rule-1, '$', '_', RIGHT, rule);     // Mark the PC with '_'

    // -------- Copy P3 to MAR 3 -------------
 
    SetRule(rule, '0', '0', RIGHT, rule+3);     // Read P3 and branch
    SetRule(rule, '1', '1', RIGHT, rule+1);
    rule++;

    // P3 is a 1
    rule = next$RIGHT(rule);                    // Skip the MAR, NPP is now on M3

    SetRule(rule, '0', '1', RIGHT, rule+3);     // Write 1 into M3
    SetRule(rule, '1', '1', RIGHT, rule+3);  
    rule++; 

    // P3 is a 0
    rule = next$RIGHT(rule);                    // Skip the MAR, NPP is now on M3

    SetRule(rule, '0', '0', RIGHT, rule+1);     // Write 0 into M3
    SetRule(rule, '1', '0', RIGHT, rule+1);  
    rule++; 

    rule = next_LEFT(rule);                     // Back to PC-Mark, next right

    // -------- Copy P2 to MAR 2 -------------

    rule = nextRIGHT(rule);                     // Skip P3
    rule = nextRIGHT(rule);                     // Skip C3

    SetRule(rule, '0', '0', RIGHT, rule+4);     // Read P2 and branch
    SetRule(rule, '1', '1', RIGHT, rule+1);
    rule++;

    // P2 is a 1
    rule = next$RIGHT(rule);                    // Skip the MAR, NPP is now on M3
    rule = nextRIGHT(rule);                     // Skip M3

    SetRule(rule, '0', '1', RIGHT, rule+4);     // Write 1 into M2
    SetRule(rule, '1', '1', RIGHT, rule+4);  
    rule++; 

    // P2 is a 0
    rule = next$RIGHT(rule);                    // Skip the MAR, NPP is now on M3
    rule = nextRIGHT(rule);                     // Skip M3

    SetRule(rule, '0', '0', RIGHT, rule+1);     // Write 0 into M2
    SetRule(rule, '1', '0', RIGHT, rule+1);  
    rule++; 

    rule = next_LEFT(rule);                     // Back to PC-Mark

    // -------- Copy P1 to MAR 1 -------------

    rule = nextRIGHT(rule);                     // Skip P3
    rule = nextRIGHT(rule);                     // Skip C3
    rule = nextRIGHT(rule);                     // Skip P2
    rule = nextRIGHT(rule);                     // Skip C2

    SetRule(rule, '0', '0', RIGHT, rule+5);     // Read P1 and branch
    SetRule(rule, '1', '1', RIGHT, rule+1);
    rule++;

    // P1 is a 1
    rule = next$RIGHT(rule);                    // Skip the MAR, NPP is now on M3
    rule = nextRIGHT(rule);                     // Skip M3
    rule = nextRIGHT(rule);                     // Skip M2

    SetRule(rule, '0', '1', RIGHT, rule+5);     // Write 1 into M1
    SetRule(rule, '1', '1', RIGHT, rule+5);  
    rule++; 

    // P1 is a 0
    rule = next$RIGHT(rule);                    // Skip the MAR, NPP is now on M3
    rule = nextRIGHT(rule);                     // Skip M3
    rule = nextRIGHT(rule);                     // Skip M2

    SetRule(rule, '0', '0', RIGHT, rule+1);     // Write 0 into M1
    SetRule(rule, '1', '0', RIGHT, rule+1);  
    rule++; 

    rule = next_LEFT(rule);                     // Back to PC-Mark

   // -------- Copy P0 to MAR 0 -------------

    rule = nextRIGHT(rule);                     // Skip P3
    rule = nextRIGHT(rule);                     // Skip C3
    rule = nextRIGHT(rule);                     // Skip P2
    rule = nextRIGHT(rule);                     // Skip C2
    rule = nextRIGHT(rule);                     // Skip P1
    rule = nextRIGHT(rule);                     // Skip C1

    SetRule(rule, '0', '0', RIGHT, rule+6);     // Read P0 and branch
    SetRule(rule, '1', '1', RIGHT, rule+1);
    rule++;

    // P0 is a 1
    rule = next$RIGHT(rule);                    // Skip the MAR, NPP is now on M3
    rule = nextRIGHT(rule);                     // Skip M3
    rule = nextRIGHT(rule);                     // Skip M2
    rule = nextRIGHT(rule);                     // Skip M1

    SetRule(rule, '0', '1', RIGHT, rule+6);     // Write 1 into M0
    SetRule(rule, '1', '1', RIGHT, rule+6);  
    rule++; 

    // P0 is a 0
    rule = next$RIGHT(rule);                    // Skip the MAR, NPP is now on M3
    rule = nextRIGHT(rule);                     // Skip M3
    rule = nextRIGHT(rule);                     // Skip M2
    rule = nextRIGHT(rule);                     // Skip M1

    SetRule(rule, '0', '0', RIGHT, rule+1);     // Write 0 into M0
    SetRule(rule, '1', '0', RIGHT, rule+1);  
    rule++; 

    rule = next_LEFT(rule);                     // Back to PC-Mark
    SetRule(rule-1, '_', '$', RIGHT, rule);     // Remark PC

    return rule;
}


// Increment the interleaved Programm counter
uint16_t IncPC(uint16_t rule) {

    // Entrypoint: Notepadpointer steht auf P3 des Program Counters
    // Exitpoint:  Notepadpointer steht auf P3 des Program Counters

    rule = next$RIGHT(rule, LEFT);                  // Skip to C1
    SetRule(rule-1, '$', '$', LEFT, rule+1);        // Next rule is NoCarry

    SetRule(rule, '0', '0', LEFT, rule+1);          // SUM = 0
    SetRule(rule, '1', '1', LEFT, rule+1);
    rule++;

    SetRule(rule, '0', '0', LEFT, rule-1);          // No Carry
    SetRule(rule, '1', '1', LEFT, rule+1);
    SetRule(rule, '$', '$', RIGHT, rule+4);         // Down without carry
    rule++;

    SetRule(rule, '0', '1', LEFT, rule-1);          // SUM = 1
    SetRule(rule, '1', '0', LEFT, rule+1);
    rule++;

    SetRule(rule, '0', '0', LEFT, rule-1);          // Carry
    SetRule(rule, '1', '1', LEFT, rule+1);
    SetRule(rule, '$', '$', RIGHT, rule+2);         // Down with carry
    rule++;

    SetRule(rule, '0', '0', LEFT, rule-1);          // SUM = 2
    rule++;

    return rule;
}


// Kopiert den Befehl (Bit 7 bis 4) aus der Speicherstelle, auf die
// der PC zeigt in das Instruction Register IR
uint16_t INSTtoIR(uint16_t rule){

    // Entrypoint: Notepadpointer steht auf P3 des Program Counters
    // Exitpoint:  NotepadPointer steht auf I3 des Instruction Registers IR

    uint8_t i, j;  

    // ------------- Mark the IR -------------
    rule = next$LEFT(rule);                     // Skip MAR
    rule = next$LEFT(rule);                     // Skip PC
    SetRule(rule-1, '$', '_', RIGHT, rule);     // Mark IR

    // ------- Skip to MAR and Mark MAR -------
    rule = next$RIGHT(rule);                    // Skip IR
    rule = next$RIGHT(rule);                    // Skip PC
    SetRule(rule-1, '$', '_', RIGHT, rule);     // Mark MAR

    // ------ Mark the memory byte, addressed by register MAR ------
    rule = MarkMemoryByte(rule);

    // ++++ Copy high nibble of marked memory byte to instruction register IR ++++
    // Destination register IR is marked
    // NP position: Bit7 of the marked byte

    // Copy 4 bits
    for(i=0; i<4; i++) {

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

        // Skip to bit3 of the marked register IR 
        rule = next_LEFT(rule);

        for(j=0; j<i; j++){
 
            // Skip jx bit right in IR
            rule = nextRIGHT(rule);     
        }

        // Write a 0 into current bit of IR
        SetRule(rule, '0', '0', RIGHT, rule+4+i);
        SetRule(rule, '1', '0', RIGHT, rule+4+i);
        rule++;

    
        // Skip to memory byte marker 
        rule = next_LEFT(rule, LEFT);
        // Skip the market destination register IR 
        rule = next_LEFT(rule);

        for(j=0; j<i; j++){
 
            // Skip jx bit right in IR
            rule = nextRIGHT(rule);     
        }

        // Write a 1 into current bit of IR
        SetRule(rule, '0', '1', RIGHT, rule+1);
        SetRule(rule, '1', '1', RIGHT, rule+1);
        rule++;

        // Skip back to Bit7 of the marked byte 
        rule = next_RIGHT(rule);
    }

    // ---- End of copy Instruction to IR ------

    // Change the last rule for remark
    // Skip back to the marker of market memory byte and remark
    SetRule(rule-1, '_', '$', RIGHT, rule);
    // 99 - Skip to the marker of the Instruction Register IR and remark it
    rule = next_LEFT(rule);
    //SetRule(rule-1, '_', '$', RIGHT, rule);
    SetRule(rule-1, '_', '$', RIGHT, RULE_END);

    // Exitpoint:  NotepadPointer steht auf I3 des Instruction Registers IR

    return rule;
}


uint16_t GenerateRuleFETCH(uint16_t rule) {

    // Entrypoint: Notepadpointer steht MAR0

    rule = PCtoMAR(rule);          // Copy Program Counter into MAR
    rule = IncPC(rule);            // Increment Program Counter
    rule = INSTtoIR(rule);         // Copy the current instruction to Register IR

    // Exitpoint:  NotepadPointer steht auf I3 des Instruction Registers IR

    return rule;
}