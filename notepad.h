/*
    SAP1PT - SAP1 Pure Turing
    Modul:  notepad.h

    Copyright(C) 2026 by Oberoner
*/

#define     NOTEPADSIZE     0x0100
#define     REG_A_START     5           // Notepad start position of register A/B
#define     MEMSTART        49          // Notepad start position of 16 byte SAP1 Memory


// Fibonacci 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233
//           0x01, 0x02, 0x03, 0x05, 0x08, 0x0D, 0x15, 0x22, 0x37, 0x59, 0x90, 0xE9
// unsigned char Program[16] = {
//                     // Fibonacci
// 	0x51,			//	LDI 0x1
// 	0x4E,			//	STA [0xE]
// 	0x50,			//	LDI 0x0
// 	0x2E,			//	ADD [0xE]
// 	0x70,			//	JC 0x0
// 	0xE0,			//	OUT
// 	0x4F,			//	STA [0xF]
// 	0x1E,			//	LDA [0xE]
// 	0x4D,			//	STA [0xD]
// 	0x1F,			//	LDA [0xF]
// 	0x4E,			//	STA [0xE]
// 	0x1D,			//	LDA [0xD]
// 	0x63,			//	JMP 0x3
// 	0x00,
// 	0x00,
// 	0x00
// };

// unsigned char Program[16] = {
//     // Sub [0xE] - [0xF]
// 	0x1E,			//	LDA [0xE]
// 	0x3F,			//	SUB [0xF]
// 	0xE0,			//	OUT
// 	0xF0,			//	HLT
// 	0x00,
// 	0x00,
// 	0x00,
// 	0x00,
// 	0x00,
// 	0x00,
// 	0x00,
// 	0x00,
// 	0x00,
// 	0x00,
// 	0x28,
// 	0x14
// };

unsigned char Program[16] = {
    // UP/Down counter
	0x1E,			//	LDA [0xE]
	0x3F,			//	SUB [0xF]
	0xE0,			//	OUT
    0x85,           //  JZ 0x5
    0x61,           //  JMP 0x1
	0x2F,           //  ADD [0xF]
	0x71,           //  JC 0x1
	0xE0,           //  OUT
	0x65,           //  JMP 5
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0xFF,
	0x01
};


const char SAP1_REGISTERS[] = (
    // ZC A/B              Output   IR   PC       MAR
    "$$10$0000000000000000$00000000$0000$00000001$0000"
);
const uint16_t npSize = 196;

uint16_t notePad[NOTEPADSIZE];
char outBuffer[10];


void makeOutStr() {

    // Erstellt aus dem Wert des Registers A einen Ausgabestring in outBuffer

    uint8_t outValue = 0;

    for(uint8_t i=REG_A_START; i<REG_A_START+16; i+=2) {

        uint8_t bit = notePad[i] - 1;
        outValue = (outValue << 1) + bit;
    }

    sprintf(outBuffer, "%d", outValue);
}

void CopyProgram(){

    uint8_t npPointer = MEMSTART;

    for(uint8_t i=0; i<16; i++) {

        notePad[npPointer] = symbol2num('$');     // Start with $
        notePad[npPointer+1] = Program[i] & 0x80 ? symbol2num('1') : symbol2num('0');
        notePad[npPointer+2] = Program[i] & 0x40 ? symbol2num('1') : symbol2num('0');
        notePad[npPointer+3] = Program[i] & 0x20 ? symbol2num('1') : symbol2num('0');
        notePad[npPointer+4] = Program[i] & 0x10 ? symbol2num('1') : symbol2num('0');
        notePad[npPointer+5] = Program[i] & 0x08 ? symbol2num('1') : symbol2num('0');
        notePad[npPointer+6] = Program[i] & 0x04 ? symbol2num('1') : symbol2num('0');
        notePad[npPointer+7] = Program[i] & 0x02 ? symbol2num('1') : symbol2num('0');
        notePad[npPointer+8] = Program[i] & 0x01 ? symbol2num('1') : symbol2num('0');

        npPointer = npPointer + 9;
    }

    // Mark the end of the memory range with $$$
    notePad[npPointer] = symbol2num('$');
    notePad[npPointer+1] = symbol2num('$'); 
    notePad[npPointer+2] = symbol2num('$'); 
}


void BuildNotepad()
{

    for(uint16_t i=0; i<MEMSTART+1; i++)
    {
        notePad[i] = symbol2num(SAP1_REGISTERS[i]);
    }

    CopyProgram();
}