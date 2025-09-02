#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row;
    int col;
    int value;
}dense_term;

void sparse_to_dense(dense_term *dense_matrix , int *size) {
    int row;
    printf("Enter row:- ");
    scanf("%d" , &row);

    int **sparse_matrix;
    sparse_matrix = (int **)malloc(sizeof(int *)*row);
    for(int i=0 ; i<row ; i++) {
        sparse_matrix[i] = (int* )malloc(sizeof(int)*row);
    }

    for(int i = 0; i < row ; i++) {
        for(int j = 0 ; j < row ; j++) {
            printf("Enter row [%d][%d] :- " , i+1 , j+1);
            scanf("%d" , &sparse_matrix[i][j]);
        }
    }

    int size_alloc=4 , counter=0;
    dense_matrix = (dense_term *)malloc(sizeof(dense_term) * size_alloc);
    for(int i = 0 ; i<row ; i++) {
        for(int j = 0 ; j<row ; j++) {
            if(sparse_matrix[i][j]) {
                    dense_matrix[counter].row = i;
                    dense_matrix[counter].col = j;
                    dense_matrix[counter].value = sparse_matrix[i][j];
                    counter++;
                }
                if(counter >= size_alloc) {
                    size_alloc<<=1;
                    dense_matrix = (dense_term *)realloc(dense_matrix, size_alloc * sizeof(dense_term));
                }
        }
    }
    *size = counter;
}

void add(dense_term *dense1, int size1 , dense_term *dense2 , int size2 , dense_term *dense_matrix , int *size) { 
    int size_alloc = size1 > size2 ? size1 : size2;
    dense_matrix = (dense_term *)malloc(sizeof(dense_term) * size_alloc);
    int i = 0 ,j = 0 , counter=0;
    while (i < size1 && j < size2) {
        if (counter >= size_alloc) {
            size_alloc <<= 1;
            dense_term *temp = (dense_term *)realloc(dense_matrix, size_alloc * sizeof(dense_term));
            if (!temp) {
                printf("Memory reallocation failed\n");
                free(dense_matrix);
                *size = 0;
                return NULL;
            }
            dense_matrix = temp;
        }
        if (dense1[i].row == dense2[j].row && dense1[i].col == dense2[j].col) {
            dense_matrix[counter].row = dense1[i].row;
            dense_matrix[counter].col = dense1[i].col;
            dense_matrix[counter].value = dense1[i].value + dense2[j].value;
            if (dense_matrix[counter].value) counter++;
            i++;
            j++;
        } else if (dense1[i].row < dense2[j].row || (dense1[i].row == dense2[j].row && dense1[i].col < dense2[j].col)) {
            dense_matrix[counter].row = dense1[i].row;
            dense_matrix[counter].col = dense1[i].col;
            dense_matrix[counter].value = dense1[i].value;
            counter++;
            i++;
        } else {
            dense_matrix[counter].row = dense2[j].row;
            dense_matrix[counter].col = dense2[j].col;
            dense_matrix[counter].value = dense2[j].value;
            counter++;
            j++;
        }
    }
    *size = counter;
}

int multiply(dense_term *dense1, int size1 , dense_term *dense2 , int size2 , dense_term *dense_matrix) {
    int counter=0;
    int size = size1 > size2 ? size1 : size2;
    dense_matrix = (dense_term *)malloc(sizeof(dense_term) * size);


}