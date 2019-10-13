#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// https://www.geeksforgeeks.org/program-decimal-binary-conversion/
// this helped me with how to convert decimal numbers to binary
char add[] = "add";
char addu[] = "addu";
char and[] = "and";
char jr[] = "jr";
char nor[] = "nor";
char or[] = "or";
char xor[] = "xor";
char slt[] = "slt";
char sltu[] = "sltu";
char sll[] = "sll";
char srl[] = "srl";
char sub[] = "sub";
char subu[] = "subu";


char mult[] = "mult";
char multu[] = "multu";
<<<<<<< HEAD
char div2[] = "div";
=======
char div1[] = "div";
>>>>>>> 9242892baa40d444e94472dcb3859eeeb3eb60c8
char divu[] = "divu";
char sra[] = "sra";
char mfhi[] = "mfhi";
char mflo[] = "mflo";
char mfc0[] = "mfc0";



char t0[] = "t0";
char t1[] = "t1";
char t2[] = "t2";
char t3[] = "t3";
char t4[] = "t4";
char t5[] = "t5";
char t6[] = "t6";
char t7[] = "t7";
char s0[] = "s0";
char s1[] = "s1";
char s2[] = "s2";
char s3[] = "s3";
char s4[] = "s4";
char s5[] = "s5";
char s6[] = "s6";
char s7[] = "s7";
char t8[] = "t8";
char t9[] = "t9";
char ra[] = "ra";

int machineCode[32];
int opCode = 0;
int rsValue = 0;
int rtValue = 0;
int rdValue = 0;
int shamtValue = 0;
int functValue = 0;


void checkInstructionSet(char opcode[], char rs[], char rt[], char rd[]);
void checkShiftInstructionSet(char opcode[], char rs[], char rt[], char rd[]);
void checkRs(char rs[]);
void checkRt(char rt[]);
void checkRd(char rd[]);

void machineCodeConverter(int rsValue, int rtValue, int rdValue, int shamtValue, int functValue);
// there are 12 r type instructions add, addu, and, jr, nor, or ,slt, sltu, sll, srl, sub, subu
// there are 8- 25 values from t0 - t7 then s0 - s7 then t8 - t9
int main(){

char opcode[5];
char rs[3];
char rt[3];
char rd[3];  

// [^,] means to read until a comma is here
printf("Enter in a R-format instruction without the $: ");
scanf("%s %[^,\n], %[^,\n], %[^,\n]" , opcode, rs, rt, rd );

if(!(strcmp(opcode, sll)) || !(strcmp(opcode, srl)) || !(strcmp(opcode, sra))){
    checkShiftInstructionSet(opcode, rs, rt, rd);
}

checkInstructionSet(opcode, rs, rt, rd);

machineCodeConverter(rsValue,rtValue,rdValue,shamtValue,functValue);




/*checkOpcode(opcode);
checkRs(rs);
checkRt(rt);
checkRd(rd);
*/

return 0;
}

void machineCodeConverter(int rsValue, int rtValue, int rdValue, int shamtvalue, int functValue){
    int counter = 0;
    int checker = 0;
    while(checker < 6){
        while(functValue > 0){
            machineCode[counter] = functValue % 2;
            functValue = functValue / 2;
            counter++;            
        }
        if(machineCode[checker] == 0){
            machineCode[checker] = 0;
        }     
        checker ++;
    }
    checker = 6;
    counter = 6;
    while(checker < 11){
        while(shamtValue > 0){
            machineCode[counter] = shamtValue % 2;
            shamtValue = shamtValue / 2;
            counter++;            
        }
        if(machineCode[checker] == 0){
            machineCode[checker] = 0;
        }     
        checker ++;
    }
    checker = 11;
    counter = 11;
    while(checker < 16){
        while(rdValue > 0){
            machineCode[counter] = rdValue % 2;
            rdValue = rdValue / 2;
            counter++;            
        }
        if(machineCode[checker] == 0){
            machineCode[checker] = 0;
        }     
        checker ++;
    }
    
    checker = 16;
    counter = 16;
    while(checker < 21){
        while(rtValue > 0){
            machineCode[counter] = rtValue % 2;
            rtValue = rtValue / 2;
            counter++;            
        }
        if(machineCode[checker] == 0){
            machineCode[checker] = 0;
        }     
        checker ++;
    }
    
    checker = 21;
    counter = 21;
    while(checker < 26){
        while(rsValue > 0){
            machineCode[counter] = rsValue % 2;
            rsValue = rsValue / 2;
            counter++;            
        }
        if(machineCode[checker] == 0){
            machineCode[checker] = 0;
        }     
        checker ++;
    }
    checker = 26;
    counter = 26;
    while(checker < 32){
        while(opCode> 0){
            machineCode[counter] = opCode % 2;
            opCode = opCode / 2;
            counter++;            
        }
        if(machineCode[checker] == 0){
            machineCode[checker] = 0;
        }     
        checker ++;
    }

    printf("Machine Code: ");
    for(int j = checker-1; j >= 0; j --){
        printf("%d", machineCode[j]);
    }
    printf("\n");
}

void checkInstructionSet(char opcode[], char rd[], char rs[], char rt[]){
    if(!(strcmp(opcode, add))){
        printf("Operation: add\n");
        checkRs(rs);
        checkRt(rt);
        checkRd(rd);
        printf("Shamt: 0\n");
        shamtValue = 0;
        printf("Funct: 20\n");
        functValue = 20;        
    } 
    if(!(strcmp(opcode, addu))){
        printf("Operation: addu\n");
        checkRs(rs);
        checkRt(rt);
        checkRd(rd);
        printf("Shamt: 0\n");
        shamtValue = 0;
        printf("Funct: 21\n");
        functValue = 21;
    }
    if(!(strcmp(opcode, and))){
        printf("Operation: and\n");
        checkRs(rs);
        checkRt(rt);
        checkRd(rd);
        printf("Shamt: 0\n");
        shamtValue = 0;
        printf("Funct: 24\n");
        functValue = 24;
    }
    if(!(strcmp(opcode, jr))){
        printf("Operation: jr\n");
        checkRs(rd);
        checkRt(rs);
        checkRd(rt);
        printf("Shamt: 0\n");
        shamtValue = 0;
        printf("Funct: 8\n");
        functValue = 8;
    }  
    if(!(strcmp(opcode, nor))){
        printf("Operation: nor\n");
        checkRs(rs);
        checkRt(rt);
        checkRd(rd);
        printf("Shamt: 0\n");
        shamtValue = 0;
        printf("Funct: 27\n");
        functValue = 27;
    }
    if(!(strcmp(opcode, or))){
        printf("Operation: or\n");
        checkRs(rs);
        checkRt(rt);
        checkRd(rd);
        printf("Shamt: 0\n");
        shamtValue = 0;
        printf("Funct: 25\n");
        functValue = 25;
    }
    if(!(strcmp(opcode, slt))){
        printf("Operation: slt\n");
        checkRs(rs);
        checkRt(rt);
        checkRd(rd);
        printf("Shamt: 0\n");
        shamtValue = 0;
        printf("Funct: 2a\n");
        functValue = 42;
    }
    if(!(strcmp(opcode, sltu))){
        printf("Operation: sltu\n");
        checkRs(rs);
        checkRt(rt);
        checkRd(rd);
        printf("Shamt: 0\n");
        shamtValue = 0;
        printf("Funct: 2b\n");
        functValue = 43;
    }

    if(!(strcmp(opcode, sub))){
        printf("Operation: sub\n");
        checkRs(rs);
        checkRt(rt);
        checkRd(rd);
        printf("Shamt: 0\n");
        shamtValue = 0;
        printf("Funct: 22\n");
        functValue = 22;
    }
    if(!(strcmp(opcode, subu))){
        printf("Operation: subu\n");
        checkRs(rs);
        checkRt(rt);
        checkRd(rd);
        printf("Shamt: 0\n");
        shamtValue = 0;
        printf("Funct: 23\n");
        functValue = 23;
    }
<<<<<<< HEAD
    if(!(strcmp(opcode, div2))){
=======
    if(!(strcmp(opcode, div1))){
>>>>>>> 9242892baa40d444e94472dcb3859eeeb3eb60c8
        printf("Operation: div\n");
        checkRs(rs);
        checkRt(rt);
        checkRd(rd);
        printf("Shamt: 0\n");
        shamtValue = 0;
        printf("Funct: 1a\n");
        functValue = 26;
    }
    if(!(strcmp(opcode, divu))){
        printf("Operation: divu\n");
        checkRs(rs);
        checkRt(rt);
        checkRd(rd);
        printf("Shamt: 0\n");
        shamtValue = 0;
        printf("Funct: 1b\n");
        functValue = 27;
    }
    if(!(strcmp(opcode, mult))){
        printf("Operation: multu\n");
        checkRs(rs);
        checkRt(rt);
        checkRd(rd);
        printf("Shamt: 0\n");
        shamtValue = 0;
        printf("Funct: 18\n");
        functValue = 18;
    }
    if(!(strcmp(opcode, multu))){
        printf("Operation: multu\n");
        checkRs(rs);
        checkRt(rt);
        checkRd(rd);
        printf("Shamt: 0\n");
        shamtValue = 0;
        printf("Funct: 19\n");
        functValue = 19;
    }
    if(!(strcmp(opcode, xor))){
        printf("Operation: xor\n");
        checkRs(rs);
        checkRt(rt);
        checkRd(rd);
        printf("Shamt: 0\n");
        shamtValue = 0;
        printf("Funct: 26\n");
        functValue = 26;
    }
    if(!(strcmp(opcode, mfhi))){
        printf("Operation: mfhi\n");
        printf("Rs: 0 (R0)\n"); 
        rsValue = 0;
        printf("Rt: 0 (R0)\n"); 
        rtValue = 0;
        checkRd(rd);
        printf("Shamt: 0\n");
        shamtValue = 0;
        printf("Funct: 16\n");
        functValue = 16;
    }
    if(!(strcmp(opcode, mflo))){
        printf("Operation: mflo\n");
        printf("Rs: 0 (R0)\n"); 
        rsValue = 0;
        printf("Rt: 0 (R0)\n"); 
        rtValue = 0;
        checkRd(rd);
        printf("Shamt: 0\n");
        shamtValue = 0;
        printf("Funct: 18\n");
        functValue = 18;
    }
    if(!(strcmp(opcode, mfc0))){
        printf("Operation: mfc0\n");
        opCode = 16;
        printf("Rs: 0 (R0)\n"); 
        rsValue = 0;
        checkRt(rt);
        checkRd(rd);
        printf("Shamt: 0\n");
        shamtValue = 0;
        printf("Funct: 00\n");
        functValue = 0;
    }    
}

void checkShiftInstructionSet(char opcode[], char rs[], char rt[], char rd[]){
    //sll and srl are differnt rs value is 0 and the last integer, rt is shamt
    if(!(strcmp(opcode, sll))){
        printf("Operation: sll\n");
        printf("Rs: 0 (R0)\n"); 
        rsValue = 0;
        checkRt(rt); 
        checkRd(rs);
        sscanf(rd, "%d", &shamtValue);
        printf("Shamt: %d\n",shamtValue);       
        printf("Funct: 00\n");
        functValue = 0;       
    }
    if(!(strcmp(opcode, srl))){
        printf("Operation: srl\n");
        printf("Rs: 0 (R0)\n");
        rsValue = 0;
        checkRt(rt); 
        checkRd(rs);
        sscanf(rd, "%d", &shamtValue);
        printf("Shamt: %d\n",shamtValue);
        printf("Funct: 02\n");
        functValue = 2;       
    }
    if(!(strcmp(opcode, sra))){
        printf("Operation: sra\n");
        printf("Rs: 0 (R0)\n");
        rsValue = 0;
        checkRt(rt); 
        checkRd(rs);
        sscanf(rd, "%d", &shamtValue);
        printf("Shamt: %d\n",shamtValue);
        printf("Funct: 03\n");
        functValue = 3;       
    }
}

void checkRs(char rs[]){
    if(!(strcmp(rs, t0))){
        printf("Rs: t0 (R8)\n");  
        rsValue = 8;
    }else
    if(!(strcmp(rs, t1))){
        printf("Rs: t1 (R9)\n"); 
        rsValue = 9; 
    }else
    if(!(strcmp(rs, t2))){
        printf("Rs: t2 (R10)\n"); 
        rsValue = 10; 
    }else
    if(!(strcmp(rs, t3))){
        printf("Rs: t3 (R11)\n");  
        rsValue = 11; 
    }else
    if(!(strcmp(rs, t4))){
        printf("Rs: t4 (R12)\n");  
        rsValue = 12; 
    }else
    if(!(strcmp(rs, t5))){
        printf("Rs: t5 (R13)\n");  
        rsValue = 13; 
    }else
    if(!(strcmp(rs, t6))){
        printf("Rs: t6 (R14)\n");  
        rsValue = 14; 
    }else
    if(!(strcmp(rs, t7))){
        printf("Rs: t7 (R15)\n");  
        rsValue = 15; 
    }else
    if(!(strcmp(rs, s0))){
        printf("Rs: s0 (R16)\n"); 
        rsValue = 16;  
    }else
    if(!(strcmp(rs, s1))){
        printf("Rs: s1 (R17)\n"); \
        rsValue = 17;  
    }else
    if(!(strcmp(rs, s2))){
        printf("Rs: s2 (R18)\n");
        rsValue = 18;   
    }else
    if(!(strcmp(rs, s3))){
        printf("Rs: s3 (R19)\n"); 
        rsValue = 19;  
    }else
    if(!(strcmp(rs, s4))){
        printf("Rs: s4 (R20)\n");  
        rsValue = 20; 
    }else
    if(!(strcmp(rs, s5))){
        printf("Rs: s5 (R21)\n");  
        rsValue = 21; 
    }else
    if(!(strcmp(rs, s6))){
        printf("Rs: s6 (R22)\n");  
        rsValue = 22; 
    }else
    if(!(strcmp(rs, s7))){
        printf("Rs: s7 (R23)\n"); 
        rsValue = 23;  
    }else
    if(!(strcmp(rs, t8))){
        printf("Rs: t8 (R24)\n");  
        rsValue = 24; 
    }else
    if(!(strcmp(rs, t9))){
        printf("Rs: t9 (R25)\n"); 
        rsValue = 25;  
    }else
    if(!(strcmp(rs, ra))){
        printf("Rs: ra(R31)\n");
        rsValue = 31; 
    }else{
        printf("Rs: 0 (R0)\n");
        rsValue = 0; 
    }   
}

void checkRt(char rt[]){
    if(!(strcmp(rt, t0))){
        printf("Rt: t0 (R8)\n");  
        rtValue = 8;
    }else
    if(!(strcmp(rt, t1))){
        printf("Rt: t1 (R9)\n");
        rtValue = 9;  
    }else
    if(!(strcmp(rt, t2))){
        printf("Rt: t2 (R10)\n");  
        rtValue = 10;
    }else
    if(!(strcmp(rt, t3))){
        printf("Rt: t3 (R11)\n");  
        rtValue = 11;
    }else
    if(!(strcmp(rt, t4))){
        printf("Rt: t4 (R12)\n");
        rtValue = 12;  
    }else
    if(!(strcmp(rt, t5))){
        printf("Rt: t5 (R13)\n");  
        rtValue = 13;
    }else
    if(!(strcmp(rt, t6))){
        printf("Rt: t6 (R14)\n"); 
        rtValue = 14; 
    }else
    if(!(strcmp(rt, t7))){
        printf("Rt: t7 (R15)\n");  
        rtValue = 15;
    }else
    if(!(strcmp(rt, s0))){
        printf("Rt: s0 (R16)\n");  
        rtValue = 16;
    }else
    if(!(strcmp(rt, s1))){
        printf("Rt: s1 (R17)\n"); 
        rtValue = 17; 
    }else
    if(!(strcmp(rt, s2))){
        printf("Rt: s2 (R18)\n"); 
        rtValue = 18; 
    }else
    if(!(strcmp(rt, s3))){
        printf("Rt: s3 (R19)\n");  
        rtValue = 19;
    }else
    if(!(strcmp(rt, s4))){
        printf("Rt: s4 (R20)\n"); 
        rtValue = 20; 
    }else
    if(!(strcmp(rt, s5))){
        printf("Rt: s5 (R21)\n");  
        rtValue = 21; 
    }else
    if(!(strcmp(rt, s6))){
        printf("Rt: s6 (R22)\n");  
        rtValue = 22; 
    }else
    if(!(strcmp(rt, s7))){
        printf("Rt: s7 (R23)\n"); 
        rtValue = 23;  
    }else
    if(!(strcmp(rt, t8))){
        printf("Rt: t8 (R24)\n"); 
        rtValue = 24;  
    }else
    if(!(strcmp(rt, t9))){
        printf("Rt: t9 (R25)\n");  
        rtValue = 25; 
    }else{
        printf("Rt: 0 (R0)\n");
        rtValue = 0; 
    }
    
}

void checkRd(char rd[]){
    if(!(strcmp(rd, t0))){
        printf("Rd: t0 (R8)\n");  
        rdValue = 8;
    }else
    if(!(strcmp(rd, t1))){
        printf("Rd: t1 (R9)\n");  
        rdValue = 9;
    }else
    if(!(strcmp(rd, t2))){
        printf("Rd: t2 (R10)\n");  
        rdValue = 10;
    }else
    if(!(strcmp(rd, t3))){
        printf("Rd: t3 (R11)\n");  
        rdValue = 11;
    }else
    if(!(strcmp(rd, t4))){
        printf("Rd: t4 (R12)\n");  
        rdValue = 12;
    }else
    if(!(strcmp(rd, t5))){
        printf("Rd: t5 (R13)\n");  
        rdValue = 13;
    }else
    if(!(strcmp(rd, t6))){
        printf("Rd: t6 (R14)\n");  
        rdValue = 14;
    }else
    if(!(strcmp(rd, t7))){
        printf("Rd: t7 (R15)\n");
        rdValue = 15;  
    }else
    if(!(strcmp(rd, s0))){
        printf("Rd: s0 (R16)\n"); 
        rdValue = 16; 
    }else
    if(!(strcmp(rd, s1))){
        printf("Rd: s1 (R17)\n");  
        rdValue = 17;
    }else
    if(!(strcmp(rd, s2))){
        printf("Rd: s2 (R18)\n");  
        rdValue = 18;
    }else
    if(!(strcmp(rd, s3))){
        printf("Rd: s3 (R19)\n"); 
        rdValue = 19; 
    }else
    if(!(strcmp(rd, s4))){
        printf("Rd: s4 (R20)\n");  
        rdValue = 20;
    }else
    if(!(strcmp(rd, s5))){
        printf("Rd: s5 (R21)\n");  
        rdValue = 21;
    }else
    if(!(strcmp(rd, s6))){
        printf("Rd: s6 (R22)\n");  
        rdValue = 22;
    }else
    if(!(strcmp(rd, s7))){
        printf("Rd: s7 (R23)\n");  
        rdValue = 23;
    }else
    if(!(strcmp(rd, t8))){
        printf("Rd: t8 (R24)\n"); 
        rdValue = 24; 
    }else
    if(!(strcmp(rd, t9))){
        printf("Rd: t9 (R25)\n");
        rdValue = 25;  
    }else{
        printf("Rd: 0 (R0)\n");
        rdValue = 0;
    }  
}