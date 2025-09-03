#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int row;
    int col;
    int value;
} sparse_term;


void get_sparse_dimensions(const sparse_term *matrix, int size, int *rows, int *cols) {
    *rows = 0;
    *cols = 0;
    if (size <= 0) return;
    for (int i = 0; i < size; i++) {
        if (matrix[i].row + 1 > *rows) {
            *rows = matrix[i].row + 1;
        }
        if (matrix[i].col + 1 > *cols) {
            *cols = matrix[i].col + 1;
        }
    }
}

sparse_term *dense_to_sparse(int *size, int *rows, int *cols) {
    int row, col;
    printf("Enter number of rows: ");
    scanf("%d", &row);
    printf("Enter number of columns: ");
    scanf("%d", &col);
    
    *rows = row;
    *cols = col;

    int counter = 0;
    int capacity = 10;
    sparse_term *sparse_matrix = (sparse_term *)malloc(sizeof(sparse_term) * capacity);
    if (!sparse_matrix) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    printf("Enter elements of the dense matrix:\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int value;
            printf("Enter element at [%d][%d]: ", i, j);
            scanf("%d", &value);
            if (value != 0) {
                if (counter >= capacity) {
                    capacity *= 2;
                    sparse_term *temp = (sparse_term *)realloc(sparse_matrix, capacity * sizeof(sparse_term));
                    if (!temp) {
                        printf("Memory reallocation failed\n");
                        free(sparse_matrix);
                        exit(1);
                    }
                    sparse_matrix = temp;
                }
                sparse_matrix[counter].row = i;
                sparse_matrix[counter].col = j;
                sparse_matrix[counter].value = value;
                counter++;
            }
        }
    }

    *size = counter;

    if (counter > 0) {
        sparse_term *temp = (sparse_term *)realloc(sparse_matrix, (*size) * sizeof(sparse_term));
        if (temp) {
            sparse_matrix = temp;
        }
    } else {
        free(sparse_matrix);
        return NULL;
    }

    return sparse_matrix;
}

sparse_term *add(const sparse_term *matrix1, int size1, int rows1, int cols1, const sparse_term *matrix2, int size2, int rows2, int cols2, int *size) {
    if (rows1 != rows2 || cols1 != cols2) {
        printf("Error: Matrix dimensions are not compatible for addition.\n");
        *size = 0;
        return NULL;
    }
    
    int capacity = size1 + size2;
    sparse_term *result_matrix = (sparse_term *)malloc(sizeof(sparse_term) * capacity);
    if (!result_matrix) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (matrix1[i].row < matrix2[j].row || (matrix1[i].row == matrix2[j].row && matrix1[i].col < matrix2[j].col)) {
            result_matrix[k++] = matrix1[i++];
        } else if (matrix1[i].row > matrix2[j].row || (matrix1[i].row == matrix2[j].row && matrix1[i].col > matrix2[j].col)) {
            result_matrix[k++] = matrix2[j++];
        } else {
            int sum = matrix1[i].value + matrix2[j].value;
            if (sum != 0) {
                result_matrix[k].row = matrix1[i].row;
                result_matrix[k].col = matrix1[i].col;
                result_matrix[k].value = sum;
                k++;
            }
            i++;
            j++;
        }
    }

    while (i < size1) {
        result_matrix[k++] = matrix1[i++];
    }
    while (j < size2) {
        result_matrix[k++] = matrix2[j++];
    }

    *size = k;
    
    if (k > 0) {
        sparse_term *temp = (sparse_term *)realloc(result_matrix, (*size) * sizeof(sparse_term));
        if (temp) {
            result_matrix = temp;
        }
    } else {
        free(result_matrix);
        return NULL;
    }
    
    return result_matrix;
}

sparse_term *multiply(const sparse_term *matrix1, int size1, int rows1, int cols1, const sparse_term *matrix2, int size2, int rows2, int cols2, int *size) {
    if (cols1 != rows2) {
        printf("Error: Matrix dimensions are not compatible for multiplication.\n");
        *size = 0;
        return NULL;
    }
    
    int result_rows = rows1;
    int result_cols = cols2;
    int **temp = (int **)calloc(result_rows, sizeof(int *));
    if (!temp) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < result_rows; i++) {
        temp[i] = (int *)calloc(result_cols, sizeof(int));
        if (!temp[i]) {
            printf("Memory allocation failed\n");
            for (int k = 0; k < i; k++) free(temp[k]);
            free(temp);
            exit(1);
        }
    }
    
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (matrix1[i].col == matrix2[j].row) {
                temp[matrix1[i].row][matrix2[j].col] += matrix1[i].value * matrix2[j].value;
            }
        }
    }

    int counter = 0;
    int capacity = 10;
    sparse_term *result_sparse = (sparse_term *)malloc(sizeof(sparse_term) * capacity);
    if (!result_sparse) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < result_rows; i++) {
        for (int j = 0; j < result_cols; j++) {
            if (temp[i][j]) {
                if (counter >= capacity) {
                    capacity *= 2;
                    sparse_term *realloc_temp = (sparse_term *)realloc(result_sparse, capacity * sizeof(sparse_term));
                    if (!realloc_temp) {
                        printf("Memory reallocation failed\n");
                        free(result_sparse);
                        exit(1);
                    }
                    result_sparse = realloc_temp;
                }
                result_sparse[counter].row = i;
                result_sparse[counter].col = j;
                result_sparse[counter].value = temp[i][j];
                counter++;
            }
        }
    }
    
    for (int i = 0; i < result_rows; i++) {
        free(temp[i]);
    }
    free(temp);

    *size = counter;

    if (counter > 0) {
        sparse_term *temp = (sparse_term *)realloc(result_sparse, (*size) * sizeof(sparse_term));
        if (temp) {
            result_sparse = temp;
        }
    } else {
        free(result_sparse);
        return NULL;
    }
    
    return result_sparse;
}


void print_sparse(const sparse_term *compact, int size) {
    if (!compact || size <= 0) {
        printf("The matrix is empty or invalid.\n");
        return;
    }
    printf("Row | Col | Value\n");
    for (int i = 0; i < size; i++) {
        printf("%d   | %d   | %d\n", compact[i].row, compact[i].col, compact[i].value);
    }
}


sparse_term *read_sparse_from_file(const char *filename, int *size, int *rows, int *cols) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s for reading.\n", filename);
        return NULL;
    }

    if (fscanf(file, "%d %d", rows, cols) != 2) {
        printf("Error: Invalid file format. Expected dimensions on the first line.\n");
        fclose(file);
        return NULL;
    }

    int capacity = 10;
    sparse_term *sparse_matrix = (sparse_term *)malloc(sizeof(sparse_term) * capacity);
    if (!sparse_matrix) {
        printf("Memory allocation failed\n");
        fclose(file);
        return NULL;
    }
    
    int counter = 0;
    while (fscanf(file, "%d %d %d", &sparse_matrix[counter].row, &sparse_matrix[counter].col, &sparse_matrix[counter].value) == 3) {
        if (counter >= capacity) {
            capacity *= 2;
            sparse_term *temp = (sparse_term *)realloc(sparse_matrix, capacity * sizeof(sparse_term));
            if (!temp) {
                printf("Memory reallocation failed\n");
                free(sparse_matrix);
                fclose(file);
                return NULL;
            }
            sparse_matrix = temp;
        }
        counter++;
    }

    fclose(file);
    *size = counter;
    
    if (counter > 0) {
        sparse_term *temp = (sparse_term *)realloc(sparse_matrix, (*size) * sizeof(sparse_term));
        if (temp) {
            sparse_matrix = temp;
        }
    } else {
        free(sparse_matrix);
        return NULL;
    }

    return sparse_matrix;
}


void write_sparse_to_file(const char *filename, const sparse_term *matrix, int size, int rows, int cols) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not open file %s for writing.\n", filename);
        return;
    }
    
    fprintf(file, "%d %d\n", rows, cols);
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d %d %d\n", matrix[i].row, matrix[i].col, matrix[i].value);
    }

    printf("Result written to %s\n", filename);
    fclose(file);
}

int main() {
    int size1 = 0, size2 = 0, size3 = 0, size4 = 0;
    int rows1 = 0, cols1 = 0, rows2 = 0, cols2 = 0;
    sparse_term *matrix1 = NULL;
    sparse_term *matrix2 = NULL;
    sparse_term *add_result = NULL;
    sparse_term *multiply_result = NULL;
    int choice;

    printf("Choose input method:\n");
    printf("1. Enter matrices manually\n");
    printf("2. Read matrices from files\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("--- Sparse Matrix 1 ---\n");
        matrix1 = dense_to_sparse(&size1, &rows1, &cols1);
        printf("\n--- Sparse Matrix 2 ---\n");
        matrix2 = dense_to_sparse(&size2, &rows2, &cols2);
    } else if (choice == 2) {
        char file1[100], file2[100];
        printf("Enter filename for Matrix 1: ");
        scanf("%s", file1);
        matrix1 = read_sparse_from_file(file1, &size1, &rows1, &cols1);
        
        printf("Enter filename for Matrix 2: ");
        scanf("%s", file2);
        matrix2 = read_sparse_from_file(file2, &size2, &rows2, &cols2);
        
        if (!matrix1 || !matrix2) {
            free(matrix1);
			free(matrix2);
			free(add_result);
			free(multiply_result);
            return 1;
        }
    } else {
        printf("Invalid choice. Exiting.\n");
        return 1;
    }
    
    printf("\nSparse Matrix 1:\n");
    print_sparse(matrix1, size1);

    printf("\nSparse Matrix 2:\n");
    print_sparse(matrix2, size2);
    
    printf("\n--- Matrix Addition ---\n");
    add_result = add(matrix1, size1, rows1, cols1, matrix2, size2, rows2, cols2, &size3);
    if (add_result) {
        printf("Result of Addition:\n");
        print_sparse(add_result, size3);
        write_sparse_to_file("add_result.txt", add_result, size3, rows1, cols1);
    }
    
    printf("\n--- Matrix Multiplication ---\n");
    multiply_result = multiply(matrix1, size1, rows1, cols1, matrix2, size2, rows2, cols2, &size4);
    if (multiply_result) {
        printf("Result of Multiplication:\n");
        print_sparse(multiply_result, size4);
        write_sparse_to_file("multiply_result.txt", multiply_result, size4, rows1, cols2);
    }


	free(matrix1);
    free(matrix2);
    free(add_result);
    free(multiply_result);
    return 0;
}
