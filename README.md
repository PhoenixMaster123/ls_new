# `ls_new` - Erweiterte Version des `ls`-Befehls

## Features ✨

*   Anzeige versteckter Dateien (`-a`)
*   Detaillierte Dateiinformationen (`-l`)
*   Rekursives Traversieren mit und ohne Threads (`-r`, `-R`)
*   Sortierung nach Größe, Zeit oder Erweiterung (`-S`, `-M`, `-x`)
*   Filterung durch Dateimuster (`"*.(pattern)"`)

## Installation 🛠️

1.  **Voraussetzungen installieren**

    ```bash
    sudo apt update && sudo apt install cmake make gcc
    ```

2.  **Repository klonen**

    ```bash
    git clone https://<TOKEN>@[github.com/CodeWizard2001/ls_new](https://www.google.com/search?q=https://github.com/CodeWizard2001/ls_new)
    cd ls_new
    ```

3.  **Build-Verzeichnis erstellen**

    ```bash
    mkdir build
    cd build
    ```

4.  **CMake konfigurieren**

    ```bash
    cmake ..
    ```

5.  **Programm kompilieren**

    ```bash
    make
    ```

6.  **Programm ausführen**

    ```bash
    ./ls_new [Optionen] [Pfad]
    ```

## Verfügbare Optionen ⚙️

| Option | Beschreibung |
|---|---|
| `-a` | Zeigt alle Dateien, inklusive versteckter (Dateien, die mit `.` beginnen). |
| `-l` | Zeigt detaillierte Informationen wie Berechtigungen, Größe und Datum. |
| `-r` | Rekursives Traversieren von Verzeichnissen (ohne Threads). |
| `-R` | Rekursives Traversieren von Verzeichnissen mit paralleler Verarbeitung (Threads). |
| `-t` | Sortiert nach Zeitstempel (neueste zuerst). |
| `-S` | Sortiert nach Dateigröße (größte zuerst). |
| `-M` | Sortiert nach letztem Änderungsdatum. |
| `-X` | Sortiert nach Dateierweiterung. |
| `"*.(pattern)"` | Filtert Dateien nach dem angegebenen Muster. |

## Anwendungsbeispiele 💡

1.  **Dateien im aktuellen Verzeichnis auflisten**

    ```bash
    ./ls_new
    ```

2.  **Alle Dateien anzeigen (inklusive versteckter)**

    ```bash
    ./ls_new -a
    ```

3.  **Detaillierte Dateiinformationen ausgeben**

    ```bash
    ./ls_new -l
    ```

4.  **Rekursive Auflistung eines Verzeichnisses ohne Threads**

    ```bash
    ./ls_new -r /path/to/directory
    ```

5.  **Rekursive Auflistung eines Verzeichnisses mit Threads**

    ```bash
    ./ls_new -R /path/to/directory
    ```

6.  **Sortierung nach Größe**

    ```bash
    ./ls_new -S
    ```

7.  **Sortierung nach letztem Änderungsdatum**

    ```bash
    ./ls_new -M
    ```

8.  **Dateien nach Erweiterung sortieren**

    ```bash
    ./ls_new -X
    ```

9.  **Nur bestimmte Dateien anzeigen (z. B. alle PNG-Dateien)**

    ```bash
    ./ls_new "*.png"
    ```

10. **Rekursive Verarbeitung mit Threads und Filterung kombinieren**

    ```bash
    ./ls_new -r "*.c"
    ```

## Lizenz ⚖️

Dieses Projekt steht unter der MIT-Lizenz. Mehr Details findest du in der Datei [LICENSE](LICENSE).

## Autoren 👨‍💻👩‍💻

*   Enrico Ebert
*   Max Tremel
*   Kristian Popov
*   Zacharias Priller
