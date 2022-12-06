#ifndef SETUP_H_INCLUDED
#define SETUP_H_INCLUDED
#define NUM_STACKS 9
#define INSTRUCTIONS "instructions.txt"

struct node;

void setup(struct node* stacks[NUM_STACKS]);

void push(char data, struct node** stack);

void move(struct node** source, struct node** dest, int qty);

void moveP2(struct node** source, struct node** dest, int qty);

#endif