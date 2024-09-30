#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NOT_IMPLEMENTED -1



/*
 *  Stduent functions - Full in each so that they return the integer value of the requested instruction
 */
int generate_load_instruction(int width, int destination, int address, int offset) {
    int opcode = 0x03;  
    return (offset << 20) | (address << 15) | (width << 12) | (destination << 7) | opcode;
}


int generate_store_instruction(int width, int address, int source, int offset) {
    int opcode = 0x23; 
    int imm_11_5 = (offset >> 5) & 0x7F;  
    int imm_4_0 = offset & 0x1F;          
    return (imm_11_5 << 25) | (source << 20) | (address << 15) | (width << 12) | (imm_4_0 << 7) | opcode;
}


int generate_math_instruction(int function, int a, int b, int destination) {
    int opcode = 0x33;  
    int funct7 = 0x00; 
    return (funct7 << 25) | (b << 20) | (a << 15) | (function << 12) | (destination << 7) | opcode;
}


int generate_constant_instruction(int value, int destination) {
    int opcode = 0x37; 
    return (value << 12) | (destination << 7) | opcode;
}

