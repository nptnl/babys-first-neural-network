#include <stdio.h>
#include "matrix.h"
#pragma once

void show_retina(Vector784 layer) {
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            unsigned char item = layer.data[28*i + j];
            if (item == 0x0) { printf("  "); }
            else if (item < 0x10) { printf("0%X", item); }
            else { printf("%X", item); }
        }
        printf("\n");
    }
}

void show_hidden1(Vector64 layer) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            unsigned char item = layer.data[8*i + j];
            if (item == 0x0) { printf("  "); }
            else if (item < 0x10) { printf("0%X", item); }
            else { printf("%X", item); }
        }
        printf("\n");
    }
}

void show_hidden2(Vector32 layer) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            unsigned char item = layer.data[8*i + j];
            if (item == 0x0) { printf("  "); }
            else if (item < 0x10) { printf("0%X", item); }
            else { printf("%X", item); }
        }
        printf("\n");
    }
}