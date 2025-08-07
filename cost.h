#include "reading.h"


// all the functions here take the gradient of various parts
// the chain rule tells us that the gradient of a neuron layer is the gradient of the NEXT layer times the sum of all effects of our neuron on the next layer
// the gradient of the edgeweights is the gradient of next neuron layer times the actual activations of previous neuron layer


Vector10 diff_judgement(Vector10 judgement, unsigned char answer) {
    Vector10 out;
    for (int a = 0; a < 10; a ++) {
        if (a == answer) { out.data[a] = add(0x7F, -judgement.data[a]); }
        else { out.data[a] = -judgement.data[a]; }
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