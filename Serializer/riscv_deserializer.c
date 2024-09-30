#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NOT_IMPLEMENTED -1

int get_opcode(int instruction) {
    return instruction & 0x7F;  
}


int get_instruction_type(int instruction) {
    int opcode = get_opcode(instruction);
    switch(opcode) {
        case 0x03: return 0;  // Load
        case 0x23: return 1;  // Store
        case 0x33: return 2;  // Math
        case 0x37: return 3;  // Constant
        default: return NOT_IMPLEMENTED;
    }
}

int get_width(int instruction) {
    return (instruction >> 12) & 0x7; 
}

int get_destination(int instruction) {
    return (instruction >> 7) & 0x1F; 
}

int get_load_address(int instruction) {
    return (instruction >> 15) & 0x1F; 
}

int get_load_offset(int instruction) {
    return (instruction >> 20) & 0xFFF;  
}

int get_store_offset(int instruction) {
    int firsthalf = (instruction >> 25) & 0x7F;  
    int secondhalf = (instruction >> 7) & 0x1F;   
    return (firsthalf << 5) | secondhalf;           
}

int get_store_source(int instruction) {
    return (instruction >> 20) & 0x1F;
}

int get_store_address(int instruction) {
    return (instruction >> 15) & 0x1F;
}

int get_math_function(int instruction) {
    return (instruction >> 12) & 0x7; 
}

int get_math_operand_a(int instruction) {
    return (instruction >> 15) & 0x1F; 
}

int get_math_operand_b(int instruction) {
    return (instruction >> 20) & 0x1F;
}

int get_constant_value(int instruction) {
    return (instruction >> 12) & 0xFFFFF;
}

const char* int_to_register(int idx) {
    if (idx >= 32) {
        printf("[ERROR] Bad register index\n");
        exit(-3);
    }
    return ((const char*[]){"zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
                            "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"})[idx];
}

const char* int_to_function(int idx) {
    if (idx >= 8) {
        printf("[ERROR] Bad function index\n");
        exit(-3);
    }
    return ((const char*[]){"add", "sll", "slt", "sltu", "xor", "srl", "or", "and"})[idx];
}

const char* int_to_width(int idx) {
    if (idx >= 5 || idx == 0x3) {
        printf("[ERROR] Bad width index\n");
        exit(-3);
    }
    return ((const char*[]){"8-bits", "16-bits", "32-bits", "", "8-bits (unsigned)", "16-bits (unsigned)"})[idx];
}

int is_implemented(const char* name, int (*fn)(int), int instruction) {
    int opcode = fn(instruction);
    if (opcode == NOT_IMPLEMENTED) {
        printf("[ERROR] `%s` has not been implemented\n", name);
        exit(-2);
    }
    return opcode;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("[ERROR] Invalid arguments\n");
        return -1;
    }
    int instruction = strtol(argv[1], NULL, 0);
    if (instruction == 0) {
        printf("[ERROR] Instruction was not a valid number");
        return -2;
    }

    printf("\n\n    Instruction  ==  ");
    for (int i=31; i>=0; i--) {
        printf("%d", (instruction >> i) & 0x1);
        if (i % 4 == 0) printf(" ");
    }
    printf("\n\n");
    switch (is_implemented("get_instruction_type", get_instruction_type, get_opcode(instruction))) {
        case 0x0 : {
            int width = is_implemented("get_width", get_width, instruction);
            int src = is_implemented("get_load_address", get_load_address, instruction);
            int offset = is_implemented("get_load_offset", get_load_offset, instruction);
 printf("    Load %s from address %s + offset %d\n", int_to_width(width), int_to_register(src), offset);
            break;
        }
        case 0x8 : {
            int width = is_implemented("get_width", get_width, instruction);
            int src = is_implemented("get_store_source", get_store_source, instruction);
            int offset = is_implemented("get_store_offset", get_store_offset, instruction);
            printf("    Store %s from register %s to address %s + offset %d\n", int_to_width(width), int_to_register(src), int_to_register(get_store_address(instruction)), offset);
            break;
        }
        case 0xC : {
            int fn = is_implemented("get_math_function", get_math_function, instruction);
            int op_a = is_implemented("get_math_operand_a", get_math_operand_a, instruction);
            int op_b = is_implemented("get_math_operand_b", get_math_operand_b, instruction);
            printf("    %s register %s and register %s\n", int_to_function(fn), int_to_register(op_a), int_to_register(op_b));
            break;
        }
        case 0xD : {
            int value = is_implemented("get_constant_value", get_constant_value, instruction);
            printf("    Load constant %d into register %s\n", value, int_to_register(get_destination(instruction)));
            break;
        }
        default : {
            printf("[ERROR] Unknown instruction type\n");
            return -1;
        }
    }
    return 0;
}