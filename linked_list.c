#include <stdio.h>
#include <stdlib.h>

typedef struct Node node_t;

struct Node {
	int data;
	node_t* next;
};

node_t* create_node();
node_t* init_node(int);

void insert_node_at_the_start(node_t**, node_t*);
void insert_node_at_the_end(node_t*, node_t*);
void insert_node_at_index(node_t*, node_t*, int);

void remove_node_at_the_start(node_t**);
void remove_node_at_the_end(node_t*);
void remove_node_at_index(node_t*, int);

int get_length_of(node_t*_list);

void print_list(node_t*);

int main() {
	node_t* list = init_node(10);
	insert_node_at_the_end(list, init_node(35));
	insert_node_at_the_end(list, init_node(15));
	remove_node_at_index(list, 1);
	print_list(list);
	
	printf("Length: %d", get_length_of(list));
	return 0;
}

node_t* create_node() {
	node_t* node = NULL;
	node = malloc(sizeof(node_t));
	
	if(node == NULL) {
		printf("Memory allocation doesn't work :( Den gamietai, kanw exit\n");
		exit(EXIT_FAILURE);
	}
	
	return node;
}

node_t* init_node(int data) {
	node_t* node = create_node();
	node->data = data;
	node->next = NULL;

	return node;
}

void insert_node_at_index(node_t* list, node_t* node, int index) {
	if(list == NULL || node == NULL) return;
	
	int length = get_length_of(list);
	
	if(index == 0) {
		printf("You can use insert_node_at_the_start() instead");
		insert_node_at_the_start(&list, node);
		return;
	}
	
	if(index > length || index < 0) {
		printf("Out of bounds :(\nYou can't use index that is greater than length or less than zero\n'");
		return;
	}
	
	node_t* current = list;
	for(int i = 0; i < index - 1; i++) current = current->next;
	node->next = current->next;
	current->next = node;
}

void insert_node_at_the_start(node_t** list, node_t* node) {
	node->next = *list;
	*list = node;
}

void remove_node_at_the_start(node_t** list) {
	node_t* temp = *list;
	free(temp);
	*list = (*list)->next;
}

void remove_node_at_index(node_t* list, int index) {
	if(list == NULL) return;
	
	int length = get_length_of(list);
	
	if(index == 0) {
		printf("You can use remove_node_at_index() instead");
		remove_node_at_the_start(&list);\
		return;
	}
	
	if(index > length || index < 0) {
		printf("Out of bounds :(\nYou can't use index that is greater than length or less than zero\n'");
		return;
	}
	
	node_t* current = list;
	for(int i = 0; i < index - 1; i++) current = current->next;
	if(current->next->next) {
		node_t* temp = current->next;
		current->next = current->next->next;
		free(temp);
	} else {
		free(current->next);
		current->next = NULL;
	}
}

void remove_node_at_the_end(node_t* list) {
	if(list == NULL) return;
	
	node_t* current = list;
	while(current->next->next) current = current->next;
	free(current->next);
	current->next = NULL;
}

void insert_node_at_the_end(node_t* list, node_t* node) {
	if(list == NULL || node == NULL) return;
	
	node_t* current = list;
	while(current->next) current = current->next;
	current->next = node;
}

int get_length_of(node_t* list) {
	if(list == NULL) return -1;
	node_t* current = list;

	int length = 1;
	
	while(current->next) {
		length++;
		current = current->next;
	}
	
	return length;
}

void print_list(node_t* list) {
	if(list == NULL) return;
	 
	node_t* current = list;
	
	do {
		printf("%p -> %d\n", current, current->data);	
	} while(current = current->next);
}
