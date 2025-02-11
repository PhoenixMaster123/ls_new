#ifndef MAIN_H
#define MAIN_H

#include "filesystem.h"
#include "threads.h"
#include "output.h"

#define HELP_TEXT \
"Usage: ls_new [OPTION]... [FILE]...\n\
List information about the FILEs (the current directory by default).\n\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
  -a, --all                  do not ignore entries starting with .\n\
  -l                         use a long listing format\n\
  -r, --reverse              reverse order while sorting\n\
  -R, --recursive            list subdirectories recursively\n\
  -z,                        list threads subdirectories recursively\n\
  -S                         sort by file size, largest first\n\
  -t                         sort by time, newest first; see --time\n\
  -X                         sort alphabetically by entry extension\n\
      --help        display this help and exit\n\
\n\
     Dateinamensmuster (z.B., *.png)\n\
Exit status:\n\
 0  if OK,\n\
 -1  if minor problems (e.g., cannot access subdirectory),\n\"

// Struktur für Programmoptionen
typedef struct {
    int show_hidden;            // Flag für -a
    int detailed;               // Flag für -l
    int reverse;                // Flag für -r
    int recursive;              // Flag für -R
    int threads;                // Flag für -z
    int sort_by_size;           // Flag für -S
    int sort_by_time;           // Flag für -t
    int sort_by_extension;      // Flag für -X
    char pattern[256];          // Dateinamensmuster (z.B., "*.png")
    char path[512];             // Zielverzeichnis (Standard: aktuelles Verzeichnis)
} Options;

// Funktionen (falls spezifische Hauptfunktionen ausgegliedert werden sollen)
void parse_arguments(int argc, char *argv[], Options *opts);

#endif // MAIN_H