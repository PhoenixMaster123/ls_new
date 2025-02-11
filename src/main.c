#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/main.h"
#include "../include/filesystem.h"
#include "../include/output.h"
#include "../include/threads.h"


void show_help() {
    printf("%s", HELP_TEXT);
    exit(EXIT_SUCCESS);
}

// Funktion zur Verarbeitung der Argumente
void parse_arguments(int argc, char *argv[], Options *opts) {
    opts->show_hidden = 0;
    opts->detailed = 0;
    opts->reverse = 0;
    opts->recursive = 0;
    opts->threads =0;
    opts->sort_by_size = 0;
    opts->sort_by_extension = 0;
    opts->pattern[0] = '\0'; // Initialize pattern to empty
    strcpy(opts->path, ".");



    int path_set = 0; // Um zu erkennen, ob der Pfad aus Argumenten gesetzt wurde

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0) {
            opts->show_hidden = 1;
        } else if (strcmp(argv[i], "-l") == 0) {
            opts->detailed = 1;
        } else if (strcmp(argv[i], "-r") == 0  || strcmp(argv[i], "--reverse") == 0) {
            opts->reverse = 1;
        } else if (strcmp(argv[i], "-R") == 0  || strcmp(argv[i], "--recursive") == 0) {
            opts->recursive = 1;
        } else if (strcmp(argv[i], "-z") == 0) {
            opts->threads = 1;
            opts->recursive = 1;
        } else if (strcmp(argv[i], "-S") == 0) {
            opts->sort_by_size = 1;
        } else if (strcmp(argv[i], "-t") == 0) {
            opts->sort_by_time = 1;
        } else if (strcmp(argv[i], "--help") == 0) {
             show_help();
        } else if (strncmp(argv[i], "*", 1) == 0) {
            strncpy(opts->pattern, argv[i], sizeof(opts->pattern) - 1);
            opts->pattern[sizeof(opts->pattern) - 1] = '\0';
        } else if (strcmp(argv[i], "-X") == 0)  {
            opts->sort_by_extension=1;
        } else {
            strncpy(opts->path, argv[i], sizeof(opts->path) - 1);
            opts->path[sizeof(opts->path) - 1] = '\0';
            path_set = 1;
        }
    }

    // Wenn kein Pfad übergeben wurde und aus stdin gelesen werden soll
    if (!path_set && !isatty(fileno(stdin))) {
        if (fgets(opts->path, sizeof(opts->path), stdin) == NULL) {
            fprintf(stderr, "Fehler: Kein Verzeichnis angegeben.\n");
            exit(EXIT_FAILURE);
        }

        // Entferne das abschließende '\n', falls vorhanden
        opts->path[strcspn(opts->path, "\n")] = '\0';
    }
}

int main(int argc, char *argv[]) {
    Options opts;

    // Argumente parsen
    parse_arguments(argc, argv, &opts);

    // Dateien aus dem Zielverzeichnis abrufen
    FileList *files = create_file_list(); // Dynamische Datenstruktur für Dateien

    if (opts.recursive) {
        if (opts.threads) {
            // Rekursive Auflistung
            if (traverse_directory_with_threads(opts.path, opts.show_hidden, files) != 0) {
                perror("Fehler beim Traversieren des Verzeichnisses");
                fprintf(stderr, "Verzeichnis: %s\n", opts.path);
                destroy_file_list(files);
                return EXIT_FAILURE;
            }
        }else {
            if (traverse_directory_recursive(opts.path, opts.show_hidden, files) != 0) {
            perror("Fehler beim Traversieren des Verzeichnisses");
            fprintf(stderr, "Verzeichnis: %s\n", opts.path);
            destroy_file_list(files);
            return EXIT_FAILURE;
        }

        }
    } else {
        // Nicht-rekursives Traversieren
        if (traverse_directory(opts.path, opts.show_hidden, files) != 0) {
            fprintf(stderr, "Fehler beim Traversieren des Verzeichnisses %s\n", opts.path);
            destroy_file_list(files);
            return EXIT_FAILURE;
        }
    }
    if (opts.pattern[0] != '\0') {
        FileList *filtered_files = create_file_list();
        FileNode *current = files->head;

        // Normalize opts.path *only if* wildcard filtering is being done:
        char normalized_path[512];
        strcpy(normalized_path, opts.path);
        if (normalized_path[strlen(normalized_path) - 1] != '/') {
            struct stat path_stat;
            if (stat(normalized_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode)) {
                strcat(normalized_path, "/");
            }
        }

        while (current != NULL) {
            char full_path[512];

            snprintf(full_path, sizeof(full_path), "%s%s", normalized_path, current->name);

            const char *filename = strrchr(full_path, '/');
            if (filename == NULL) {
                filename = current->name;
            } else {
                filename++;
            }

            if (wildcard_match(filename, opts.pattern)) {
                add_file_to_list(filtered_files, current->name, &current->file_stat);
            }
            current = current->next;
        }

        destroy_file_list(files);
        files = filtered_files;
    }

    if (opts.sort_by_size) {
        sort_file_list_by_size(files);
    }else if (opts.sort_by_extension) {
        sort_file_list_by_extension(files);
    }

    if (opts.sort_by_time) {
        sort_file_list_by_time(files);
    }

    if (opts.reverse) {
        reverse_file_list(files);
    }

    // Ausgabe generieren
    if (opts.detailed) {
        print_detailed(files);
    } else {
        print_simple(files);
    }

    // Speicher freigeben
    destroy_file_list(files);

    return EXIT_SUCCESS;
}
