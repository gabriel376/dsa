#include "list.h"

/*
 * Internal helper functions
 */
static Node *List_node_new(void *data);
static void List_node_free(Node *node);
static Node *List_init(List *list, void *data);
static void List_remove(List *list, Node *node);

/*
 * Creates a new List
 */
List *List_new(Free free) {
    List *list = calloc(1, sizeof(List));
    list->free = free;
    return list;
}

/*
 * Free List allocated memory
 */
void List_free(List *list) {
    List_clear(list);
    free(list);
}

/*
 * Creates a new Node
 */
static Node *List_node_new(void *data) {
    Node *node = calloc(1, sizeof(Node));
    node->data = data;
    return node;
}

/*
 * Free Node allocated memory
 */
static void List_node_free(Node *node) {
    free(node);
}

/*
 * List is empty ?
 */
int List_is_empty(List *list) {
    return list->head ? 0 : 1;
}

/*
 * List has some Node ?
 */
int List_has_some(List *list) {
    return list->head ? 1 : 0;
}

/*
 * List contains Node ?
 */
int List_contains(List *list, Node *node) {
    return List_get_index(list, node) >= 0;
}

/*
 * Get Node index
 */
int List_get_index(List *list, Node *node) {
    Node *current = list->head;
    for (int i = 0; current; i++) {
        if (node == current) {
            return i;
        }
        current = current->next;
    }
    return -1;
}

/*
 * Get Node at index
 */
Node *List_get_at(List *list, int index) {
    Node *current = list->head;
    for (int i = 0; current; i++) {
        if (i == index) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/*
 * List init
 */
static Node *List_init(List *list, void *data) {
    Node *new = List_node_new(data);
    list->head = new;
    list->tail = new;
    list->size = 1;
    return new;
}

/*
 * Add Node to List head
 */
Node *List_add_head(List *list, void *data) {
    if (list->head) {
        return List_add_before(list, list->head, data);
    }
    return List_init(list, data);
}

/*
 * Add Node to List tail
 */
Node *List_add_tail(List *list, void *data) {
    if (list->tail) {
        return List_add_after(list, list->tail, data);
    }
    return List_init(list, data);
}

/*
 * Add Node before other node
 */
static void List_add_node_before(List *list, Node *node, Node *new) {
    new->prev = node->prev;
    new->next = node;
    if (node->prev) {
        node->prev->next = new;
    } else {
        list->head = new;
    }
    node->prev = new;
    list->size++;
}

/*
 * Add Node before other node
 */
Node *List_add_before(List *list, Node *node, void *data) {
    Node *new = List_node_new(data);
    List_add_node_before(list, node, new);
    return new;
}

/*
 * Add Node after other node
 */
static void List_add_node_after(List *list, Node *node, Node *new) {
    new->prev = node;
    new->next = node->next;
    if (node->next) {
        node->next->prev = new;
    } else {
        list->tail = new;
    }
    node->next = new;
    list->size++;
}

/*
 * Add Node after other node
 */
Node *List_add_after(List *list, Node *node, void *data) {
    Node *new = List_node_new(data);
    List_add_node_after(list, node, new);
    return new;
}

/*
 * Add Node at index
 */
Node *List_add_at(List *list, int index, void *data) {
    Node *current = list->head;

    for (int i = 0; current; i++) {
        if (i == index) {
            return List_add_before(list, current, data);
        }
        current = current->next;
    }

    return NULL;
}

/*
 * Swap Nodes
 */
void List_swap(List *list, Node *a, Node *b) {
    if (a == b->prev) {
        List_remove(list, b);
        List_add_node_before(list, a, b);

    } else if (b == a->prev) {
        List_remove(list, a);
        List_add_node_before(list, b, a);

    } else {
        List_remove(list, a);
        List_remove(list, b);

        if (!a->next) {
            Node *temp = b->next;
            List_add_node_after(list, list->tail, b);
            List_add_node_before(list, temp, a);

        } else if (!b->next) {
            Node *temp = a->next;
            List_add_node_after(list, list->tail, a);
            List_add_node_before(list, temp, b);

        } else {
            Node *temp = a->next;
            List_add_node_before(list, b->next, a);
            List_add_node_before(list, temp, b);
        }
    }
}

/*
 * Shift List left
 */
void List_shift_left(List *list) {
    Node *node = list->head;
    List_remove(list, node);
    List_add_node_after(list, list->tail, node);
}

/*
 * Shift List right
 */
void List_shift_right(List *list) {
    Node *node = list->tail;
    List_remove(list, node);
    List_add_node_before(list, list->head, node);
}

/*
 * Reverse List
 */
void List_reverse(List *list) {
    Node *a = list->head;
    Node *b = list->tail;
    while (a && b && a != b) {
        List_swap(list, a, b);
        Node *temp = a->prev;
        a = b->next;
        b = temp;
    }
}

/*
 * Clear List nodes
 */
void List_clear(List *list) {
    while (list->head) {
        List_delete(list, list->head);
    }
}

/*
 * Remove Node from List
 */
static void List_remove(List *list, Node *node) {
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    list->size--;
}

/*
 * Delete Node from List
 */
void List_delete(List *list, Node *node) {
    List_remove(list, node);
    list->free(node->data);
    List_node_free(node);
}

/*
 * Delete Node at index from List
 */
void List_delete_at(List *list, int index) {
    Node *node = List_get_at(list, index);
    List_delete(list, node);
}
