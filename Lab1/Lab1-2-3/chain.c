#include <stdio.h>
#include <stdlib.h> // includes malloc(), free(), realloc()
#include <string.h> // includes memcpy()
#include <math.h>
#include "chain.h" // do not modify this file

// put your function prototypes for additional helper functions below:

// implementation
matrix *create_matrix(int num_rows, int num_cols)
{
    matrix *mat = (matrix *) malloc(sizeof(matrix));
    mat->num_rows = num_rows;
    mat->num_cols = num_cols;
    mat->data = (int **) malloc(sizeof(int *) * num_rows);

    int row_idx;
    for(row_idx = 0; row_idx < num_rows; ++row_idx) {
        mat->data[row_idx] = (int *) malloc(sizeof(int) * num_cols);
    }
    for (int row_idx = 0; row_idx < mat->num_rows; ++row_idx) {
        for (int col_idx = 0; col_idx < mat->num_cols; ++col_idx) {
            mat->data[row_idx][col_idx] = 0;
        }
    }


    return mat;
}


void add_row(matrix *mat, int *row)
{

    mat->data = realloc(mat->data, sizeof(int *) * (mat->num_rows + 1));
    int* new_row = (int*) malloc(sizeof (int*)*(mat->num_cols)) ;
    for (int i = 0 ; i < mat->num_cols ; i++){
        new_row[i] = row[i];
    }
    mat->data[mat->num_rows] = new_row;

    (mat->num_rows)+= 1;

}

void add_col(matrix *mat, int *col)
{
    for (int i = 0 ; i < mat->num_rows ; ++i){
        mat->data[i] = (int*) realloc(mat->data[i], sizeof(int) * (mat->num_cols + 1));
        mat->data[i][mat->num_cols] = col[i];
    }
    mat->num_cols+=1;
}

void increment(matrix *mat, int num)
{

//    for (int* p = &mat->data[0][0] ; p <= &mat->data[mat->num_rows - 1][mat->num_cols - 1] ; ++p ){
//        *p += num;
//    }

    for (int i = 0 ; i < mat->num_rows ; ++i){
        for (int j = 0 ; j < mat->num_cols ; ++j){
            mat->data[i][j] += num;
        }
    }

}

void scalar_multiply(matrix *mat, int num)
{
    for (int i = 0 ; i < mat->num_rows ; ++i){
        for (int j = 0 ; j < mat->num_cols ; ++j){
            mat->data[i][j] *= num;
        }
    }

}

void scalar_divide(matrix *mat, int num)
{
    for (int i = 0 ; i < mat->num_rows ; ++i){
        for (int j = 0 ; j < mat->num_cols ; ++j){
            mat->data[i][j] /= num;
        }
    }
}

void scalar_power(matrix *mat, int num)
{
    for (int row_idx = 0; row_idx < mat->num_rows; ++row_idx) {
        for (int col_idx = 0; col_idx < mat->num_cols; ++col_idx) {
            mat->data[row_idx][col_idx] = pow(mat->data[row_idx][col_idx], num);
        }
    }
}

void delete_matrix(matrix *mat)
{

    for (int row_idx = 0; row_idx < mat->num_rows; ++row_idx) {
        free(mat->data[row_idx]);
    }
    free(mat->data);
    free(mat);

}


/*
    DO NOT MODIFY BELOW
*/
// print out matrix in row-major order
// elements in the same row are space-separated
// each row starts in a new line
void print_matrix(matrix *mat)
{
    int row_idx, col_idx;
    for(row_idx = 0; row_idx < mat->num_rows; ++row_idx) {
        for(col_idx = 0; col_idx < mat->num_cols; ++col_idx) {
            if (col_idx == mat->num_cols-1) {
                printf("%d\n", mat->data[row_idx][col_idx]);
            } else {
                printf("%d ", mat->data[row_idx][col_idx]);
            }
        }
    }
}



void insert_node_before(chain *lst, int index, matrix *mat){

    node* new_node = (node*) malloc (sizeof(node));
    new_node->mat = mat;

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


void insert_node_after(chain *lst, int index, matrix *mat)
{
    if (index != -1) {
        insert_node_before(lst, index + 1, mat);
    }
    else{
        node* new_node = (node*) malloc (sizeof(node));
        new_node->mat = mat;
        new_node->prev = lst->head->prev;
        new_node->next = lst->head;
        lst->head->prev->next = new_node;
        lst->head->prev = new_node;


    }
}

void delete_node(chain *lst, int index)
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

void delete_list(chain *lst)
{
    node* temp = lst->head->next;
    while (temp != lst->head){
        temp = temp->next;
        free(temp->prev);
    }
    free(lst->head);

    // TODO
}








