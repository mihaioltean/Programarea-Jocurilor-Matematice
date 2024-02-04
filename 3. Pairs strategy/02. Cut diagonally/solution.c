// by Mihai Oltean
// last update on 2024.2.04.0
// ----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
// ----------------------------------------------------------------------
int main(void)
{
  unsigned int n, m;
  printf("Input n, m:");
  scanf("%u%u", &n, &m);
  // who is winning ?
  if (!((n % 2) && (m % 2))){
        printf("Player A does not have a perfect winning strategy!\n");
        printf("Player A quits the game!\n");
        getchar();
        return 0;
    }
    printf("Player A has a perfect winning strategy!\n");
    printf("Let's play!\n");
// A moves
    printf("A cuts position [1, 1].\n"); 
    unsigned int move_x = 1;
    unsigned int move_y = 1;

    if (n % 2){ 
        while (move_x != n){
            printf("Enter the B\'s move [x, y]:");
            scanf("%u%u", &move_x, &move_y); // MUST validate move!
            printf("A cuts position [%u,%u].\n", move_x + 1, 1);
            move_x++;
        }
    }
    else{ 
        while (move_y != m){
            printf("Enter the B\'s move [x, y]:");
            scanf("%u%u", &move_x, &move_y); // MUST validate move!
            printf("A cuts position [%u,%u].\n", 1, move_y + 1);
            move_y++;
        }
    }

    printf("A won! Game over!\n");
    getchar();
    return 0;
}
// ----------------------------------------------------------------------
