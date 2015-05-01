#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct linked_list_node;
typedef struct linked_list_node llist_node;

struct linked_list_node {
    struct linked_list_node * next;
    int data;
};


bool
llist_insert_front(llist_node ** head, int data) {
    llist_node *new_node = malloc(sizeof(llist_node));
    
    if (!new_node) {
	return false;
    }

    new_node->data = data;
    new_node->next = *head;

    *head = new_node;

    return true;
}


llist_node *
llist_find(llist_node * const head, int data) {
    llist_node * current_node = head;
    
    while (current_node != 0 && current_node->data != data) {
	current_node = current_node->next;
    }

    return current_node;
}


bool
llist_delete_node(llist_node ** head, llist_node * delete_me) {
    if (!head || !*head || !delete_me) {
	return false;
    }

    if (*head == delete_me) {
	*head = (*head)->next;
	free(delete_me);

	return true;
    }

    llist_node * elem = *head;

    while (elem) {
	if (elem->next == delete_me) {
	    elem->next = elem->next->next;
	    free(delete_me);
		
	    return true;
	}

	elem = elem->next;
    }

    return false;
}


void
llist_traverse(llist_node * head, void (*visit)(llist_node *)) {
    llist_node * current_node = head;

    while (current_node) {
	visit(current_node);
	current_node = current_node->next;
    }
}


void
llist_delete_list(llist_node ** head) {
    llist_node * tmp;

    while (!head) {
	tmp = (*head)->next;
	free(head);
	*head = tmp;
    }
}


void llist_visit_print(llist_node * node) {
    printf("%d", node->data);

    if (node->next) {
	printf(" -> ");
    }
}


int main (int argc, char ** argv) {
    llist_node * list = 0;

    llist_insert_front(&list, 2);
    llist_insert_front(&list, 4);
    llist_insert_front(&list, 1);

    llist_traverse(list, llist_visit_print);
    printf("\n");

    llist_delete_node(&list, list->next);

    llist_traverse(list, llist_visit_print);
    printf("\n");

    llist_delete_node(&list, list);

    llist_traverse(list, llist_visit_print);
    printf("\n");
    
    return 0;
}

