# Minimal erforderliche CMake-Version
cmake_minimum_required(VERSION 3.10)

# Projektname und Sprache
project(FileLister LANGUAGES C)

# Setzt die C-Standardversion
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Verzeichnisse
set(SRC_DIR src)
set(INCLUDE_DIR include)

# Quellen
set(SOURCES
    ${SRC_DIR}/main.c
    ${SRC_DIR}/filesystem.c
    ${SRC_DIR}/output.c
    ${SRC_DIR}/threads.c
)

# Ziel hinzufügen: Ausführbare Datei
add_executable(ls_new ${SOURCES})

# Include-Verzeichnis für Header hinzufügen
target_include_directories(ls_new PRIVATE ${INCLUDE_DIR})

# Optionale Warnungen
target_compile_options(ls_new PRIVATE -Wall -Wextra -pedantic)

# Optional: Threads-Bibliothek (falls nötig)
find_package(Threads REQUIRED)
target_link_libraries(ls_new PRIVATE Threads::Threads)
