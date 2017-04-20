/*
  Garry Griggs
  Assignment 5: Solve in C
  Programming Languages
  Dr. Ladd
*/

#include "../headers/Expression.h"

// varCount and variables keeps track of variables in expression
int varCount = 0;
char*  variables[20];

// Returns: char** - the list of variables
char** vars() {
    return variables;
}

// Returns: varCount, the amount of variables in variables array
int getVarCount() {
    return varCount;
}

// Parameters: var - the variable being added to list
// Post-Condition: adds variable to vars list
void addVar(char* var) {
    if (!isInList(variables, var, varCount)){
        variables[varCount] = var;
        varCount++;
    }
}

// Post-Condition: prints variable list to terminal
void printVars() {
    int i;
    printf("{%s", variables[0]);
    for (i = 1; i < varCount; i++)
        printf(", %s", variables[i]);
    printf("}\n");
}

// Post-Condition: resets variable list for next iteration
void resetVars() {
    varCount = 0;
}

// Parameters:       var - the variable to solve for
//             exp - the expression tree to solve
// Post-Condition: solves for the variable passed in and
//                 prints new expression
Expression* solve(char* var, Expression* exp) {
    // if found solution return
    if (strcmp(lhs(exp)->piece, var) == 0) {
        return exp;
    // if solution is on right side swap and return
    } else if (strcmp(rhs(exp)->piece, var) == 0) {
        Expression* temp = malloc(sizeof(Expression));
        temp->type  = exp->type;
        temp->piece = exp->piece;
        temp->lhs   = exp->rhs;
        temp->rhs   = exp->lhs;
    // if right side not an op return
    } else if (rhs(exp)->type != UNARYOP  &&
               rhs(exp)->type != BINARYOP &&
               rhs(exp)->type != NEGUNARY) {
        return NULL;
    } else { // do algebra
        // allocated pieces needed for solution
        Expression* tempRoot     = malloc(sizeof(Expression));
        Expression* tempRootTwo  = malloc(sizeof(Expression));
        Expression* tempLhs      = malloc(sizeof(Expression));
        Expression* tempOtherLhs = malloc(sizeof(Expression));
        Expression* tempRhs      = malloc(sizeof(Expression));
        Expression* innerLeft    = malloc(sizeof(Expression));
        Expression* innerRight   = malloc(sizeof(Expression));
        // if unary op, do unary op math
        if (rhs(exp)->type == UNARYOP) {
            innerLeft  = rhs(exp)->lhs;
            setExpression(tempLhs, invertOp(rhs(exp)->piece), exp->lhs, NULL);            
            setExpression(tempRoot, exp->piece, tempLhs, innerLeft);
            
            return solve(var, tempRoot);
        } else if (rhs(exp)->type == BINARYOP) { // binary op do binary algebra
            innerLeft  = rhs(exp)->lhs;
            innerRight = rhs(exp)->rhs;
            // special cased for divide and subtract for left side
            // flip lefts side to avoid complexity
            if (rhs(exp)->piece[0] == '/' || rhs(exp)->piece[0] == '-') {
                setExpression(tempLhs, rhs(exp)->piece, innerLeft, lhs(exp));
                setExpression(tempRoot, exp->piece, tempLhs, innerRight);
            } else { // else do normal left side algebra
                setExpression(tempLhs, invertOp(rhs(exp)->piece), lhs(exp), innerLeft);
                setExpression(tempRoot, exp->piece, tempLhs, innerRight);
            }
            
            // no special cases for right side algebra in binary ops
            setExpression(tempOtherLhs, invertOp(rhs(exp)->piece), lhs(exp), innerRight);
            setExpression(tempRootTwo, exp->piece, tempOtherLhs, innerLeft);
            // if solution down left side return, else return right side
            if (solve(var, tempRoot) != NULL)
                return solve(var, tempRoot);
            else
                return solve(var, tempRootTwo);
        
        } else if (rhs(exp)->type == NEGUNARY) { // negative number negate other side
            setExpression(tempLhs, getOp(rhs(exp)->piece), exp->lhs, NULL);
            innerLeft = rhs(exp)->lhs;
            setExpression(tempRhs, innerLeft->piece, NULL, NULL);
            setExpression(tempRoot, exp->piece, tempLhs, tempRhs);
            // solution found for neg unary op, return to avoid loops
            if (strcmp(rhs(tempRoot), var) == 0)
                return tempRoot;
            return solve(var, tempRoot);
        }
    }
}

// Parameters: this - the expression to get the lhs for
// Returns: lhs of expression
Expression* lhs(Expression* this) {
    return this->lhs;
}

// Parameters: this - the expression to get the rhs for
// Returns: rhs of expression
Expression* rhs(Expression* this) {
    return this->rhs;
}

// Parameters: this - the expression to build
//                  opratr - the operator
//             lhs - the left hand side of the expression
//             rhs - the right hand side of expression
// Result: This sets all the values of a passed in expression
//         to the passed in values.
void setExpression(Expression* this, char* piece, Expression* lhs, Expression* rhs) {
    this->type = getType(piece);
    if (this->type == EXPRESSION) {        
        this->piece = getOp(piece);
        this->type = getType(this->piece);
    } else {
        this->piece = piece;
    }
    if (this->type == VARIABLE) {
        addVar(this->piece);        
    }
    this->lhs = lhs;
    this->rhs = rhs;
}

// Parameters: this - and expression to recursively build
// Post-Condition: edits passed in expression
void buildExpression(Expression* this, char* exp) {
    // test if just variable statement
    if (this->type != BINARYOP && this->type != UNARYOP)
        return;
    recurBuildExp(this, exp);
}

// Parameters: Expression* - and expression to recursively build
//                   char* - the current expression piece being parsed
// Post-Condition: recursively builds expression parse tree
void recurBuildExp(Expression* this, char* exp) {
    if (this->type != BINARYOP && this->type != UNARYOP && this->type != NEGUNARY)
        return;

    // declare left side build set and recur
    Expression* lhs = malloc(sizeof(Expression));
    setExpression(lhs, getLhsString(exp), NULL, NULL);
    this->lhs = lhs;
    recurBuildExp(lhs, getLhsString(exp));

    // If not a unary op declare right side build set and recur
    if (this->type != UNARYOP && this->type != NEGUNARY) {
        Expression* rhs = malloc(sizeof(Expression));
        setExpression(rhs, getRhsString(exp), NULL, NULL);
        this->rhs = rhs;
        recurBuildExp(rhs, getRhsString(exp));
    }
}

// Parameters: this - Expression to print
// Post-Condition: prints the expression to terminal
void print(Expression* this) {
    if (this == NULL)
        return;
    if (this->type == UNARYOP) {
        printf("(");
        printf("%s ", this->piece);
        print(this->lhs);
        if (strcmp(this->piece, "expt") == 0)
            printf(" 2");
        printf(")");
    } else if (this->type == BINARYOP) {
        printf("(");
        printf("%s ", this->piece);
        print(this->lhs);
        if (this->rhs != NULL)
            printf(" ");
        print(this->rhs);
        printf(")");
    } else {
        printf("%s", this->piece);
    }
}

// Parameters: Expression - the first expression to compare
//             Expression - the second expression to compare
// Returns: true if the two expressions are identical, false otherwise
bool equals(Expression* this, Expression* that) {
    if (this == NULL && that != NULL)
        return false;
    if (this != NULL && this == NULL)
        return false;
    if (this == NULL && that == NULL)
        return true;
    if ((strcmp(this->piece, that->piece) == 0))
        return (equals(this->lhs, that->lhs) && equals(this->rhs, that->rhs));
    return false;
}

// Parameters: Expression - the expression to get the hash code for
// Returns: the integer hashcode of the operator
int hashCode(Expression* this) {
    return 0;
}
