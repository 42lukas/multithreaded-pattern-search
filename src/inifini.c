#include "search.h"

void GenList(void) {
    DIR *dir = opendir(SEARCH_DIR);
    if (!dir) {
        fprintf(stderr, "GenList: Kann Verzeichnis '%s' nicht öffnen: %s\n",
                SEARCH_DIR, strerror(errno));
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // '.' und '..' sowie versteckte Dateien überspringen
        if (entry->d_name[0] == '.') {
            continue;
        }
        Add2List(entry->d_name);
    }

    closedir(dir);
}

void init(void) {
    g_list_head = NULL;
    g_list_tail = NULL;
    GenList();
}

void finish(void) {
    // Erst anzeigen
    ShowList();

    // Dann alles freigeben
    Node *cur = g_list_head;
    while (cur) {
        Node *next = cur->next;
        pthread_mutex_destroy(&cur->mutex);
        free(cur);
        cur = next;
    }

    g_list_head = NULL;
    g_list_tail = NULL;
}
