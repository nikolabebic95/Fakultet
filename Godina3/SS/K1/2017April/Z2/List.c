#include <stdio.h>
#include <stdlib.h>

typedef struct list_element_struct {
    int data;
    struct list_element_struct *next;
} ListElement;

ListElement *loadList(int n) {
    int i;
    ListElement *head = NULL;
    ListElement *tail;
    ListElement *new_element;

    for (i = 0; i < n; i++) {
        new_element = (ListElement *)malloc(sizeof(ListElement));
        if (new_element == NULL) exit(-1);
        new_element->next = NULL;
        scanf("%d", &new_element->data);
        if (head == NULL) head = new_element;
        else tail->next = new_element;
        tail = new_element;
    }

    return head;
}

void freeList(ListElement **head) {
    ListElement *old_head;
    while (*head != NULL) {
        old_head = *head;
        *head = (*head)->next;
        free(old_head);
    }
}

void printList(ListElement *head) {
    ListElement *curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }

    printf("\n");
}

void test() {
    // Used for testing
}
