/*

[N]     [Q]         [N]            
[R]     [F] [Q]     [G] [M]        
[J]     [Z] [T]     [R] [H] [J]    
[T] [H] [G] [R]     [B] [N] [T]    
[Z] [J] [J] [G] [F] [Z] [S] [M]    
[B] [N] [N] [N] [Q] [W] [L] [Q] [S]
[D] [S] [R] [V] [T] [C] [C] [N] [G]
[F] [R] [C] [F] [L] [Q] [F] [D] [P]
 1   2   3   4   5   6   7   8   9

*/
#include "day5.h"

void setup(struct node* stacks[NUM_STACKS]) {
    char st1_init[8] = {'F','D','B','Z','T','J','R','N'};
    for (int i=0;i<8;i++)
        push(st1_init[i], &stacks[0]);

    char st2_init[5] = {'R', 'S', 'N', 'J', 'H'};
    for (int i=0;i<5;i++)
        push(st2_init[i], &stacks[1]);

    char st3_init[8] = {'C', 'R', 'N', 'J', 'G', 'Z', 'F', 'Q'};
    for (int i=0;i<8;i++)
        push(st3_init[i], &stacks[2]);

    char st4_init[7] = {'F', 'V', 'N', 'G', 'R', 'T', 'Q'};
    for (int i=0;i<7;i++)
        push(st4_init[i], &stacks[3]);

    char st5_init[4] = {'L', 'T', 'Q', 'F'};
    for (int i=0;i<4;i++)
        push(st5_init[i], &stacks[4]);

       char st6_init[8] = {'Q', 'C', 'W', 'Z', 'B', 'R', 'G', 'N'};
    for (int i=0;i<8;i++)
        push(st6_init[i], &stacks[5]);

    char st7_init[7] = {'F', 'C', 'L', 'S', 'N', 'H', 'M'};
    for (int i=0;i<7;i++)
        push(st7_init[i], &stacks[6]);

    char st8_init[6] = {'D', 'N', 'Q', 'M', 'T', 'J'};
    for (int i=0;i<6;i++)
        push(st8_init[i], &stacks[7]);

    char st9_init[3] = {'P', 'G', 'S'};
    for (int i=0;i<3;i++)
        push(st9_init[i], &stacks[8]);

    // char st1_init[2] = {'Z', 'N'};
    // for (int i=0;i<2;i++)
    //     push(st1_init[i], &stacks[0]);

    // char st2_init[3] = {'M', 'C', 'D'};
    // for (int i=0;i<3;i++)
    //     push(st2_init[i], &stacks[1]);

    // char st3_init[1] = {'P'};
    // for (int i=0;i<1;i++)
    //     push(st3_init[i], &stacks[2]);
}
