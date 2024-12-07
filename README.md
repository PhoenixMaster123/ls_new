
# `ls_new` - Unterstützte Optionen und Anwendungsbeispiele

## Unterstützte Optionen
- **`-a`**: Zeige alle Dateien, einschließlich versteckter Dateien (Dateien, deren Name mit `.` beginnt).
- **`-l`**: Zeige detaillierte Informationen zu Dateien (z. B. Größe, Berechtigungen).
- **`-r`**: Rekursives Traversieren von Verzeichnissen ohne Threads.
- **`-R`**: Rekursives Traversieren von Verzeichnissen mit Threads (parallelisiert).

### Standard:
- **Pfad**: Angabe des Verzeichnisses, das durchsucht werden soll.  
  **Default**: Aktuelles Verzeichnis (`.`).
- **Pipeline**: Eingabe eines Verzeichnispfades über stdin mit einer Pipe.

---

## Beispiele und Anwendungsfälle

### 1. Dateien im aktuellen Verzeichnis auflisten
```bash
./ls_new
```
- Gibt eine einfache Liste von Dateien im aktuellen Verzeichnis aus.
- **Hinweis:** Versteckte Dateien werden nicht angezeigt.

---

### 2. Alle Dateien einschließlich versteckter Dateien anzeigen
```bash
./ls_new -a
```
- Listet alle Dateien (einschließlich versteckter) im aktuellen Verzeichnis.

---

### 3. Detaillierte Dateiinformationen anzeigen
```bash
./ls_new -l
```
- Zeigt Dateinamen, Größen, Berechtigungen und andere Details für das aktuelle Verzeichnis.

---

### 4. Rekursives Traversieren eines Verzeichnisses (ohne Threads)
```bash
./ls_new -r /path/to/directory
```
- Durchsucht `/path/to/directory` rekursiv und listet alle Dateien und Unterverzeichnisse.

---

### 5. Rekursives Traversieren eines Verzeichnisses (mit Threads)
```bash
./ls_new -R /path/to/directory
```
- Parallelisiertes Traversieren von `/path/to/directory` mithilfe von Threads.
- **Vorteil:** Beschleunigt die Verarbeitung bei großen Verzeichnissen.

---

### 6. Pfad über eine Pipeline übergeben
```bash
echo "/path/to/directory" | ./ls_new
```
- Liest den Pfad `/path/to/directory` aus der Standard-Eingabe (stdin) und listet Dateien darin auf.

---

### 7. Rekursives Traversieren mit Threads und Pipeline
```bash
echo "/path/to/directory" | ./ls_new -R
```
- Liest den Pfad aus der Pipeline und führt eine rekursive Traversierung mit Threads aus.

---

### 8. Kombinierte Optionen
```bash
./ls_new -a -l -R /path/to/directory
```
- Zeigt alle Dateien (einschließlich versteckter) mit detaillierten Informationen an und traversiert das Verzeichnis rekursiv mit Threads.
