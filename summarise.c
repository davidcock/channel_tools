#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[]) {
    int r, c;
    int min, max;
    int rmin, rmax;
    size_t *counts, total_count, out_of_range, malformed;

    if(argc < 3) {
        fprintf(stderr, "Usage: %s <range min> <range max>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    min= atoi(argv[1]);
    max= atoi(argv[2]);

    if(min < 0 || max < 0 || max < min) {
        fprintf(stderr, "Invalid range: %d - %d\n", min, max);
        exit(EXIT_FAILURE);
    }

    counts= calloc(max - min + 1, sizeof(size_t));
    if(!counts) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    total_count= 0;
    out_of_range= 0;
    malformed= 0;
    rmin= INT_MAX;
    rmax= INT_MIN;

    while(!feof(stdin) && !ferror(stdin)) {
        int n;

        n= scanf("%d %d\n", &c, &r);
        if(n != 2) {
            malformed++;
            continue;
        }

        total_count++;

        if(c < min || max < c) {
            out_of_range++;
            continue;
        }

        counts[c - min]++;

        if(r < rmin) rmin= r;
        if(rmax < r) rmax= r;
    }

    printf("%lu %lu %lu %d %d", total_count, out_of_range, malformed, rmin,
            rmax);
    for(c= 0; c <= max - min; c++)
        printf(" %lu", counts[c]);
    printf("\n");

    return 0;
}