#include <stdio.h>
#include <assert.h>

int charToDec(char c) {
    int d;
    d = (int)c;
    if (d >= 48 && d <= 57)
        return d - 48;
    else
        return d - 87;
}

char decToChar(int d) {
    if (d >= 0 && d <= 9)
        return (char)(d + 48);
    else
        return (char)(d + 87);
}

void printNum(int decNum, int b) {
    char bChar;
    if (decNum > 0) {
        bChar = decToChar(decNum % b);
        decNum = decNum / b;
        printNum(decNum, b);
        printf("%c", bChar);
    }
}

int main(void) {
    int a, b, decDig, decNum;
    char c;

    printf("Please enter the numbers base:\n");
    scanf("%d", &a);
    if (a < 2 || a > 16)
        printf("Invalid input base\n");
    assert(a >= 2 && a <= 16);

    printf("Please enter the desired base:\n");
    scanf("%d", &b);
    if (b < 2 || b > 16)
        printf("Invalid desired base\n");
    assert(b >= 2 && b <= 16);
    
    getchar();
    printf("Please enter a number in base %d:\n" , a);
    while ((c = getchar()) != '\n' && c != EOF) {
        decDig = charToDec(c);
        if (decDig < 0 || decDig >= a) 
            printf("Invalid number!\n");
        assert(decDig >= 0 && decDig < a);

        decNum = decNum * a + decDig;
    }

    printf("The result is: ");
    printNum(decNum, b);
    printf("%c", '\n');

    return 0;
}