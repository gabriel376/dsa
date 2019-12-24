#include "vendor/unity.h"
#include "../src/list.h"

#define LENGTH(xs) (sizeof(xs) / sizeof(xs[0]))

void TEST_ASSERT_EQUAL_LIST(List *list, Node *nodes[], int size) {
    Node *forward = list->head;
    Node *backward = list->tail;
    for (int i = 0; i < size; i++) {
        TEST_ASSERT_EQUAL_PTR(forward, nodes[i]);
        TEST_ASSERT_EQUAL_PTR(backward, nodes[size-i-1]);
        forward = forward->next;
        backward = backward->prev;
    }
}

void test_list_new(void) {
    List *list = List_new(free);

    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_NULL(list->tail);
    TEST_ASSERT_NULL(list->current);

    List_free(list);
}

void test_list_add_head() {
    List *list = List_new(free);

    Node *node1 = List_add_head(list, NULL);
    Node *nodes1[] = { node1 };
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    Node *node2 = List_add_head(list, NULL);
    Node *nodes2[] = { node2, node1 };
    TEST_ASSERT_EQUAL_LIST(list, nodes2, LENGTH(nodes2));

    Node *node3 = List_add_head(list, NULL);
    Node *nodes3[] = { node3, node2, node1 };
    TEST_ASSERT_EQUAL_LIST(list, nodes3, LENGTH(nodes3));

    List_free(list);
}

void test_list_add_tail(void) {
    List *list = List_new(free);

    Node *node1 = List_add_tail(list, NULL);
    Node *nodes1[] = { node1 };
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    Node *node2 = List_add_tail(list, NULL);
    Node *nodes2[] = { node1, node2 };
    TEST_ASSERT_EQUAL_LIST(list, nodes2, LENGTH(nodes2));

    Node *node3 = List_add_tail(list, NULL);
    Node *nodes3[] = { node1, node2, node3 };
    TEST_ASSERT_EQUAL_LIST(list, nodes3, LENGTH(nodes3));

    List_free(list);
}

void test_list_add_before() {
    List *list = List_new(free);

    Node *node1 = List_add_tail(list, NULL);
    Node *node2 = List_add_tail(list, NULL);
    Node *node3 = List_add_tail(list, NULL);
    Node *node4 = List_add_tail(list, NULL);
    Node *node5 = List_add_tail(list, NULL);
    Node *nodes1[] = { node1, node2, node3, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    Node *node6 = List_add_before(list, node1, NULL);
    Node *nodes2[] = { node6, node1, node2, node3, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes2, LENGTH(nodes2));

    Node *node7 = List_add_before(list, node3, NULL);
    Node *nodes3[] = { node6, node1, node2, node7, node3, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes3, LENGTH(nodes3));

    Node *node8 = List_add_before(list, node5, NULL);
    Node *nodes4[] = { node6, node1, node2, node7, node3, node4, node8, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes4, LENGTH(nodes4));

    List_free(list);
}

void test_list_add_after() {
    List *list = List_new(free);

    Node *node1 = List_add_tail(list, NULL);
    Node *node2 = List_add_tail(list, NULL);
    Node *node3 = List_add_tail(list, NULL);
    Node *node4 = List_add_tail(list, NULL);
    Node *node5 = List_add_tail(list, NULL);
    Node *nodes1[] = { node1, node2, node3, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    Node *node6 = List_add_after(list, node1, NULL);
    Node *nodes2[] = { node1, node6, node2, node3, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes2, LENGTH(nodes2));

    Node *node7 = List_add_after(list, node3, NULL);
    Node *nodes3[] = { node1, node6, node2, node3, node7, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes3, LENGTH(nodes3));

    Node *node8 = List_add_after(list, node5, NULL);
    Node *nodes4[] = { node1, node6, node2, node3, node7, node4, node5, node8 };
    TEST_ASSERT_EQUAL_LIST(list, nodes4, LENGTH(nodes4));

    List_free(list);
}

void test_list_add_at() {
    List *list = List_new(free);

    TEST_ASSERT_NULL(List_add_at(list, -1, NULL));
    TEST_ASSERT_NULL(List_add_at(list, 1, NULL));

    Node *node1 = List_add_tail(list, NULL);
    Node *node2 = List_add_tail(list, NULL);
    Node *node3 = List_add_tail(list, NULL);
    Node *node4 = List_add_tail(list, NULL);
    Node *node5 = List_add_tail(list, NULL);
    Node *nodes1[] = { node1, node2, node3, node4, node5 };

    TEST_ASSERT_NULL(List_add_at(list, -1, NULL));
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    TEST_ASSERT_NULL(List_add_at(list, 6, NULL));
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    Node *node6 = List_add_at(list, 0, NULL);
    Node *nodes2[] = { node6, node1, node2, node3, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes2, LENGTH(nodes2));

    Node *node7 = List_add_at(list, 4, NULL);
    Node *nodes3[] = { node6, node1, node2, node3, node7, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes3, LENGTH(nodes3));

    Node *node8 = List_add_at(list, 6, NULL);
    Node *nodes4[] = { node6, node1, node2, node3, node7, node4, node8, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes4, LENGTH(nodes4));

    List_free(list);
}

void test_list_size() {
    List *list = List_new(free);

    TEST_ASSERT_EQUAL_INT(0, list->size);

    List_add_head(list, NULL);
    TEST_ASSERT_EQUAL_INT(1, list->size);

    List_add_tail(list, NULL);
    TEST_ASSERT_EQUAL_INT(2, list->size);

    List_add_before(list, list->tail, NULL);
    TEST_ASSERT_EQUAL_INT(3, list->size);

    List_add_after(list, list->head, NULL);
    TEST_ASSERT_EQUAL_INT(4, list->size);

    List_add_at(list, 1, NULL);
    TEST_ASSERT_EQUAL_INT(5, list->size);

    List_swap(list, list->head, list->tail);
    TEST_ASSERT_EQUAL_INT(5, list->size);

    List_shift_left(list);
    TEST_ASSERT_EQUAL_INT(5, list->size);

    List_shift_right(list);
    TEST_ASSERT_EQUAL_INT(5, list->size);

    List_delete(list, list->head);
    TEST_ASSERT_EQUAL_INT(4, list->size);

    List_delete_at(list, 1);
    TEST_ASSERT_EQUAL_INT(3, list->size);

    List_clear(list);
    TEST_ASSERT_EQUAL_INT(0, list->size);

    List_free(list);
}

void test_list_is_empty() {
    List *list = List_new(free);

    TEST_ASSERT_TRUE(List_is_empty(list));

    List_add_head(list, NULL);
    TEST_ASSERT_FALSE(List_is_empty(list));

    List_add_head(list, NULL);
    TEST_ASSERT_FALSE(List_is_empty(list));

    List_add_tail(list, NULL);
    TEST_ASSERT_FALSE(List_is_empty(list));

    List_add_head(list, NULL);
    TEST_ASSERT_FALSE(List_is_empty(list));

    List_add_tail(list, NULL);
    TEST_ASSERT_FALSE(List_is_empty(list));

    List_free(list);
}

void test_list_has_some() {
    List *list = List_new(free);

    TEST_ASSERT_FALSE(List_has_some(list));

    List_add_head(list, NULL);
    TEST_ASSERT_TRUE(List_has_some(list));

    List_add_head(list, NULL);
    TEST_ASSERT_TRUE(List_has_some(list));

    List_add_tail(list, NULL);
    TEST_ASSERT_TRUE(List_has_some(list));

    List_add_head(list, NULL);
    TEST_ASSERT_TRUE(List_has_some(list));

    List_add_tail(list, NULL);
    TEST_ASSERT_TRUE(List_has_some(list));

    List_free(list);
}

void test_list_contains() {
    List *list = List_new(free);

    TEST_ASSERT_FALSE(List_contains(list, NULL));

    Node *node1 = List_add_tail(list, NULL);
    Node *node2 = List_add_tail(list, NULL);
    Node *node3 = List_add_tail(list, NULL);
    Node *node4 = List_add_tail(list, NULL);
    Node *node5 = List_add_tail(list, NULL);

    TEST_ASSERT_FALSE(List_contains(list, NULL));

    Node node6;
    TEST_ASSERT_FALSE(List_contains(list, &node6));

    TEST_ASSERT_TRUE(List_contains(list, node1));
    TEST_ASSERT_TRUE(List_contains(list, node2));
    TEST_ASSERT_TRUE(List_contains(list, node3));
    TEST_ASSERT_TRUE(List_contains(list, node4));
    TEST_ASSERT_TRUE(List_contains(list, node5));

    List_free(list);
}

void test_list_get_index() {
    List *list = List_new(free);

    TEST_ASSERT_EQUAL_INT(-1, List_get_index(list, NULL));

    Node *node1 = List_add_tail(list, NULL);
    Node *node2 = List_add_tail(list, NULL);
    Node *node3 = List_add_tail(list, NULL);
    Node *node4 = List_add_tail(list, NULL);
    Node *node5 = List_add_tail(list, NULL);

    TEST_ASSERT_EQUAL_INT(-1, List_get_index(list, NULL));

    Node node6;
    TEST_ASSERT_EQUAL_INT(-1, List_get_index(list, &node6));

    TEST_ASSERT_EQUAL_INT(0, List_get_index(list, node1));
    TEST_ASSERT_EQUAL_INT(1, List_get_index(list, node2));
    TEST_ASSERT_EQUAL_INT(2, List_get_index(list, node3));
    TEST_ASSERT_EQUAL_INT(3, List_get_index(list, node4));
    TEST_ASSERT_EQUAL_INT(4, List_get_index(list, node5));

    List_free(list);
}

void test_list_get_at() {
    List *list = List_new(free);

    Node *node1 = List_add_tail(list, NULL);
    Node *node2 = List_add_tail(list, NULL);
    Node *node3 = List_add_tail(list, NULL);
    Node *node4 = List_add_tail(list, NULL);
    Node *node5 = List_add_tail(list, NULL);

    TEST_ASSERT_NULL(List_get_at(list, -1));
    TEST_ASSERT_NULL(List_get_at(list, 5));

    TEST_ASSERT_EQUAL_PTR(node1, List_get_at(list, 0));
    TEST_ASSERT_EQUAL_PTR(node2, List_get_at(list, 1));
    TEST_ASSERT_EQUAL_PTR(node3, List_get_at(list, 2));
    TEST_ASSERT_EQUAL_PTR(node4, List_get_at(list, 3));
    TEST_ASSERT_EQUAL_PTR(node5, List_get_at(list, 4));

    List_free(list);
}

void test_list_swap() {
    List *list = List_new(free);

    Node *node1 = List_add_tail(list, NULL);
    Node *node2 = List_add_tail(list, NULL);
    Node *node3 = List_add_tail(list, NULL);
    Node *node4 = List_add_tail(list, NULL);
    Node *node5 = List_add_tail(list, NULL);
    Node *nodes1[] = { node1, node2, node3, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    List_swap(list, node1, node2);
    Node *nodes2[] = { node2, node1, node3, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes2, LENGTH(nodes2));

    List_swap(list, node1, node2);
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    List_swap(list, node1, node3);
    Node *nodes3[] = { node3, node2, node1, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes3, LENGTH(nodes3));

    List_swap(list, node1, node3);
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    List_swap(list, node1, node4);
    Node *nodes4[] = { node4, node2, node3, node1, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes4, LENGTH(nodes4));

    List_swap(list, node1, node4);
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    List_swap(list, node1, node5);
    Node *nodes5[] = { node5, node2, node3, node4, node1 };
    TEST_ASSERT_EQUAL_LIST(list, nodes5, LENGTH(nodes5));

    List_swap(list, node1, node5);
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    List_swap(list, node2, node3);
    Node *nodes6[] = { node1, node3, node2, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes6, LENGTH(nodes6));

    List_swap(list, node2, node3);
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    List_swap(list, node2, node4);
    Node *nodes7[] = { node1, node4, node3, node2, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes7, LENGTH(nodes7));

    List_swap(list, node2, node4);
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    List_swap(list, node2, node5);
    Node *nodes8[] = { node1, node5, node3, node4, node2 };
    TEST_ASSERT_EQUAL_LIST(list, nodes8, LENGTH(nodes8));

    List_swap(list, node2, node5);
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    List_swap(list, node3, node4);
    Node *nodes9[] = { node1, node2, node4, node3, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes9, LENGTH(nodes9));

    List_swap(list, node3, node4);
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    List_swap(list, node3, node5);
    Node *nodes10[] = { node1, node2, node5, node4, node3 };
    TEST_ASSERT_EQUAL_LIST(list, nodes10, LENGTH(nodes10));

    List_swap(list, node3, node5);
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    List_swap(list, node4, node5);
    Node *nodes11[] = { node1, node2, node3, node5, node4 };
    TEST_ASSERT_EQUAL_LIST(list, nodes11, LENGTH(nodes11));

    List_swap(list, node4, node5);
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    List_free(list);
}

void test_list_shift_left() {
    List *list = List_new(free);

    Node *node1 = List_add_tail(list, NULL);
    Node *node2 = List_add_tail(list, NULL);
    Node *node3 = List_add_tail(list, NULL);
    Node *node4 = List_add_tail(list, NULL);
    Node *node5 = List_add_tail(list, NULL);
    Node *nodes1[] = { node1, node2, node3, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    List_shift_left(list);
    Node *nodes2[] = { node2, node3, node4, node5, node1 };
    TEST_ASSERT_EQUAL_LIST(list, nodes2, LENGTH(nodes2));

    List_shift_left(list);
    Node *nodes3[] = { node3, node4, node5, node1, node2 };
    TEST_ASSERT_EQUAL_LIST(list, nodes3, LENGTH(nodes3));

    List_shift_left(list);
    Node *nodes4[] = { node4, node5, node1, node2, node3 };
    TEST_ASSERT_EQUAL_LIST(list, nodes4, LENGTH(nodes4));

    List_free(list);
}

void test_list_shift_right() {
    List *list = List_new(free);

    Node *node1 = List_add_tail(list, NULL);
    Node *node2 = List_add_tail(list, NULL);
    Node *node3 = List_add_tail(list, NULL);
    Node *node4 = List_add_tail(list, NULL);
    Node *node5 = List_add_tail(list, NULL);
    Node *nodes1[] = { node1, node2, node3, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    List_shift_right(list);
    Node *nodes2[] = { node5, node1, node2, node3, node4 };
    TEST_ASSERT_EQUAL_LIST(list, nodes2, LENGTH(nodes2));

    List_shift_right(list);
    Node *nodes3[] = { node4, node5, node1, node2, node3 };
    TEST_ASSERT_EQUAL_LIST(list, nodes3, LENGTH(nodes3));

    List_shift_right(list);
    Node *nodes4[] = { node3, node4, node5, node1, node2 };
    TEST_ASSERT_EQUAL_LIST(list, nodes4, LENGTH(nodes4));

    List_free(list);
}

void test_list_reverse() {
    List *list = List_new(free);

    Node *node1 = List_add_tail(list, NULL);
    Node *node2 = List_add_tail(list, NULL);
    Node *node3 = List_add_tail(list, NULL);
    Node *node4 = List_add_tail(list, NULL);
    Node *node5 = List_add_tail(list, NULL);
    Node *nodes1[] = { node1, node2, node3, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    List_reverse(list);
    Node *nodes2[] = { node5, node4, node3, node2, node1 };
    TEST_ASSERT_EQUAL_LIST(list, nodes2, LENGTH(nodes2));

    List_reverse(list);
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    List_free(list);
}

void test_list_clear() {
    List *list = List_new(free);

    Node *node1 = List_add_tail(list, NULL);
    Node *node2 = List_add_tail(list, NULL);
    Node *node3 = List_add_tail(list, NULL);
    Node *node4 = List_add_tail(list, NULL);
    Node *node5 = List_add_tail(list, NULL);
    Node *nodes1[] = { node1, node2, node3, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    List_clear(list);
    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_NULL(list->tail);

    List_free(list);
}

void test_list_delete() {
    List *list = List_new(free);

    Node *node1 = List_add_tail(list, NULL);
    Node *node2 = List_add_tail(list, NULL);
    Node *node3 = List_add_tail(list, NULL);
    Node *node4 = List_add_tail(list, NULL);
    Node *node5 = List_add_tail(list, NULL);
    Node *nodes1[] = { node1, node2, node3, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    List_delete(list, node1);
    Node *nodes2[] = { node2, node3, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes2, LENGTH(nodes2));

    List_delete(list, node3);
    Node *nodes3[] = { node2, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes3, LENGTH(nodes3));

    List_delete(list, node5);
    Node *nodes4[] = { node2, node4 };
    TEST_ASSERT_EQUAL_LIST(list, nodes4, LENGTH(nodes4));

    List_free(list);
}

void test_list_delete_at() {
    List *list = List_new(free);

    Node *node1 = List_add_tail(list, NULL);
    Node *node2 = List_add_tail(list, NULL);
    Node *node3 = List_add_tail(list, NULL);
    Node *node4 = List_add_tail(list, NULL);
    Node *node5 = List_add_tail(list, NULL);
    Node *nodes1[] = { node1, node2, node3, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes1, LENGTH(nodes1));

    List_delete_at(list, 0);
    Node *nodes2[] = { node2, node3, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes2, LENGTH(nodes2));

    List_delete_at(list, 1);
    Node *nodes3[] = { node2, node4, node5 };
    TEST_ASSERT_EQUAL_LIST(list, nodes3, LENGTH(nodes3));

    List_delete_at(list, 2);
    Node *nodes4[] = { node2, node4 };
    TEST_ASSERT_EQUAL_LIST(list, nodes4, LENGTH(nodes4));

    List_free(list);
}

int main(void) {
   UnityBegin("test/test_list.c");

   RUN_TEST(test_list_new);
   RUN_TEST(test_list_add_head);
   RUN_TEST(test_list_add_tail);
   RUN_TEST(test_list_add_before);
   RUN_TEST(test_list_add_after);
   RUN_TEST(test_list_add_at);
   RUN_TEST(test_list_size);
   RUN_TEST(test_list_is_empty);
   RUN_TEST(test_list_has_some);
   RUN_TEST(test_list_contains);
   RUN_TEST(test_list_get_index);
   RUN_TEST(test_list_get_at);
   RUN_TEST(test_list_swap);
   RUN_TEST(test_list_shift_left);
   RUN_TEST(test_list_shift_right);
   RUN_TEST(test_list_reverse);
   RUN_TEST(test_list_clear);
   RUN_TEST(test_list_delete);
   RUN_TEST(test_list_delete_at);

   UnityEnd();
   return 0;
}
