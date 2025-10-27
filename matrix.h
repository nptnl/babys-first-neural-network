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
    return product >> 7;
}
// special multiplication because retina neurons are different type
char mul_retina(unsigned char neuron, char weight) {
    short product = (neuron >> 1) * weight;
    return product >> 7;
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
    char data[64][784];
} Matrix64;
// matrix for edgeweights hidden1 → hidden2
typedef struct {
    char data[32][64];
} Matrix32;
// matrix for edgeweights hidden2 → judgement
typedef struct {
    char data[10][32];
} Matrix10;

// next three functions are just matrix multiplication at different scales
Vector64 lumen_one(Vector784 before, Matrix64 mapping) {
    Vector64 after;
    for (int a = 0; a < 64; a++) {
        after.data[a] = 0x0;
        for (int b = 0; b < 784; b++) {
            after.data[a] = add(after.data[a], mul_retina(before.data[b], mapping.data[a][b]));
        }
        // if (after.data[a] < 0x00) { after.data[a] = 0x00; }
    }
    return after;
}
Vector32 lumen_two(Vector64 before, Matrix32 mapping) {
    Vector32 after;
    for (int a = 0; a < 32; a++) {
        after.data[a] = 0x0;
        for (int b = 0; b < 64; b++) {
            after.data[a] = add(after.data[a], mul(before.data[b], mapping.data[a][b]));
        }
        // if (after.data[a] < 0x00) { after.data[a] = 0x00; }
    }
    return after;
}
Vector10 lumen_three(Vector32 before, Matrix10 mapping) {
    Vector10 after;
    for (int a = 0; a < 10; a++) {
        after.data[a] = 0x0;
        for (int b = 0; b < 32; b++) {
            after.data[a] = add(after.data[a], mul(before.data[b], mapping.data[a][b]));
        }
        if (after.data[a] < 0x00) { after.data[a] = 0x00; }
    }
    return after;
}


// LEARNRATE is a multiplier on the gradient
static char LEARNRATE = 0x7F;
// LEARNBUFF is a limit on the overall adjustment in terms of the distance between x and the endpoint (0x7F or -0x7F)
static char LEARNBUFF = 0x40;

char max_adjust(char cur, char grad) {
    char max_pos = mul(add(-cur, 0x7F), LEARNBUFF);
    char max_neg = mul(add(-cur, -0x7F), LEARNBUFF);
    char adjust = mul(grad, LEARNRATE);
    if (adjust > max_pos) { adjust = max_pos; }
    if (adjust < max_neg) { adjust = max_neg; }
    return add(cur, adjust);
}

// these add a scaled-down gradient to the edgeweights in the matrices
Matrix64 readd_m64(Matrix64 current, Matrix64 gradient) {
    for (int a = 0; a < 64; a++) {
        for (int b = 0; b < 784; b++) {
            // current.data[a][b] = add(current.data[a][b], mul(gradient.data[a][b], LEARNRATE));
            current.data[a][b] = max_adjust(current.data[a][b], gradient.data[a][b]);
        }
    }
    return current;
}
Matrix32 readd_m32(Matrix32 current, Matrix32 gradient) {
    for (int a = 0; a < 32; a++) {
        for (int b = 0; b < 64; b++) {
            // current.data[a][b] = add(current.data[a][b], mul(gradient.data[a][b], LEARNRATE));
            current.data[a][b] = max_adjust(current.data[a][b], gradient.data[a][b]);
        }
    }
    return current;
}
Matrix10 readd_m10(Matrix10 current, Matrix10 gradient) {
    for (int a = 0; a < 10; a++) {
        for (int b = 0; b < 32; b++) {
            // current.data[a][b] = add(current.data[a][b], mul(gradient.data[a][b], LEARNRATE));
            current.data[a][b] = max_adjust(current.data[a][b], gradient.data[a][b]);
        }
    }
    return current;
}

#include <stdlib.h>
// these are for testing purposes
Matrix64 funky64() {
    Matrix64 matrix;
    for (int a = 0; a < 64; a++) {
        for (int b = 0; b < 784; b++) {
            matrix.data[a][b] = rand() >> 28;
            // if ((a + b) % 4 == 1) { matrix.data[a][b] = -matrix.data[a][b]; }
        };
    }
    return matrix;
}
Matrix32 funky32() {
    Matrix32 matrix;
    for (int a = 0; a < 32; a++) {
        for (int b = 0; b < 64; b++) {
            matrix.data[a][b] = rand() >> 26;
            // if ((a + b) % 4 == 1) { matrix.data[a][b] = -matrix.data[a][b]; }
        };
    }
    return matrix;
}
Matrix10 funky10() {
    Matrix10 matrix;
    for (int a = 0; a < 10; a++) {
        for (int b = 0; b < 32; b++) {
            matrix.data[a][b] = rand() >> 26;
            // if ((a + b) % 4 == 1) { matrix.data[a][b] = -matrix.data[a][b]; }
        };
    }
    return matrix;
}