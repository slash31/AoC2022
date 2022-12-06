#include <stdio.h>
#include <strings.h>

#define BUFSIZE 4096
#define MARKERSIZE 4
#define MESSAGESIZE 14

int nodupes(char * wdw, int lidx, int ridx) {
    for (int i=lidx; i<ridx; i++) {
        for (int j=i+1; j<ridx; j++) {
            if (wdw[i]==wdw[j])
                return 0;
        }
    }
    return 1;
}
int main() {
    char buf[BUFSIZE*sizeof(char)] = "";
    FILE *fp = fopen ("input.txt", "r");
    if(fp != NULL) {
       fgets(buf, BUFSIZE*sizeof(char), fp);
    }
    for (int i=0; i<strlen(buf)-MARKERSIZE; i++) {
        if (nodupes(buf,i,i+MARKERSIZE)) {
            printf("Part 1 answer: %d\n", i+MARKERSIZE);
            break;
        }
    }
    for (int i=0; i<strlen(buf)-MESSAGESIZE; i++) {
        if (nodupes(buf,i,i+MESSAGESIZE)) {
            printf("Part 2 answer: %d\n", i+MESSAGESIZE);
            break;
        }
    }

    return 0;
}