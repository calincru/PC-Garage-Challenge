#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

/* Boolean support */
#ifndef __bool_true_false_are_defined
 #define bool   int
 #define false  0
 #define true   1
 #define __bool_true_false_are_defined  1
#endif

#define MAX_SIZE    1024    /* Max size of final modified string */
#define MAX_IN_SIZE 512     /* Max size of input string */

bool isCons(char);
void latinize(char *, size_t);

int main()
{
    FILE *in = fopen("Input5.txt", "r");
    FILE *out = fopen("Output5.txt", "w");
    char *prop;     /* The input string */
    size_t n;       /* Input string size */

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
    int i;              /* Auxiliary counter for shifting words */
    int shift;          /* Number of right-shift positions */
    char *suffix;       /* "ei" or "lei" */
    char aux;           /* Temporarily store the value of the first char */
    int wordStart = 0;  /* Beginning of current word */
    int wordEnd;        /* End of current word */
    bool capInitial;    /* True if the current word is capitalized */
    bool beginsWithC;   /* True if the current word begins with a cons */

    suffix = malloc(4);

    while ( p[wordStart] != '\0' ) {
        /* Search for the next word */
        while ( !isalpha(p[wordStart]) ) {
            ++wordStart;
        }
        wordEnd = wordStart;

        /* Search for the end of found word */
        while ( isalpha(p[wordEnd] )) {
            wordEnd++;
        }
        wordEnd--;

        /* Move all consonants at the end of the word */
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
            /* Always put lower case letters at the end */
            p[wordEnd] = tolower(aux);
        }

        /* Determine what suffix and shift to be used */
        if ( beginsWithC ) {
            shift = 2;
            memcpy(suffix, "ei", 2);
        } else {
            shift = 3;
            memcpy(suffix, "lei", 3);
        }

        /* Capitalize if necesary */
        if (capInitial) {
            p[wordStart] = toupper(p[wordStart]);
        }

        /* Shift the string to the right [shift] characters */
        for (i = n + shift; i > wordEnd + shift; i--) {
            p[i] = p[i-shift];
        }

        /* Add the suffix to the word */
        for (i = 0; i < shift; i++) {
            p[wordEnd + i + 1] = suffix[i];
        }
        wordStart = wordEnd + shift + 1;
        n += shift;
    }
    free(suffix);
}

/* Checks if a letter is a consonant, regardless of case */
bool isCons(char a) {
    static char cons[] = "bcdfghjklmnopqrstvwxz";
    if ( strchr(cons, tolower(a)) ) {
        return true;
    }
    return false;
}
