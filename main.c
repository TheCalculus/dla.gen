#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIMX 65
#define DIMY 65

#define ITERATIONS 100

bool level[DIMX][DIMY];

uint8_t x = 33, y = 33; // coordinate of initial / current pixel
size_t  n = 0;          // number of neighbours of initial / current pixel

double grand() {
    return (double)random() /
           (double)RAND_MAX;
}

struct cell {
    bool*   pointer;
    uint8_t x, y;
};

struct cell* arr[DIMX * 2];

void increment_and_evaluate(size_t* inc, struct cell** arr,
                            uint8_t xx, uint8_t yy) {
    if (level[xx][yy] == true) return;
    (*inc)++;

    arr[*inc]->pointer = &(level[xx][yy]);
    printf("arr[%zu]->pointer = %p\n", *inc, arr[*inc]->pointer);
    arr[*inc]->x = xx;
    arr[*inc]->y = yy;
}

void neighbours(struct cell* arr[4], size_t* n) {
    if (x <= 0 || x >= DIMX ||
        y <= 0 || y >= DIMY)
        return;

    increment_and_evaluate(n, arr, x - 1, y);
    increment_and_evaluate(n, arr, x + 1, y);
    increment_and_evaluate(n, arr, x, y - 1);
    increment_and_evaluate(n, arr, x, y + 1);
}

int main() {
    srandom(time(NULL));
    int index = 0;

    for (int i = 0; i < DIMX * 2; i++)
        arr[i] = malloc(sizeof(struct cell*));

    for (int i = 0; i < ITERATIONS; i++) {
        neighbours(arr, &n);
        index = (int)(1 + grand() * n);
        *(arr[index]->pointer) = true;
        x = arr[index]->x;
        y = arr[index]->y;

        n = 0;
    }

    for (int i = 0; i < DIMX * 2; i++)
        free(arr[i]);

    return 0;
}
