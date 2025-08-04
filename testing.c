#include <stdio.h>
#include "cost.h"
#include "./matrix.h"
#include "./printing.h"

int main() {

    Matrix64 lumen1 = funky64();
    Matrix32 lumen2 = funky32();
    Matrix10 lumen3 = funky10();

    ImageAndLabel input = get_one_input();
    Vector64 hidden1;
    Vector32 hidden2;
    Vector10 judgement;

    for (int a = 0; a < 100; a ++) {
        hidden1 = lumen_one(input.image, lumen1);
        hidden2 = lumen_two(hidden1, lumen2);
        judgement = lumen_three(hidden2, lumen3);


        // printf("------- Retina -------\n");
        // show_retina(input.image);
        // printf("------- Hidden 1 -------\n");
        // show_hidden1(hidden1);
        // printf("------- Hidden 2 -------\n");
        // show_hidden2(hidden2);
        // printf("------- Judgement -------\n");
        // display_judgement(judgement);

        if (a % 10 == 0) {
            printf("------- iteration %d -------\n", a);
            display_judgement(judgement);
        }

        Vector10 grad_judgement = diff_judgement(judgement, input.label);
        Matrix10 grad_lumen3 = diff_lumen_three(hidden2, grad_judgement);
        Vector32 grad_hidden2 = diff_hidden2(lumen3, grad_judgement);
        Matrix32 grad_lumen2 = diff_lumen_two(hidden1, grad_hidden2);
        Vector64 grad_hidden1 = diff_hidden1(lumen2, hidden2);
        Matrix64 grad_lumen1 = diff_lumen_one(input.image, grad_hidden1);

        // printf("------- ∇ Judgement -------\n");
        // display_judgement(grad_judgement);
        // printf("------- ∇ Hidden 2 -------\n");
        // show_hidden2(grad_hidden2);
        // printf("------- ∇ Hidden 1 -------\n");
        // show_hidden1(grad_hidden1);

        lumen1 = readd_m64(lumen1, grad_lumen1);
        lumen2 = readd_m32(lumen2, grad_lumen2);
        lumen3 = readd_m10(lumen3, grad_lumen3);
    }

    printf("------- Judgement -------\n");
    display_judgement(judgement);

    return 0;
}

