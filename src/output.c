#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/output.h"
#include "../include/filesystem.h"

// Einfache Ausgabe der Dateinamen
void print_simple(FileList *list) {
    FileNode *current = list->head;
    while (current) {
        printf("%s\n", current->name);
        current = current->next;
    }
}

// Detaillierte Ausgabe der Dateiinformationen
void print_detailed(FileList *list) {
    FileNode *current = list->head;

    while (current) {
        char permissions[11];
        format_permissions(current->file_stat.st_mode, permissions);

        char time_buffer[64];
        format_time(current->file_stat.st_mtime, time_buffer, sizeof(time_buffer));

        printf("%s %5ld %s %s\n",
               permissions,
               current->file_stat.st_size,
               time_buffer,
               current->name);

        current = current->next;
    }
}

// Hilfsfunktion: Formatieren der Zugriffsrechte
void format_permissions(mode_t mode, char *buffer) {
    buffer[0] = S_ISDIR(mode) ? 'd' : '-';
    buffer[1] = (mode & S_IRUSR) ? 'r' : '-';
    buffer[2] = (mode & S_IWUSR) ? 'w' : '-';
    buffer[3] = (mode & S_IXUSR) ? 'x' : '-';
    buffer[4] = (mode & S_IRGRP) ? 'r' : '-';
    buffer[5] = (mode & S_IWGRP) ? 'w' : '-';
    buffer[6] = (mode & S_IXGRP) ? 'x' : '-';
    buffer[7] = (mode & S_IROTH) ? 'r' : '-';
    buffer[8] = (mode & S_IWOTH) ? 'w' : '-';
    buffer[9] = (mode & S_IXOTH) ? 'x' : '-';
    buffer[10] = '\0';
}

// Hilfsfunktion: Formatieren des Zeitstempels
void format_time(time_t time, char *buffer, size_t buffer_size) {
    struct tm *tm_info = localtime(&time);
    strftime(buffer, buffer_size, "%Y-%m-%d %H:%M", tm_info);
}
