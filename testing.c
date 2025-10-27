#include <stdio.h>
#include "cost.h"
#include "./matrix.h"
#include "./printing.h"

typedef struct {
    Matrix64 lumen1;
    Matrix32 lumen2;
    Matrix10 lumen3;
} Network;


int print_vectors(Vector784 retina, Vector64 hidden1, Vector32 hidden2, Vector10 judgement) {
    printf("retina\n");
    show_retina(retina);
    printf("hidden1\n");
    show_hidden1(hidden1);
    printf("hidden2\n");
    show_hidden2(hidden2);
    printf("judgement\n");
    display_judgement(judgement);
}

Network train_once(Network current, Vector784 retina, unsigned char answer) {

    // forward propagation
    Vector64 hidden1 = lumen_one(retina, current.lumen1);
    Vector32 hidden2 = lumen_two(hidden1, current.lumen2);
    Vector10 judgement = lumen_three(hidden2, current.lumen3);

    printf("%d : %d\n", answer, judgement.data[answer]);

    // printf("judgement\n");
    // display_judgement(judgement);
    // printf("lumen3\n");
    // show_lumen3(current.lumen3);

    // backward propagation
    Vector10 grad_judgement = diff_judgement(judgement, answer);
    Matrix10 grad_lumen3 = diff_lumen_three(hidden2, grad_judgement);
    Vector32 grad_hidden2 = diff_hidden2(current.lumen3, grad_judgement);
    Matrix32 grad_lumen2 = diff_lumen_two(hidden1, grad_hidden2);
    Vector64 grad_hidden1 = diff_hidden1(current.lumen2, hidden2);
    Matrix64 grad_lumen1 = diff_lumen_one(retina, grad_hidden1);

    // printf("∇ judgement\n");
    // display_judgement(grad_judgement);
    // printf("∇ lumen3\n");
    // show_lumen3(grad_lumen3);

    // readjust weights
    // current.lumen1 = readd_m64(current.lumen1, grad_lumen1);
    // current.lumen2 = readd_m32(current.lumen2, grad_lumen2);
    // current.lumen3 = readd_m10(current.lumen3, grad_lumen3);
    
    return current;
}

Vector10 feed_and_show_steps(Network current, Vector784 retina, unsigned char answer) {
    // forward propagation
    Vector64 hidden1 = lumen_one(retina, current.lumen1);
    Vector32 hidden2 = lumen_two(hidden1, current.lumen2);
    Vector10 judgement = lumen_three(hidden2, current.lumen3);

    printf("retina\n");
    show_retina(retina);
    printf("hidden1\n");
    show_hidden1(hidden1);
    printf("hidden2\n");
    show_hidden2(hidden2);
    printf("judgement\n");
    display_judgement(judgement);

    return judgement;
}


int finite_test(Network current) {
    FILE *train = fopen("./training*", "rb");
    FILE *label = fopen("./labels*", "rb");
    get_headers(train, label);

    for (int test = 0; test < 2; test ++) {
        ImageAndLabel next = get_next(train, label);
        feed_and_show_steps(current, next.image, next.label);
    }
    fclose(train);
    fclose(label);
}

Network finite_train(Network current) {
    FILE *train = fopen("./training*", "rb");
    FILE *label = fopen("./labels*", "rb");
    get_headers(train, label);

    for (int item = 0; item < 10; item ++) {
        ImageAndLabel next = get_next(train, label);
        current = train_once(current, next.image, next.label);
    }

    fclose(train);
    fclose(label);

    return current;
}

int main() {

    Network baby;
    baby.lumen1 = funky64();
    baby.lumen2 = funky32();
    baby.lumen3 = funky10();

    for (int iteration = 0; iteration < 1000; iteration ++) { baby = finite_train(baby); };

    finite_test(baby);
    show_lumen3(baby.lumen3);
    show_lumen2(baby.lumen2);

    return 0;
}

