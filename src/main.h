#ifndef MAIN_H
#define MAIN_H

#include "filesystem.h"
#include "threads.h"
#include "output.h"

// Funktionen (falls spezifische Hauptfunktionen ausgegliedert werden sollen)
void parse_arguments(int argc, char *argv[], int *show_hidden, int *detailed, int *use_threads, char **path);

#endif // MAIN_H
