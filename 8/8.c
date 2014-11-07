#include <stdio.h>


int main() {
    unsigned X, Y;      /* Input numbers */
    unsigned contor = 0;    /* Number of operations */
    FILE *in = fopen("Input8.txt", "r");
    FILE *out = fopen("Output8.txt", "w");

    fscanf(in, "%u%u", &X, &Y);

    while (Y > X) {
        if (Y % 2)
            Y--;
        else {
            if (Y/2 < X) {
                contor += Y - X - 1;
            }
            Y /= 2;
        }
        contor++;
    }

    fprintf(out, "%u", contor);

    fclose(in);
    fclose(out);
    return 0;
}
