#include <stdio.h>


typedef struct {
    unsigned char data[784];
} InputVector;

typedef struct {
    unsigned char data[784][784];
} InputInputMatrix;

InputVector input_input(
    InputVector before, InputInputMatrix mapping
) {
    InputVector after;
    for (int a = 0; a < 784; a ++) {
        after.data[a] = 0x0;
    }
    for (int a = 0; a < 784; a++) {
        for (int b = 0; b < 784; b++) {
            after.data[a] += before.data[b] * mapping.data[a][b];
        }
    }
    return after;
}

InputInputMatrix input_identity() {
    InputInputMatrix matrix;
    for (int a = 0; a < 784; a ++) {
        for (int b = 0; b < 784; b ++) {
            matrix.data[a][b] = 0x0;
        }
    }
    for (int a = 0; a < 784; a++) {
        for (int b = 0; b < 784; b++) {
            if (a == b) { matrix.data[a][b] = 0x1; }
            else { matrix.data[a][b] = 0x0; }
        };
    }
    return matrix;
}