#include <stdio.h>
#include <stdlib.h>

int main(){

    unsigned int mips = 2484ffff;

    int opcode, temp, instr;

    opcode = mips >> 26;

    temp = mips << 6;
    temp = temp >> 27;
    instr = temp;

    printf("%d\n", instr);
    
    

}