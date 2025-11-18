#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>
#include <limits.h>   // PATH_MAX
#include <errno.h>

// ---- Konfiguration ----
#define NUM_THREADS      4                 // 4–8 laut Aufgabenblatt
#define MAX_FILENAME_LEN 256              // interne Begrenzung
#define SEARCH_PATTERN   "TODO"             // Suchmuster
#define SEARCH_DIR       "./ToSearch"     // Verzeichnis mit Textdateien

// ---- Datentyp für Listenknoten ----
typedef struct Node {
    char filename[MAX_FILENAME_LEN];  // Dateiname
    pthread_mutex_t mutex;            // Mutex pro Datei
    int thread_id;                    // Nummer des Threads (0 = keiner)
    int found;                        // 1 = gefunden, 0 = nicht gefunden
    struct Node *next;                // nächster Knoten
} Node;

// ---- Globale Variablen ----
extern Node *g_list_head;
extern Node *g_list_tail;

// ---- Schnittstelle ----
// init / finish
void init(void);
void finish(void);

// Listenverwaltung
void GenList(void);
void Add2List(const char *filename);
void ShowList(void);

// Suche in einer Datei
int Search(const char *filename);

// Threadfunktion
void *ThrdFunc(void *arg);

#endif // SEARCH_H
