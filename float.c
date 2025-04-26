#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main() {
    char mode;
    char input[100];

    printf("Enter mode (-f for float to binary, -b for binary to float): ");
    scanf(" %c", &mode);
    
    if (mode != 'f' && mode != 'b') {
        fprintf(stderr, "Invalid mode: %c\n", mode);
        return 1;
    }

    printf("Enter value: ");
    scanf("%s", input);

    if (mode == 'f') {
        float value = strtof(input, NULL);
        
        int sign = (value < 0) ? 1 : 0;
        value = fabs(value);
        int exponent = 0;
        while (value >= 2) {
            value /= 2;
            exponent++;
        }
        while (value < 1) {
            value *= 2;
            exponent--;
        }
        exponent += 127; 
        float mantissa = value - 1;

        printf("Binary: ");
        for (int i = 31; i >= 0; i--) {
            printf("%d", (int)(mantissa * pow(2, i)));
        }
        printf("\n");
        printf("Sign: %d\n", sign);
        printf("Exponent: %d\n", exponent);
        printf("Mantissa: %.7g\n", mantissa);
        printf("Value: %.7g\n", value);
    } else {
        int sign = input[0] - '0';
        int exponent = atoi(input + 1);
        float mantissa = 1;
        for (int i = 9; i >= 0; i--) {
            mantissa += (input[i + 1] - '0') * pow(2, -i - 1);
        }

        exponent -= 127;
        if (sign) {
            mantissa *= -1;
        }

        float value = mantissa * pow(2, exponent);

        printf("Binary: %s\n", input);
        printf("Sign: %d\n", sign);
        printf("Exponent: %d\n", exponent);
        printf("Mantissa: %.7g\n", mantissa);
        printf("Value: %.7g\n", value);
    }

    return 0;
}