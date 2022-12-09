#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#define BUFLEN 4096
#define INFILE "input.txt"
#define GRIDSIZE 99


int p1(int forest[GRIDSIZE][GRIDSIZE], int map[GRIDSIZE][GRIDSIZE]) {
    int r, c;
    int t = 0;

    for (r = 0; r < GRIDSIZE; r++) { // skip first and last rows since they're automatically visible
        int lhmax = 0, rhmax = 0;
        int j = GRIDSIZE - 1;
        for (c = 0; c < GRIDSIZE;c++) {
            if (forest[r][c] > lhmax || c == 0) {
                lhmax = forest[r][c];
                map[r][c] = 1;
            }
            if (forest[r][j] > rhmax || j == GRIDSIZE-1) {
                rhmax = forest[r][j];
                map[r][j] = 1;
            }
            --j;
        }
    }
    for (c = 0; c < GRIDSIZE; c++) { // skip first and last rows since they're automatically visible
        int umax = 0, lmax = 0;
        int j = GRIDSIZE - 1;
        for (r = 0; r < GRIDSIZE;r++) {
            if (forest[r][c] > umax || r == 0) {
                umax = forest[r][c];
                map[r][c] = 1;
            }
            if (forest[j][c] > lmax || j == GRIDSIZE-1) {
                lmax = forest[j][c];
                map[j][c] = 1;
            }
            --j;
        }
    }
    for (r = 0; r < GRIDSIZE;r++) {
        for (c = 0; c < GRIDSIZE;c++) {
            if (map[r][c] == 1)
                t++;
        }
    }
    return t;
}

int p2(int forest[GRIDSIZE][GRIDSIZE], int map[GRIDSIZE][GRIDSIZE]) {
    int r, c, m, max_view = 0;
    
     for (r = 1; r < GRIDSIZE-1;r++) {
        for (c = 1; c < GRIDSIZE-1;c++) {
            int uview = 0, dview = 0, lview = 0, rview = 0, cview = 0;
            if (map[r][c] == 1) {
                m = r - 1;
                while (forest[m][c] < forest[r][c] && m > 0) {
                    --m;
                }
                uview = r - m;
                m = r + 1;
                while (forest[m][c] < forest[r][c] && m < GRIDSIZE-1) {
                    ++m;
                }
                dview = m-r;
                m = c - 1;
                while (forest[r][m] < forest[r][c] && m > 0) {
                    --m;
                }
                lview = c - m;
                m = c + 1;
                while (forest[r][m] < forest[r][c] && m < GRIDSIZE-1) {
                    ++m;  
                }
                rview = m - c;
            }
            cview = (uview * dview * lview * rview);
            max_view = max_view < cview ? cview : max_view;
        }
    }
    return max_view;
}

int main () {

    char buf[BUFLEN] = "";
    FILE *fp = fopen (INFILE, "r");
    int r = 0, c;
    int forest[GRIDSIZE][GRIDSIZE];
    int map[GRIDSIZE][GRIDSIZE] = {0};

    // create the forest from the data file
    while (fgets (buf, BUFLEN, fp)) {
        for (c = 0; c < GRIDSIZE; c++) {
            forest[r][c] = buf[c] - '0';
        }
        ++r;
    }

    printf("Part one answer is: %d\n", p1(forest, map));
    printf("Part two answer is: %d\n", p2(forest, map));

    return 0;

}