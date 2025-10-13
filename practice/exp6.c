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

        // E -> id
        if (top >= 1 && stack[top] == 'd' && stack[top - 1] == 'i') {
            stack[top - 1] = 'E';
            top--;
            stack[top + 1] = '\0';
            changed = 1;
            printStep("Reduce E->id");
        }

        // E -> (E)
        else if (top >= 2 && stack[top] == ')' && stack[top - 1] == 'E' && stack[top - 2] == '(') {
            stack[top - 2] = 'E';
            top -= 2;
            stack[top + 1] = '\0';
            changed = 1;
            printStep("Reduce E->(E)");
        }

        // E -> E+E
        else if (top >= 2 && stack[top] == 'E' && stack[top - 1] == '+' && stack[top - 2] == 'E') {
            stack[top - 2] = 'E';
            top -= 2;
            stack[top + 1] = '\0';
            changed = 1;
            printStep("Reduce E->E+E");
        }

        // E -> E*E
        else if (top >= 2 && stack[top] == 'E' && stack[top - 1] == '*' && stack[top - 2] == 'E') {
            stack[top - 2] = 'E';
            top -= 2;
            stack[top + 1] = '\0';
            changed = 1;
            printStep("Reduce E->E*E");
        }
    } while (changed);
}

int main() {
    printf("Enter input string: ");
    scanf("%s", input);

    printf("\n%-20s\t%-20s\t%-20s", "STACK", "INPUT", "ACTION");

    while (1) {
        // shift 'id' as a single token
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

        reduce(); // try reductions

        // check acceptance
        if (i == strlen(input) && strcmp(stack, "E") == 0) {
            printStep("ACCEPT");
            printf("\n\nResult: ACCEPTED\n");
            break;
        }

        // if input over and no full reduction
        if (i >= strlen(input)) {
            printStep("REJECT");
            printf("\n\nResult: REJECTED\n");
            break;
        }
    }

    return 0;
}
