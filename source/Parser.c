/*
  Garry Griggs
  Assignment 5: Solve in C
  Programming Languages
  Dr. Ladd
*/

#include "../headers/Parser.h"

// Parameters: exp - expression to check if valid open and close
//                   parens
// Returns: true if equal, false otherwise
bool malFormedExp(char* exp) {
    // Counters for left and right parens
    int leftParen = 0, rightParen = 0, i = 0;

    // Loop through and count parens
    for (; i < strlen(exp); i++) {
        if (exp[i] == '(')
            leftParen++;
        else if (exp[i] == ')')
            rightParen++;
    }
    // Return true if unequal amount of closing and opening parens
    return (leftParen != rightParen);
}

// Parameters:   exp - the expression to grab substring of
//             start - where to start copying
//              stop - where to stop copying
// Returns: the substring from exp
char* sub(char* exp, int start, int stop) {
    char* sub = malloc(100);
    int i;

    for (i = 0; start < stop; start++, i++)
        sub[i] = exp[start];

    sub[i] = '\0';
    return sub;
}

// Parameters: exp - expression to get op of
// Returns: op of exp
char* getOp(char* exp) {
    if (exp == NULL) {
        return NULL;
    } else if (malFormedExp(exp)) {
        printf("Error: malformed expression.\n");
        exit(1);
    }
    char* op = malloc(20);

    int start = 1, i;

    for (i = 0; i < strlen(exp); i++, start++) {
        if (exp[start] == ' ' || exp[start] == ')')
            break;
        op[i] = exp[start];
    }
    op[i] = '\0';
    return op;
}

// Parameters: exp - expression to get lhs of
// Returns: lhs of exp
char* getLhsString(char* exp) {
    // Check if valid formed expression
    if (exp == NULL) {
        return NULL;
    } else if (malFormedExp(exp)) {
        printf("Error: malformed expression.\n");
        exit(1);
    }

    int i, start, stop;

    // Starting value of the lhs side in exp
    start = (strlen(getOp(exp)) + 2);
    //if (strcmp(getOp(exp), "exp") == 0)
    //    printf("OP: %s\n", getOp(exp));
    stop = start;

    // Get the whole left expression wrapped in parens
    if (exp[start] == '(') {
        int leftParen;
        leftParen = 0;
        // get stopping position  of lhs based on parens
        for (i = start; i < strlen(exp); i++) {
            if (exp[i] == '(')
                leftParen++;
            if (exp[i] == ')')
                leftParen--;
            stop++;
            if (leftParen == 0)
                break;
        }
    } else { // Not wrapped in parens, grab lhs substring
        for (i = start; i < strlen(exp); i++) {
            if (exp[i] == ' ' || exp[i] == ')')
                break;
            else
                stop++;
        }
    }
    // Grab the substring of lhs form indexes
    char * lhs = malloc(100);
    lhs = sub(exp, start, stop);
    return lhs;
}

// Parameters: exp - expression to get rhs of
// Returns: rhs of exp
char* getRhsString(char* exp) {
    // Check if valid formed expression
    if (exp == NULL || isUnaryOP(getOp(exp))) {
        return NULL;
    } else if (malFormedExp(exp)) {
        printf("Error: malformed expression.\n");
        exit(1);
    }

    // Starting and stopping indexes for substring
    int start, stop, i;
    start = strlen(exp) - 2;
    stop = strlen(exp) - 2;
    // check if right side is enclose in parens
    if (exp[start] == ')') {
        int rightParen;
        rightParen = 0;
        // grab stopping point for right side based on parens
        for (i = start; i >= 0; i--) {
            if (exp[i] == ')')
                rightParen++;
            if (exp[i] == '(')
                rightParen--;
            stop--;
            if (rightParen == 0)
                break;
        }
    } else { // Not wrapped in parens, grab rhs substring
        for (i = start; i >= 0; i--) {
            if (exp[i] != ' ')
                stop--;
            else
                break;
        }
    }
    // Grab the substring of rhs form indexes
    char * rhs = malloc(100);
    rhs = sub(exp, stop + 1, start + 1);
    return rhs;
}

// Parameters: op - the operator to invert
// Returns: the inverted operator
char* invertOp(char* op) {
    if (op[0] == '=') return "=";
    if (op[0] == '-') return "+";
    if (op[0] == '+') return "-";
    if (op[0] == '*') return "/";
    if (op[0] == '/') return "*";
    if (strcmp(op, "log") == 0) return "exp";
    if (strcmp(op, "exp") == 0) return "log";
    if (strcmp(op, "sqrt") == 0) return "expt";
    if (strcmp(op, "expt") == 0) return "sqrt";
}
