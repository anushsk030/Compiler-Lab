#include <stdio.h>
#include <string.h>

char input[50];
char stack[50];
int top = -1;
int i = 0;

void printStep(char *action) {
    printf("\n%-20s\t%-20s\t%-20s", stack, input + i, action);
}

void reduce() {
    int changed;
    do {
        changed = 0;

        // S -> aSb
        if (top >= 2 && stack[top] == 'b' && stack[top - 1] == 'S' && stack[top - 2] == 'a') {
            stack[top - 2] = 'S';
            top -= 2;
            stack[top + 1] = '\0';
            changed = 1;
            printStep("Reduce S->aSb");
        }

        // S -> ab
        else if (top >= 1 && stack[top] == 'b' && stack[top - 1] == 'a') {
            stack[top - 1] = 'S';
            top--;
            stack[top + 1] = '\0';
            changed = 1;
            printStep("Reduce S->ab");
        }
    } while (changed);
}

int main() {
    printf("Enter input string: ");
    scanf("%s", input);

    printf("\n%-20s\t%-20s\t%-20s", "STACK", "INPUT", "ACTION");

    while (1) {
        // shift next symbol
        stack[++top] = input[i++];
        stack[top + 1] = '\0';
        printStep("Shift");

        reduce();

        // check acceptance
        if (i == strlen(input) && strcmp(stack, "S") == 0) {
            printStep("ACCEPT");
            printf("\n\nResult: ACCEPTED\n");
            break;
        }

        if (i >= strlen(input)) {
            printStep("REJECT");
            printf("\n\nResult: REJECTED\n");
            break;
        }
    }

    return 0;
}
