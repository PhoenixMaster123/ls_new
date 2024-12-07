#ifndef OUTPUT_H
#define OUTPUT_H

#include "filesystem.h"

// Funktionen zur Ausgabe
void print_simple(FileList *list);
void print_detailed(FileList *list);

// Hilfsfunktionen zur Formatierung
void format_permissions(mode_t mode, char *buffer);
void format_time(time_t time, char *buffer, size_t buffer_size);

#endif // OUTPUT_H
