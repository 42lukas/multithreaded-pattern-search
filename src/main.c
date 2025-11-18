#include "search.h"

int main(void) {
    pthread_t threads[NUM_THREADS];

    // Initialisierung und Listenaufbau
    init();

    // Threads starten
    for (long i = 0; i < NUM_THREADS; ++i) {
        long thread_num = i + 1;  // Nummern 1..NUM_THREADS
        int rc = pthread_create(&threads[i], NULL, ThrdFunc, (void *)thread_num);
        if (rc != 0) {
            fprintf(stderr, "main: pthread_create(%ld) failed: %s\n",
                    thread_num, strerror(rc));
        }
    }

    // Auf Threads warten
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Aufräumen (inkl. ShowList)
    finish();

    return 0;
}
