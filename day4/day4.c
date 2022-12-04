#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFLEN 4096

int p1(int e1lb, int e1ub, int e2lb, int e2ub) {
    if (e1lb <= e2lb && e2ub <= e1ub) // test if e1 contains e2
        return 1;
    else if (e2lb <= e1lb && e1ub <= e2ub) // test if e2 contains e1
        return 1;
    return 0;
}

int p2(int e1lb, int e1ub, int e2lb, int e2ub) {
    if ((e1lb <= e2lb && e2lb <= e1ub) || (e1lb <= e2ub && e2ub <= e1ub) ) // test if e1 overlaps with e2
        return 1;
    else if ((e2lb <= e1lb && e1lb <= e2ub) || (e2lb <= e1ub && e1ub <= e2ub) ) // test if e2 overlaps with e1
        return 1;
    return 0;
}

int main() {

    char buf[BUFLEN] = "";
    FILE *fp = fopen ("input.txt", "r");
    int p1c = 0;
    int p2c = 0;

    while (fgets (buf, BUFLEN, fp)) {
        size_t len = strlen (buf);
        // process if the line isn't empty (newline only)
        if (len > 1) {
            char *e1 = strtok(buf, ","); // get elf one's range
            char *e2 = strtok(NULL, ","); // get elf two's range
            int e1lb = atoi(strtok(e1, "-")); // elf one's lower bound
            int e1ub = atoi(strtok(NULL, ",")); // elf one's uppber bound
            int e2lb = atoi(strtok(e2, "-")); // elf one's lower bound
            int e2ub = atoi(strtok(NULL, ",")); // elf one's upper bound
            p1c += p1(e1lb, e1ub, e2lb, e2ub); // part 1
            p2c += p2(e1lb, e1ub, e2lb, e2ub); // part 2
        }
    }
    printf("Part 1 answer: %d\n", p1c);
    printf("Part 2 answer: %d\n", p2c);
    return 0;
}
