#include "search.h"

void *ThrdFunc(void *arg)
{
    int my_id;
    char logname[64];
    FILE *logfp;
    Node *current;
    int loop_active;
    int lock_result;
    int search_result;
    int occurrence_count;   /* NEU */
    int done = 0;

    my_id = *((int *)arg);

    snprintf(logname, sizeof(logname), "thread_%02d.log", my_id);
    logfp = fopen(logname, "w");
    if (logfp == NULL) {
        fprintf(stderr, "Thread %d: Konnte Logdatei %s nicht öffnen.\n", my_id, logname);
    }

    current = g_head;
    if (current == NULL) {
        loop_active = 0;
    } else {
        loop_active = 1;
    }

    while (loop_active == 1) {
        if (current->thread_id == 0) {
            lock_result = pthread_mutex_trylock(&current->mutex);
            if (lock_result == 0) {
                current->thread_id = my_id;

                if (logfp != NULL) {
                    fprintf(logfp, "Thread %d: Datei %s reserviert.\n",
                            my_id, current->filename);
                } else {
                    fprintf(stderr, "Thread %d: Datei %s reserviert.\n",
                            my_id, current->filename);
                }

                pthread_mutex_unlock(&current->mutex);

                occurrence_count = 0;
                search_result = Search(current->filename, &occurrence_count);

                lock_result = pthread_mutex_lock(&current->mutex);
                if (lock_result == 0) {
                    current->found = search_result;
                    current->count = occurrence_count;
                    pthread_mutex_unlock(&current->mutex);
                }

                if (logfp != NULL) {
                    fprintf(logfp,
                            "Thread %d: Suche in Datei %s abgeschlossen, Ergebnis: %d, Anzahl: %d.\n",
                            my_id, current->filename, search_result, occurrence_count);
                } else {
                    fprintf(stderr,
                            "Thread %d: Suche in Datei %s abgeschlossen, Ergebnis: %d, Anzahl: %d.\n",
                            my_id, current->filename, search_result, occurrence_count);
                }

            } else {
                if (logfp != NULL) {
                    fprintf(logfp,
                            "Thread %d: Knoten fuer Datei %s ist blockiert.\n",
                            my_id, current->filename);
                } else {
                    fprintf(stderr,
                            "Thread %d: Knoten fuer Datei %s ist blockiert.\n",
                            my_id, current->filename);
                }
            }
        } else {
            if (logfp != NULL) {
                fprintf(logfp,
                        "Thread %d: Datei %s wird/bzw. wurde von Thread %d bearbeitet.\n",
                        my_id, current->filename, current->thread_id);
            } else {
                fprintf(stderr,
                        "Thread %d: Datei %s wird/bzw. wurde von Thread %d bearbeitet.\n",
                        my_id, current->filename, current->thread_id);
            }
        }

        current = current->next;
        if (current == NULL) {
            loop_active = 0;
        }
    }

    if (logfp != NULL) {
        fclose(logfp);
    }

    done = 1;
    if (done) {
        /* genau ein return wie gefordert */
    }

    return NULL;
}