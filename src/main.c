#include "search.h"

int main(void)
{
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    int i;
    int create_ok = 1;
    int join_ok = 1;
    int exit_code = EXIT_SUCCESS;

    init();

    i = 0;
    while (i < NUM_THREADS) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, ThrdFunc, &thread_ids[i]) != 0) {
            fprintf(stderr, "Fehler beim Erzeugen von Thread %d.\n", i + 1);
            create_ok = 0;
        }
        i = i + 1;
    }

    i = 0;
    while (i < NUM_THREADS) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Fehler beim Warten auf Thread %d.\n", i + 1);
            join_ok = 0;
        }
        i = i + 1;
    }

    finish();

    if (create_ok == 0 || join_ok == 0) {
        exit_code = EXIT_FAILURE;
    }

    return exit_code;
}
