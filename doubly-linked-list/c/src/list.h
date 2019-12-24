#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct Node Node;
typedef struct List List;
typedef void (*Free)(void*);

struct Node {
    void *data;
    Node *next;
    Node *prev;
};

struct List {
    Node *head;
    Node *tail;
    Node *current;
    size_t size;
    Free free;
};

List *List_new(void (*free)(void *data));
void List_free(List *list);

int List_is_empty(List *list);
int List_contains(List *list, Node *node);
int List_has_some(List *list);

int List_get_index(List *list, Node *node);
Node *List_get_at(List *list, int index);

Node *List_add_head(List *list, void *data);
Node *List_add_tail(List *list, void *data);
Node *List_add_before(List *list, Node *ref, void *data);
Node *List_add_after(List *list, Node *ref, void *data);
Node *List_add_at(List *list, int index, void *data);

void List_swap(List *list, Node *a, Node *b);
void List_shift_left(List *list);
void List_shift_right(List *list);
void List_reverse(List *list);

void List_clear(List *list);
void List_delete(List *list, Node *node);
void List_delete_at(List *list, int index);

#endif
