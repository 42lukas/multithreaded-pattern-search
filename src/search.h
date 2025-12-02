#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>

#define MAX_FILENAME_LEN 64
#define MAX_PATH_LEN 260

/* Suchverzeichnis und Muster (Vorgaben aus Aufgabe, Beispielwerte) */
#define SEARCH_DIR "D:\\Programmieren\\Repos\\multithreaded-pattern-search\\ToSearch" // for mac "./ToSearch"
#define PATTERN "TODO"      /* Hier ggf. das gewünschte Muster anpassen */
#define NUM_THREADS 4     /* Zwischen 4 und 8 */

/* Knoten der einfach verketteten Liste */
typedef struct Node {
    char filename[MAX_FILENAME_LEN + 1]; /* Dateiname (ohne Pfad) */
    pthread_mutex_t mutex;               /* Mutex für diesen Knoten */
    int thread_id;                       /* Nummer des Threads */
    int found;                           /* 1 wenn Muster gefunden, 0 sonst */
    int count;                           /* Anzahl Vorkommen von PATTERN */
    struct Node *next;                   /* Zeiger auf nächsten Knoten */
} Node;

/* Globale Anfangsadresse der Liste */
extern Node *g_head;

/* Funktionsprototypen */
void init(void);
void finish(void);

void GenList(void);
void Add2List(const char *filename);
int Search(const char *filename, int *occurrences);
void ShowList(void);

void *ThrdFunc(void *arg);

#endif /* SEARCH_H */
