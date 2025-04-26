#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Make stack, might've said make it max of 10?
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
        printf("Stack overflow!\n"); // get it.. stackoverflow
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
            if (isEmpty(&stack)) {
                printf("Error: Not enough operands!\n");
                initStack(&stack); 
                break;
            }
            int b = pop(&stack);
            if (isEmpty(&stack)) {
                printf("Error: Not enough operands!\n");
                initStack(&stack); 
                break;
            }
            int a = pop(&stack);
            int result = add(a, b);
            push(&stack, result);
        } else if (strcmp(token, "sub") == 0) {
            if (isEmpty(&stack)) {
                printf("Error: Not enough operands!\n");
                initStack(&stack); 
                break;
            }
            int b = pop(&stack);
            if (isEmpty(&stack)) {
                printf("Error: Not enough operands!\n");
                initStack(&stack); 
                break;
            }
            int a = pop(&stack);
            int result = sub(a, b);
            push(&stack, result);
        } else if (strcmp(token, "div") == 0) {
            if (isEmpty(&stack)) {
                printf("Error: Not enough operands!\n");
                initStack(&stack); 
                break;
            }
            int b = pop(&stack);
            if (isEmpty(&stack)) {
                printf("Error: Not enough operands!\n");
                initStack(&stack); 
                break;
            }
            int a = pop(&stack);
            int result = divs(a, b);
            push(&stack, result);
        } else if (strcmp(token, "mult") == 0) {
            if (isEmpty(&stack)) {
                printf("Error: Not enough operands!\n");
                initStack(&stack); 
                break;
            }
            int b = pop(&stack);
            if (isEmpty(&stack)) {
                printf("Error: Not enough operands!\n");
                initStack(&stack); 
                break;
            }
            int a = pop(&stack);
            int result = mul(a, b);
            push(&stack, result);
        } else {
            int value = atoi(token);
            push(&stack, value);
        }
    }

    if (!isEmpty(&stack)) {
        printf("%d", pop(&stack));
    }

    return 0;
}