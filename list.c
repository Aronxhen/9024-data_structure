#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "list.h"

typedef struct node {
    string data;
    struct node *next;
} *Node;

struct List_Repr {
    Node head;
    Node tail;
    int total;
};

/***************************** GENERAL INTERFACE ******************************/

/**
 * list_create
 *
 * @brief Allocate the required memory for a new list.
 *
 * @return The new list. If there's an error (e.g. out of memory), return NULL.
 */

//create one node
Node node_create(string data) {
    Node new_node = malloc(sizeof(struct node));
    assert(new_node != NULL);
    //now data is a pointer we can not equal to new->data
    //add 1 because '\0'
    new_node->data = malloc(strlen(data) + 1);
    //copy from data to new->data
    strcpy(new_node->data, data);
    //initialize pointer next
    new_node->next = NULL;
    return new_node;
}

//create one list
list list_create(void) {
    list new_list = malloc(sizeof(struct List_Repr));
    assert(new_list != NULL);
    // initialize struct List_Repr
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->total = 0;

    return new_list;
}

/**
 * list_destroy
 *
 * @brief Free all memory associated with the given list.
 *
 * @param list The list to be destroyed. If it's NULL, do nothing.
 */
void list_destroy(list l) {
    if (l != NULL) {
        Node current = l->head;
        Node next = NULL;
        while (current != NULL) {
            next = current->next;
            free(current->data);
            free(current);
            current = next;
        }
        free(l);
    }
}
/**
 * list_is_empty
 *
 * @brief Determines whether a given list is empty or not.
 *
 * @param list The list to check. If it's NULL, the list is empty.
 * @return     True if there are no items in the list
 *             False if there are items in the list
 */
bool list_is_empty(list l) {
    bool empty = true;
    if (l != NULL && l->total > 0) {
        empty = false;
    }
    return empty;
}

/**
 * list_length
 *
 * @brief Returns the number of items in the list.
 *
 * @param list The list to check. If it's NULL, the list is empty.
 * @return     The number of items in the list.
 */
size_t list_length(list l) {
    if (l != NULL) {
        return l->total;
    }
    return 0;
}
/****************************** STACK INTERFACE *******************************/

/**
 * list_push
 *
 * @brief Push an item onto the top of the stack.
 *
 * @param   list The stack to push. If it's NULL, do nothing.
 * @param string The item to be pushed onto the stack. If it's NULL, do nothing.
 */
void list_push(list l, string data) {
    if (l != NULL && data != NULL) {
        Node new_node = node_create(data);
        if (l->head == NULL) {
            l->head = l->tail = new_node;
        } else {
            //firstly change next pointer of node
            l->tail->next = new_node;
            //then change the last pointer of list
            l->tail = new_node;

        }
        l->total++;
    }
}

/**
 * list_pop
 *
 * @brief Pop an item from the top of the stack.
 *
 * @param list The stack to pop. If it's NULL, do nothing.
 * @return     The item popped from the top of the stack. If the stack is
 *             empty, return NULL.
 */
string list_pop(list l) {
    string result = NULL;
    if (l != NULL && l->head != NULL) {
        if (l->tail == l->head) {
            result = l->head->data;
            free(l->head);
            l->total--;
            l->head = NULL;
            l->tail = NULL;
        } else {
            Node current = l->head;
            while (current->next != l->tail) {
                current = current->next;
            }
            //we already know the last one
            //we can immediately pop
            result = l->tail->data;
            free(l->tail);
            //change the tail
            l->tail = current;
            //init the tail next
            l->tail->next = NULL;
            l->total--;
        }
    }
    return result;
}
/****************************** QUEUE INTERFACE *******************************/

/**
 * list_enqueue
 *
 * @brief Enqueue an item at the rear of the queue.
 *
 * @param   list The queue to enqueue. If it's NULL, do nothing.
 * @param string The item to be enqueued.  If it's NULL, do nothing.
 */
void list_enqueue(list l, string data) {
    if (l != NULL) {
        Node new_node = node_create(data);
        if (l->head == NULL) {
            l->head = new_node;
            l->tail = new_node;
        } else {
            //firstly change next pointer of node
            l->tail->next = new_node;
            //then change the last pointer of list
            l->tail = new_node;
        }
        l->total++;
    }
}

/**
 * list_dequeue
 *
 * @brief Dequeue an item from the head of the queue.
 *
 * @param list The queue to dequeue. If it's NULL, do nothing.
 * @return     The item dequeued from the head of the queue. If the queue is
 *             empty, return NULL.
 */
string list_dequeue(list l) {
    string result = NULL;
    if (l != NULL) {
        if (l->head != NULL) {
            //p is delete node
            Node p = l->head;
            result = p->data;
            l->head = l->head->next;
            free(p);
            // if head = tail
            l->total--;
            if (l->total == 0) {
                l->head = l->tail = NULL;
            }
        }
    }
    return result;
}
/******************************* SET INTERFACE ********************************/

/**
* list_add
*
* @brief Add an item to the set, if it is not already in the set.
*
* @param   list The set to add to. If it's NULL, do nothing.
* @param string The item to be added.  If it's NULL, or already in the set,
*               do nothing.
*/
void list_add(list l, string data) {
    //use contains
    if (l != NULL && list_contains(l, data) == false) {
        list_push(l, data);
    }
}

/**
* list_remove
*
* @brief Remove an item from the set.
*
* @param   list The set to remove from. If it's NULL, do nothing.
* @param string The item to be removed. If it's NULL, or not in the set,
*               do nothing.
*/
void list_remove(list l, string data) {
    string result = NULL;
    if (l != NULL && l->head != NULL) {
        if (list_contains(l, data) == true) {
            Node p = l->head;
            Node t = l->tail;
            // if the head data is remove goal
            if (strcmp(p->data, data) == 0) {
                result = list_dequeue(l);
            } else if (strcmp(t->data, data) == 0) {
                result = list_pop(l);
            } else {
                Node previous = l->head;
                Node current = previous->next;
                while (current != l->tail) {
                    if (strcmp(current->data, data) == 0) {
                        break;
                    }
                    previous = current;
                    current = current->next;
                }
                //pp is delete node
                previous->next = current->next;
                result = current->data;
                free(current);
                l->total--;
            }
        }
        free(result);
    }
}
/**
* list_contains
*
* @brief Check if an item is a member of the set.
*
* @param   list The set to check. If it's NULL, return false.
* @param string The item to check. If it's NULL, return false.
* @return       true if the item is in the set, false otherwise.
*/
bool list_contains(list l, string data) {
    bool contains = false;
    if (l != NULL) {
        Node current = l->head;
        while (current != NULL) {
            if (strcmp(current->data, data) == 0) {
                contains = true;
                break;
            }
            current = current->next;
        }
        return contains;
    }
    return contains;
}
