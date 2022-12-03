#include <stdio.h>
#include <string.h>

#define BUFLEN 4096
#define UCA 65
#define LCA 97
#define VOFFSET 26

int get_pack_val (char* input) {   
    size_t slen = strlen (input); 
    for (int i = 0; i < slen/2; i++) {
        for (int j = slen/2; j < slen; j++) {
            if (input[i] == input[j]) {
                int c = (int)input[i];
                if (c < LCA) {
                    return (c-UCA+VOFFSET+1); // ascii val - table offset + value range offset + 1 (idx at 0)
                } else {
                    return (c-LCA+1); // ascii val - table offset + 1 (idx at 0)
                }
            }
        }
    }
    return 0;
}

void chars_in_string(char* line, int * ap) {
    size_t slen = strlen (line);
    for (int i = 0; i < slen; i++) {
        int c = (int)line[i];
        if (c < LCA) {
            ap[(c-UCA+VOFFSET)] = 1;
        } else {
            ap[(c-LCA)] = 1;
        }
    }
}

int get_badge_val (char* line_1, char* line_2, char* line_3) {
    int l1_c[52] = {0};
    int l2_c[52] = {0};
    int l3_c[52] = {0};
    
    chars_in_string(line_1,l1_c);
    chars_in_string(line_2,l2_c);
    chars_in_string(line_3,l3_c);
    
    for (int i=0; i<52; i++) {
        if (l1_c[i] ==1  && l2_c[i] == 1 && l3_c[i] == 1) {
            return i+1; 
        }
    } 
    return 0; 
}

int main () {
    int p1_total = 0;
    int p2_total = 0;
    size_t n = 1;
    char buf[BUFLEN] = "";
    FILE *fp = fopen ("input.txt", "r");

    // call part one solution function
    while (fgets (buf, BUFLEN, fp)) {
        p1_total += get_pack_val(buf);
    }

    // call part two solution function
    rewind(fp);
    char l1[BUFLEN], l2[BUFLEN], l3[BUFLEN];
    int count = 1;
    while (fgets (buf, BUFLEN, fp)) {
        if (1 == count) {
            strcpy(l1, buf);
        } else if (2 == count) {
            strcpy(l2, buf);
        } else {
            count = 0;
            strcpy(l3,buf);
            p2_total += get_badge_val(l1, l2, l3);
        }
        count ++;
    }
    
    fclose(fp);
    printf("Part 1 answer: %d\n", p1_total);
    printf("Part 2 answer: %d\n", p2_total);
    return 0;
}
