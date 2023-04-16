#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <corecrt.h>
#include <stdio.h>
#include <stdlib.h>

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



#endif //VECTOR_VECTOR_H
