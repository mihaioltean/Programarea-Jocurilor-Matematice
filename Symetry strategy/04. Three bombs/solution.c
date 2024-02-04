// by Mihai Oltean
// last update on 2024.2.04.0
// ----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
// ----------------------------------------------------------------------
int main(void)
{
    unsigned int n;

    printf("Input the board size:"); 
    scanf("%u", &n);
    printf("Player A has a perfect winning strategy!\n");
    printf("Let's play!\n");
// A moves
    printf("A takes all pieces having the top-left corner at [2, 2].\n");

    unsigned int row = 3; 
    unsigned int col = 3; 
    while ((row > 2) && (col > 2)){
        printf("B's move [row, col]:");
        scanf("%u%u", &row, &col); // should do some validation here
        if ((row > 2) && (col > 2))
            printf("A takes all pieces having the top-left corner at [%u, %u].\n", col, row);
        else
            printf("B took a black piece!\n");
    }
  
    printf("A won! Game over!\n");
    getchar();
    return 0;
}
// ----------------------------------------------------------------------