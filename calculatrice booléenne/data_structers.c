#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define DATA_SIZE 10
#define CAPACITY 100


typedef struct StringNode {
    char data[DATA_SIZE];
    struct StringNode *next;
} StringNode;

typedef struct BoolNode {
    bool data;
    struct BoolNode *next;
} BoolNode;




typedef struct Stack_string {
    StringNode *top;
    char *popedString;
} Stack_string;

typedef struct Stack_bool {
    BoolNode *top;
} Stack_bool;

typedef struct LinkedList {
    StringNode *head;
    StringNode *tail;
} LinkedList;


Stack_string *stack_string_init() {
    Stack_string *newStack = (Stack_string*)malloc(sizeof(Stack_string));
    newStack->top = NULL;
    newStack->popedString = NULL;
    return newStack; 
}

bool stack_string_isEmpty(Stack_string *my_stack) {
    return my_stack->top == NULL;
}

void stack_string_push(Stack_string *my_stack,char *newData){
    StringNode *newStringNode = (StringNode*)malloc(sizeof(StringNode));
    if(newStringNode == NULL) {
        printf("Memory allocation failed in stack_push() \n");
        return;
    }
    strcpy(newStringNode->data,newData);
    newStringNode->next = my_stack->top;
    my_stack->top = newStringNode;
}


char *stack_string_pop(Stack_string *my_stack) {
    if(stack_string_isEmpty(my_stack)) {
        printf("Stack is empty ! \n");
        return NULL;
    }
    free(my_stack->popedString);
    StringNode *tmp = my_stack->top;
    my_stack->popedString = strdup(tmp->data);
    my_stack->top = my_stack->top->next;
    free(tmp);
    return my_stack->popedString;
}

char *stack_string_top(Stack_string *my_stack) {
    if(stack_string_isEmpty(my_stack)) {
        printf("Stack is empty ! \n");
        return NULL;
    }
    return my_stack->top->data;
}

void stack_string_free(Stack_string *my_stack) {
    StringNode *current = my_stack->top;
    while (current != NULL)
    {
        StringNode *tmp = current;
        current = current->next;
        free(tmp);
    }
    free(my_stack);
}


Stack_bool *stack_bool_init() {
    Stack_bool *newStack = (Stack_bool*)malloc(sizeof(Stack_bool));
    newStack->top = NULL;
    return newStack; 
}

bool stack_bool_isEmpty(Stack_bool *my_stack) {
    return my_stack->top == NULL;
}

void stack_bool_push(Stack_bool *my_stack,bool newData){
    BoolNode *newBoolNode = (BoolNode*)malloc(sizeof(BoolNode));
    if(newBoolNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    newBoolNode->data = newData;
    newBoolNode->next = my_stack->top;
    my_stack->top = newBoolNode;
}


bool stack_bool_pop(Stack_bool *my_stack) {
    if(stack_bool_isEmpty(my_stack)) {
        printf("Stack is empty ! \n");
        return NULL;
    }
    BoolNode *tmp = my_stack->top;
    bool value = tmp->data;
    my_stack->top = my_stack->top->next;
    free(tmp);
    return value;
}

bool stack_bool_top(Stack_bool *my_stack) {
    if(stack_bool_isEmpty(my_stack)) {
        printf("Stack is empty ! \n");
        return NULL;
    }
    return my_stack->top->data;
}

void stack_bool_free(Stack_bool *my_stack) {
    BoolNode *current = my_stack->top;
    while (current != NULL)
    {
        BoolNode *tmp = current;
        current = current->next;
        free(tmp);
    }
    free(my_stack);
}


LinkedList* list_create() {
    LinkedList *newList = malloc(sizeof(LinkedList));
    newList->head = newList->tail = NULL;
    return newList;
}



int list_isEmpty(LinkedList *myList) {
    return myList->head == NULL;
}



void list_insert(LinkedList *myList,char *newData) {
    StringNode *newStringNode = (StringNode*)malloc(sizeof(StringNode));
    if(newStringNode == NULL) {
        printf("Memeory allocation Failed! \n");
        exit(1);
    }
    strcpy(newStringNode->data,newData);
    newStringNode->next = NULL;
    if(list_isEmpty(myList))
        myList->head = newStringNode;
    else
        myList->tail->next = newStringNode;
    
    myList->tail = newStringNode;
}

void list_display(LinkedList *myList) {
    StringNode *current = myList->head;
    while (current != NULL)
    {
        printf("%s ",current->data);
        current = current->next;
    }
    printf("\n");
}


void list_free(LinkedList *myList){
    StringNode *current = myList->head;
    while (current != NULL)
    {
        StringNode *tmp = current;
        current = current->next;
        free(tmp);
    }
    free(myList);
}



typedef struct HashStringNode {
    char *key;
    bool value;
    struct HashStringNode *next;
} HashStringNode;


typedef struct 
{
    HashStringNode **buckets;
    int capacity;
    int size;
} HashTable;


unsigned int hash(char *key) {
    unsigned int hashValue = 5381;
    int c;
    while ((c=*key++))
    {
        hashValue = ((hashValue << 5) + hashValue) + c;
    }
    return hashValue % CAPACITY;
}

HashStringNode *createStringNode(char *key,bool value) {
    HashStringNode *newStringNode = (HashStringNode*)malloc(sizeof(HashStringNode));
    newStringNode->key = strdup(key);
    newStringNode->value = value;
    newStringNode->next = NULL;
    return newStringNode;
}

void free_hash_StringNode(HashStringNode *Stringnode) {
    free(Stringnode->key);
    free(Stringnode);
}

HashTable* createTable() {
    HashTable *newTable = (HashTable*)malloc(sizeof(HashTable));
    newTable->capacity = CAPACITY;
    newTable->size = 0;
    newTable->buckets = (HashStringNode**)calloc(CAPACITY,sizeof(HashStringNode*));
    return newTable;
}

void table_insert(HashTable *table,char *key,bool value) {
    unsigned int index = hash(key);
    HashStringNode *current = table->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value; // Update the value if the key already exists
            return;
        }
        current = current->next;
    }
    HashStringNode *newStringNode = createStringNode(key, value);
    newStringNode->next = table->buckets[index];
    table->buckets[index] = newStringNode;
    table->size++;
}

bool table_get(HashTable *table, char *key) {
    unsigned int index = hash(key);
    HashStringNode *current = table->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    
    if(current == NULL) {
        printf("Value not exists in table! \n");
        exit(1);
    }
}

void table_remove(HashTable *table,char *key) {
    unsigned int index = hash(key);
    HashStringNode *prev,*current;
    current = table->buckets[index];
    prev = NULL;

    while (current != NULL)
    {
        if(strcmp(current->key,key) == 0) {
            // One StringNode in the table
            if(prev == NULL) {
                table->buckets[index] = current->next;
            }else {
                prev->next = current->next;
            }            
            table->size--;
            free_hash_StringNode(current);
            return;
        }

        prev = current;
        current = current->next;
    } 
}

void free_table(HashTable *table) {
    for (int i = 0; i < table->size ; i++)
    {
        HashStringNode *current = table->buckets[i];
        while (current != NULL)
        {
            HashStringNode *tmp = current;
            current = current->next;
            free_hash_StringNode(tmp);
        }
    }
    
    free(table->buckets);
    free(table);
}


void print_table(HashTable* table) {
    printf("Hash Table (Capacity: %d, Size: %d):\n", table->capacity, table->size);
    for (int i = 0; i < table->capacity; i++) {
        printf("Bucket %d: ", i);
        HashStringNode* current = table->buckets[i];
        while (current != NULL) {
            printf("%s:%d -> ", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}
