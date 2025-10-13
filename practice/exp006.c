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

        // T -> id
        if (top >= 1 && stack[top] == 'd' && stack[top - 1] == 'i') {
            stack[top - 1] = 'T';
            top--;
            stack[top + 1] = '\0';
            changed = 1;
            printStep("Reduce T->id");
        }

        // F -> T
        else if (top >= 0 && stack[top] == 'T') {
            stack[top] = 'F';
            stack[top + 1] = '\0';
            changed = 1;
            printStep("Reduce F->T");
        }

        // S -> F
        else if (top >= 0 && stack[top] == 'F') {
            stack[top] = 'S';
            stack[top + 1] = '\0';
            changed = 1;
            printStep("Reduce S->F");
        }

    } while (changed);
}

int main() {
    printf("Enter input string: ");
    scanf("%s", input);

    printf("\n%-20s\t%-20s\t%-20s", "STACK", "INPUT", "ACTION");

    while (1) {
        // Shift 'id' as a single token
        if (input[i] == 'i' && input[i + 1] == 'd') {
            stack[++top] = 'i';
            stack[++top] = 'd';
            stack[top + 1] = '\0';
            i += 2;
            printStep("Shift id");
        } else {
            stack[++top] = input[i++];
            stack[top + 1] = '\0';
            printStep("Shift");
        }

        reduce();

        // Acceptance condition
        if (i == strlen(input) && strcmp(stack, "S") == 0) {
            printStep("ACCEPT");
            printf("\n\nResult: ACCEPTED\n");
            break;
        }

        // Rejection condition
        if (i >= strlen(input)) {
            printStep("REJECT");
            printf("\n\nResult: REJECTED\n");
            break;
        }
    }

    return 0;
}
