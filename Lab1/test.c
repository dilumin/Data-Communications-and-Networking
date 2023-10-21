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

int main()
{
    list * lst = (list *) malloc(sizeof(list));
    lst->head = NULL;
	run(lst);
    print_list(lst);
    free(lst);
	return 0;
}

void run(list *lst)
{
    char* input = (char*) malloc(sizeof(char) * 20);
    printf("Enter a list of words separated by commas: ");
    scanf("%s", input);
    
    // Read the entire line up to newline character

    char *token = strtok(input, ",");
    int i = 0;
    while(token != NULL){
        insert_node_before(lst, i, token);
        printf("%s\n", token);
        i++;
        token = strtok(NULL, ",");
    }
}

void print_list(list *lst)
{
    node *current = lst->head;
    if (current != NULL)
    {
        // print the list with space after each word
        do
        {
            printf("%s ", current->word);
            current = current->next;
        } while (current != lst->head);
    }

    else
    {
        printf("The list is empty.\n");
    }
}