#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIMX 10
#define DIMY 10

#define ITERATIONS 100

struct cell {
    int x, y;
    double value;
};

struct cell   level[DIMX][DIMY];
struct cell** empty_neighbours;
size_t current_index;
size_t still_empty;

double grand() {
    return (double)random() /
           (double)RAND_MAX;
}

bool alreadyAppended(struct cell* cell) {
    for (int i = 0; i < current_index; i++)
        if (empty_neighbours[i]->x == cell->x &&
            empty_neighbours[i]->y == cell->y)
            return true;

    return false;
}

void appendNeighbour(struct cell* cell) {
    if (cell->value == 0 && !alreadyAppended(cell)) {
        empty_neighbours[current_index++] = cell;
        still_empty++;
    }
}

void recalculateNeighbours() {
    struct cell* last = empty_neighbours[current_index];

    appendNeighbour(&level[last->x + 1][last->y]);
    appendNeighbour(&level[last->x - 1][last->y]);
    appendNeighbour(&level[last->x][last->y + 1]);
    appendNeighbour(&level[last->x][last->y - 1]);
}

int main() {
    srandom(time(NULL));

    empty_neighbours    = (struct cell**)calloc(DIMX * 2, sizeof(struct cell*));
    empty_neighbours[0] = &level[DIMX / 2][DIMY / 2];

    current_index = 0, still_empty = 0;

    for (int i = 0; i < ITERATIONS; i++) {
        recalculateNeighbours();
        if (still_empty == 0) continue;

        int rand_index = (int)(grand() * still_empty);

        while (empty_neighbours[rand_index] != NULL &&
               empty_neighbours[rand_index]->value == 1)
            rand_index++;

        empty_neighbours[rand_index]->value = 1;
        still_empty--;
    }

    for (int i = 0; i < DIMX; i++) {
        for (int j = 0; j < DIMY; j++)
            printf("%d", (int)level[i][j].value);
        printf("\n");
    }

    free(empty_neighbours);

    return 0;
}

