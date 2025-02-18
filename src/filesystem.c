#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <math.h>
#include "../include/filesystem.h"

// Definition der FileNode-Struktur

// Erstellt eine neue FileList
FileList *create_file_list() {
    FileList *list = (FileList *)malloc(sizeof(FileList));
    if (!list) {
        perror("Fehler beim Allokieren der Datei-Liste");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    return list;
}

// Fügt eine Datei in die Liste ein
void add_file_to_list(FileList *list, const char *name,const struct stat *file_stat) {
    FileNode *new_node = (FileNode *)malloc(sizeof(FileNode));
    if (!new_node) {
        perror("Fehler beim Allokieren eines Datei-Knotens");
        exit(EXIT_FAILURE);
    }

    strncpy(new_node->name, name, sizeof(new_node->name) - 1);
    new_node->name[sizeof(new_node->name) - 1] = '\0';
    new_node->file_stat = *file_stat;
    new_node->next = NULL;

    if (list->tail) {
        list->tail->next = new_node;
    } else {
        list->head = new_node;
    }
    list->tail = new_node;
    list->count++;
}

// Gibt die Liste und ihre Elemente frei
void destroy_file_list(FileList *list) {
    FileNode *current = list->head;
    while (current) {
        FileNode *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

// Traversiert ein Verzeichnis und fügt Dateien zur Liste hinzu
int traverse_directory(const char *path, int show_hidden, FileList *list) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("Fehler beim Öffnen des Verzeichnisses");
        return -1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (!show_hidden && entry->d_name[0] == '.') {
            continue; // Überspringt versteckte Dateien
        }

        char full_path[512];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat file_stat;
        if (stat(full_path, &file_stat) == -1) {
            perror("Fehler beim Abrufen von Datei-Informationen");
            continue;
        }

        add_file_to_list(list, entry->d_name, &file_stat);
    }

    closedir(dir);
    return 0;
}


int wildcard_match(const char *str, const char *pattern) {
    switch (*pattern) {
        case '\0':  // End of pattern
            return *str == '\0'; // Match if string is also empty
        case '*':   // Wildcard
            return wildcard_match(str, pattern + 1) || // Match * with empty string
                   (*str != '\0' && wildcard_match(str + 1, pattern)); // Match * with 1+ chars
        case '?':   // Any single character
            return *str != '\0' && wildcard_match(str + 1, pattern + 1); // Match any char + rest
        default:    // Literal character
            return *str == *pattern && wildcard_match(str + 1, pattern + 1); // Match char + rest
    }
}

int traverse_directory_recursive(const char *path, int show_hidden, FileList *list) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("Fehler beim Öffnen des Verzeichnisses");
        return -1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Überspringe "." und ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Überspringe versteckte Dateien, wenn show_hidden deaktiviert ist
        if (!show_hidden && entry->d_name[0] == '.') {
            continue;
        }
        char full_path[512];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat file_stat;
        if (stat(full_path, &file_stat) == -1) {
            perror("Fehler beim Abrufen von Datei-Informationen");
            continue;
        }

        add_file_to_list(list, entry->d_name, &file_stat);

        // Prüfe, ob es sich um ein Verzeichnis handelt und rufe die Funktion rekursiv auf
        if (S_ISDIR(file_stat.st_mode)) {
            if (traverse_directory_recursive(full_path, show_hidden, list) != 0) {
                closedir(dir); // Verzeichnis schließen, bevor du den Fehler weitergibst
                return -1;
            }
        }
    }

    closedir(dir); // Verzeichnis schließen
    return 0;
}
void sort_file_list_by_size(FileList *list) {
    if (!list->head || !list->head->next) {
        return;
    }

    for (FileNode *i = list->head; i != NULL; i = i->next) {
        for (FileNode *j = i->next; j != NULL; j = j->next) {
            if (i->file_stat.st_size < j->file_stat.st_size) {

                char temp_name[256];
                struct stat temp_stat;

                strncpy(temp_name, i->name, sizeof(temp_name));
                temp_stat = i->file_stat;

                strncpy(i->name, j->name, sizeof(i->name));
                i->file_stat = j->file_stat;

                strncpy(j->name, temp_name, sizeof(j->name));
                j->file_stat = temp_stat;
            }
        }
    }
}


const char* get_extension(const char* filename) {
    const char* dot = strrchr(filename, '.'); // Suche nach dem letzten Punkt
    if (!dot || dot == filename) return "";   // Keine Dateiendung vorhanden
    return dot + 1;                           // Rückgabe der Erweiterung
}

void sort_file_list_by_time(FileList *list)
{
    if (!list->head || !list->head->next) return;

    for(FileNode *i = list->head; i != NULL; i = i->next)
    {
        for(FileNode *j = i->next; j != NULL; j = j->next)
        {
            if(i->file_stat.st_mtime < j->file_stat.st_mtime)
            {
            char temp_name[256];
            struct stat temp_stat;

            strncpy(temp_name, i->name, sizeof(temp_name));
            temp_stat = i->file_stat;

            strncpy(i->name, j->name, sizeof(i->name));
            i->file_stat = j->file_stat;

            strncpy(j->name, temp_name, sizeof(j->name));
            j->file_stat = temp_stat;
            }
        }
    }
}

void sort_file_list_by_extension(FileList *list) {
    if (!list->head || !list->head->next) {
        return; // Keine Sortierung erforderlich
    }

    for (FileNode *i = list->head; i != NULL; i = i->next) {
        for (FileNode *j = i->next; j != NULL; j = j->next) {
            const char* ext_i = get_extension(i->name);
            const char* ext_j = get_extension(j->name);

            // Vergleiche Erweiterungen lexikografisch
            if (strcmp(ext_i, ext_j) > 0) {
                // Tausche die Inhalte der Knoten
                char temp_name[256];
                struct stat temp_stat;

                strncpy(temp_name, i->name, sizeof(temp_name));
                temp_stat = i->file_stat;

                strncpy(i->name, j->name, sizeof(i->name));
                i->file_stat = j->file_stat;

                strncpy(j->name, temp_name, sizeof(j->name));
                j->file_stat = temp_stat;
            }
        }
    }
}

void reverse_file_list(FileList *list) {
    if (!list || !list->head || !list->head->next) {
        return;
    }

    FileNode *prev = NULL;
    FileNode *current = list->head;
    FileNode *next = NULL;

    while (current) {
        next = current->next; 
        current->next = prev;  
        prev = current;        
        current = next;
    }
  
    list->head = prev;
}