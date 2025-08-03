#include <stdio.h>
#include "./reading.h"

int main() {
    InputVector retina = get_one_input();
    InputInputMatrix identity = input_identity();
    InputVector output = input_input(retina, identity);
    show_retina(output.data);
    return 0;
}