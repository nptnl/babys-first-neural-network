#include <stdio.h>
#pragma once

char add(char lhs, char rhs) {
    short sum = lhs + rhs;
    char out;
    if (sum >> 8 > 0x0) { out = 0x7F; }
    else if (sum >> 8 < 0x0) { out = -0x7F; }
    else { out = sum; }
    return out;
}
char mul(char lhs, char rhs) {
    short product = lhs * rhs;
    return product >> 8;
}
char mul_retina(unsigned char neuron, char weight) {
    short product = neuron * weight;
    return product >> 8;
}


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

typedef struct {
    char data[784][64];
} Matrix64;
typedef struct {
    char data[64][32];
} Matrix32;
typedef struct {
    char data[32][10];
} Matrix10;


Vector64 lumen_one(Vector784 before, Matrix64 mapping) {
    Vector64 after;
    for (int a = 0; a < 64; a ++) {
        after.data[a] = 0x0;
    }
    for (int a = 0; a < 64; a++) {
            for (int b = 0; b < 784; b++) {
            after.data[a] = add(after.data[a], mul_retina(before.data[b], mapping.data[b][a]));
        }
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
    }
    return after;
}


Matrix64 identity64() {
    Matrix64 matrix;
    for (int a = 0; a < 784; a++) {
        for (int b = 0; b < 64; b++) {
            if (a == b) { matrix.data[a][b] = 0x1; }
            else { matrix.data[a][b] = 0x0; }
        };
    }
    return matrix;
}
Matrix32 identity32() {
    Matrix32 matrix;
    for (int a = 0; a < 64; a++) {
        for (int b = 0; b < 32; b++) {
            if (a == b) { matrix.data[a][b] = 0x1; }
            else { matrix.data[a][b] = 0x0; }
        };
    }
    return matrix;
}
Matrix10 identity10() {
    Matrix10 matrix;
    for (int a = 0; a < 32; a++) {
        for (int b = 0; b < 10; b++) {
            if (a == b) { matrix.data[a][b] = 0x1; }
            else { matrix.data[a][b] = 0x0; }
        };
    }
    return matrix;
}

Matrix64 funky64() {
    Matrix64 matrix;
    for (int a = 0; a < 784; a++) {
        for (int b = 0; b < 64; b++) {
            if ((a + b) % 700 == 0) { matrix.data[a][b] = 0x3F; }
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
            else { matrix.data[a][b] = 0x00; }
        };
    }
    return matrix;
}
Matrix10 funky10() {
    Matrix10 matrix;
    for (int a = 0; a < 32; a++) {
        for (int b = 0; b < 10; b++) {
            if ((a + b) % 2 == 0) { matrix.data[a][b] = 0x3F; }
            else { matrix.data[a][b] = 0x00; }
        };
    }
    return matrix;
}

Matrix64 readd_m64(Matrix64 current, Matrix64 gradient) {
    for (int a = 0; a < 784; a++) {
        for (int b = 0; b < 64; b++) {
            current.data[a][b] = add(current.data[a][b], gradient.data[a][b]);
        }
    }
    return current;
}
Matrix32 readd_m32(Matrix32 current, Matrix32 gradient) {
    for (int a = 0; a < 64; a++) {
        for (int b = 0; b < 32; b++) {
            current.data[a][b] = add(current.data[a][b], gradient.data[a][b]);
        }
    }
    return current;
}
Matrix10 readd_m10(Matrix10 current, Matrix10 gradient) {
    for (int a = 0; a < 32; a++) {
        for (int b = 0; b < 10; b++) {
            current.data[a][b] = add(current.data[a][b], gradient.data[a][b]);
        }
    }
    return current;
}