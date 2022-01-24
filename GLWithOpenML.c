// because you are running a parallel codes multiple times in a loop,
// it would be better to make the thread swarm first and schedule the
// tasks in each loop iteration, to avoid multiple creation and destruction
// of working threads
#pragma omp parallel
for (curgen = 0; curgen < gens_max; curgen++)
{
    #pragma omp for
    for (t = 0; t < nrows*ncols; t++)
    {
        int i = t / ncols;
        int j = t % ncols;
        const int inorth = mod (i-1, nrows);
        const int isouth = mod (i+1, nrows);
        const int jwest = mod (j-1, ncols);
        const int jeast = mod (j+1, ncols);

        const char neighbor_count = 
            BOARD (ingrid, inorth, jwest) + 
            BOARD (ingrid, inorth, j) + 
            BOARD (ingrid, inorth, jeast) + 
            BOARD (ingrid, i, jwest) +
            BOARD (ingrid, i, jeast) + 
            BOARD (ingrid, isouth, jwest) +
            BOARD (ingrid, isouth, j) + 
            BOARD (ingrid, isouth, jeast);

        BOARD(outgrid, i, j) = alivep (neighbor_count, BOARD (ingrid, i, j));
    }
    SWAP_BOARDS( outgrid, ingrid );
}