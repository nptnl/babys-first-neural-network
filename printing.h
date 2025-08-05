#include <stdio.h>
#include "matrix.h"
#pragma once

void plothex(char item) {
    if (item > 0x00) { printf(" %02X ", item); }
    else if (item < 0x00) { printf("-%02X ", item); }
    else { printf("    "); }
}

void plothex_retina(unsigned char item) {
    if (item == 0x0) { printf("  "); }
    else { printf("%02X", item); }
}

void show_retina(Vector784 layer) {
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            plothex_retina(layer.data[28*i + j]);
        }
        printf("\n");
    }
}
void show_hidden1(Vector64 layer) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            plothex(layer.data[8*i + j]);
        }
        printf("\n");
    }
}
void show_hidden2(Vector32 layer) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            plothex(layer.data[8*i + j]);
        }
        printf("\n");
    }
}
void display_judgement(Vector10 layer) {
    for (int a = 0; a < 10; a ++) {
        printf("%d | %d\n", a, layer.data[a]);
    }
}

void show_lumen3(Matrix10 weights) {
    for (int a = 0; a < 10; a ++) {
        for (int b = 0; b < 32; b ++) {
            plothex(weights.data[a][b]);
        }
        printf("\n");
    }
}
void show_lumen2(Matrix32 weights) {
    for (int a = 0; a < 32; a ++) {
        for (int b = 0; b < 64; b ++) {
            plothex(weights.data[a][b]);
        }
        printf("\n");
    }
}
void show_lumen1(Matrix64 weights) {
    for (int a = 0; a < 64; a ++) {
        for (int b = 0; b < 784; b ++) {
            plothex(weights.data[a][b]);
        }
        printf("\n");
    }
}