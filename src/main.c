#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"
#include "output.h"
#include "threads.h"


// Struktur für Programmoptionen
typedef struct {
    int show_hidden;     // Flag für -a
    int detailed;        // Flag für -l
    int recursive;       // Flag für -r
    char path[512];      // Zielverzeichnis (Standard: aktuelles Verzeichnis)
} Options;

// Funktion zur Verarbeitung der Argumente
void parse_arguments(int argc, char *argv[], Options *opts) {
    opts->show_hidden = 0;
    opts->detailed = 0;
    opts->recursive = 0;
    strcpy(opts->path, "."); // Standard: aktuelles Verzeichnis

    int path_set = 0; // Um zu erkennen, ob der Pfad aus Argumenten gesetzt wurde

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) {
            opts->show_hidden = 1;
        } else if (strcmp(argv[i], "-l") == 0) {
            opts->detailed = 1;
        } else if (strcmp(argv[i], "-r") == 0) {
            opts->recursive = 1;
        } else {
            // Wenn ein Pfad übergeben wurde
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
        // Rekursive Auflistung
        if (traverse_directory_with_threads(opts.path, opts.show_hidden, files) != 0) {
            perror("Fehler beim Traversieren des Verzeichnisses");
            fprintf(stderr, "Verzeichnis: %s\n", opts.path);
            destroy_file_list(files);
            return EXIT_FAILURE;
        }
    } else {
        // Nicht-rekursives Traversieren
        if (traverse_directory(opts.path, opts.show_hidden, files) != 0) {
            fprintf(stderr, "Fehler beim Traversieren des Verzeichnisses %s\n", opts.path);
            destroy_file_list(files);
            return EXIT_FAILURE;
        }
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
