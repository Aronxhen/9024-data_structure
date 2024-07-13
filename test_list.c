//
// Created by RBT on 21/3/2024.
//
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include <string.h>
#include <assert.h>

void test_01() {
    list l = list_create();
    assert(l!=NULL);
    assert(list_is_empty(l) == true);
    assert(list_contains(l, "a") == false);
    printf("list_create() test passed.\n");
    list_destroy(l);
}

void test_stack_01() {
    list l = list_create();
    assert(l!=NULL);
    assert(list_is_empty(l) == true);
    assert(list_contains(l, "a") == false);

    // 压栈
    list_push(l, "a");
    assert(list_is_empty(l) == false);
    assert(list_contains(l, "a") == true);
    list_pop(l);
    // 弹栈
    assert(list_is_empty(l) == true);
    assert(list_contains(l, "a") == false);

    char num[10];
    char *result;
    for(int i = 0; i < 10; i++) {
        sprintf(num, "%d", i);
        list_push(l, num);
    }


    assert(list_is_empty(l) == false);
    for(int i = 0; i < 5; i++) {
        result = list_pop(l);
        // 释放内存
        free(result);
    }
    // 弹出一个
    result = list_pop(l);
//    printf("%s\n", result);
    assert(strcmp(result, "4") == 0);
    free(result);

    for(int i = 0; i < 4; i++) {
        result = list_pop(l);
        // 释放内存
        free(result);
    }

    assert(list_is_empty(l) == true);

    printf("test_stack_01() test passed.\n");
    list_destroy(l);
}

void test_queue_01() {
    list l = list_create();
    assert(l!=NULL);
    assert(list_is_empty(l) == true);
    assert(list_contains(l, "a") == false);

    // 入队
    list_enqueue(l, "a");
    assert(list_is_empty(l) == false);
    assert(list_contains(l, "a") == true);
    list_dequeue(l);
    // 弹栈
    assert(list_is_empty(l) == true);
    assert(list_contains(l, "a") == false);

    char num[10];
    char *result;
    for(int i = 0; i < 10; i++) {
        sprintf(num, "%d", i);
        list_enqueue(l, num);
    }

    assert(list_is_empty(l) == false);
    for(int i = 0; i < 5; i++) {
        result = list_dequeue(l);
        // 释放内存
        free(result);
    }
    // 弹出一个
    result = list_dequeue(l);
    assert(strcmp(result, "5") == 0);
    free(result);

    for(int i = 0; i < 4; i++) {
        result = list_dequeue(l);
        // 释放内存
        free(result);
    }

    assert(list_is_empty(l) == true);

    printf("test_queue_01() test passed.\n");
    list_destroy(l);
}

void test_set_01() {
    list l = list_create();
    assert(l!=NULL);
    assert(list_is_empty(l) == true);
    assert(list_contains(l, "a") == false);

    // 入队
    list_add(l, "a");
    assert(list_is_empty(l) == false);
    assert(list_contains(l, "a") == true);
    list_remove(l, "a");
    // 弹栈
    assert(list_is_empty(l) == true);
    assert(list_contains(l, "a") == false);

    char num[10];
    char *result;
    for(int i = 0; i < 10; i++) {
        sprintf(num, "%d", i);
        list_add(l, num);
    }

    for(int i = 0; i < 10; i++) {
        sprintf(num, "%d", i);
        list_add(l, num);
    }
    // 删掉5个
    assert(list_is_empty(l) == false);
    for(int i = 0; i < 5; i++) {
        sprintf(num, "%d", i);
        list_remove(l, num);
    }
    assert(list_length(l) == 5);

    list_add(l, "hello");
    assert(list_length(l) == 6);

    for(int i = 5; i < 10; i++) {
        sprintf(num, "%d", i);
        list_remove(l, num);
    }

    assert(list_is_empty(l) == false);
    assert(list_length(l) == 1);

    result = list_pop(l);

    assert(strcmp(result, "hello") == 0);
    free(result);
    assert(list_is_empty(l) == true);

    printf("test_set_01() test passed.\n");
    list_destroy(l);
}

int main() {
    test_01();
    test_stack_01();
    test_queue_01();
    test_set_01();

    return 0;
}