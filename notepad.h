#define     NOTEPADSIZE     0x0100

// Fibonacci 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233
//           0x01, 0x02, 0x03, 0x05, 0x08, 0x0D, 0x15, 0x22, 0x37, 0x59, 0x90, 0xE9
unsigned char Fibonacci[16] = {
	0x51,			//	LDI 0x1
	0x4E,			//	STA [0xE]
	0x50,			//	LDI 0x0
	0x2E,			//	ADD [0xE]
	0x70,			//	JC 0x0
	0xE0,			//	OUT
	0x4F,			//	STA [0xF]
	0x1E,			//	LDA [0xE]
	0x4D,			//	STA [0xD]
	0x1F,			//	LDA [0xF]
	0x4E,			//	STA [0xE]
	0x1D,			//	LDA [0xD]
	0x63,			//	JMP 0x3
	0x00,
	0x00,
	0x00
};

const char npItems[] = (
    "$$10$0000000000000000$00000000$0000$00000001$0000$01010001$01001110$01010000$00101110$01110001$01001110$01010000$00101110$01010001$01001110$01010000$00101110$01010001$01001110$01010000$01010000$$$"
);
const uint16_t npSize = 196;

int notePad[NOTEPADSIZE];

const uint8_t MEMSTART = 49;    // Start position of memory in the notepad
const uint8_t A_START = 5;      // Start position of Register A/B in the notepad


char outBuffer[10];

void makeOutStr() {

    // Erstellt aus dem Wert des Registers A einen Ausgabestring in outBuffer

    uint8_t outValue = 0;

    outValue = outValue | notePad[A_START] == 2 ? 0x80 : 0x00;
    outValue = outValue | notePad[A_START+2] == 2 ? 0x40 : 0x00;
    outValue = outValue | notePad[A_START+4] == 2 ? 0x20 : 0x00;
    outValue = outValue | notePad[A_START+6] == 2 ? 0x10 : 0x00;
    outValue = outValue | notePad[A_START+8] == 2 ? 0x08 : 0x00;
    outValue = outValue | notePad[A_START+10] == 2 ? 0x04 : 0x00;
    outValue = outValue | notePad[A_START+12] == 2 ? 0x02 : 0x00;
    outValue = outValue | notePad[A_START+14] == 2 ? 0x01 : 0x00;

    sprintf(outBuffer, "%d", outValue);
}

void CopyProgram(){

    uint8_t npPointer = MEMSTART;

    for(uint8_t i=0; i<16; i++) {

        notePad[npPointer] = 3;     // Start with $
        notePad[npPointer+1] = Fibonacci[i] & 0x80 ? 2 : 1;
        notePad[npPointer+2] = Fibonacci[i] & 0x40 ? 2 : 1;
        notePad[npPointer+3] = Fibonacci[i] & 0x20 ? 2 : 1;
        notePad[npPointer+4] = Fibonacci[i] & 0x10 ? 2 : 1;
        notePad[npPointer+5] = Fibonacci[i] & 0x08 ? 2 : 1;
        notePad[npPointer+6] = Fibonacci[i] & 0x04 ? 2 : 1;
        notePad[npPointer+7] = Fibonacci[i] & 0x02 ? 2 : 1;
        notePad[npPointer+8] = Fibonacci[i] & 0x01 ? 2 : 1;

        npPointer = npPointer + 9;
    }
}

void copyNPItems()
{
    char npItem;
    for(uint16_t i=0; i<npSize; i++)
    {
        notePad[i] = symbol2num(npItems[i]);
    }

    CopyProgram();
}