#include "./reading.h"

float cost(Vector10 output, unsigned char answer) {
    float total = 0.0;
    for (int a = 0; a < 10; a ++) {
        float floatized = output.data[a];
        if (a == answer) { total += (1.0 - floatized) * (1.0 - floatized); }
        else { total += floatized * floatized; }
    }
    return total;
}