int hexValue[32];
    int counter = 0;
    while(counter < 8){
        while(instr > 0){
            hexValue[counter] = instr % 10;
            instr /= 10;
            counter++;
        }
        if(counter > 6){
            if(hexValue[counter] == 0){
            hexValue[counter] = 0;
            }
            counter++;
        } else{
            break;
        }
    }

    int base = 1;
    int decimalValue = 0;
    
    for(int i = 0; i < counter ; i ++){
        if(hexValue[i] >= 0 && hexValue[i] <= 9){
            decimalValue += hexValue[i]*base;
            base = base * 16;
        } 
    }

    int binaryValue[32];
    int place1 = 0;
    int place2 = 0;
    while(place1 < 32){
        while(decimalValue > 0){
            binaryValue[place2] = decimalValue % 2;
            decimalValue = decimalValue / 2; 
            place2++;
        }
        if(binaryValue[place1] == 0){
            binaryValue[place1] = 0;
        }
        place1++;
    }
    

    for(int j = 0; j < 30; j ++){
        printf("%d", binaryValue[j]);
    }
    printf("\n");
       

    // opcode check
    int opcodeCheck = 0;
    int base2 = 1;
    for(int m = 26;m < 32;m++){
        if(binaryValue[m] == 1){
            opcodeCheck += base2;
        }
        base2 *= 2;
    }
    d->op = opcodeCheck;
    //printf("opcode: %d",opcodeCheck);
    
    int rsValue = 0, rtValue = 0, rdValue = 0, shamtValue = 0, immedValue = 0, targetValue = 0, functValue = 0;

    if(opcodeCheck == 0){
        // r format
        d->type = R;
        base2 = 1;
        for(int m = 21;m < 26;m++){
            if(binaryValue[m] == 1){
                rdValue += base2;
            }
            base2 *= 2;
        }
        d->regs.r.rd = rdValue;

        base2 = 1;
        for(int n = 16;n < 21;n++){
            if(binaryValue[n] == 1){
                rsValue += base2;
            }
            base2 *= 2;
        }
        d->regs.r.rs = rsValue;

        base2 = 1;
        for(int n = 11; n < 16; n++){
            if(binaryValue[n] == 1){
                rtValue += base2;
            }
            base2 *= 2;
        }
        d->regs.r.rt = rtValue;

        base2 = 1;
        for(int n = 6; n < 11; n++){
            if(binaryValue[n] == 1){
                shamtValue += base2;
            }
            base2 *= 2;
        }
        d->regs.r.shamt = shamtValue;

        base2 = 1;
        for(int n = 0; n < 6; n++){
            if(binaryValue[n] == 1){
                functValue += base2;
            }
            base2 *= 2;
        }
        d->regs.r.funct = functValue;
        
    }else if(opcodeCheck == 2 || opcodeCheck == 3){
        // j format
        d->type = J;
        base2 = 1;
        for(int m = 0;m < 26;m++){
        if(binaryValue[m] == 1){
            targetValue += base2;
        }
        base2 *= 2;
    }
    d->regs.j.target = targetValue;

    }else{
        //i format
        d->type = I;
        int base2 = 1;
        for(int m = 21; m < 26; m++){
            if(binaryValue[m] == 1){
                rsValue += base2;
            }
            base2 *= 2;
        }
        d->regs.i.rs = rsValue;

        base2 = 1;
        for(int n = 16; n < 21; n++){
            if(binaryValue[n] == 1){
                rtValue += base2;
            }
            base2 *= 2;
        }
        d->regs.i.rt = rtValue;

        base2 = 1;
        for(int n = 0;n < 16;n++){
            if(binaryValue[n] == 1){
                immedValue += base2;
            }
            base2 *= 2;
        }

        d->regs.i.addr_or_immed = immedValue;
    }

    rVals->R_rs = mips.registers[rsValue];
    rVals->R_rt = mips.registers[rtValue];
    rVals->R_rd = mips.registers[rdValue];