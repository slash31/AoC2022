#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFLEN 4096

int sortCmp (const void * a, const void * b) {
   return ( *(int*)b - *(int*)a );
}

int main () {

    size_t n = 1;
    char buf[BUFLEN] = "";
    FILE *fp = fopen ("input.txt", "r");   

    int cVal = 0;
    int hVals[3] = {0,0,0};
    while (fgets (buf, BUFLEN, fp)) {
        size_t len = strlen (buf);
        if (len > 1)  { 
            buf[--len] = 0;
            cVal = cVal + atoi(buf);
        } else { 
            if (cVal > hVals[2]) {
				hVals[2] = cVal;
                int n = sizeof(hVals) / sizeof(hVals[0]);
				qsort(hVals, n, sizeof(int), sortCmp);
			}
			cVal = 0;
        }   
    }
    fclose (fp);
    printf("Top Elf carries %d, top three combined carry %d\n",hVals[0], hVals[0]+hVals[1]+hVals[2]);

    return 0;
}