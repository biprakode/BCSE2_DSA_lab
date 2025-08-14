#include <stdio.h>
#include <stdlib.h>
void user_append(int **arr , int *size);
void display(int *arr, int size);
void insert_before(int **arr , int *size , int ref);
void insert_after(int **arr , int *size , int ref);
void delete_ref(int **arr , int *size , int ref);
void delete_pos(int **arr , int *size , int pos);
void insert_pos(int **arr , int *size , int pos);
int getmiddle(int *arr , int *size);
int get_nth_fromend(int *arr , int *size , int n);

int main() {
    int *arr = (int *)malloc(sizeof(int) * 1);
    arr[0] = 0;
    int choice=0 , pos , n , ref , size=1;
    do {
        printf("\nMenu:\n");
        printf("1. Append elements\n");
        printf("2. Insert before reference\n");
        printf("3. Insert after reference\n");
        printf("4. Delete by reference\n");
        printf("5. Delete by position\n");
        printf("6. Get middle element\n");
        printf("7. Get nth from end\n");
        printf("8. Display\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                user_append(&arr, &size);
                break;
            case 2:
                printf("Enter reference: ");
                scanf("%d", &ref);
                insert_before(&arr, &size, ref);
                break;
            case 3:
                printf("Enter reference: ");
                scanf("%d", &ref);
                insert_after(&arr, &size, ref);
                break;
            case 4:
                printf("Enter reference to delete: ");
                scanf("%d", &ref);
                delete_ref(&arr, &size, ref);
                break;
            case 5:
                printf("Enter position to delete: ");
                scanf("%d", &pos);
                delete_pos(&arr, &size, pos);
                break;
            case 6:
                if (size > 0) printf("Middle: %d\n", getmiddle(arr, &size));
                else printf("Array empty\n");
                break;
            case 7:
                printf("Enter n: ");
                scanf("%d", &n);
                if (size > 0) printf("%d from end: %d\n", n, get_nth_fromend(arr, &size, n));
                else printf("Array empty\n");
                break;
            case 8:
                display(arr, size);
                break;
            case 0:
                free(arr);
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 0);

    return 0;
}

void display(int *arr, int size) {
    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void user_append(int **arr , int *size) { // here array is of type (.....,0)
    int data;
    printf("Press -1 to stop appending:- ");
    do {
        // start by overwriting 0
        printf("data:- ");
        scanf("%d" , &data);
        if((data) != -1) {
            *arr = (int *)realloc(*arr, sizeof(int) * (*size + 1));
            (*arr)[*size - 1] = data; // overwrite 0
            (*arr)[*size] = 0; // add 0 to end
            (*size)++;
        } else {
            printf("array stored");
            break;
        }
    }while(1);
}

void insert_before(int **arr , int *size , int ref) {
    int found = 0 , data;
    for(int i = 0 ; i<*size ;  i++) {
        if((*arr)[i] == ref) {
            found = 1;
            printf("Enter data:- ");
            scanf("%d" , &data);
            *arr = (int *)realloc(*arr , sizeof(int) * (++*(size)));
            for(int j = *size-1; j>i; j--) {
                (*arr)[j] = (*arr)[j-1]; 
            }
            (*arr)[i] = data;
            break;
        } 
    }
    if(!found) {
        printf("Reference not found");
    }
}

void insert_after(int **arr , int *size , int ref) {
    int found = 0 , data;
    for(int i = 0 ; i<*size ;  i++) {
        if((*arr)[i] == ref) {
            found = 1;
            printf("Enter data:- ");
            scanf("%d" , &data);
            (++(*size));
            *arr = (int *)realloc(*arr , sizeof(int) * (*size));
            if((*arr)[i+1] == 0) {
                (*arr)[i+1] = data;
                (*arr)[i+2] = 0;
                return;
            }
            for(int j = *size-1; j>i+1; j--) {
                (*arr)[j] = (*arr)[j-1]; 
            }
            (*arr)[i+1] = data;
        } 
    }
    if(!found) {
        printf("Reference not found");
    }
}

void delete_ref(int **arr , int *size , int ref) {
    int found = 0 , data;
    for(int i = 0 ; i<*size ;  i++) {
        if((*arr)[i] == ref) {
            found = 1;
            for(int j=i ; j<*size-1 ; j++) {
                (*arr)[j] = (*arr)[j+1]; 
            }
            (*size)--;
            *arr = (int *)realloc(*arr, sizeof(int) * (*size));
            printf("\nref deleted\n");
        } 
    }
    if(!found) {
        printf("Reference not found");
    }
}

void insert_pos(int **arr , int *size , int pos) {
    if (pos >= *size || pos<=0) {
        printf("Inavlid position");
        return;
    }
    for(int j=pos ; j<*size-1 ; j++) {
        (*arr)[j+1] = (*arr)[j];
    }
    printf("Enter data:- ");
    scanf("%d" , &(*arr)[pos]);
}

void delete_pos(int **arr , int *size , int pos) {
    if (pos >= *size || pos<=0) {
        printf("Inavlid position");
        return;
    }
    for(int j=pos-1 ; j<*size-1 ; j++) {
        (*arr)[j] = (*arr)[j+1]; 
    }
    (*size)--;
    *arr = (int *)realloc(*arr, sizeof(int) * (*size));
    printf("\npos deleted\n");
}

int getmiddle(int *arr , int *size) {
    return arr[(*size - 1) / 2];
}

int get_nth_fromend(int *arr , int *size , int n) {
    if (n <= 0 || n > *size) {
        printf("Invalid n\n");
        return -1;
    }
    return arr[*size - n];
}