#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>

#define MAX_FILENAME_LEN 64
#define MAX_PATH_LEN 260
#define SEARCH_DIR "../ToSearch"
#define PATTERN "TODO"
#define NUM_THREADS 4


typedef struct Node {
    char filename[MAX_FILENAME_LEN + 1];
    pthread_mutex_t mutex;
    int thread_id;
    int found;
    int count;
    struct Node *next;
} Node;

//Globale Anfangsadresse der Liste
extern Node *g_head;

//Prototypen
void init(void);
void finish(void);
void GenList(void);
void Add2List(const char *filename);
int Search(const char *filename, int *occurrences);
void ShowList(void);

void *ThrdFunc(void *arg);

#endif
