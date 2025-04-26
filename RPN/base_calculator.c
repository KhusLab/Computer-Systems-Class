#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} Stack;

void initStack(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, int value) {
    if (stack->top == MAX_STACK_SIZE - 1) {
        printf("Stack overflow!\n");
        return;
    }
    stack->data[++stack->top] = value;
}

int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow!\n");
        return -1;
    }
    return stack->data[stack->top--];
}


unsigned int customStrtoul(char* str, int base) {
    unsigned int result = 0;
    int i = 0;
    if (base == 2) {
        i = 2; 
    } else if (base == 16) {
        i = 2; 
    }
    for (; str[i] != '\0'; i++) {
        if (base == 2) {
            result = result * 2 + (str[i] - '0');
        } else if (base == 10) {
            result = result * 10 + (str[i] - '0');
        } else if (base == 16) {
            if (str[i] >= '0' && str[i] <= '9') {
                result = result * 16 + (str[i] - '0');
            } else {
                result = result * 16 + (str[i] - 'a' + 10);
            }
        }
    }
    return result;
}

// Operations
int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int divs(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero!\n");
        return -1;
    }
    return a / b;
}

int mul(int a, int b) {
    return a * b;
}

int main(int argc, char* argv[]) {
    Stack stack;
    initStack(&stack);

    for (int i = 1; i < argc; i++) {
        char* token = argv[i];
        if (strcmp(token, "add") == 0) {
            int a = pop(&stack);
            int b = pop(&stack);
            push(&stack, add(a, b));
        } else if (strcmp(token, "sub") == 0) {
            int a = pop(&stack);
            int b = pop(&stack);
            push(&stack, sub(a, b));
        } else if (strcmp(token, "div") == 0) {
            int a = pop(&stack);
            int b = pop(&stack);
            push(&stack, divs(a, b));
        } else if (strcmp(token, "mult") == 0) {
            int a = pop(&stack);
            int b = pop(&stack);
            push(&stack, mul(a, b));
        } else {
            int base = 10;
            if (strncmp(token, "0b", 2) == 0) {
                base = 2;
            } else if (strncmp(token, "0x", 2) == 0) {
                base = 16;
            }
            int value = customStrtoul(token, base);
            push(&stack, value);
        }
    }

    if (!isEmpty(&stack)) {
        printf("%d", pop(&stack));
    }

    return 0;
}