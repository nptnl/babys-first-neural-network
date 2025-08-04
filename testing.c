#include <stdio.h>
#include "cost.h"
#include "./matrix.h"
#include "./printing.h"

int main() {
    ImageAndLabel input = get_one_input();
    Vector64 hidden1 = lumen_one(input.image, funky64());
    Vector32 hidden2 = lumen_two(hidden1, funky32());
    Vector10 judgement = lumen_three(hidden2, funky10());


    printf("------- Retina -------\n");
    show_retina(input.image);
    printf("------- Hidden 1 -------\n");
    show_hidden1(hidden1);
    printf("------- Hidden 2 -------\n");
    show_hidden2(hidden2);
    printf("------- Judgement -------\n");
    for (int a = 0; a < 10; a ++) {
        printf("%d | %X\n", a, judgement.data[a]);
    }

    printf("------- ∇ Judgement -------\n");
    Vector10 grad_judgement = diff_judgement(judgement, 0x5);
    for (int a = 0; a < 10; a ++) {
        printf("%d | 0x%X\n", a, grad_judgement.data[a]);
    }

    printf("------- ∇ Lumen Three -------\n");
    Matrix10 grad_lumen_three = diff_lumen_three(hidden2, grad_judgement);
    for (int a = 0; a < 10; a ++) {
        for (int b = 0; b < 32; b ++) {
            unsigned char item = grad_lumen_three.data[a][b];
            if (item == 0x0) { printf("  "); }
            else { printf("%X", item); }
        }
        printf("\n");
    }

    return 0;
}