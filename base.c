// courtesy of VScode copilot ;)
// argument "0x1C" returns "28", argument "28" returns "0x1C"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_hex(const char *str) {
    return (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'));
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    const char *input = argv[1];
    char *endptr;
    long value;

    if (is_hex(input)) {
        value = strtol(input, &endptr, 16);
        if (*endptr != '\0') {
            fprintf(stderr, "Invalid hex input.\n");
            return 1;
        }
        printf("%ld\n", value);
    } else {
        // Check if input is a valid decimal number
        for (size_t i = 0; input[i]; ++i) {
            if (!isdigit((unsigned char)input[i])) {
                fprintf(stderr, "Invalid decimal input.\n");
                return 1;
            }
        }
        value = strtol(input, &endptr, 10);
        printf("0x%lX\n", value);
    }

    return 0;
}