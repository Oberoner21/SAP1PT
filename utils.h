uint8_t symbol2num(char symbol){

    uint8_t num;
    switch(symbol){
        case '_': num = 0;   break;
        case '0': num = 1;   break;
        case '1': num = 2;   break;
        case '$': num = 3;   break;
    }

    return num;
}