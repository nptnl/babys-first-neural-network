#include <stdio.h>
#include "matrix.h"
#include "printing.h"

// the first few bytes of the training data just contain info about the data
int get_headers(FILE *train, FILE *label) {
    unsigned char train_head[16];
    unsigned char label_head[8];
    fread(train_head, 4, 4, train);
    fread(label_head, 4, 2, label);
    return 0;
}

// "burns" the retina by reading the 28 x 28 x byte image onto it
int burn_retina(FILE *input, unsigned char buffer[784]) {
    fread(buffer, 1, 784, input);
    return 0;
}
// gets label (the correct value) for determining gradients
int peek_label(FILE *input, unsigned char out[1]) {
    fread(out, 1, 1, input);
    return 0;
}

// all the pixels of the image + the label
typedef struct {
    Vector784 image;
    unsigned char label;
} ImageAndLabel;

// for testing purposes, gets a nice picture of the number 5
ImageAndLabel get_one_input() {
    FILE *train;
    FILE *label;
    train = fopen("./training*", "rb");
    label = fopen("./labels*", "rb");
    Vector784 image;
    unsigned char solution[1];
    get_headers(train, label);
    burn_retina(train, image.data);
    peek_label(label, solution);
    ImageAndLabel output = { .image = image, .label = solution[0] };
    fclose(train);
    fclose(label);
    return output;
}