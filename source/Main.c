/*
  Garry Griggs
  Assignment 5: Solve in C
  Programming Languages
  Dr. Ladd
*/

#include "../headers/Expression.h"

// This is the drive for SOLVE
// solve can solve prefix algebra
// for any variable in its expression

// Declare prototypes to keep main at top

// Post-Conditions: prompts user for expression entry type
// Returns: char representing type
char* intro();

// Parameters: char* - expression to parse and solve
// Post-Condition: solves expression for each variable in it
void parseExpression(char*);

// Parameters: expfile - a file with expressions to solve
// Post-Condition: calls parseExpression on each expression
void parseExpFile(char*);

int main(void) {
    // Get manual entry or file entry
    char* answer = intro();

    // If test equality get two expressions and test equality
    // If manual run with manual expression else read from file
    // If file get file name
    if (strcmp(answer, "t") == 0) {
        // grab the two expression strings
        char* this = malloc(100);
        char* that = malloc(100);
        printf("Enter expression one: ");        
        scanf(" %100[^\n]", this);        
        printf("Enter expression two: ");        
        scanf(" %100[^\n]", that);
        // allocate memory for two expressions
        Expression* one = (Expression*)malloc(sizeof(Expression));
        Expression* two = (Expression*)malloc(sizeof(Expression));

        // build two expressions
        setExpression(one, this, NULL, NULL);
        buildExpression(one, this);
        setExpression(two, that, NULL, NULL);
        buildExpression(two, that);
        // compare two expressions
        if (equals(one, two))
            printf("Expressions are equal.\n");
        else
            printf("Expressions are not equal.\n");
        // free the memory
        free(this);
        free(that);
        free(one);
        free(two);
    // Manual solve entry
    } else if (strcmp(answer, "m") == 0) {
        char* exp = malloc(100);
        printf("Enter your expression: ");
        scanf(" %100[^\n]", exp);
        parseExpression(exp);
        free(exp);
    } else { // read in from a file and solve each expression
        char* expfile = malloc(100);
        printf("Enter you file name: ");
        scanf("%s", expfile);
        parseExpFile(expfile);
        free(expfile);
    }
    free(answer);
    // success return 0
    return 0;
}

// Post-Conditions: prompts user for expression entry type
// Returns: char representing type
char* intro() {
    char* answer = malloc(100);
    while (strcmp(answer, "m") != 0 && strcmp(answer, "f") != 0 && strcmp(answer, "t") != 0) {
        printf("Do you want to enter an expression (m)anually, by (f)ile, or (t)est equality of two expressions? ");
        scanf("%s", answer);
    }
    return answer;
}

// Parameters: exp - expression to parse and solve
// Post-Condition: solves expression for each variable in it
void parseExpression(char* exp) {
    // Start root expression
    Expression* this = (Expression*)malloc(sizeof(Expression));

    // Initialize root expression
    setExpression(this, exp, NULL, NULL);

    // build expression parse tree
    buildExpression(this, exp);
        
    // Get list of variable to solve for
    char** currentVariables;
    currentVariables = vars();
    if (currentVariables != NULL);

    // Print the list of variables
    printVars();

    // Call solve on each variable
    int i;
    for (i = 0; i < getVarCount(); i++) {
        // allocate a new solution
        Expression* solution = (Expression*)malloc(sizeof(Expression));
        solution = solve(currentVariables[i], this);
        // print solution
        printf("Solution for %s: ", currentVariables[i]);
        print(solution);
        printf("\n");
        // free memory
        free(solution);
    }

    // Reset the list of variable
    resetVars();
    free(this);
}

// Parameters: expfile - a file with expressions to solve
// Post-Condition: calls parseExpression on each expression in file
void parseExpFile(char* expfile) {
    // get data from file
    FILE *fp;
    fp = fopen(expfile, "r");
    while (feof(fp) == 0) {        
        char * exp = malloc(100);
        fscanf(fp, " %100[^\n]", exp);
        // read in eol break
        if (strlen(exp) == 0)
            break;
        // solve the expression
        parseExpression(exp);
        free(exp);
    }
}
