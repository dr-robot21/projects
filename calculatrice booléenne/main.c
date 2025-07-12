#include <stdio.h>
#include "calculatrice_booleen.c"



bool boolean_calculator(char *expression) {
    
    bool result;
    HashTable *table = createTable();
    LinkedList *infix = readBooleanExpression(expression);
    printf("infix expression : ");
    list_display(infix);

    LinkedList *simpliedInfix = simplifyExpression(infix);
    printf("Expression infix simplifier : ");
    list_display(simpliedInfix);
    
    LinkedList *postfix = infixToPostfix(simpliedInfix);
    printf("postfix expression : ");
    list_display(postfix);
    if(list_isEmpty(postfix)) {
        printf("The expression is empty ! \n");
        exit(1);
    }
    
    printf("Saisir les valeurs des variables ( 1 = 'true' , 0 = 'false' ): \n");
    getExpressionValues(postfix,table);
    result = evaluatPostfixExpression(postfix,table);
    
    list_free(simpliedInfix);
    list_free(infix);
    list_free(postfix);
    free_table(table);

    return result;
}




int main() {

    char expression[1000];
    printf("Enter new expression : ");
    fgets(expression,1000,stdin);
    bool result = boolean_calculator(expression);
    printf("result : %s \n", result ? "true" : "false");
    return 0;
}







