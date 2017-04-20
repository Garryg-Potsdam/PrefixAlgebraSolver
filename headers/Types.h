/*
  Garry Griggs
  Assignment 5: Solve in C
  Programming Languages
  Dr. Ladd
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

// enum defines the types of expression parts
// for construction of structs in expression pieces
typedef enum ExpressionType {
    VARIABLE,
    CONSTANT,
    BINARYOP,
    UNARYOP,
    EXPRESSION,
    NEGUNARY,
    ENUMNULL
} ExpType;

// Parameters:  char** - a list of strings
//               char* - item to check in list for
//                 int - the size of the list
// Returns: true if item is in list, false otherwise
bool isInList(char**, char*, int);

// Parameters: char* to get type of
// Returns: ExpType - the type of the expression string
//                    (unaryop, binaryop, constant, variable)
extern ExpType getType(char*);

// Parameters: char* to check if operator
// Returns: true if is, false otherwise
extern bool isOperator(char*);

// Parameters: char* to check if negative unary operator
// Returns: true if is, false otherwise
extern bool isNegUnary(char*);

// Parameters: char* to check if binaryop
// Returns: true if is, false otherwise
extern bool isBinaryOP(char*);

// Parameters: char* to check if unaryop
// Returns: true if is, false otherwise
extern bool isUnaryOP(char*);

// Parameters: char* to check if constant
// Returns: true if is, false otherwise
extern bool isConstant(char*);
