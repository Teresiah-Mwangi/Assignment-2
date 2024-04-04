#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Stack {
    int top;
    int Stack_Storage ;
    int* array;
};

int main() {
    char exp[100];
    printf("Enter an infix expression: ");
    scanf("%99s", exp);
    printf("Expression:\n%s\n", exp);
    ConvertToPostfix(exp);
    printf("Result: %d\n", evalueuatePostfix(exp));
    return 0;
}
struct Stack* createStack(int Stack_Storage ) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack)
        return NULL;
    stack->top = -1;
    stack->Stack_Storage =Stack_Storage;
    stack->array = (int*)malloc(stack->Stack_Storage * sizeof(int));
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

char peek(struct Stack* stack) {
    return stack->array[stack->top];
}

char pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '$';
}

void push(struct Stack* stack, char op) {
    stack->array[++stack->top] = op;
}

int isOperand(char ch) {
    return isdigit(ch);
}

int Prec(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '%':
            return 3;
    }
    return -1;
}
int ConvertToPostfix(char* exp) {
    int i, k;
    struct Stack* stack = createStack(strlen(exp));
    if (!stack)
        return -1;

    for (i = 0, k = -1; exp[i]; ++i) {
        if (isOperand(exp[i]))
            exp[++k] = exp[i];
        else if (exp[i] == '(')
            push(stack, exp[i]);
        else if (exp[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(')
                exp[++k] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != '(')
                return -1;
            else
                pop(stack);
        } else {
            while (!isEmpty(stack) && Prec(exp[i]) <= Prec(peek(stack)))
                exp[++k] = pop(stack);
            push(stack, exp[i]);
        }
    }

    while (!isEmpty(stack))
        exp[++k] = pop(stack);
    exp[++k] = '\0';

    printf("Postfix Expression:\n");
    for (int i = 0; exp[i]; i++) {
        printf("%c ", exp[i]);
    }
    printf("\n");
}

int evalueuatePostfix(char* exp) {
    struct Stack* stack = createStack(strlen(exp));
    int i;
    if (!stack)
        return -1;

    for (i = 0; exp[i]; ++i) {
        if (isdigit(exp[i]))
            push(stack, exp[i] - '0');
        else {
            int value1 = pop(stack);
            int value2 = pop(stack);
            switch (exp[i]) {
                case '+':
                    push(stack, value2 + value1);
                    break;
                case '-':
                    push(stack, value2 - value1);
                    break;
                case '*':
                    push(stack, value2 * value1);
                    break;
                case '/':
                    push(stack, value2 / value1);
                    break;
                case '%':
                    push(stack, value2 % value1);
                    break;
            }
        }
    }
    return pop(stack);
}

