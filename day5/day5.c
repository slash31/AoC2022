#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "day5.h"

#define BUFLEN 4096

struct node {
    char data;
    struct node *next;
};

void push(char data, struct node** stack){
    struct node* Node = (struct node*)malloc(sizeof(struct node)); 
    Node -> data = data;
    Node -> next = (stack != NULL) ? *stack : NULL; 
    (*stack) = Node;  
}

void move(struct node** source, struct node** dest, int qty){
    if (*source != NULL) {
        for (int i=0;i < qty; i++) {
            // pop from source stack
            char data = (*source) -> data;
            struct node* tempPtr = *source;
            *source = (*source) -> next;
            free(tempPtr);
            //push to the dest stack
            push(data, dest);
        }
    } 
}

void moveP2(struct node** source, struct node** dest, int n){
    char * tdata = calloc(n, sizeof(char));
    // pop n items from source stack
    for (int i = 0; i < n; i++) {
        char data = (*source) -> data;
        if (data != '\0') {
            tdata[i] = data;
            struct node* tempPtr = *source;
            *source = (*source) -> next;
            free(tempPtr);
        }
    }
    // push data to the dest stack
    for (int i = n-1; i >=0; i--)
        if (tdata[i] != '\0') {
            push(tdata[i], dest);
        }
    free(tdata);
}

char peek(struct node* stack) {
    if (stack != NULL) {
        return stack -> data;
    } else {
        return '.';
    }
}


int main() {

    // create stacks to hold crates
    struct node* stacks[NUM_STACKS];
    int qty, src, dst;

    for (int i = 0; i < NUM_STACKS;  i++) {
        stacks[i] = (struct node*)malloc(sizeof(struct node));
    }
    // manual stack setup function contained in setup.c
    setup(stacks);

    char buf[BUFLEN] = "";
    FILE *fp = fopen (INSTRUCTIONS, "r");
    while (fgets (buf, BUFLEN, fp)) {
        size_t len = strlen (buf);
        sscanf(buf, "move %d from %d to %d\n", &qty, &src, &dst);
        move(&stacks[src - 1],&stacks[dst - 1], qty);
        //moveP2(&stacks[src - 1], &stacks[dst - 1], qty);
    }
    printf("Top crates in each stack: ");
    for (int i = 0; i < NUM_STACKS; i++) {
        char val = peek(stacks[i]);
        printf("%c", val);
    }
    printf("\n");
    return 0;
}

