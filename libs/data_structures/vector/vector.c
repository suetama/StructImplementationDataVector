#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "vector.h"

void test(){
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
    test_popBack_notEmptyVector();
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

    deleteVector(&v);

    printVector(&v);

    return 0;
}

