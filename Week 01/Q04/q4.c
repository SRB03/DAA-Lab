#include <stdio.h>
#include <stdlib.h>

// Recursive function to solve ToH and count moves
void towerOfHanoi(int n, char source, char aux, char dest, long long *moves) {
    if (n == 0) {
        return;
    }
    towerOfHanoi(n - 1, source, dest, aux, moves);
    (*moves)++;
    towerOfHanoi(n - 1, aux, source, dest, moves);
}

int main() {
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    
    if (gnuplotPipe == NULL) {
        printf("Error: Could not open Gnuplot. Ensure it is installed and in your PATH.\n");
        return 1;
    }

    printf("Calculating ToH moves and generating plot...\n");

    // Configuring the plot
    fprintf(gnuplotPipe, "set terminal pngcairo size 800,600 enhanced font 'Arial,12'\n");
    fprintf(gnuplotPipe, "set output 'toh_moves.png'\n");
    fprintf(gnuplotPipe, "set title 'Towers of Hanoi: Moves Required vs Number of Discs' font ',14' \n");
    fprintf(gnuplotPipe, "set xlabel 'Number of Discs (n)' font ',12' \n");
    fprintf(gnuplotPipe, "set ylabel 'Total Moves (Log Scale)' font ',12' \n");
    
    // Set logarithmic scale for the y-axis (base 10)
    fprintf(gnuplotPipe, "set logscale y 10\n");
    
    // Set x-axis range and ticks
    fprintf(gnuplotPipe, "set xrange [1:16]\n");
    fprintf(gnuplotPipe, "set xtics 1,1,16\n");
    fprintf(gnuplotPipe, "set grid\n");

    fprintf(gnuplotPipe, "plot '-' with linespoints linewidth 2 pointtype 7 pointsize 1.5 linecolor rgb 'blue' title 'Moves = 2^n - 1'\n");

    // Calculate moves for n = 1 to 16 and stream the data to Gnuplot
    for (int n = 1; n <= 16; n++) {
        long long moves = 0;
        towerOfHanoi(n, 'A', 'B', 'C', &moves);
        // printf("n = %d \t Moves = %lld\n", n, moves);
        fprintf(gnuplotPipe, "%d %lld\n", n, moves);
    }

    fprintf(gnuplotPipe, "e\n");
    pclose(gnuplotPipe);
    
    return 0;
}