#include <stdio.h>
#include <stdlib.h>
#include <string.h>	
#include <time.h>

typedef struct Tree_Node {
    int data;
    struct Tree_Node *left;
    struct Tree_Node *right;
}node;
void display_tree(node *tree_node, char *spacer);

void insert(node **tree, int value) {
    if (*tree == NULL) {
        *tree = (node *)malloc(sizeof(node));
        (*tree)->data = value;
        (*tree)->left = NULL;
        (*tree)->right = NULL;
        return;
    }
    
    if (value < (*tree)->data) {
        insert(&((*tree)->left), value);
    } else if (value > (*tree)->data) {
        insert(&((*tree)->right), value);
    }
}

void display(node *tree) {
    char tree_spacer[1000] = "";
    display_tree(tree, tree_spacer);
}

void display_tree(node *tree_node, char *spacer) {
    if (tree_node == NULL) return;
    
    printf("%s%d\n", spacer, tree_node->data);
    
    char left_spacer[1000], right_spacer[1000];
    strcpy(left_spacer, spacer);
    strcpy(right_spacer, spacer);
    
    strcat(left_spacer, "├── ");  
    strcat(right_spacer, "└── ");  
    
    if (tree_node->left)
        display_tree(tree_node->left, left_spacer);
    if (tree_node->right)
        display_tree(tree_node->right, right_spacer);
}

void inorder(node *node){
    if(node == NULL) {
        return;
    }
    inorder(node->left);
    printf("%d , " , node->data);
    inorder(node->right);
}

void preorder(node *node){
    if(node == NULL) {
        return;
    }
    printf("%d , " , node->data);
    preorder(node->left);
    preorder(node->right);
}

void postorder(node *node){
    if(node == NULL) {
        return;
    }
    postorder(node->left);
    postorder(node->right);
    printf("%d , " , node->data);
}

void del(node *tree) {
    if (tree == NULL) {
        return;
    }
    del(tree->left);
    del(tree->right);
    free(tree);
}

int main(int argc, char *argv[]) {
        if (argc != 2) {
            fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        
        FILE *fp = fopen(argv[1], "w+");
        if (!fp) {
            perror("Failed to open file");
            exit(EXIT_FAILURE);
        }
        
        srand(time(NULL));
        for (int i = 0; i < 25; i++) {
            fprintf(fp, "%d\n", rand() % 100);
        }
        rewind(fp);
        
        node *my_tree = NULL;
        int temp;
        while (fscanf(fp, "%d", &temp) == 1) {
            insert(&my_tree, temp);
        }
        fclose(fp);
        
        printf("Tree structure:\n");
        display(my_tree);
        
        printf("\nInorder traversal:\n");
        inorder(my_tree);
        
        printf("\nPreorder traversal:\n");
        preorder(my_tree);
        
        printf("\nPostorder traversal:\n");
        postorder(my_tree);

        printf("\n");
        del(my_tree);
        
        return 0;
    }