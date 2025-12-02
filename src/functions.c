#include "search.h"

Node *g_head = NULL; //Definition der globalen Liste

//Hilfsfunktion: sichere Kopie des Dateinamens, max. MAX_FILENAME_LEN Zeichen
static void copy_filename(char *dest, const char *src)
{
    size_t i = 0;
    size_t len = strlen(src);

    while (i < MAX_FILENAME_LEN && i < len) {
        dest[i] = src[i];
        i = i + 1;
    }
    dest[i] = '\0';
}


void init(void)
{
    g_head = NULL;
    GenList();
}


void GenList(void)
{
    DIR *dir;
    struct dirent *entry;
    int loop_active;

    dir = opendir(SEARCH_DIR);
    if (dir == NULL) {
        perror("Fehler beim Öffnen des Suchverzeichnisses");
        loop_active = 0;
    } else {
        loop_active = 1;
    }

    while (loop_active == 1) {
        entry = readdir(dir);
        if (entry == NULL) {
            loop_active = 0;
        } else {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                Add2List(entry->d_name);
            }
        }
    }

    if (dir != NULL) {
        closedir(dir);
    }
}

void Add2List(const char *filename)
{
    Node *node;


    node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Speicherreservierung für Knoten fehlgeschlagen.\n");
    } else {
        copy_filename(node->filename, filename);
        pthread_mutex_init(&node->mutex, NULL);
        node->thread_id = 0;
        node->found = 0;
        node->count = 0;
        node->next = g_head;
        g_head = node;
    }
}

int Search(const char *filename, int *occurrences)
{
    char fullpath[MAX_PATH_LEN];
    FILE *fp;
    char buffer[1024];
    int loop_active;
    int local_count = 0;
    char *pos;
    int inner_active;

    snprintf(fullpath, sizeof(fullpath), "%s\\%s", SEARCH_DIR, filename);

    fp = fopen(fullpath, "r");
    if (fp == NULL) {
        fprintf(stderr, "Konnte Datei %s nicht öffnen.\n", fullpath);
        loop_active = 0;
    } else {
        loop_active = 1;
    }

    while (loop_active == 1) {
        if (fgets(buffer, sizeof(buffer), fp) == NULL) {
            loop_active = 0;
        } else {
            pos = buffer;
            inner_active = 1;

            while (inner_active == 1) {
                pos = strstr(pos, PATTERN);
                if (pos == NULL) {
                    inner_active = 0;
                } else {
                    local_count = local_count + 1;
                    pos = pos + strlen(PATTERN);
                }
            }
        }
    }

    if (fp != NULL) {
        fclose(fp);
    }

    if (occurrences != NULL) {
        *occurrences = local_count;
    }

    return (local_count > 0);
}

void ShowList(void)
{
    Node *current = g_head;
    int loop_active;

    if (current == NULL) {
        loop_active = 0;
    } else {
        loop_active = 1;
    }

    while (loop_active == 1) {
        printf("Datei: %-8s | Thread: %d | Gefunden: %d | Anzahl: %d\n",
               current->filename,
               current->thread_id,
               current->found,
               current->count);

        current = current->next;
        if (current == NULL) {
            loop_active = 0;
        }
    }
}


void finish(void)
{
    Node *current = g_head;
    Node *next;
    int loop_active;

    ShowList();

    if (current == NULL) {
        loop_active = 0;
    } else {
        loop_active = 1;
    }

    while (loop_active == 1) {
        next = current->next;
        pthread_mutex_destroy(&current->mutex);
        free(current);
        current = next;
        if (current == NULL) {
            loop_active = 0;
        }
    }

    g_head = NULL;
}
