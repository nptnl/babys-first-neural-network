#include <stdio.h>
#include "cost.h"
#include "./matrix.h"
#include "./printing.h"

typedef struct {
    Matrix64 lumen1;
    Matrix32 lumen2;
    Matrix10 lumen3;
} Network;

Network train(Network current, Vector784 retina, unsigned char answer) {

    Vector10 judgement;

    for (int a = 0; a < 10000; a ++) {
    // forward propagation
    Vector64 hidden1 = lumen_one(retina, current.lumen1);
    Vector32 hidden2 = lumen_two(hidden1, current.lumen2);
    judgement = lumen_three(hidden2, current.lumen3);

    //     printf("------ Old Lumen Three ------\n");
    // show_lumen3(current.lumen3);

    // backward propagation
    Vector10 grad_judgement = diff_judgement(judgement, answer);
    Matrix10 grad_lumen3 = diff_lumen_three(hidden2, grad_judgement);
    Vector32 grad_hidden2 = diff_hidden2(current.lumen3, grad_judgement);
    Matrix32 grad_lumen2 = diff_lumen_two(hidden1, grad_hidden2);
    Vector64 grad_hidden1 = diff_hidden1(current.lumen2, hidden2);
    Matrix64 grad_lumen1 = diff_lumen_one(retina, grad_hidden1);

    // readjust weights
    current.lumen1 = readd_m64(current.lumen1, grad_lumen1);
    current.lumen2 = readd_m32(current.lumen2, grad_lumen2);
    current.lumen3 = readd_m10(current.lumen3, grad_lumen3);

    if (a % 1000 == 0) {
    printf("------ iteration %d ------\n", a);
    display_judgement(judgement);
    }
    }
    // printf("------ ∇ Judgement ------\n");
    // display_judgement(grad_judgement);
    // printf("------ ∇ Lumen Three ------\n");
    // show_lumen3(grad_lumen3);
    // printf("------ New Lumen Three ------\n");
    // show_lumen3(current.lumen3);

    return current;
}


#include <limits.h>

int main() {
    
    Network baby;
    baby.lumen1 = funky64();
    baby.lumen2 = funky32();
    baby.lumen3 = funky10();

    ImageAndLabel input = get_one_input();

    train(baby, input.image, input.label);

    // char x = 0x30;
    // char y = 0x70;
    // printf("x = %d\n", x);
    // printf("-x = %d\n", -x);
    // printf("y = %02X\n", y);
    // printf("x+y = %02X\n", (char)(x + y));
    // printf("add x y = %02X\n", add(x, y));
    // printf("x-y = %02X\n", x - y);
    // printf("add x -y = %02X\n", add(x, -y));

    return 0;
}

