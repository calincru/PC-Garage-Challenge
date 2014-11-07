#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

#ifndef __bool_true_false_are_defined
 #define bool int
 #define false 0
 #define true 1
 #define __bool_true_false_are_defined 1
#endif

#define MAX_SIZE 1024
#define MAX_IN_SIZE 512

bool isCons(char);
bool isVoc(char);
void latinize(char *, size_t);

int main()
{
    FILE *in = fopen("Input5.txt", "r");
    FILE *out = fopen("Output5.txt", "w");
    char *prop;
    size_t n;

    prop = malloc( MAX_SIZE );
    fgets(prop, MAX_IN_SIZE-1, in);
    n = strlen(prop);
    latinize(prop, n);
    fprintf(out, "%s", prop);

    free(prop);
    fclose(in);
    fclose(out);
    return 0;
}

void latinize(char *p, size_t n) {
    int i;
    int shift;
    char *suffix;
    char aux;
    int wordStart = 0;
    int wordEnd;
    bool capInitial;
    bool beginsWithC;

    suffix = malloc(4);

    while ( p[wordStart] != '\0' ) {
        while ( !isalpha(p[wordStart]) ) {
            ++wordStart;
        }
        wordEnd = wordStart;
        while ( isalpha(p[wordEnd] )) {
            wordEnd++;
        }
        wordEnd--;

        beginsWithC = false;
        capInitial=false;
        while ( isCons(p[wordStart]) ) {
            beginsWithC = true;
            if ( isupper(p[wordStart]) ) {
                capInitial = true;
            }
            aux = p[wordStart];
            for (i = wordStart; i < wordEnd; i++) {
                p[i] = p[i+1];
            }
            p[wordEnd] = tolower(aux);
        }
        if ( beginsWithC ) {
            shift = 2;
            memcpy(suffix, "ei", 2);
        } else {
            shift = 3;
            memcpy(suffix, "lei", 3);
        }
        if (capInitial) {
            p[wordStart] = toupper(p[wordStart]);
        }
        for (i = n + shift; i > wordEnd + shift; i--) {
            p[i] = p[i-shift];
        }
        for (i = 0; i < shift; i++) {
            p[wordEnd + i + 1] = suffix[i];
        }
        wordStart = wordEnd + shift + 1;
        n += shift;
    }
    free(suffix);
}

bool isCons(char a) {
    static char cons[] = "bcdfghjklmnopqrstvwxz";
    if ( strchr(cons, tolower(a)) ) {
        return true;
    }
    return false;
}
