#include "data_structers.c"

LinkedList* readBooleanExpression(char *expression) {
    LinkedList *list = list_create();
    char tmp[DATA_SIZE];
    short tmp_size = 0;
    char *current = expression;
    while (*current != '\0')
    {
        if(*current == ' ' || *current == '\n' || *current == '\t' || *current == '(' || *current == ')') {
            if(tmp_size > 0) {
                tmp[tmp_size] = '\0';
                list_insert(list,tmp);
                tmp_size = 0;
            }

            if(*current == '(') {
                list_insert(list,"(");
            }else if(*current == ')') {
                list_insert(list,")");
            }

        }else {
            tmp[tmp_size++] = *current;
        }
        current++;
    }

    if(tmp_size > 0) {
        tmp[tmp_size] = '\0';
        list_insert(list,tmp);
        tmp_size = 0;
    }
    return list;
}

short operatorPriority(char *operator) {
    if(strcmp(operator,"NOT") == 0 || strcmp(operator,"not") == 0) return 3;
    if(strcmp(operator,"AND") == 0 || strcmp(operator,"and") == 0) return 2;
    if(strcmp(operator,"OR") == 0 || strcmp(operator,"or") == 0) return 1;
    return 0;
}

short isOperator(char *operator) {
    char operations[7][5] = {"NOT","not","AND","and","or","OR"};
    for(int i =0 ; i < 6; i++) {
        if(strcmp(operator,operations[i]) == 0) return 1;
    }
    return 0;
}

LinkedList* infixToPostfix(LinkedList *infix) { 
    LinkedList *postfix = list_create();
    Stack_string *stack = stack_string_init();
    StringNode *current = infix->head;

    while (current != NULL) {

        char *data = current->data;

        if (isOperator(data) || strcmp(data, "(") == 0 || strcmp(data, ")") == 0) {
            if (stack_string_isEmpty(stack) || strcmp(data, "(") == 0) {
                stack_string_push(stack, data);
            } 
            else if (strcmp(data, ")") == 0) {
                while (!stack_string_isEmpty(stack)) {
                    char *top = stack_string_pop(stack);
                    if (strcmp(top, "(") == 0) break;
                    list_insert(postfix, top);
                }
            } 
            else {
                while (!stack_string_isEmpty(stack)) {
                    char *top = stack_string_top(stack);
                    if (strcmp(top, "(") == 0 || operatorPriority(data) > operatorPriority(top)) {
                        break;
                    }
                    list_insert(postfix, stack_string_pop(stack));
                }
                stack_string_push(stack, data);
            }
        } else {
            list_insert(postfix, data);
        }
        current = current->next;
    }
    

    while (!stack_string_isEmpty(stack)) {
        char *top = stack_string_pop(stack);
        if(strcmp(top,"(") == 0) continue;
        list_insert(postfix, top);
    }

    return postfix;
}


void getExpressionValues(LinkedList *postfix , HashTable *table) {
    StringNode *current = postfix->head;
    while (current != NULL)
    {
        char *data = current->data;
        if(!isOperator(data)) {
            int input;
            bool value;
            printf("Enter the value of %s: ",data);
            scanf("%d",&input);
            value = (input > 0) ? true : false;
            table_insert(table,data,value);
        };
        current = current->next;
    }
}


bool AND(bool a , bool b) {
    return a && b;
}

bool NOT(bool a) {
    return !a;
}

bool OR(bool a, bool b) {
    return a || b;
}



bool evaluatPostfixExpression(LinkedList *postfix,HashTable *table){
    Stack_bool *stack = stack_bool_init();
    StringNode *current = postfix->head;
    while (current != NULL)
    {
        char *data = current->data;
        if(!isOperator(data)) {
            stack_bool_push(stack,table_get(table,data));
        }else {

            if(stack_bool_isEmpty(stack)) {
                printf("The expression is incorrect \n");
                exit(1);
            };

            bool result;
            if(strcmp(data,"and") == 0 || strcmp(data,"AND") == 0) {
                bool operand1 = stack_bool_pop(stack);
                if(stack_bool_isEmpty(stack)) {
                    printf("The expression is incorrect \n");
                    exit(1);
                }
                bool operand2 = stack_bool_pop(stack);
                result = AND(operand1,operand2);
            }else if(strcmp(data,"or") == 0 || strcmp(data,"OR") == 0) {
                bool operand1 = stack_bool_pop(stack);
                if(stack_bool_isEmpty(stack)) {
                    printf("The expression is incorrect \n");
                    exit(1);
                }
                bool operand2 = stack_bool_pop(stack);
                result = OR(operand1,operand2);
            }else if(strcmp(data,"not") == 0 || strcmp(data,"NOT") == 0) {
                result = NOT(stack_bool_pop(stack));
            }else {
                break;
            }
            stack_bool_push(stack,result);
        }
        current = current->next;
    }
    return stack_bool_pop(stack);
}


LinkedList* simplifyExpression(LinkedList *infix) {
    StringNode *current = infix->head;
    LinkedList *simplifiedList = list_create();
    int notCount = 0;
    char *exprNot;
    while (current != NULL)
    {
        char *data = current->data;

        if(strcmp(data,"not") == 0 || strcmp(data,"NOT") == 0) {
            notCount++;
            exprNot = data; // get the not in expression
        }else {
            if(notCount >= 1 && notCount % 2 != 0) 
                list_insert(simplifiedList,exprNot);
            list_insert(simplifiedList,data);
            notCount = 0;
        }
        current = current->next;
    }
    
    return simplifiedList;
}