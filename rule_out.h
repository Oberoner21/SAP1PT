/*
    SAP1PT - SAP1 Pure Turing
    Modul:  rule_out.h

    Copyright(C) 2026 by Oberoner
*/

/*
    Instruction rule for OUT
    Entry conditions: IR and current MMB is marked
    Entry point     : NP pointer position I0 of Instruction Register IR
    Exit point      : NP pointer position M0 of Memory Address Register MAR 
    Rules           : 205 
*/
void GenerateRuleOUT(uint16_t rule) {

    uint8_t i;

    // Remark IR
    SetRule(rule, '_', '_', LEFT, rule+1);
    SetRule(rule, '0', '0', LEFT, rule+1);
    SetRule(rule, '1', '1', LEFT, rule+1);
    SetRule(rule, '$', '$', LEFT, rule+1);
    rule++;

    rule = next_LEFT(rule);
    SetRule(rule-1, '_', '$', LEFT, rule);

    // Mark the Output register
    rule = next$LEFT(rule);
    SetRule(rule-1, '$', '_', LEFT, rule);

    // Mark register A/B
    rule = next$LEFT(rule);
    SetRule(rule-1, '$', '_', RIGHT, rule);

    // Copy interleaved A register into Output register
    rule = CopyAtoMMB(rule);

    // Remark A/B
    rule = nextLEFT(rule);
    SetRule(rule, '_', '$', RIGHT, rule+1);
    rule++;

    // Seek to O7
    rule = next_RIGHT(rule);
    SetRule(rule-1, '_', '_', RIGHT, rule); 

    // Out A

    for(i=0; i<8; i++) {

        SetRule(rule, '0', '0', RIGHT, rule+1, CLKOUT);
        SetRule(rule, '1', '1', RIGHT, rule+1, CLKOUT);
        rule++;

        // Bei i=7 setzt das Lesen und Schreiben des Zeichens '$' (2)
        // die Datenleitung DATA1 von LOW auf HIGH und triggert damit
        // die Datenübernahme vom Shift- in das Ausgaberegister des
        // 75HC565 Schieberegisters.
        rule = nextLEFT(rule);      // Set CLKOUT LOW
        rule = nextRIGHT(rule);
    }

    // Seek right to MMB and remarke it
    rule = next_RIGHT(rule);
    SetRule(rule-1, '_', '$', LEFT, rule);
    // Seek left to Output register and remark it
    rule = next_LEFT(rule);
    SetRule(rule-1, '_', '$', RIGHT, rule);
    // Skip right Output register
    rule = next$RIGHT(rule);   
    // Skip right Instruction Register IR
    rule = next$RIGHT(rule);     
    // Skip right Program counter PC
    rule = next$RIGHT(rule); 
    // Skip right MAR and go to RULE_FETCH
    rule = next$RIGHT(rule);
    SetRule(rule-1, '$', '$', LEFT, RULE_FETCH); 

}