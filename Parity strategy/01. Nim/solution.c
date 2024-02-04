// Nim game implemented in C
// by Mihai Oltean
// last update on 2024.1.31.0
// ----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// ----------------------------------------------------------------------
#define max_num_stacks 10
// ----------------------------------------------------------------------
int read_data(const char* filename, unsigned int* num_stacks, unsigned int* stacks)
{
    /*
    below is an example of input file
    3
    3 4 5
    */
    FILE *f = fopen(filename, "r");
    if (!f)
        return 0;
    fscanf(f, "%u", num_stacks);
    for (int i = 0; i < *num_stacks; i++)
        fscanf(f, "%u", &stacks[i]);
    fclose(f);
    return 1;
}
// ----------------------------------------------------------------------
int valid_move(int stack_index, int num_coins, unsigned int num_stacks, unsigned int *stacks)
{
    if (stack_index < 0 || stack_index >= num_stacks){
        printf("Invalid stack index!\n");
        return 0;
    }
    if (num_coins <= 0 || num_coins > stacks[stack_index]){
        printf("Invalid number of coins!\n");
        return 0;
    }

    return 1;
}
// ----------------------------------------------------------------------
void print_game_state(unsigned int num_stacks, unsigned int *stacks)
{
    printf("Currently the stacks are:");
    for (unsigned int i = 0; i < num_stacks; i++)
        printf("%u ", stacks[i]);
    printf("\n");
}
// ----------------------------------------------------------------------
int main(void)
{
    unsigned int stacks[max_num_stacks];
    unsigned int num_stacks;
// read data
    if (!read_data("nim.in", &num_stacks, stacks)){
        printf("Cannot find/read file!\n");
        getchar();
        return 0;
    }
// preparation
    unsigned int xor_sum = 0; 
    unsigned int num_total_coins = 0;
    for (unsigned int i = 0; i < num_stacks; i++){
        xor_sum ^= stacks[i]; 
        num_total_coins += stacks[i];
    }
// who is winning
    if (xor_sum == 0){
        printf("Player A does not have a perfect winning strategy!\n");
        printf("Player A quits the game!\n");
        getchar();
        return 0;
    }
    printf("Player A has a perfect winning strategy!\n");
    printf("Let's play!\n");
    unsigned int num_total_extracted = 0;
// find the first move for A
    unsigned int poz = log(xor_sum) / log(2); // get the greatest power of 2 from xor_sum
    if ((int)(exp((poz + 1) * log(2))) == xor_sum) 
        poz++;

    unsigned int A_stack_index = 0;
    while (((int)(exp(poz * log(2))) & stacks[A_stack_index]) == 0) // find the stack
        A_stack_index++;

    unsigned int A_num_coins = stacks[A_stack_index] - (xor_sum ^ stacks[A_stack_index]);
// process A's move
    printf("A extracts %u coins from stack %u.\n", A_num_coins, A_stack_index);
    num_total_extracted += A_num_coins;
    stacks[A_stack_index] -= A_num_coins;
    print_game_state(num_stacks, stacks);

// show info for B
    printf("B moves must be introduce as: Stack_index Num_extracted_coins\n");
    printf("Note: first stack has index 0.\n");

    while (num_total_extracted != num_total_coins){
        xor_sum = 0;
// read B move
        printf("Enter the B\'s move:");
        int B_stack_index, B_num_coins;

        do{
           scanf("%d%d", &B_stack_index, &B_num_coins);
            if (valid_move(B_stack_index, B_num_coins, num_stacks, stacks))
                break;
            else
                printf("Invalid move!\n");
        } while(1);
// process B move 
        xor_sum ^= stacks[B_stack_index];
        num_total_extracted += B_num_coins;
        stacks[B_stack_index] -= B_num_coins;
        xor_sum ^= stacks[B_stack_index];

        print_game_state(num_stacks, stacks);

// compute move for A
        poz = log(xor_sum) / log(2);
        if ((unsigned int)(exp((poz + 1) * log(2))) == xor_sum) 
            poz++;
        
        A_stack_index = 0;
        while ( ((unsigned int)(exp(poz * log(2))) & stacks[A_stack_index]) == 0)
            A_stack_index++;

        A_num_coins = stacks[A_stack_index] - (xor_sum ^ stacks[A_stack_index]);
// process A move
        printf("A extracts %u coins from stack %u.\n", A_num_coins, A_stack_index);
        num_total_extracted += A_num_coins;
        stacks[A_stack_index] -= A_num_coins; 

        print_game_state(num_stacks, stacks);
    }
    printf("A won! Game over!\n");
    getchar();
    return 0;
}
// ----------------------------------------------------------------------
