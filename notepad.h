#define     NOTEPADSIZE     0x0100

//const char npItems[] = ("$$01_00110$0010011011001001$");        // 0x5A + 0x29 = 0x83

const char npItems[] = (
    "$$10$0000000000000000$00000000$0000$00000001$0000$01010001$01001110$01010000$00101110$01010001$01001110$01010000$00101110$01010001$01001110$01010000$00101110$01010001$01001110$01010000$01010000$$$"
);
const uint16_t npSize = 196;

int notePad[NOTEPADSIZE];

const uint8_t PC = 0;
uint8_t nppPC = 42;      // Notepad position of $ right C1

void SetPC(){

    notePad[nppPC] = PC & 0x01 ? 2 : 1;
    notePad[nppPC-2] = PC & 0x02 ? 2 : 1;
    notePad[nppPC-4] = PC & 0x04 ? 2 : 1;
    notePad[nppPC-6] = PC & 0x08 ? 2 : 1;
}

void copyNPItems()
{
    char npItem;
    for(uint16_t i=0; i<npSize; i++)
    {
        notePad[i] = symbol2num(npItems[i]);
    }

    SetPC();
}