#include<stdio.h>

int endian_swap(unsigned int x) {
    return (x>>24) | 
        ((x<<8) & 0x00FF0000) |
        ((x>>8) & 0x0000FF00) |
        (x<<24);
}

int main() {
    FILE *ptr;
    ptr = fopen("./base", "rb");
    int buffer[10];
    fread(buffer, 4, 4, ptr);
    for (short a = 0; a < 4; a ++) {
        int swapped = endian_swap(buffer[a]);
        printf("%d | 0x%x\n", a+1, swapped);
    }
    return 0;
}
