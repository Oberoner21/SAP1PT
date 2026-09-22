
// Kopiert den Wert des Programm counters in das Memory Address Register
uint16_t PCtoMAR(uint16_t rule){

    // Entrypoint: Notepadpointer steht MAR0
    // Exitpoint: Programm counter P3

    // ++++++++++++++++++++ Copy Notepad to MAR +++++++++++++++++++++++++++

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

    // The comment numbers are the rule offsets 

    // Entrypoint: Notepadpointer steht auf P3 des Program Counters
    // Exitpoint:  NotepadPointer steht auf I3 des Instruction Registers IR

    uint8_t i;  

    // ------------- Mark the IR -------------
    rule = next$LEFT(rule);
    rule = next$LEFT(rule);
    SetRule(rule-1, '$', '_', RIGHT, rule);

    // ------- Skip to MAR and Mark MAR -------
    rule = next$RIGHT(rule);                    // Skip IR
    rule = next$RIGHT(rule);                    // Skip PC
    SetRule(rule-1, '$', '_', RIGHT, rule);     // Mark MAR

    // ------------- Byte search tree ---------

    // Notepadpointer is on position M3

    // 1
    SetRule(rule, '0', '0', RIGHT, rule+4);     // MAR3 = 0
    SetRule(rule, '1', '1', RIGHT, rule+1);     // MAR3 = 1
    rule++;
    // 2
    SetRule(rule, '0', '0', RIGHT, rule+6);     // MAR2 = 0
    SetRule(rule, '1', '1', RIGHT, rule+1);     // MAR2 = 1
    rule++;
    // 3
    SetRule(rule, '0', '0', RIGHT, rule+8);     // MAR1 = 0
    SetRule(rule, '1', '1', RIGHT, rule+1);     // MAR1 = 1
    rule++;
    // 4
    SetRule(rule, '0', '0', RIGHT, rule+26);    // MAR0 = 0
    SetRule(rule, '1', '1', RIGHT, rule+27);    // MAR0 = 1
    rule++;
    // 5
    SetRule(rule, '0', '0', RIGHT, rule+1);     // MAR3 = 0 & MAR2 = 0
    SetRule(rule, '1', '1', RIGHT, rule+4);     // MAR3 = 0 & MAR2 = 1
    rule++;
    // 6
    SetRule(rule, '0', '0', RIGHT, rule+1);     // MAR3 = 0 & MAR2 = 0 & MAR1 = 0
    SetRule(rule, '1', '1', RIGHT, rule+4);     // MAR3 = 0 & MAR2 = 0 & MAR1 = 1
    rule++;
    // 7
    SetRule(rule, '0', '0', RIGHT, rule+9);     // MAR3 = 0 & MAR2 = 0 & MAR1 = 0 & MAR0 = 0
    SetRule(rule, '1', '1', RIGHT, rule+10);    // MAR3 = 0 & MAR2 = 0 & MAR1 = 0 & MAR0 = 1
    rule++;
    // 8
    SetRule(rule, '0', '0', RIGHT, rule+5);     // MAR3 = 1 & MAR2 = 0 & MAR1 = 0
    SetRule(rule, '1', '1', RIGHT, rule+4);     // MAR3 = 1 & MAR2 = 0 & MAR1 = 1
    rule++;
    // 9
    SetRule(rule, '0', '0', RIGHT, rule+6);     // MAR3 = 0 & MAR1 = 0 & MAR1 = 0
    SetRule(rule, '1', '1', RIGHT, rule+5);     // MAR3 = 0 & MAR1 = 0 & MAR1 = 1
    rule++;
    // 10
    SetRule(rule, '0', '0', RIGHT, rule+8);     // MAR3 = 0 & MAR2 = 0 & MAR1 = 1 & MAR0 = 0;
    SetRule(rule, '1', '1', RIGHT, rule+9);     // MAR3 = 0 & MAR2 = 0 & MAR1 = 1 & MAR0 = 1;
    rule++;
    // 11
    SetRule(rule, '0', '0', RIGHT, rule+17);    // MAR3 = 1 & MAR2 = 1 & MAR1 = 1 & MAR0 = 0;
    SetRule(rule, '1', '1', RIGHT, rule+18);    // MAR3 = 1 & MAR2 = 1 & MAR1 = 1 & MAR0 = 1;
    rule++;
    // 12
    SetRule(rule, '0', '0', RIGHT, rule+14);    // MAR3 = 1 & MAR2 = 0 & MAR1 = 1 & MAR0 = 0;
    SetRule(rule, '1', '1', RIGHT, rule+15);    // MAR3 = 1 & MAR2 = 0 & MAR1 = 1 & MAR0 = 1;
    rule++;
    // 13
    SetRule(rule, '0', '0', RIGHT, rule+11);    // MAR3 = 1 & MAR2 = 0 & MAR1 = 0 & MAR0 = 0;
    SetRule(rule, '1', '1', RIGHT, rule+12);    // MAR3 = 1 & MAR2 = 0 & MAR1 = 1 & MAR0 = 1;
    rule++;
    // 14
    SetRule(rule, '0', '0', RIGHT, rule+8);     // MAR3 = 0 & MAR2 = 1 & MAR1 = 1 & MAR0 = 0;
    SetRule(rule, '1', '1', RIGHT, rule+9);     // MAR3 = 0 & MAR2 = 1 & MAR1 = 1 & MAR0 = 1;
    rule++;
    // 15
    SetRule(rule, '0', '0', RIGHT, rule+5);     // MAR3 = 0 & MAR2 = 1 & MAR1 = 0 & MAR0 = 0;
    SetRule(rule, '1', '1', RIGHT, rule+6);     // MAR3 = 0 & MAR2 = 1 & MAR1 = 0 & MAR0 = 1;
    rule++;

    // 16 - Mark Memory Byte0
    SetRule(rule, '$', '_', LEFT, rule+31);
    rule++;

    // 17 ... 31 - Skip $ right of MAR
    for(i=0; i<15; i++) {

        SetRule(rule, '$', '$', RIGHT, rule+15);
        rule++;    
    }

    // 32 - Mark Memory Byte
    rule = next$RIGHT(rule);
    SetRule(rule-1, '$', '_', LEFT, rule+14); 

    // 33...46 - Skip Memory Byte
    for(i=0; i<14; i++){

        rule = next$RIGHT(rule);
        SetRule(rule-1, '$', '$', RIGHT, rule-2);   
    }

    // 47 - Remark MAR
    rule = next_LEFT(rule);
    SetRule(rule-1, '_', '$', RIGHT, rule);

    // 48 - Skip to Bit7 of the marked byte 
    rule = next_RIGHT(rule);
    SetRule(rule-1, '_', '_', RIGHT, rule);

    // ---------- Copy Bit7 to Bit4 of the marked memory byte into IR ------------- 

    // Destination register is marked
    // Notepadpointer is on position Bit7 of the marked byte

    // 49 - Read Bit7 of marked memory Byte and branche
    SetRule(rule, '0', '0', RIGHT, rule+1);
    SetRule(rule, '1', '1', RIGHT, rule+5);
    rule++;
    // 50 - Skip to memory byte marker 
    rule = next_LEFT(rule, LEFT); 
    // 51 - Skip to bit3 of the market register IR 
    rule = next_LEFT(rule);
    // 52 - Write a 0 into IR3
    SetRule(rule, '0', '0', RIGHT, rule+4);
    SetRule(rule, '1', '0', RIGHT, rule+4);
    rule++;

    // 53 - Skip to memory byte marker 
    rule = next_LEFT(rule, LEFT);
    // 54 - Skip to mark of the market register IR 
    rule = next_LEFT(rule);
    // 55 - Write a 1 into IR3
    SetRule(rule, '0', '1', RIGHT, rule+1);
    SetRule(rule, '1', '1', RIGHT, rule+1);
    rule++;

    // 56 - Skip back to Bit7 of the marked byte 
    rule = next_RIGHT(rule);

    // ----- Bit6 -------
    
    // 57 - Skip right to bit6 of the marked memory byte
    rule = nextRIGHT(rule);
    // 58 - Read Bit6 of marked memory Byte and branche
    SetRule(rule, '0', '0', RIGHT, rule+1);
    SetRule(rule, '1', '1', RIGHT, rule+5);
    rule++;
    // 59 - Skip to memory byte marker 
    rule = next_LEFT(rule, LEFT);
    // 60 - Skip to bit3 of the market register IR 
    rule = next_LEFT(rule);
    // 61 - Skip right bit2 of the marked register IR
    rule = nextRIGHT(rule);  
    // 62 - Write a 0 into IR2
    SetRule(rule, '0', '0', RIGHT, rule+5);
    SetRule(rule, '1', '0', RIGHT, rule+5);
    rule++;

    // 63 - Skip to memory byte marker 
    rule = next_LEFT(rule, LEFT);
    // 64 - Skip to bit3 of the market register IR 
    rule = next_LEFT(rule);
    // 65 - Skip right bit2 of the marked register IR
    rule = nextRIGHT(rule);  
    // 66 - Write a 1 into IR2
    SetRule(rule, '0', '1', RIGHT, rule+1);
    SetRule(rule, '1', '1', RIGHT, rule+1);
    rule++;

    // 67 - Skip back to Bit7 of the marked byte 
    rule = next_RIGHT(rule);

    // ----- Bit5 -------
    
    // 68 - Skip right to bit6 of the marked memory byte
    rule = nextRIGHT(rule); 
    // 69 - Skip right to bit5 of the marked memory byte
    rule = nextRIGHT(rule); 
    // 70 - Read Bit5 of marked memory Byte and branche
    SetRule(rule, '0', '0', RIGHT, rule+1);
    SetRule(rule, '1', '1', RIGHT, rule+6);
    rule++;
    // 71 - Skip to memory byte marker 
    rule = next_LEFT(rule, LEFT); 
    // 72 - Skip to bit3 of the market register IR 
    rule = next_LEFT(rule);
    // 73 - Skip right bit2 of the marked register IR
    rule = nextRIGHT(rule);   
    // 74 - Skip right bit1 of the marked register IR
    rule = nextRIGHT(rule); 
    // 75 - Write a 0 into IR2
    SetRule(rule, '0', '0', RIGHT, rule+6);
    SetRule(rule, '1', '0', RIGHT, rule+6);
    rule++;

    // 76 - Skip to memory byte marker 
    rule = next_LEFT(rule, LEFT); 
    // 77 - Skip to bit3 of the market register IR 
    rule = next_LEFT(rule);
    // 78 - Skip right bit2 of the marked register IR
    rule = nextRIGHT(rule);    
    // 79 - Skip right bit1 of the marked register IR
    rule = nextRIGHT(rule); 
    // 80 - Write a 1 into IR2
    SetRule(rule, '0', '1', RIGHT, rule+1);
    SetRule(rule, '1', '1', RIGHT, rule+1);
    rule++;

    // 81 - Skip back to Bit7 of the marked byte
    rule = next_RIGHT(rule);

    // ----- Bit4 -------
    
    // 82 - Skip right to bit6 of the marked memory byte
    rule = nextRIGHT(rule); 
    // 83 - Skip right to bit5 of the marked memory byte
    rule = nextRIGHT(rule); 
    // 84 - Skip right to bit4 of the marked memory byte
    rule = nextRIGHT(rule); 
    // 85 - Read Bit4 of marked memory Byte and branche
    SetRule(rule, '0', '0', RIGHT, rule+1);
    SetRule(rule, '1', '1', RIGHT, rule+7);
    rule++;
    // 86 - Skip to memory byte marker 
    rule = next_LEFT(rule, LEFT); 
    // 87 - Skip right bit3 of the market register IR 
    rule = next_LEFT(rule);
    // 88 - Skip right bit2 of the marked register IR
    rule = nextRIGHT(rule);    
    // 89 - Skip right bit1 of the marked register IR
    rule = nextRIGHT(rule); 
    // 90 - Skip right bit0 of the marked register IR
    rule = nextRIGHT(rule); 
    // 91 - Write a 0 into IR2
    SetRule(rule, '0', '0', RIGHT, rule+7);
    SetRule(rule, '1', '0', RIGHT, rule+7);
    rule++;

    // 92 - Skip to memory byte marker 
    rule = next_LEFT(rule, LEFT);
    // 93 - Skip to bit3 of the market register IR 
    rule = next_LEFT(rule);
    // 94 - Skip right bit2 of the marked register IR
    rule = nextRIGHT(rule);   
    // 95 - Skip right bit1 of the marked register IR
    rule = nextRIGHT(rule); 
    // 96 - Skip right bit0 of the marked register IR
    rule = nextRIGHT(rule); 
    // 97 - Write a 1 into IR2
    SetRule(rule, '0', '1', RIGHT, rule+1);
    SetRule(rule, '1', '1', RIGHT, rule+1);
    rule++;

    // ---- End of copy Instruction to IR ------

    // 98 - Skip back to the marker of market memory byte and remark
    rule = next_RIGHT(rule);
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