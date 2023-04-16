#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <corecrt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct vector {
    int *data; // указатель на элементы вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
} vector;


vector createVector(size_t n) {
    vector *v = (vector*)malloc(sizeof(vector));  // выделяем память под структуру
    if (v == NULL) {  // проверяем, удалось ли выделить память
        fprintf(stderr, "bad alloc");  // выводим сообщение об ошибке в поток ошибок
        exit(1);                       // завершаем программу с кодом 1
    }
    if (n == 0) {  // если размер вектора равен 0, то емкость также равна 0
        v->data = NULL;  // указатель на данные вектора равен NULL
        v->size = 0;
        v->capacity = 0;
    } else {
        v->data = (int*)malloc(n * sizeof(int));  // выделяем память под массив данных
        if (v->data == NULL) {  // проверяем, удалось ли выделить память
            fprintf(stderr, "bad alloc");  // выводим сообщение об ошибке в поток ошибок
            exit(1);                       // завершаем программу с кодом 1
        }
        v->size = n;       // устанавливаем размер вектора
        v->capacity = n;   // устанавливаем емкость вектора
    }

    return *v;              // возвращаем дескриптор вектора
}

void printVector(vector *v) {
    for (size_t i = 0; i < v->size; i++) {
        printf("%d ", v->data[i]);
    }
    printf("\n");
}

void printVector1(vector *v) {
    for (size_t i = 0; i < v->capacity; i++) {
        printf("%d ", v->data[i]);
    }
    printf("\n");
}

void reserve(vector *v, size_t newCapacity) {
    if (newCapacity == 0) {
        free(v->data);  // если newCapacity == 0, то освобождаем память, выделенную под массив данных
        v->data = NULL;
        v->size = 0;
        v->capacity = 0;
    } else if (newCapacity > v->capacity) {
        int *newData = (int*)realloc(v->data, newCapacity * sizeof(int));  // перевыделяем память под массив данных
        if (newData == NULL) {  // проверяем, удалось ли перевыделить память
            fprintf(stderr, "bad alloc");  // выводим сообщение об ошибке в поток ошибок
            exit(1);                       // завершаем программу с кодом 1
        }
        v->data = newData;
        v->capacity = newCapacity;
    } else if (newCapacity < v->size) {
        v->size = newCapacity;  // уменьшаем размер вектора до newCapacity
    }
}

void clear(vector *v){
    v->size = 0;
}

void shrinkToFit(vector *v){
    v->capacity = v->size;
    v->data = realloc(v->data, v->size * sizeof(int));
}

void deleteVector(vector *v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

bool isEmpty(vector *v) {
    return v->size == 0;
}

bool isFull(vector *v) {
    return v->size == v->capacity;
}

int getVectorValue(vector *v, size_t i) {
    return v->data[i];
}

void pushBack(vector *v, int x) {
    if (isFull(v)) {
        reserve(v, v->capacity * 2);
    }
    v->data[v->size++] = x;
}

void test_pushBack_emptyVector() {
    vector v = createVector(0);
    pushBack(&v, 42);
    assert(v.size == 1);
    assert(v.data[0] == 42);
    deleteVector(&v);
}

void test_pushBack_fullVector() {
    vector v = createVector(1);
    v.data[0] = 1;
    pushBack(&v, 42);
    assert(v.size == 2);
    assert(v.capacity == 2);
    assert(v.data[0] == 1);
    assert(v.data[1] == 42);
    deleteVector(&v);
}

void popBack(vector *v) {
    if (v->size == 0) {
        fprintf(stderr, "Error: Cannot pop from empty vector\n");
        exit(1);
    }
    v->size--;
}

void test_popBack_notEmptyVector() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(v.size == 1);
    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity == 1);
}

int* atVector(vector *v, size_t index) {
    if (index >= v->size) {
        fprintf(stderr, "IndexError: a[%zu] is not exists\n", index);
        exit(1);
    }

    return v->data + index;
}

int* back(vector *v) {
    if (v->size == 0) {
        fprintf(stderr, "Error: vector is empty\n");
        exit(1);
    }
    return &(v->data[v->size - 1]);
}

int* front(vector *v) {
    if (v->size == 0) {
        fprintf(stderr, "Error: Vector is empty\n");
        exit(1);
    }
    return &(v->data[0]);
}

void test_atVector_notEmptyVector() {
    vector v = createVector(2);
    pushBack(&v, 5);
    pushBack(&v, 10);
    int* ptr = atVector(&v, 0);
    assert(*ptr == 5);
    ptr = atVector(&v, 1);
    assert(*ptr == 10);
    clear(&v);
}

void test_atVector_requestToLastElement() {
    vector v = createVector(2);
    pushBack(&v, 5);
    pushBack(&v, 10);
    int* ptr = atVector(&v, 1);
    assert(*ptr == 10);
    clear(&v);
}

void test_back_oneElementInVector() {
    vector v = createVector(2);
    pushBack(&v, 5);
    int* ptr = back(&v);
    assert(*ptr == 5);
    clear(&v);
}

void test_front_oneElementInVector() {
    vector v = createVector(2);
    pushBack(&v, 5);
    int* ptr = front(&v);
    assert(*ptr == 5);
    clear(&v);
}

#endif //VECTOR_VECTOR_H
