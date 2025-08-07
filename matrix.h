#include <stdio.h>
#pragma once

// nonlinear addition to avoid byte overflow
char add(char lhs, char rhs) {
    short sum = lhs + rhs;
    char out;
    // cap positive values at 0x7F = 127
    if (sum > 0x7F) { out = 0x7F; }
    // cap negative values at -0x7F = -127
    else if (sum < -0x7F) { out = -0x7F; }
    else { out = sum; }
    return out;
}
// multiplication is explained in readme
// the bytes are treated as fractions, so 0.2 * 0.3 = 0.06 not 0.06
// this becomes 0x20 * 0x30 → 0x06
char mul(char lhs, char rhs) {
    short product = lhs * rhs;
    return product >> 8;
}
// special multiplication because retina neurons are different type
char mul_retina(unsigned char neuron, char weight) {
    short product = neuron * weight;
    return product >> 8;
}

// the neuron layer structures
// input "Retina" layer 784
// first hidden layer 64
// second hidden layer 32
// output "Judgement" layer 10
typedef struct {
    unsigned char data[784];
} Vector784;
typedef struct {
    char data[64];
} Vector64;
typedef struct {
    char data[32];
} Vector32;
typedef struct {
    char data[10];
} Vector10;

// matrix for edgeweights retina → hidden1
typedef struct {
    char data[784][64];
} Matrix64;
// matrix for edgeweights hidden1 → hidden2
typedef struct {
    char data[64][32];
} Matrix32;
// matrix for edgeweights hidden2 → judgement
typedef struct {
    char data[32][10];
} Matrix10;

// next three functions are just matrix multiplication at different scales
Vector64 lumen_one(Vector784 before, Matrix64 mapping) {
    Vector64 after;
    for (int a = 0; a < 64; a ++) {
        after.data[a] = 0x0;
    }
    for (int a = 0; a < 64; a++) {
            for (int b = 0; b < 784; b++) {
            after.data[a] = add(after.data[a], mul_retina(before.data[b], mapping.data[b][a]));
        }
        // if (after.data[a] < 0x00) { after.data[a] = 0x00; }
    }
    return after;
}
Vector32 lumen_two(Vector64 before, Matrix32 mapping) {
    Vector32 after;
    for (int a = 0; a < 32; a ++) {
        after.data[a] = 0x0;
    }
    for (int a = 0; a < 32; a++) {
            for (int b = 0; b < 64; b++) {
            after.data[a] = add(after.data[a], mul(before.data[b], mapping.data[b][a]));
        }
        // if (after.data[a] < 0x00) { after.data[a] = 0x00; }
    }
    return after;
}
Vector10 lumen_three(Vector32 before, Matrix10 mapping) {
    Vector10 after;
    for (int a = 0; a < 10; a ++) {
        after.data[a] = 0x0;
    }
    for (int a = 0; a < 10; a++) {
            for (int b = 0; b < 32; b++) {
            after.data[a] = add(after.data[a], mul(before.data[b], mapping.data[b][a]));
        }
        // if (after.data[a] < 0x00) { after.data[a] = 0x00; }
    }
    return after;
}

// these add a scaled-down (bitshifted) gradient to the edgeweights in the matrices
Matrix64 readd_m64(Matrix64 current, Matrix64 gradient) {
    for (int a = 0; a < 784; a++) {
        for (int b = 0; b < 64; b++) {
            current.data[a][b] = add(current.data[a][b], gradient.data[a][b] >> 3);
        }
    }
    return current;
}
Matrix32 readd_m32(Matrix32 current, Matrix32 gradient) {
    for (int a = 0; a < 64; a++) {
        for (int b = 0; b < 32; b++) {
            current.data[a][b] = add(current.data[a][b], gradient.data[a][b] >> 3);
        }
    }
    return current;
}
Matrix10 readd_m10(Matrix10 current, Matrix10 gradient) {
    for (int a = 0; a < 32; a++) {
        for (int b = 0; b < 10; b++) {
            current.data[a][b] = add(current.data[a][b], gradient.data[a][b] >> 3);
        }
    }
    return current;
}


// these are for testing purposes
Matrix64 funky64() {
    Matrix64 matrix;
    for (int a = 0; a < 784; a++) {
        for (int b = 0; b < 64; b++) {
            if ((a + b) % 500 == 0) { matrix.data[a][b] = 0x3F; }
            else { matrix.data[a][b] = 0x00; }
        };
    }
    return matrix;
}
Matrix32 funky32() {
    Matrix32 matrix;
    for (int a = 0; a < 64; a++) {
        for (int b = 0; b < 32; b++) {
            if ((a + b) % 20 == 0) { matrix.data[a][b] = 0x3F; }
            else { matrix.data[a][b] = 0x03; }
        };
    }
    return matrix;
}
Matrix10 funky10() {
    Matrix10 matrix;
    for (int a = 0; a < 32; a++) {
        for (int b = 0; b < 10; b++) {
            if ((a + b) % 2 == 0) { matrix.data[a][b] = 0x3F; }
            else { matrix.data[a][b] = 0x20; }
        };
    }
    return matrix;
}