#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#define BUFLEN 4096
#define MAXDEPTH 256
#define MAXFILES 256
#define FSSIZE 70000000
#define MINSPACE 30000000

long p1result = 0;
long root_size = 0;
long p2result = 0;

struct file {
    char * name;
    long size;
};

struct directory {
    char * name;
    struct directory *parent;
    struct directory *subdirs[MAXDEPTH];
    struct file *files[MAXFILES];
    long size;
};

struct directory* mkdir(char * name, struct directory** current_dir) {
    for (int i=0; i<MAXDEPTH; i++) {
        if ((*current_dir) -> subdirs[i] != NULL) {
            continue;
        } else {
            (*current_dir) -> subdirs[i] = (struct directory*)malloc(sizeof(struct directory));
            (*current_dir) -> subdirs[i] -> name = strdup(name);
            (*current_dir) -> subdirs[i] -> parent = *current_dir;
            return (*current_dir) -> subdirs[i];
        }
    }
    return NULL;
}

struct directory* get_subdir(char * name, struct directory** current_dir) {
    for (int i=0; i<MAXDEPTH; i++){
        if ((*current_dir) -> subdirs[i] == NULL)
            return NULL;
        if (strcmp((*current_dir) -> subdirs[i] -> name,name) == 0)
            return (*current_dir) -> subdirs[i];
    }
    return NULL;
}

int dir_size(struct directory** current_dir) {
    (*current_dir) -> size = 0;
    for (int i=0; i<MAXFILES; i++) {
        if ((*current_dir) -> files[i] != NULL) {
            (*current_dir) -> size += (*current_dir) -> files[i] -> size;
        } else {
            break;
        }
    }
    for (int i=0; i<MAXDEPTH; i++) {
        if ((*current_dir) -> subdirs[i] == NULL)
            break;
        (*current_dir) -> size += dir_size(&(*current_dir) -> subdirs[i]);
    }
    if ((*current_dir) -> size < 100000)
        p1result += (*current_dir) -> size;

    if ((FSSIZE-root_size) + (*current_dir) -> size >= MINSPACE && (*current_dir) -> size < p2result)
        p2result = (*current_dir) -> size;

    return (*current_dir) -> size;
}

void mkfile(char * fname, int fsize, struct directory** current_dir) {
    for (int i=0; i<MAXFILES; i++) {
        if ((*current_dir) -> files[i] != NULL) {
            continue;
        } else {
            (*current_dir) -> files[i] = (struct file*)malloc(sizeof(struct file));
            (*current_dir) -> files[i] -> name = strdup(fname);
            (*current_dir) -> files[i] -> size = fsize;
            break;
        }
    }
}

struct file* get_file(char * fname, struct directory** current_dir) {
    for (int i=0; i<MAXFILES; i++){
        if ((*current_dir) -> files[i] == NULL)
            return NULL;
        if (strcmp((*current_dir) -> files[i] -> name, fname) == 0)
            return (*current_dir) -> files[i];
    }
    return NULL;
}


int main() {

    char buf[BUFLEN] = "";
    FILE *fp = fopen ("input.txt", "r");

    // create a root directory variable
    struct directory* root_dir = (struct directory*)malloc(sizeof(struct directory));
    root_dir -> name = "/";
    root_dir -> size = 0;
    root_dir -> parent = root_dir;

    // track the current dir (set it to root initially)
    struct directory* current_dir = root_dir;
    
    while (fgets (buf, BUFLEN, fp)) {
        size_t len = strlen (buf);
        // process if the line isn't empty (newline only)
        if (len > 1) {
            buf[strcspn(buf, "\n")] = 0;
            char *t1 = strtok(buf, " ");
            if (t1[0]=='$') {// this is a command
                char *cmd = strtok(NULL, " ");
                if (strcmp(cmd, "ls")==0) { // list current directory
                    ;
                } else if (strcmp(cmd, "cd")==0) { // change directory
                    char *name = strtok(NULL, " ");
                    if (strcmp(name,"..")==0) {
                        current_dir = current_dir -> parent;
                    } else if (strcmp(name,"/")==0) {
                        current_dir = root_dir;
                    } else {
                        struct directory* tmp_dir = get_subdir(name, &current_dir);
                        if (tmp_dir == NULL)
                            tmp_dir = mkdir(name, &current_dir);
                        current_dir = tmp_dir;
                    }
                    
                }
            } else if (t1[0] >= '0' && t1[0] <= '9') { // left-hand token is a file size
                char *name = strtok(NULL, " ");
                struct file* tmp_file= get_file(name, &current_dir);
                if (tmp_file == NULL)
                    mkfile(name, atoi(t1), &current_dir);
            }
        }
    }

    root_size = dir_size(&root_dir);
    printf("Part one answer: %ld\n", p1result);

    p2result = 99999999;
    int tmp = dir_size(&root_dir);
    printf("Part two answer: %ld\n", p2result);

    return 0;
}