#include "reading.h"

float cost(Vector10 output, unsigned char answer) {
    float total = 0.0;
    for (int a = 0; a < 10; a ++) {
        float floatized = output.data[a];
        if (a == answer) { total += (1.0 - floatized) * (1.0 - floatized); }
        else { total += floatized * floatized; }
    }
    return total;
}

Vector10 diff_judgement(Vector10 judgement, unsigned char answer) {
    Vector10 out;
    for (int a = 0; a < 10; a ++) {
        if (a == answer) { out.data[a] = -judgement.data[a] - 0x01; }
        else { out.data[a] = judgement.data[a]; }
    }
    return out;
}

Matrix10 diff_lumen_three(Vector32 before, Vector10 grad_after) {
    Matrix10 out;
    for (int a = 0; a < 10; a ++) {
        for (int b = 0; b < 32; b ++) {
            out.data[a][b] = mul(grad_after.data[a], before.data[b]);
        }
    }
    return out;
}

Vector32 diff_hidden2(Matrix10 weights, Vector10 grad_after) {
    Vector32 out;
    for (int b = 0; b < 32; b ++) {
        out.data[b] = 0x0;
        for (int a = 0; a < 10; a ++) {
            out.data[b] = add(out.data[b], mul(weights.data[a][b], grad_after.data[a]));
        }
    }
    return out;
}

Matrix32 diff_lumen_two(Vector64 before, Vector32 grad_after) {
    Matrix32 out;
    for (int a = 0; a < 32; a ++) {
        for (int b = 0; b < 64; b ++) {
            out.data[a][b] = mul(grad_after.data[a], before.data[b]);
        }
    }
    return out;
}

Vector64 diff_hidden1(Matrix32 weights, Vector32 grad_after) {
    Vector64 out;
    for (int b = 0; b < 64; b ++) {
        out.data[b] = 0x0;
        for (int a = 0; a < 32; a ++) {
            out.data[b] = add(out.data[b], mul(weights.data[a][b], grad_after.data[a]));
        }
    }
    return out;
}

Matrix64 diff_lumen_one(Vector784 before, Vector64 grad_after) {
    Matrix64 out;
    for (int a = 0; a < 64; a ++) {
        for (int b = 0; b < 784; b ++) {
            out.data[a][b] = mul(grad_after.data[a], before.data[b]);
        }
    }
    return out;
}