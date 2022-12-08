#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#define BUFLEN 4096
#define MAXDEPTH 256

struct directory {
    char * name;
    struct directory *parent; 
    struct directory *subdirs[MAXDEPTH];
    int size;
};


int main() {
    struct directory* root_dir = (struct directory*)malloc(sizeof(struct directory));
    printf("%d\n", root_dir->subdirs[0] == NULL);
    root_dir->subdirs[0] = (struct directory*)malloc(sizeof(struct directory));
    printf("%d\n", root_dir->subdirs[0] == NULL);
    int temp = '5';
    printf("sss %d\n", temp >= 48 && temp <= 57);
    return 0;
}