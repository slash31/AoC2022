#include <stdio.h>
#include <string.h>

#define BUFLEN 4096

int score (char op, char mp) {
    int score = 0;
    switch(mp) {
        case 'X':
            score += 1;// base points
            if (op == 'A') // draw
                score += 3;
            else if (op == 'C') // win
                score += 6;
            break;
        case 'Y':
            score += 2;// base points
            if (op == 'B') // draw
                score += 3;
            else if (op == 'A') // win
                score += 6;
            break;
        case 'Z':
            score += 3; // base points
            if (op == 'C') // draw
                score += 3;
            else if (op == 'B') // win
                score += 6;
    }
    return score;
}

// scoreP2 added for part 2
int scoreP2(char op, char mp) {
    int score = 0;
    switch(mp) {
        case 'X': // lose
            if (op == 'B') // paper, we throw rock
                score += 1;
            else if (op == 'C') // scissors, we throw paper
                score += 2;
            else
                score += 3; // rock, we throw scissors
            break;
        case 'Y': // draw
            score += 3; // base points
            if (op == 'A') // both throw rock
                score += 1;
            else if (op == 'B') // both throw paper
                score += 2;
            else
                score += 3; // both throw scissors
            break;
        case 'Z': // win
            score += 6; // base points
            if (op == 'C') // scissors, we throw rock
                score += 1;
            else if (op == 'A') // rock, we throw paper
                score += 2;
            else
                score += 3; // paper, we throw scissors
    }
    return score;
}

int main () {

    size_t n = 1;
    char buf[BUFLEN] = "";
    FILE *fp = fopen ("input.txt", "r");   
    int s = 0;
    int sP2 = 0; // added for part 2

    while (fgets (buf, BUFLEN, fp)) {
        size_t len = strlen (buf);
        // process if the line isn't empty (newline only)
        if (len > 1) {
            char *op = strtok(buf, " "); // get the left token
            char *mp = strtok(NULL, " "); // get the right token
            s += score(op[0], mp[0]); // score this round and add it to the total
            sP2 += scoreP2(op[0], mp[0]); // added for part 2 (score according to p2 rules)
        }
    }
    printf("Max score for Part 1 is: %d\n", s);
    printf("Max score for Part 2 is: %d\n", sP2); // added for part 2
    fclose (fp);
    return 0;
}