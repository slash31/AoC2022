#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define BUFLEN 4096
#define INFILE "input.txt"
#define GRIDH 41
#define GRIDW 181

typedef struct point {
    int r;
    int c;
} Point;

typedef struct node {
    struct point coords;
    char elevation;
    int cost;
    bool discovered;
    bool visited;
    struct node *neighbors[4];
    struct node *prev;
} Node;

typedef struct nodelist {
    struct node *node;
    struct nodelist *prev;
    struct nodelist *next;
} NodeList;

typedef struct graph {
    struct node nodes[GRIDH][GRIDW];
    int node_count;
    struct node *start;
    struct node *end;
    int lc_path;
    int tcost;
} Graph;

void setup(Graph *graph) {
    char buf[BUFLEN] = "";
    FILE *fp = fopen(INFILE, "r");
    int i, j;
    int r = 0, c;
    int cost = 0;

    graph->lc_path = graph->node_count = 0;

    while (fgets(buf, BUFLEN, fp)) {
        for (c = 0; c < GRIDW; c++) {
            Node *thisnode = &graph->nodes[r][c];
            thisnode->coords.r = r;
            thisnode->coords.c = c;
            thisnode->cost = INT_MAX;
            thisnode->discovered = false;
            thisnode->visited = false;
            thisnode->prev = NULL;
            char elevation = buf[c];
            if (elevation == 'S') {
                thisnode->elevation = 'a';
                thisnode->cost = 0;
                graph->start = thisnode;
            } else if (elevation == 'E') {
                thisnode->elevation = 'z';
                graph->end = thisnode;
            } else {
                thisnode->elevation = elevation;
            }
            ++graph->node_count;
        }
        ++r;
    }

    for (i = 0; i < GRIDH; i++) {
        for (j = 0; j < GRIDW; j++) {
            Node *thisnode = &graph->nodes[i][j];
            Point adj[4] = {{i, j + 1}, {i, j - 1}, {i + 1, j}, {i - 1, j}};
            for (int k = 0; k < 4; k++) {
                int nr = adj[k].r;
                int nc = adj[k].c;
                if (nc >= 0 && nc < GRIDW && nr >= 0 && nr < GRIDH) {
                    Node *neighbor = &graph->nodes[nr][nc];
                    if (neighbor->elevation - thisnode->elevation <= 1){
                        thisnode->neighbors[k] = neighbor;
                    }
                }
            }
        }
    }
}

int shortest_path(Graph *graph) {
    Node *thisnode = graph->start;
    NodeList *unvisited = NULL;
    NodeList *unvisited_t = NULL;
    int cost = 0;

    while (thisnode != graph->end) {
        thisnode->visited = 1;
        int adj_cost = cost + 1;
        for (int i = 0; i < 4; i++) {
            Node *neighbor = thisnode->neighbors[i];
            if (neighbor) {
                if (neighbor->visited)
                    continue;
                if (adj_cost < neighbor->cost) {
                    neighbor->cost = adj_cost;
                    neighbor->prev = thisnode;
                }
                if (!neighbor->discovered) {
                    NodeList *discovered = calloc(1, sizeof(NodeList));
                    discovered->node = neighbor;
                    discovered->prev = unvisited_t;
                    if (unvisited_t) {
                        unvisited_t->next = discovered;
                        unvisited_t = discovered;
                    } else {
                        unvisited = discovered;
                        unvisited_t = discovered;
                    }
                    neighbor->discovered = true;
                }   
            }
        }

        NodeList *lc_neighbor = NULL;
        int min_cost = INT_MAX;
        NodeList *adj_node = unvisited;

        while (adj_node) {
            int node_cost = adj_node->node->cost;
            if (node_cost < min_cost) {
                min_cost = node_cost;
                lc_neighbor = adj_node;
            }
            adj_node = adj_node->next;
        }

        if (lc_neighbor) {
            if (lc_neighbor->prev) {
                lc_neighbor->prev->next = lc_neighbor->next;
            }
            if (lc_neighbor->next) {
                lc_neighbor->next->prev = lc_neighbor->prev;
            }
            if (lc_neighbor == unvisited) {
                unvisited = unvisited->next;
            }
            if (lc_neighbor == unvisited_t) {
                unvisited_t = unvisited_t->prev;
            }
                
            // Move to the currently best node
            thisnode = lc_neighbor->node;
            cost = min_cost;
            free(lc_neighbor);
        } else {
            cost = INT_MAX;
            break;
        }
    }
    graph->tcost = cost;
    NodeList *nodes = unvisited;
    while (nodes) {
        NodeList *temp = nodes->next;
        free(nodes);
        nodes = temp;
    }
    return cost;
}

// Credit: I rewrote a fair amount of this after reading through this code:
// https://github.com/tbpaolini/Advent-of-Code/blob/master/2022/Day%2012/day_12.c
// Specifically the use of a doubly-linked list (type NodeList) to track the
// unseen nodes.

int main() {

    Graph *graph = (Graph *)calloc(1, sizeof *graph);
    setup(graph);
    printf("Part one answer: %d\n", shortest_path(graph));

    //p2
    int *dists;
    dists = malloc(sizeof(int)*1000);
    for (int i = 0; i < GRIDH; i++) {
        for (int j = 0; j < GRIDW; j++) {
            if (graph->nodes[i][j].elevation == 'a') {
                setup(graph);
                graph->start = &graph->nodes[i][j];
                *dists++ = shortest_path(graph);
            }
        }
    }

    int cost = INT_MAX;
    int tcost = *--dists;
    while(tcost) {
        if (tcost < cost)
            cost = tcost;
        tcost = *--dists;
    }
    printf("Part two answer: %d\n", cost);

    free(graph);
    return 0;
}