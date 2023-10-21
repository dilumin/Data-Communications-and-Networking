// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <string.h> // includes strlen(), memcpy()
#include <ctype.h> // includes toupper(), tolower()

// user-defined header files
#include "node.h" // do not modify this file

// put your function prototypes for additional helper functions below:


// implementation
void insert_node_before(list *lst, int index, char *word){

    node* new_node = (node*) malloc (sizeof(node));
    new_node->word = word;

    if (lst->head== NULL ){
        lst->head = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
    }
    else if(index > 0){
        node* temp = lst->head;
        for (int i = index ; i > 0 ; i-- ){
            temp = temp->next;
        }
        new_node->prev = temp->prev;
        new_node->next = temp;
        temp->prev->next = new_node;
        temp->prev = new_node;

    }else if (index < 0 ){
        node* temp = lst->head;
        for (int i = index ; i < 0 ; i++ ){
            temp = temp->prev;
        }
        new_node->prev = temp->prev;
        new_node->next = temp;
        temp->prev->next = new_node;
        temp->prev = new_node;
    }
	else if(index == 0){
		new_node->next = lst->head;
		new_node->prev = lst->head->prev;
		lst->head->prev->next = new_node;
		lst->head->prev = new_node;
		lst->head = new_node;
	}


}

void insert_node_after(list *lst, int index, char *word)
{
    if (index != -1) {
        insert_node_before(lst, index + 1, word);
    }
    else{
        node* new_node = (node*) malloc (sizeof(node));
        new_node->word = word;
        new_node->prev = lst->head->prev;
        new_node->next = lst->head;
        lst->head->prev->next = new_node;
        lst->head->prev = new_node;


    }
}


char *list_to_sentence(list *lst)
{
	// TODO
    return NULL; // Change this line accordingly
}

void delete_node(list *lst, int index)
{
	if (index >= 0){
	node* temp = lst->head;
	for (int i = index ; i >0 ; i--){
		temp = temp->next;
	}
	if (temp == lst->head){
		lst->head = temp->next;
		lst->head->prev = temp->prev;
		temp->prev->next = lst->head;
	}else{
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
	free(temp);
    }
    else{
        node* temp = lst->head;
        for (int i = index ; i < 0 ; i++){
            temp = temp->prev;
        }
        temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
        free(temp);
        

    }

}

void delete_list(list *lst)
{
	node* temp = lst->head->next;
	while (temp != lst->head){
		temp = temp->next;
		free(temp->prev);
	}
	free(lst->head);
	
	// TODO
}



