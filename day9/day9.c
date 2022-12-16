#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <math.h>
#define BUFLEN 4096
#define OFFSET 500

const int GRIDSIZE = 1000;

struct point{
    int x;
    int y;
};

double gap (int hx, int hy, int tx, int ty) {
    return sqrt(pow(hx - tx, 2.0) + pow(hy - ty, 2.0));
}

void moveHead(char d, int a, struct point* head[], int len, int visited[GRIDSIZE][GRIDSIZE]) {
    for (int i = 0; i < a; i++) {
        switch(d) {
            case 'U':
                ++head[0] -> y;
                break;
            case 'D':
                --head[0] -> y;
                break;
            case 'L':
                --head[0] -> x;
                break;
            case 'R':
                ++head[0] -> x;
        }
        for (int j = 0; j < len - 1; j++) {
            // move the tails
            int delta_x = head[j] -> x - head[j+1] -> x;
            int delta_y = head[j] -> y - head[j+1] -> y;
            if (gap(head[j] -> x, head[j] -> y, head[j+1] -> x, head[j+1] -> y) >= 2.0) {
                if ((d == 'U' || d == 'D')) {
                    (head[j+1]) -> y = (head[j+1]) -> y + (delta_y > 0 ? 1 : delta_y < 0 ? -1 : 0);
                    (head[j+1]) -> x = (head[j+1]) -> x + (delta_x > 0 ? 1 : delta_x < 0 ? -1 : 0);
                } else if ((d == 'L' || d == 'R')) {
                    (head[j+1]) -> x = (head[j+1]) -> x + (delta_x > 0 ? 1 : delta_x < 0 ? -1 : 0);
                    (head[j+1]) -> y = (head[j+1]) -> y + (delta_y > 0 ? 1 : delta_y < 0 ? -1 : 0);
                }
            }

            
        }
        visited[head[len-1] -> x + OFFSET][head[len-1] -> y + OFFSET] = 1;
        

    }    
}

int main() {

    char buf[BUFLEN] = "";
    FILE *fp = fopen ("input.txt", "r");
    
    // get length of input
    int c = 0;
    while (fgets (buf, BUFLEN, fp))
        ++c;
    rewind(fp);

    int rope_len = 2;
    int rope2_len = 10; // added for part 2


    struct point* rope[rope_len];
    for (int i = 0; i < rope_len;  i++) {
        rope[i] = (struct point*)malloc(sizeof(struct point));
        rope[i] -> x = 0;
        rope[i] -> y=0;
    }

    struct point* rope2[rope2_len];
    for (int i = 0; i < rope2_len;  i++) {
        rope2[i] = (struct point*)malloc(sizeof(struct point));
        rope2[i] -> x = 0;
        rope2[i] -> y=0;
    }

    int visited[GRIDSIZE][GRIDSIZE] = {0};
    int visited2[GRIDSIZE][GRIDSIZE] = {0}; // added for part 2

    while (fgets (buf, BUFLEN, fp)) {
        size_t len = strlen (buf);
        char d;
        int a;

        // process if the line isn't empty (newline only)
        if (len > 1) {
            buf[strcspn(buf, "\n")] = 0;
            d = strtok(buf, " ")[0];
            a = atoi(strtok(NULL, " "));
        }
        moveHead(d, a, rope, rope_len, visited);
        moveHead(d, a, rope2, rope2_len, visited2);
    }
    int p1count = 0, p2count = 0;
    for (int i = 0; i < GRIDSIZE;i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            if (visited[i][j] == 1)
                ++p1count;
        }
    }
    // added this for loop for part 2
    for (int i = 0; i < GRIDSIZE;i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            if (visited2[i][j] == 1)
                ++p2count;
        }
    }
    printf("Part one answer: %d\n", p1count);
    printf("Part two answer: %d\n", p2count);
}
