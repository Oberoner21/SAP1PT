
uint16_t GenerateRuleRESET(uint16_t rule) {

    // Entrypoint is notepad pointer position 0

    // ------------ Skip to position MAR0 -------------

    rule = next$RIGHT(rule);                        // Skip first $
    rule = next$RIGHT(rule);                        // Skip second $
    rule = next$RIGHT(rule);                        // Skip the flags
    rule = next$RIGHT(rule);                        // Skip the A/B Register
    rule = next$RIGHT(rule);                        // Skip the Output Register
    rule = next$RIGHT(rule);                        // Skip the Instruction Register
    rule = next$RIGHT(rule);                        // Skip the Program counter

    rule = next$RIGHT(rule);                        // Skip the MAR an go to rule FETCH
    SetRule(rule-1, '$', '$', LEFT, rule);

    return rule;
}