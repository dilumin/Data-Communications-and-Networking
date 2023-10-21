// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <string.h>

// user-defined header files
#include "node.h"

// macros

#define INSERT_BEFORE 1
#define INSERT_AFTER 2
#define DELETE_NODE 3
#define DELETE_LIST 4

// function prototypes
void print_list(list * lst); 
void run(list * lst);


int main()
{
    list * lst = (list *) malloc(sizeof(list));
    lst->head = NULL;
	run(lst);
    print_list(lst);
    free(lst);
	return 0;
}

// parse the input
void run(list *lst) 
{
    char* sentence = (char* ) malloc(sizeof(char) * 256) ;
    int i =0;
    scanf("%s",sentence);
    char* token = strtok(sentence, ",");
    while(token != NULL){
        insert_node_before(lst, i, token);
        i++;
        token = strtok(NULL, ",");
    }

    int a;
    int b;
    print_list(lst);
    scanf("%d",&a);
    while(a != 0){

        scanf("%d",&b);
        char* c = (char*) malloc(sizeof(char ) * MAX_WORD_LENGTH);

        switch (a) {
            case INSERT_BEFORE:
                scanf("%s",c);
                insert_node_before(lst ,b ,c);
                scanf("%d",&a);
                print_list(lst);
                break;
            case INSERT_AFTER:
                scanf("%s",c);
                insert_node_after(lst , b ,c);
                scanf("%d",&a);
                print_list(lst);
                break;
            case  DELETE_NODE:
                delete_node(lst ,b);
                print_list(lst);
                scanf("%d",&a);
                break;
            case DELETE_LIST:
                delete_list(lst);
                print_list(lst);
                scanf("%d",&a);
                break;

        }
       

    }


	
}

//Print the list contents
void print_list(list * lst)
{
    node* temp = lst->head;
    while(temp->next != lst->head){
        printf("%s ", temp->word);
        temp = temp->next;
    }
    printf("%s\n", temp->word);

   
}

