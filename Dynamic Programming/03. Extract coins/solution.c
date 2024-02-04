// by Mihai Oltean
// last update on 2024.2.04.0
// ----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
// ----------------------------------------------------------------------
#define MaxN 100
// ----------------------------------------------------------------------
int read_data(const char* filename, 
          unsigned int *num_coins, unsigned int* coin_color)
{
    FILE *f = fopen(filename, "r");
    if (!f)
      return 0;
    fscanf(f, "%u", num_coins);
    for (unsigned int i = 0; i < *num_coins; i++)
      fscanf(f, "%u", &coin_color[*num_coins - 1 - i]);
    fclose(f);

    return 1;
}
// ----------------------------------------------------------------------
int main(void)
{
  unsigned int num_coins;
  unsigned int coin_color[MaxN];

// read data
    if (!read_data("in1.txt", &num_coins, coin_color)){
        printf("Cannot find/read file!\n");
        getchar();
        return 0;
    }

// compute strategy with Dynamic Programming
    unsigned char c[MaxN + 1]; // c[0] is unused!
    c[1] = 1;
    for (int i = 1; i < num_coins; i++)
        if (coin_color[i] != coin_color[i - 1])
            c[i + 1] = !c[i];
        else 
          c[i + 1] = 1;
// who is winnning?
    if (!c[num_coins]){
      printf("Player A does not have a perfect winning strategy!\n");
      printf("Player A quits the game!\n");
      getchar();
      return 0;
    }
    printf("Player A has a perfect winning strategy!\n");
    printf("Let's play!\n");
    
// compute A's move
    unsigned int k = num_coins;
    while (c[k]) 
      k--;
    unsigned int A_num_coins = num_coins - k;
    printf("A extracts %u coins.\n", A_num_coins);
    num_coins = k;

    while (num_coins){
// get B move
        printf("Enter the B\'s move:");
        int B_num_coins;

        do{
           scanf("%d", &B_num_coins);
            if (B_num_coins <= num_coins) // more validation required
                break;
            else
                printf("Invalid move!\n");
        } while(1);

        num_coins -= B_num_coins;
        k = num_coins;

// compute A's move
        while (c[k]) 
            k--;
        unsigned int A_num_coins = num_coins - k;
        printf("A extracts %u coins.\n", A_num_coins);
        num_coins = k;
    }

    printf("A won! Game over!\n");
    getchar();
    return 0;
}
// ----------------------------------------------------------------------
