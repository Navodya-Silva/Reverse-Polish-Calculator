#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

// Define the stack structure
typedef struct {
    int top;
    double items[STACK_SIZE];
} Stack;

// Function prototypes
void initializeStack(Stack *s);
void push(Stack *s, double value);
double pop(Stack *s);
double calculate(char op, double a, double b);
void printStack(const Stack *s);
void printInstructions(void);
void handleInput(Stack *stack);
void handleError(const char *message);

// Function to print instructions
void printInstructions(void) {
    printf("**==========================**\n");
    printf("  Reverse Polish Calculator\n");
    printf("=============================\n\n");
    printf("Instructions:\n");
    printf("  Enter numbers with '?'\n");
    printf("  Enter operations (+, -, *, /)\n");
    printf("  Enter '=' to show the top of the stack\n");
    printf("  Enter '#' to exit\n\n");
    printf("Enter your math expression: ");
}

// Function to handle input
void handleInput(Stack *stack) {
    char token;
    double operand, a, b;

    while (1) {
        scanf(" %c", &token); // Handle leading whitespaces
        if (token == '?') {
            scanf("%lf", &operand);
            push(stack, operand);
        } else if (token == '+' || token == '-' || token == '*' || token == '/') {
            b = pop(stack);
            a = pop(stack);
            push(stack, calculate(token, a, b));
        } else if (token == '=') {
            printf(">>> %lf\n", stack->items[stack->top]);
            printf("\n");
        } else if (token == '#') { // Stop condition
            printf("Goodbye!\n");
            break;
        } else {
            printf("Invalid input\n");
        }
        printStack(stack); // Print the stack state for debugging
    }
}

// Function to initialize the stack
void initializeStack(Stack *s) {
    s->top = -1;
}

// Function to push a value onto the stack
void push(Stack *s, double value) {
    if (s->top == STACK_SIZE - 1) {
        handleError("Stack Overflow");
    }
    s->items[++(s->top)] = value;
}

// Function to pop a value from the stack
double pop(Stack *s) {
    if (s->top == -1) {
        handleError("Stack Underflow");
    }
    return s->items[(s->top)--];
}

// Function to perform arithmetic operations
double calculate(char op, double a, double b) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0) {
                handleError("Division by zero");
            }
            return a / b;
        default:
            handleError("Invalid operator");
            return 0; // This line will never be reached due to exit in handleError
    }
}

// Function to print the stack for debugging
void printStack(const Stack *s) {
    printf("Stack state: ");
    for (int i = 0; i <= s->top; i++) {
        printf("%lf ", s->items[i]);
    }
    printf("\n");
}

// Function to handle errors
void handleError(const char *message) {
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

int main() {
    Stack stack;
    initializeStack(&stack);

    printInstructions();
    handleInput(&stack);

    return 0;
}

