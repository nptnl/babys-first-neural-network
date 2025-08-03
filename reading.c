#include<stdio.h>

unsigned char endian_swap(unsigned char x) {
    return (x>>24) | ((x<<8) & 0x00FF0000) | ((x>>8) & 0x0000FF00) | (x<<24);
}

int get_header(FILE *ptr, unsigned char buffer[784]) {
    fread(buffer, 4, 4, ptr);
    return 0;
}

int burn_retina(FILE *input, unsigned char buffer[784]) {
    fread(buffer, 1, 784, input);
    return 0;
}

int show_retina(unsigned char buffer[784]) {
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            if (buffer[28 * i + j] == 0x0) { printf("  "); }
            else { printf("%X", buffer[28*i+j]); }
        }
        printf("\n");
    }
    return 0;
}

int main() {
    FILE *file;
    file = fopen("./training*", "rb");
    unsigned char buffer[784] = {0};
    if (get_header(file, buffer) != 0) { return -1; }

    burn_retina(file, buffer);
    show_retina(buffer);

    burn_retina(file, buffer);
    show_retina(buffer);


    fclose(file);
    return 0;
}

