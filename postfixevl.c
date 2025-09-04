#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    if (top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack[++top] = c;
}

char pop() {
    if (top == -1)
        return -1;
    return stack[top--];
}

int precedence(char c) {
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// Infix to Postfix Conversion
void infixToPostfix(char* exp, char* postfix) {
    int i, k = 0;
    char c;

    for (i = 0; exp[i] != '\0'; i++) {
        c = exp[i];

        if (isalnum(c)) { // operand
            postfix[k++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while ((c = pop()) != '(') {
                postfix[k++] = c;
            }
        } else { // operator
            while (top != -1 && precedence(stack[top]) >= precedence(c)) {
                postfix[k++] = pop();
            }
            push(c);
        }
    }

    while (top != -1) {
        postfix[k++] = pop();
    }
    postfix[k] = '\0';
}

// Evaluate Postfix Expression
int evalPostfix(char* postfix) {
    int stackEval[MAX];
    int topEval = -1;
    int i, op1, op2;

    for (i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];

        if (isdigit(c)) {
            stackEval[++topEval] = c - '0';
        } else {
            op2 = stackEval[topEval--];
            op1 = stackEval[topEval--];

            switch (c) {
                case '+': stackEval[++topEval] = op1 + op2; break;
                case '-': stackEval[++topEval] = op1 - op2; break;
                case '*': stackEval[++topEval] = op1 * op2; break;
                case '/': stackEval[++topEval] = op1 / op2; break;
                case '^': stackEval[++topEval] = (int)pow(op1, op2); break;
            }
        }
    }
    return stackEval[topEval];
}

int main() {
    char exp[MAX], postfix[MAX];
    printf("Enter infix expression (single-digit operands): ");
    scanf("%s", exp);

    infixToPostfix(exp, postfix);
    printf("Postfix Expression: %s\n", postfix);

    int result = evalPostfix(postfix);
    printf("Evaluation Result: %d\n", result);

    return 0;
}
