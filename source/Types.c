/*
  Garry Griggs
  Assignment 5: Solve in C
  Programming Languages
  Dr. Ladd
*/

#include "../headers/Types.h"

// Parameters:  list - a list of strings
//             piece - item to check in list for
//              size - the size of the list
// Returns: true if item is in list, false otherwise
bool isInList(char ** list, char* piece, int size) {
    int i;
    // Check if is an operator in the list
    for (i = 0; i < size; i++)
        if (strcmp(piece, list[i]) == 0)
            return true;
    return false; // not op, return
}

// Parameters: char* to get type of
// Returns: ExpType - the type of the expression string
//                    (unaryop, binaryop, constant, variable)
ExpType getType(char* piece) {
    // check if negative unary op
    if (piece[0] == '(' && isNegUnary(piece)) {
        return NEGUNARY;
    }

    // check  its a paren surrounded expression
    if (piece[0] == '(') {
        return EXPRESSION;
    }
    // check if it is an operator either binary or unary
    if (isOperator(piece)) {
        if (isBinaryOP(piece)) {
            return BINARYOP;
        } else if (isUnaryOP(piece)) {
            return UNARYOP;
        } else {
            printf("Your code done fucked up.\n");
            exit(1);
        }
    // check if it is a constant
    } else if (isConstant(piece)) {
        return CONSTANT;
    } else { // nothing else must be a variable
        return VARIABLE;
    }
}

// Parameters: piece - to check if negative unary operator
// Returns: true if is, false otherwise
bool isNegUnary(char* piece) {
    return (piece[1] == '-' &&
            strcmp((const char*)getLhsString(piece),
                   (const char*)getRhsString(piece)) == 0);
}

// Parameters: piece - to check if operator
// Returns: true if is, false otherwise
bool isOperator(char* piece) {
    char* ops[9] = {"=", "+", "-", "*", "/", "expt", "sqrt", "exp", "log"};
    return isInList(ops, piece, 9);
}

// Parameters: piece - to check if binaryop
// Returns: true if is, false otherwise
bool isBinaryOP(char* piece) {
    char* ops[5] = {"=", "+", "-", "*", "/"};
    return isInList(ops, piece, 5);
}

// Parameters: piece - to check if unaryop
// Returns: true if is, false otherwise
bool isUnaryOP(char* piece) {
    char* ops[4] = {"expt", "sqrt", "exp", "log"};
    return isInList(ops, piece, 4);
}

// Parameters: piece - to check if constant
// Returns: true if is, false otherwise
bool isConstant(char* piece) {
    if (strcmp(piece, "pi") == 0)
        return true;
    float f = atof(piece);
    return !(f == 0.0);
}
