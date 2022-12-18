#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#define BUFLEN 4096
#define FBHT 6
#define FBWD 40

int cycle;

void draw(int, int (*fb)[40]);

int do_cycle (int xreg, int fb[FBHT][FBWD]) {
    draw(xreg, fb);
    ++cycle;
    if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220) {
        return cycle * xreg;
    }
    return 0;
}

void draw (int xreg, int fb[FBHT][FBWD]) {
    int line = (cycle - 1) / FBWD;
    int spos = cycle % FBWD;
    if (xreg >= spos - 1 && xreg <= spos + 1) {
        fb[line][spos] = 1;
    } else {

    }
}

int main() {

    char buf[BUFLEN] = "";
    FILE *fp = fopen ("input.txt", "r");
    int xreg = 1;
    cycle = 0;
    int ssum = 0;
    int fb[FBHT][FBWD] = {0};

    while (fgets (buf, BUFLEN, fp)) {
        size_t len = strlen (buf);
        char * op;
        int val;
        if (len > 1) {
            buf[strcspn(buf, "\n")] = 0;
            op = strtok(buf, " ");
            if (strcmp("noop",op) == 0) {
                ssum += do_cycle(xreg, fb);
            } else {
                ssum += do_cycle(xreg, fb);
                ssum += do_cycle(xreg, fb);
                int v = atoi(strtok(NULL, " "));
                xreg += v;
            }
        }

    }
    printf("\nPart one answer: %d\n\n", ssum);

    for (int i = 0; i < FBHT; i++) {
        for (int j = 0; j < FBWD; j++) {
            if (fb[i][j] == 1) {
                printf("#");
            } else {
                printf(".");
            }
            //printf("value of fb[%d][%d] is %d\n", i, j, fb[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}