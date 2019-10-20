#include <stdio.h>
#include <stdlib.h>

/*
opcode is using x = 6, y = 26;
rs is using x = 5 y = 21
*/
int getRegisterValues(unsigned int instr, int x, int y);
int checkNegImmed(unsigned int immedValue);
int main(){
    unsigned int instr = 0x2484ffff;
    int opcode = instr >> 26;
    int registerLength = 5;
    int registerLocation = 21;
    int register2Location = 16;
    int immedLocation = 0;
    int immedLength = 15;
    int negMask = 1 << 14;

    int result = getRegisterValues(instr, registerLength, registerLocation);
    int result2 = checkNegImmed(getRegisterValues(instr, immedLength, immedLocation));
    printf("%d %d\n", result, result2);
    printf("%d",negMask);
}

int getRegisterValues(unsigned int instr, int x, int y){
    int mask = ((1 << x) - 1) << y;
    int registerValue = 0; 
    registerValue = instr & mask;
    registerValue = registerValue >> y;

    return registerValue;
}

int checkNegImmed(unsigned int immedValue){

    int negMask = 1 << 14;
    int negValue;

    if((immedValue & negMask) > 0){
        negValue = (~immedValue) + 1;
    }
    negValue = negValue >> 15;
    return negValue;

}
