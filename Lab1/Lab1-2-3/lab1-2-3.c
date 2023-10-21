// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <string.h>

// user-defined header files
#include "chain.h"

// function prototypes
void print_chain(chain * chn);
void run(chain * chn);



int main()
{
    chain * chn = (chain *) malloc(sizeof(chain));
    chn->head = NULL;
    run(chn);
    print_chain(chn);
    free(chn);
    return 0;
}

matrix* copy_matrix(matrix *m){

    matrix *mat1 = (matrix *)malloc(sizeof(matrix));
    int** mat_cpy = (int**)malloc (sizeof (int*) * m->num_rows);
    mat1->num_rows = m->num_rows;
    mat1->num_cols = m->num_cols;
    for (int o = 0 ; o < m->num_rows ; o++){
        int *row_ = (int *)malloc(sizeof(int) * mat1->num_cols);
//        memcpy( mat_cpy[o] , m->data[o] , m->num_cols * sizeof(int));
        for (int u = 0 ; u < m->num_cols ; u++){
            row_[u] = m->data[o][u];
        }
        mat_cpy[o] = row_;
    }
    mat1->data = mat_cpy;
    return mat1;

}


// parse the input
void run(chain *chn)
{

    matrix *mat = (matrix *)malloc(sizeof(matrix));


    int num_rows, num_cols;
    num_cols = 0;
    char *sentence = (char *)malloc(sizeof(char) * 256);

    scanf("%i", &num_rows);
    mat->data = (int **) malloc(sizeof(int *)  * num_rows);
    getchar();

    fgets(sentence, 256, stdin);
    mat->num_rows = 0;



    int *first_row = (int *)malloc(sizeof(int) * 256);
    char *token = strtok(sentence, " ");
    while (token != NULL) {
        first_row[num_cols] = atoi(token); // Corrected atoi usage
        ++num_cols;
        token = strtok(NULL, " ");
    }
    first_row = realloc(first_row , sizeof(int*) *num_cols);
    mat->num_cols = num_cols;
    mat->num_rows = num_rows;
    mat->data[0] = first_row;

    int temp;
    int l = 1;

    for (int times = 0 ; times  < num_rows -1 ; times++){
        int *row = (int *)malloc(sizeof(int) * num_cols);
        for (int t = 0 ; t < num_cols ; t++){
            scanf("%d" , &temp);
            row[t] = temp;
        }
        l++;


        mat->data[l-1] = row;

    }

//    chn->head->mat = mat;
    chn->head = (node*) malloc(sizeof(node));
    chn->head->mat = copy_matrix(mat);
    chn->head->next = chn->head;
    chn->head->prev = chn->head;
    int choose;
    while ( 1 ){

        scanf("%d" ,&choose);
        if (choose == 0){
            break;
        }

        int input;
        int new_arr[ mat->num_cols];
        int new_coll [mat->num_rows];
        switch(choose){
            case 2:
                for (int l1 = 0 ; l1 < mat->num_cols ; l1 ++){
                    scanf("%d" ,&input);
                    new_arr[l1] = input;
                }
                add_row(mat , new_arr);
                break;

            case 5:
                scanf("%d" , &input);
                scalar_multiply(mat ,input);

                break;


            case 4:
                scanf("%d" , &input);
                increment(mat , input);
                break;
            case 3:
                for (int l1 = 0 ; l1 < mat->num_rows ; l1 ++){
                    scanf("%d" ,&input);
                    new_coll[l1] = input;
                }
                add_col(mat , new_coll);
                break;

            case 6:
                scanf("%d" , &input);
                scalar_divide(mat ,input);

                break;
            case 7:
                scanf("%d" , &input);
                scalar_power(mat ,input);

                break;

        }
        matrix * m1 = copy_matrix(mat);
        insert_node_after(chn,-1,m1 );
    }


}

//Print the chain
void print_chain(chain * chn)
{


    node* n1= chn->head;
    print_matrix(n1->mat);
    printf("\n");
    n1 = n1->next;
    while(n1 != chn->head){
        print_matrix(n1->mat);
        n1 = n1->next;
        printf("\n");
    }




}

