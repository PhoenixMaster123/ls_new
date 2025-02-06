#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"
#include "output.h"
#include "threads.h"


// Programmoptionen
typedef struct {
    int show_hidden;     // -a
    int detailed;        // -l
    int recursive;       // -r
    int threads;         // -t
    int sort_by_size;    // -S
    int sort_by_extension; // -X
    char path[512];

} Options;
void show_help() {
    printf("Verwendung: ls_new [OPTIONEN] [PFAD]\n\
Zeige Dateien in einem Verzeichnis an.\n\
\nOptionen:\n\
  -a               Zeige alle Dateien, einschließlich versteckter Dateien (Dateien, deren Name mit '.' beginnt).\n\
  -l               Zeige detaillierte Informationen zu Dateien (z. B. Größe, Berechtigungen).\n\
  -r               Rekursives Traversieren von Verzeichnissen ohne Threads.\n\
  -t               Rekursives Traversieren von Verzeichnissen mit Threads (parallelisiert).\n\
  -S               Sortiere Dateien nach Größe (größte zuerst).\n\
  -X               Sortiere Dateien nach extension (nach Alphabet).\n\
  -h, --help       Zeige diese Hilfe an.\n\
\nPfad:\n  Standardmäßig wird das aktuelle Verzeichnis (.) verwendet, falls kein Pfad angegeben ist.\n\
\nBeispiele:\n\
  ./ls_new                       Listet Dateien im aktuellen Verzeichnis auf.\n\
  ./ls_new -a                    Listet alle Dateien (einschließlich versteckter) auf.\n\
  ./ls_new -l                    Zeigt detaillierte Informationen zu Dateien.\n\
  ./ls_new -r /path/to/dir       Durchsucht ein Verzeichnis rekursiv ohne Threads.\n\
  ./ls_new -t /path/to/dir       Durchsucht ein Verzeichnis rekursiv mit Threads.\n\
  echo \"/path/to/dir\" | ./ls_new Liest den Pfad aus der Standard-Eingabe (stdin).\n\
  ./ls_new -a -l -t /path/to/dir Zeigt alle Dateien mit Details und rekursivem Traversieren mit Threads an.\n");
    exit(EXIT_SUCCESS);
}


void parse_arguments(int argc, char *argv[], Options *opts) {
    opts->show_hidden = 0;
    opts->detailed = 0;
    opts->recursive = 0;
    opts->threads =0;
    opts->sort_by_size = 0;
    strcpy(opts->path, ".");

    int path_set = 0; // Um zu erkennen, ob der Pfad aus Argumenten gesetzt wurde

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) {
            opts->show_hidden = 1;
        } else if (strcmp(argv[i], "-l") == 0) {
            opts->detailed = 1;
        }
        //entfernen
        else if (strcmp(argv[i], "-r") == 0) {
            opts->recursive = 1;
        } else if (strcmp(argv[i], "-t") == 0) {
            opts->threads = 1;
            opts->recursive = 1;
        }else if (strcmp(argv[i], "-S") == 0) {
            opts->sort_by_size=1;
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            show_help();
        }
        else if (strcmp(argv[i], "-X") == 0)  {
            opts->sort_by_extension=1;
        }
        else {

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
    if (opts.sort_by_size) {
        sort_file_list_by_size(files);
    }else if (opts.sort_by_extension) {
        sort_file_list_by_extension(files);
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
