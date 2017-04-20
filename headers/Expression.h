/*
  Garry Griggs
  Assignment 5: Solve in C
  Programming Languages
  Dr. Ladd
*/

#include <time.h>
#include "Types.h"
#include "Parser.h"

// Very simple Expression struct
// Treat as immutable: once one is declared
// exptype determines if variable, constant, expression, binaryop, or unaryop
typedef struct __Expression_t {
    ExpType type;
    char* piece;
    struct Expression* lhs;
    struct Expression* rhs;
} Expression;

// Parameters: Expression - the expression to build
//                  char* - the operator
//             Expression - the left hand side of the expression
//             Expression - the right hand side of expression
// Result: This sets all the values of a passed in expression
//         to the passed in values.
extern void setExpression(Expression*, char*, Expression*, Expression*);

// Parameters: Expression* - and expression to recursively build
//                   char* - the expression being parsed
// Post-Condition: edits passed in expression
extern void buildExpression(Expression*, char*);

// Parameters: Expression* - and expression to recursively build
//                   char* - the current expression piece being parsed
// Post-Condition: recursively builds expression parse tree
extern void recurBuildExp(Expression*, char*);

// Returns: char** - the list of variables
extern char** vars();

// Returns: varCount, the amount of variables in variables array
extern int getVarCount();

// Parameters: char* - the variable being added to list
// Post-Condition: adds variable to vars list
extern void addVar(char*);

// Post-Condition: prints variable list to terminal
extern void printVars();

// Post-Condition: resets variable list for next iteration
extern void resetVars();

// Parameters:       char* - the variable to solve for
//             Expression* - the expression tree to solve
// Post-Condition: solves for the variable passed in
// Returns: the solved expression
extern Expression* solve(char*, Expression*);

// Parameters: Expression - the first expression to compare
//             Expression - the second expression to compare
// Returns: true if the two expressions are identical, false otherwise
extern bool equals(Expression*, Expression*);

// Parameters: Expression - the expression to get the hash code for
// Returns: the integer hashcode of the operator
extern int hashCode(Expression*);

// Parameters: Expression* - the expression to get the lhs for
// Returns: lhs of expression
extern Expression* lhs(Expression*);

// Parameters: Expression* - the expression to get the rhs for
// Returns: rhs of expression
extern Expression* rhs(Expression*);
