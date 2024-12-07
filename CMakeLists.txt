# Minimal erforderliche CMake-Version
cmake_minimum_required(VERSION 3.10)

# Projektname und Sprache
project(FileLister LANGUAGES C)

# Setzt die C-Standardversion
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Verzeichnisse
set(SRC_DIR src)

# Quellen und Header
set(SOURCES
        ${SRC_DIR}/main.c
        ${SRC_DIR}/filesystem.c
        ${SRC_DIR}/output.c
        ${SRC_DIR}/threads.c
)

set(HEADERS
        ${SRC_DIR}/filesystem.h
        ${SRC_DIR}/output.h
        ${SRC_DIR}/threads.h
)

# Ziel hinzufügen: Ausführbare Datei
add_executable(ls_new ${SOURCES} ${HEADERS})

# Optionale Warnungen
target_compile_options(ls_new PRIVATE -Wall -Wextra -pedantic)

# Optional: Threads-Bibliothek (falls nötig)
find_package(Threads REQUIRED)
target_link_libraries(ls_new PRIVATE Threads::Threads)
