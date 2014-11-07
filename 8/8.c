#include <stdio.h>


int main()
{
    unsigned X, Y, contor = 0;
    FILE *in = fopen("Input8.txt", "r");
    FILE *out = fopen("Output8.txt", "w");

    fscanf(in, "%u%u", &X, &Y);

    while (Y > X) {
        if (Y % 2)
            Y--;
        else
            Y /= 2;

        contor++;
    }

    fprintf(out, "%u\n", contor);

    fclose(in);
    fclose(out);
    return 0;
}
