// CURRENT ALWAYS -> LATEST (NOT NULL)

#include <stdio.h>
#include <stdlib.h>

typedef struct Node_struct {
	int val;
	struct Node_struct *next;
}Node;

Node *head = NULL;

Node *create_Node(int val) {
	Node *temp_node = (Node *)malloc(sizeof(Node));
	if(!temp_node) {
		printf("malloc failed");
		return NULL;
	}
	temp_node->val = val;
	temp_node->next = NULL;
	return temp_node;
}

void create_LL() {
	Node *current = NULL;
	int newLL = 0;
	if(!head) {	
		newLL = 1;	
		head = create_Node(-1); // sentinel Node
		current = head;
	}else {
		current = head;
		while (current->next!= NULL){
			current = current->next;
		}
	}
	int val;
	do {
		printf("Enter val (-1 to stop):- ");
		scanf("%d" , &val);
		if(val != -1) {
			current->next = create_Node(val);
		}
		else break;
		current = current->next;
	}while(1);
	printf("List created:- ");
	if(newLL){
		Node *temp = head;
		head = head->next;
		free(temp); // freeing sentinel node
	}
}

void print_LL() {
	Node *current = head;
	while(current) {
		printf("%d -> " , current->val);
		current = current->next;
	}
}

int empty_LL() {
	return head == NULL ? 1 : 0;
}

void delete_LL() {
	if(empty_LL()){
		printf("List empty !!");
		return;
	}
	Node *current = head;
	Node *previous = NULL;
	while(current) {
		previous = current;
		current = current->next;
		free(previous);
	}
	Node *temp = head;
	free(head);
}

void insert_after_data(int data) {
	if(empty_LL()){
		printf("List empty !!");
		return;
	}
	Node *current = head;
	int found = 0 , val;
	while(current != NULL) {
		if(data == current->val) {
			found = 1;
			printf("Enter new_val:- ");
			scanf("%d" , &val);
			Node *newnode = create_Node(val);
			if(current->next) {
				Node *temp = current->next;
				current->next = newnode;
				newnode->next = temp;
			} else {
				current->next = newnode;
			}
		}
		current = current->next;
	}	
	if(found) {
		printf("New data inserted after\n");
		
	}
	else printf("Data not found\n");
}

void insert_before_data(int data) {
	if(empty_LL()){
		printf("List empty !!");
		return;
	}
	Node *current = head;
	Node *previous = NULL;
	int found = 0 , val;
	while(current != NULL) {
		if(data == current->val) {
			found = 1;
			printf("Enter new_val:- ");
			scanf("%d" , &val);
			Node *newnode = create_Node(val);
			if(previous->next) {
				Node *temp = previous->next;
				previous->next = newnode;
				newnode->next = temp;
			}
		}
		previous = current;
		current = current->next;
	}	
	if(found){
		printf("New data inserted before\n");
		
	}
	else printf("Data not found\n");
}

void delete_ref(int ref) {
	int found = 0 , val;
	if(empty_LL()){
		printf("List empty !!");
		return;
	}
	if(ref == head->val) {
		Node *temp = head;
		head = head->next;
		free(temp);
		found = 1;
	}
	Node *current = head;
	Node *previous = NULL;
	while(current != NULL) {
		if(ref == current->val) {
			found = 1;
			Node *temp = current;
			previous->next = current->next;
			current = current->next;
			free(temp);
			
		}else {
			previous = current;
			current = current->next;
		}
	}
	if(found) {
		printf("Data deleted\n");
	}
	else printf("Data not found\n");	
}

void delete_pos(int pos) {
	int counter = 0 , deleted = 0;
	if(empty_LL()){
		printf("List empty !!");
		return;
	}
	if(pos == 0) {
		Node *temp = head;
		head = head->next;
		free(temp);
	}
	Node *current = head;
	Node *previous = NULL;

	while(current != NULL) {
		if(counter+3 == pos) { // account for human index & sentinel
			deleted = 1;
			Node *temp = current;
			previous->next = current->next;
			free(temp);
			current = current->next;
			break;
		} else {
			previous = current;
			current = current->next;
			counter++;
		}
	}
	if(deleted) {
		printf("Data deleted\n");
		
	}
	else printf("Data not found\n");
}

Node *get_middle() {
	Node *slow = head;
	Node *fast = head;

	while(fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

Node *get_nth_fromend(int nth) {
	if(empty_LL()){
		printf("List empty !!");
		return NULL;
	}
	Node *slow = head;
    Node *fast = head;
	for (int i = 0; i < nth; i++) {
        if (fast == NULL) {
            return NULL;
        }
        fast = fast->next;
    }
	while (fast != NULL) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}


int main() {
    int *arr = (int *)malloc(sizeof(int) * 1);
    arr[0] = 0;
    int choice=0 , pos , n , ref , size=1;
    printf("Create Linked_list\n");
    create_LL();
    do {
        printf("\nMenu:\n");
        printf("1. Create Linked_List\n");
        printf("2. Insert before ref\n");
        printf("3. Insert after ref\n");
        printf("4. Delete by data\n");
        printf("5. Delete by position\n");
        printf("6. Get middle element\n");
        printf("7. Get nth from end\n");
        printf("8. Display\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
	Node *temp;

        switch (choice) {
            case 1:
                printf("Batch insert new LL\n");
				create_LL();
                break;
            case 2:
                printf("Enter reference: ");
                scanf("%d", &ref);
                insert_before_data(ref);
                break;
            case 3:
                printf("Enter reference: ");
                scanf("%d", &ref);
                insert_after_data(ref);
                break;
            case 4:
                printf("Enter reference to delete: ");
                scanf("%d", &ref);
                delete_ref(ref);
                break;
            case 5:
                printf("Enter position to delete: ");
                scanf("%d", &pos);
                delete_pos(pos);
                break;
            case 6:
				temp = get_middle();
				printf("middle node:- %d\n" , temp->val);
                break;
            case 7:
            	printf("Enter nth pos: ");
                scanf("%d", &pos);
				temp = get_nth_fromend(pos);
				if(!temp) {
					printf("Index out of bounds");
					break;
				}
				printf("nth_from_end node:- %d\n" , temp->val);
                break;
            case 8:
                print_LL();
                break;
            case 0:
                delete_LL();
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 0);

    return 0;
}
