#ifndef THREADS_H
#define THREADS_H

#include "filesystem.h"

// Funktionen für Multithreading
int traverse_directory_with_threads(const char *path, int show_hidden, FileList *file_list);

#endif // THREADS_H
