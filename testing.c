#include <stdio.h>
#include "./cost.h"

int main() {
    ImageAndLabel input = get_one_input();
    Vector64 hidden1 = lumen_one(input.image, identity64());
    Vector32 hidden2 = lumen_two(hidden1, identity32());
    Vector10 output = lumen_three(hidden2, identity10());
    for (int a = 0; a < 10; a ++) {
        printf("%d | 0x%X\n", a, output.data[a]);
    }
    cost(output, input.label);
    unsigned char x = 0xF5;
    float bongbong = x * 0.00390625;
    printf("%f\n", bongbong);
    return 0;
}