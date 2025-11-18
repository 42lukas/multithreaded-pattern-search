#define _GNU_SOURCE   // für getline unter manchen Libcs
#include "search.h"

int Search(const char *filename) {
    if (!filename) {
        return 0;
    }

    char fullpath[PATH_MAX];
    if (snprintf(fullpath, sizeof(fullpath), "%s/%s", SEARCH_DIR, filename)
        >= (int)sizeof(fullpath)) {
        fprintf(stderr, "Search: Pfad zu lang für '%s'\n", filename);
        return 0;
    }

    FILE *fp = fopen(fullpath, "r");
    if (!fp) {
        fprintf(stderr, "Search: Kann Datei '%s' nicht öffnen: %s\n",
                fullpath, strerror(errno));
        return 0;
    }

    char *line = NULL;
    size_t cap = 0;
    ssize_t len;
    int found = 0;

    while ((len = getline(&line, &cap, fp)) != -1) {
        (void)len; // aktuell nicht benutzt
        if (strstr(line, SEARCH_PATTERN) != NULL) {
            found = 1;
            break;
        }
    }

    free(line);          // Zeilenpuffer freigeben
    fclose(fp);          // Datei direkt schließen

    return found;
}
