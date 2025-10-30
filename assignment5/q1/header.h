#include <stdio.h>
#include <stdlib.h>
#include <string.h>	

typedef struct Tree_Node {
	char data[32];
    struct Tree_Node *left;
    struct Tree_Node *right;
}node;

