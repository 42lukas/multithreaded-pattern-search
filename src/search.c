#define _GNU_SOURCE   // für getline unter manchen Libcs
#include "search.h"

int Search(const char *filename) {
    if (!filename)
        return 0;

    char fullpath[PATH_MAX];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", SEARCH_DIR, filename);

    FILE *fp = fopen(fullpath, "r");
    if (!fp)
        return 0;

    char *line = NULL;
    size_t cap = 0;
    ssize_t len;

    int total = 0;
    const char *p;

    while ((len = getline(&line, &cap, fp)) != -1) {
        p = line;
        while ((p = strstr(p, SEARCH_PATTERN)) != NULL) {
            total++;
            p += strlen(SEARCH_PATTERN); // weiter gehen, um mehrere Treffer zu zählen
        }
    }

    free(line);
    fclose(fp);

    return total;    // liefert jetzt Anzahl der Treffer
}
