#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#define BUFLEN 4096
#define INFILE "input.txt"
#define NUM_MONKEYS 8
#define ROUNDS_P1 20
#define ROUNDS_P2 10000

typedef struct monkey {
    long items[100];
    int num_items;
    char operator;
    int operand;
    int testval;
    int tdest;
    int fdest;
    int icount;
} monkey;

void print_monkey (int mnum, struct monkey* monkeys[]) {
    monkey *m = monkeys[mnum];
    printf("Monkey %d:\n", mnum);
    printf("\tstarting items: ");
    for (int i = 0; m -> items[i] != 0; i++)
        printf("%ld  ", m -> items[i]);
    printf("\tnum items: %d\n", m -> num_items);
    printf("\toperator: %c\n", m -> operator);
    printf("\toperand: %d\n", m -> operand);
    printf("\ttest val: %d\n", m -> testval);
    printf("\tIf T -> %d, If F -> %d\n", m -> tdest, m -> fdest);
    printf("\tinspection count: %d\n", m -> icount);
}

void throw(int idx, long w, int sm, int dm, struct monkey* monkeys[]) {
    int next = monkeys[dm] -> num_items++;
    monkeys[dm] -> items[next] = w;
    // yes i know this is inefficient
    int sli = --monkeys[sm] -> num_items;
    for (int i = idx; i < sli; i++)
        monkeys[sm] -> items[i] = monkeys[sm] -> items[i+1];
    monkeys[sm] -> items[sli] = 0;
}

void monkeytime(int mnum, int wrf, int lcm, struct monkey* monkeys[]) {
    monkey *m = monkeys[mnum];
    unsigned long w = 0;
    while (m -> items[0] != 0) {
        long item = m -> items[0];
        long op;
        if (m -> operand == -1)
            op = item;
        else 
            op = m -> operand;
        m -> icount += 1;
        if (m -> operator == '+')
            w = (item + op) / wrf;
        else if (m -> operator == '*')
            w = (item * op) / wrf;
        if (w % m -> testval == 0)
            throw(0, w % lcm, mnum, m -> tdest, monkeys);
        else
            throw(0, w % lcm, mnum, m -> fdest, monkeys);
    }
}

void setup(struct monkey* monkeys[]) {
    char buf[BUFLEN] = "";
    FILE *fp = fopen (INFILE, "r");

    while (fgets (buf, BUFLEN, fp)) {
        size_t len = strlen (buf);
        char * key;
        int mnum;
        char ttok[100];
        if (len > 1) {
            if (sscanf(buf,"Monkey %d", &mnum) == 1) {
                struct monkey* Monkey = (struct monkey*)malloc(sizeof(struct monkey));
                monkeys[mnum] = Monkey;
            } else if (sscanf(buf, "  Starting items%s", ttok) == 1) {
                buf[strcspn(buf, "\n")] = 0;
                key = strtok(buf, ":");
                int c = 0;
                for (char * tmp = strtok (NULL, ","); tmp; tmp = strtok (NULL, ",")) {
                    monkeys[mnum] -> items[c] = atoi(tmp);
                    monkeys[mnum] -> num_items += 1;
                    ++c;
                }
            }
            if (sscanf(buf,"  Operation: new = old %c old", &monkeys[mnum] -> operator) == 1)
                monkeys[mnum] -> operand = -1;
            sscanf(buf,"  Operation: new = old %c %d", &monkeys[mnum] -> operator, &monkeys[mnum] -> operand);
            sscanf(buf, "  Test: divisible by %d", &monkeys[mnum] -> testval);
            sscanf(buf, "    If true: throw to monkey %d", &monkeys[mnum] -> tdest);
            sscanf(buf, "    If false: throw to monkey %d", &monkeys[mnum] -> fdest);
        }
    }
}

int sortCmp (const void * a, const void * b) {
   return ( *(int*)b - *(int*)a );
}

unsigned long monkeybiz(struct monkey* monkeys[]) {
    // return the product of the two highest inspection counts
    int icounts[NUM_MONKEYS];
    for (int i = 0; i < NUM_MONKEYS; i++)
        icounts[i] = monkeys[i] -> icount;
    qsort(icounts, NUM_MONKEYS, sizeof(int), sortCmp);
    return (unsigned long)icounts[0] * (unsigned long)icounts[1];
}

int main () {
    
    monkey* *monkeys = malloc(NUM_MONKEYS * sizeof *monkeys);
    int i = 0, lcm = 1;

    setup(monkeys);

    // this took me forever to figure out using (really poor) search terms in Google :/
    for (i = 0; i < NUM_MONKEYS; i++)
        lcm = lcm * monkeys[i] -> testval;

    for (int i = 0; i < ROUNDS_P1; i++)
        for (int j = 0; j < NUM_MONKEYS; j++)
            monkeytime(j, 3, lcm, monkeys);
    printf("Part one answer: %ld\n", monkeybiz(monkeys));
    free(monkeys);

    //rinse and repeat for part 2
    *monkeys = malloc(NUM_MONKEYS * sizeof *monkeys);
    setup(monkeys);

    for (int i = 0; i < ROUNDS_P2; i++)
        for (int j = 0; j < NUM_MONKEYS; j++)
            monkeytime(j, 1, lcm, monkeys);

    printf("Part two answer: %ld\n", monkeybiz(monkeys));
    return 0;
}
