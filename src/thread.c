#include "search.h"

void *ThrdFunc(void *arg) {
    long thread_num = (long)arg;        // 1..NUM_THREADS
    char logname[64];

    snprintf(logname, sizeof(logname), "logs/thread_%ld.log", thread_num);

    FILE *log = fopen(logname, "w");
    if (!log) {
        fprintf(stderr, "Thread %ld: Kann Logdatei '%s' nicht öffnen\n",
                thread_num, logname);
        return NULL;
    }

    Node *cur = g_list_head;
    while (cur) {
        // Drei Fälle laut Aufgabenstellung

        if (cur->thread_id == 0) {
            // Noch niemand reserviert – versuchen zu locken
            int rc = pthread_mutex_trylock(&cur->mutex);
            if (rc == 0) {
                // unter Lock nochmal prüfen
                if (cur->thread_id == 0) {
                    cur->thread_id = (int)thread_num;
                    fprintf(log,
                            "[Thread %ld] Reserviere Datei '%s'\n",
                            thread_num, cur->filename);
                    // Mutex wieder freigeben, bevor die Suche läuft
                    pthread_mutex_unlock(&cur->mutex);

                    int result = Search(cur->filename);

                    // Ergebnis in Knoten schreiben
                    pthread_mutex_lock(&cur->mutex);
                    cur->found = result;
                    pthread_mutex_unlock(&cur->mutex);

                    fprintf(log,
                            "[Thread %ld] Suche in '%s' beendet, Pattern %sgefunden\n",
                            thread_num,
                            cur->filename,
                            result ? "" : "nicht ");
                } else {
                    // Zwischenzeitlich von anderem Thread reserviert
                    int owner = cur->thread_id;
                    pthread_mutex_unlock(&cur->mutex);
                    fprintf(log,
                            "[Thread %ld] Datei '%s' schon von Thread %d reserviert\n",
                            thread_num, cur->filename, owner);
                }
            } else {
                // Mutex bereits gesperrt
                fprintf(log,
                        "[Thread %ld] Datei '%s' ist aktuell gesperrt, überspringe\n",
                        thread_num, cur->filename);
            }
        } else {
            // Bereits von anderem Thread bearbeitet/ reserviert
            fprintf(log,
                    "[Thread %ld] Datei '%s' wird von Thread %d bearbeitet/ist fertig\n",
                    thread_num, cur->filename, cur->thread_id);
        }

        fflush(log); // direkt schreiben
        cur = cur->next;
    }

    fclose(log);
    return NULL;
}
