#include <stdio.h>
#include <string.h>

int mod(int x, int y) { return x % y; }

char alivep(int neighbours, char alive) {
    if (alive && (neighbours == 2 || neighbours == 3)) return 1;
    else {
        if (neighbours == 3) return 1; else return 0;
    }
}

// Swapping the two grids   
#define SWAP_BOARDS( b1, b2 )  do { \
 char* temp = b1; \
 b1 = b2; \
 b2 = temp; \
 } while(0)

// Simplifying access to grid elements
#define BOARD( G, X, Y )  ((G)[ncols*(X)+(Y)])

char* sequential_game_of_life(char* outgrid, char* ingrid,
    const int nrows, const int ncols, const int gens_max) {

    const int NC = ncols;
    int curgen, i, j;

    for (curgen = 0; curgen < gens_max; curgen++)
    {

        for (i = 0; i < nrows; i++)
        {
            for (j = 0; j < ncols; j++)
            {
                const int inorth = mod(i - 1, nrows);
                const int isouth = mod(i + 1, nrows);
                const int jwest = mod(j - 1, ncols);
                const int jeast = mod(j + 1, ncols);

                const char neighbor_count =
                    BOARD(ingrid, inorth, jwest) +
                    BOARD(ingrid, inorth, j) +
                    BOARD(ingrid, inorth, jeast) +
                    BOARD(ingrid, i, jwest) +
                    BOARD(ingrid, i, jeast) +
                    BOARD(ingrid, isouth, jwest) +
                    BOARD(ingrid, isouth, j) +
                    BOARD(ingrid, isouth, jeast);

                BOARD(outgrid, i, j) = alivep(neighbor_count, BOARD(ingrid, i, j));
            }
        }
        SWAP_BOARDS(outgrid, ingrid);
    }
    return outgrid;
}

void print_board(char* ingrid, int nrows, int ncols)
{
    for (int i = 0;i < nrows;++i)
    {
        for (int j = 0;j < ncols;++j)
        {
            printf("%c", BOARD(ingrid, i, j) == 0 ? '.' : '*');
        }
        printf("\n");
    }
}

int main() {
    const int NR = 15;
    const int NC = 15;
    const int GENS_MAX = 20;

    char ingrid[NR * NC];
    char outgrid[NR * NC];
    memset(ingrid, 0, NR * NC * sizeof(ingrid[0]));

    //draw an example pattern
    ingrid[5 * NC + 5] = 1;
    ingrid[5 * NC + 6] = 1;
    ingrid[5 * NC + 7] = 1;
    ingrid[5 * NC + 8] = 1;
    ingrid[6 * NC + 5] = 1;
    ingrid[7 * NC + 5] = 1;
    ingrid[8 * NC + 5] = 1;
    ingrid[9 * NC + 5] = 1;

    printf("Initial board\n");
    print_board(ingrid, NR, NC);

    char* out = sequential_game_of_life(outgrid, ingrid, NR, NC, GENS_MAX);

    printf("Final board\n");
    print_board(out, NR, NC);
}
