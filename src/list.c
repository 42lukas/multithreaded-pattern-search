#include "search.h"

Node *g_list_head = NULL;
Node *g_list_tail = NULL;

void Add2List(const char *filename) {
    if (filename == NULL || filename[0] == '\0') {
        return;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Add2List: malloc failed\n");
        return;
    }

    // Dateiname kopieren
    strncpy(node->filename, filename, MAX_FILENAME_LEN - 1);
    node->filename[MAX_FILENAME_LEN - 1] = '\0';

    // Felder initialisieren
    if (pthread_mutex_init(&node->mutex, NULL) != 0) {
        fprintf(stderr, "Add2List: pthread_mutex_init failed\n");
        free(node);
        return;
    }

    node->thread_id = 0;
    node->found = 0;
    node->next = NULL;

    // Am Ende der Liste anhängen (O(1) dank Tail-Zeiger)
    if (g_list_head == NULL) {
        g_list_head = node;
        g_list_tail = node;
    } else {
        g_list_tail->next = node;
        g_list_tail = node;
    }
}

void ShowList(void) {
    printf("=== Ergebnisliste ===\n");
    Node *cur = g_list_head;
    while (cur) {
        printf("Datei: %-20s | Thread: %2d | Pattern gefunden: %d\n",
               cur->filename, cur->thread_id, cur->found);
        cur = cur->next;
    }
}
