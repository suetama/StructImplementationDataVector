#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "vector.h"

void test(){
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
    test_popBack_notEmptyVector();
    test_atVector_notEmptyVector();
    test_atVector_requestToLastElement();
    test_back_oneElementInVector();
    test_front_oneElementInVector();
}

int main() {
    vector v = createVector(5);
    v.data[0] = 1;
    v.data[1] = 2;
    v.data[2] = 3;
    v.data[3] = 4;
    v.data[4] = 5;

    printVector(&v);

    reserve(&v, 3);

    printVector1(&v);

    shrinkToFit(&v);

    printVector1(&v);

    printf("%d\n", getVectorValue(&v, 3));

    int *a = atVector(&v, 1);

    printf("%d\n", *a);

    int *back1 = back(&v);

    printf("%d\n", *back1);

    int *front1 = front(&v);

    printf("%d\n", *front1);

    deleteVector(&v);

    printVector(&v);

    return 0;
}

