/* Week 3 Assignment: Working with lists */

/* Use the linear linked list code to store a randomly generated set of 100 integers.  Now write a routine that 
will rearrange the list in sorted order of these values. Note you might want to use bubble sort to do this. 
Print these values in rows of 5 on the screen. How will this work? Compare two adjacent list elements and if 
they are out of order swap them. After a first pass the largest element will have bubbled to the end of the list. 
Each pass can look at one less element as the end of a list stays sorted.*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node
Node* create_node(int data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    if (!new_node) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Function to append node to the end
void append(Node** head_ref, int data) {
    Node* new_node = create_node(data);
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    Node* current = *head_ref;
    while (current->next != NULL)
        current = current->next;
    current->next = new_node;
}

// Bubble sort on linked list (by swapping data)
void bubble_sort(Node* head) {
    if (head == NULL) return;

    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                // Swap data
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Function to print the list in rows of 5
void print_list(Node* head) {
    int count = 0;
    while (head != NULL) {
        printf("%5d ", head->data);
        head = head->next;
        count++;
        if (count % 5 == 0)
            printf("\n");
    }
}

// Free the list
void free_list(Node* head) {
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    Node* head = NULL;
    srand(time(NULL));

    // Create list of 100 random integers
    for (int i = 0; i < 100; i++) {
        append(&head, rand() % 1000);  // numbers between 0 and 999
    }

    printf("Original list:\n");
    print_list(head);

    bubble_sort(head);

    printf("\nSorted list:\n");
    print_list(head);

    free_list(head);
    return 0;
}




