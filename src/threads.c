#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "threads.h"
#include "filesystem.h"

// Struktur für Thread-Aufgaben
typedef struct {
    char path[512];
    int show_hidden;
    FileList *file_list;
    pthread_mutex_t *list_mutex;
} ThreadTask;

// Worker-Funktion für Threads
void *thread_worker(void *arg) {
    ThreadTask *task = (ThreadTask *)arg;

    // Traversieren des Verzeichnisses
    if (traverse_directory(task->path, task->show_hidden, task->file_list) != 0) {
        fprintf(stderr, "Fehler beim Traversieren des Verzeichnisses %s\n", task->path);
    }

    free(task); // Freigeben der Task-Struktur
    return NULL;
}

// Rekursive Verzeichnisdurchläufe mit Threads
int traverse_directory_with_threads(const char *path, int show_hidden, FileList *file_list) {
    printf("Mit Threads\n");
    DIR *dir = opendir(path);
    if (!dir) {
        perror("Fehler beim Öffnen des Verzeichnisses");
        return -1;
    }

    struct dirent *entry;
    pthread_t threads[128];
    int thread_count = 0;

    pthread_mutex_t list_mutex = PTHREAD_MUTEX_INITIALIZER;

    while ((entry = readdir(dir)) != NULL) {
        if (!show_hidden && entry->d_name[0] == '.') {
            continue; // Überspringe versteckte Dateien
        }

        char full_path[512];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat file_stat;
        if (stat(full_path, &file_stat) == -1) {
            perror("Fehler beim Abrufen von Datei-Informationen");
            continue;
        }

        // Fügt die Datei zur Liste hinzu
        pthread_mutex_lock(&list_mutex);
        add_file_to_list(file_list, entry->d_name, &file_stat);
        pthread_mutex_unlock(&list_mutex);

        // Wenn es sich um ein Unterverzeichnis handelt, starten Sie einen neuen Thread
        if (S_ISDIR(file_stat.st_mode) &&
            strcmp(entry->d_name, ".") != 0 &&
            strcmp(entry->d_name, "..") != 0) {
            ThreadTask *task = (ThreadTask *)malloc(sizeof(ThreadTask));
            if (!task) {
                perror("Fehler beim Allokieren eines Thread-Tasks");
                closedir(dir);
                return -1;
            }

            strncpy(task->path, full_path, sizeof(task->path) - 1);
            task->path[sizeof(task->path) - 1] = '\0';
            task->show_hidden = show_hidden;
            task->file_list = file_list;
            task->list_mutex = &list_mutex;

            if (pthread_create(&threads[thread_count], NULL, thread_worker, task) != 0) {
                perror("Fehler beim Erstellen eines Threads");
                free(task);
                closedir(dir);
                return -1;
            }

            thread_count++;
            if (thread_count >= 128) {
                fprintf(stderr, "Zu viele Threads erstellt, maximale Anzahl erreicht.\n");
                break;
            }
        }
    }

    closedir(dir);

    // Warten Sie auf alle Threads
    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&list_mutex);
    return 0;
}
