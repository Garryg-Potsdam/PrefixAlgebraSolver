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

// Parameters: char* - expression to get op of
// Returns: op of exp
extern char* getOp(char*);

// Parameters: char* - expression to get lhs of
// Returns: lhs of exp
extern char* getLhsString(char*);

// Parameters: char* - expression to get rhs of
// Returns: rhs of exp
extern char* getRhsString(char*);

// Parameters: char* - expression to check if valid open and close
//                   parens
// Returns: true if equal, false otherwise
extern bool checkExpForm(char*);

// Parameters: char* - the expression to grab substring of
//               int - where to start copying
//               int - where to stop copying
// Returns: the substring from exp
extern char* sub(char*, int, int);

// Parameters: char* - the operator to invert
// Returns: the inverted operator
extern char* invertOp(char*);
