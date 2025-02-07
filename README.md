<div style="background-color: #f0f0f0; padding: 20px; border-radius: 8px;">
  <h1 style="color: #333; margin-top: 0;"><code>ls_new</code> - Erweiterte Version des <code>ls</code>-Befehls</h1>

<h2>Features</h2>


  <ul style="list-style-type: disc; padding-left: 20px; margin-top: 10px;">
    <li>Anzeige versteckter Dateien (<code>-a</code>)</li>
    <li>Detaillierte Dateiinformationen (<code>-l</code>)</li>
    <li>Rekursives Traversieren mit und ohne Threads (<code>-r</code>, <code>-R</code>)</li>
    <li>Sortierung nach Größe, Zeit oder Erweiterung (<code>-S</code>, <code>-M</code>, <code>-x</code>)</li>
    <li>Filterung durch Dateimuster (<code>"*.(pattern)"</code>)</li>
  </ul>

 <h2>Installation Guide</h2>
  <ol style="padding-left: 20px; margin-top: 10px;">
    <li>
      <p><strong>Voraussetzungen installieren</strong></p>
      <pre style="background-color: #e0e0e0; padding: 10px; border-radius: 4px; font-family: monospace; overflow-x: auto;">sudo apt update && sudo apt install cmake make gcc</pre>
    </li>
    <li>
      <p><strong>Repository klonen</strong></p>
      <pre style="background-color: #e0e0e0; padding: 10px; border-radius: 4px; font-family: monospace; overflow-x: auto;">git clone https://&lt;TOKEN&gt;@github.com/CodeWizard2001/ls_new
cd ls_new</pre>
    </li>
    <li>
      <p><strong>Build-Verzeichnis erstellen</strong></p>
      <pre style="background-color: #e0e0e0; padding: 10px; border-radius: 4px; font-family: monospace; overflow-x: auto;">mkdir build
cd build</pre>
    </li>
    <li>
      <p><strong>CMake konfigurieren</strong></p>
      <pre style="background-color: #e0e0e0; padding: 10px; border-radius: 4px; font-family: monospace; overflow-x: auto;">cmake ..</pre>
    </li>
    <li>
      <p><strong>Programm kompilieren</strong></p>
      <pre style="background-color: #e0e0e0; padding: 10px; border-radius: 4px; font-family: monospace; overflow-x: auto;">make</pre>
    </li>
    <li>
      <p><strong>Programm ausführen</strong></p>
      <pre style="background-color: #e0e0e0; padding: 10px; border-radius: 4px; font-family: monospace; overflow-x: auto;">./ls_new [Optionen] [Pfad]</pre>
    </li>
  </ol>
</div>

<h2>Verfügbare Optionen</h2>

  <table style="width: 100%; border-collapse: collapse; margin-top: 10px;">
    <thead>
      <tr style="background-color: #e0e0e0;">
        <th style="padding: 8px; text-align: left; border: 1px solid #ddd;">Option</th>
        <th style="padding: 8px; text-align: left; border: 1px solid #ddd;">Beschreibung</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td style="padding: 8px; border: 1px solid #ddd;"><code>-a</code></td>
        <td style="padding: 8px; border: 1px solid #ddd;">Zeigt alle Dateien, inklusive versteckter (Dateien, die mit <code>.</code> beginnen).</td>
      </tr>
      <tr>
        <td style="padding: 8px; border: 1px solid #ddd;"><code>-l</code></td>
        <td style="padding: 8px; border: 1px solid #ddd;">Zeigt detaillierte Informationen wie Berechtigungen, Größe und Datum.</td>
      </tr>
      <tr>
        <td style="padding: 8px; border: 1px solid #ddd;"><code>-r</code></td>
        <td style="padding: 8px; border: 1px solid #ddd;">Rekursives Traversieren von Verzeichnissen (ohne Threads).</td>
      </tr>
      <tr>
        <td style="padding: 8px; border: 1px solid #ddd;"><code>-R</code></td>
        <td style="padding: 8px; border: 1px solid #ddd;">Rekursives Traversieren von Verzeichnissen mit paralleler Verarbeitung (Threads).</td>
      </tr>
      <tr>
        <td style="padding: 8px; border: 1px solid #ddd;"><code>-t</code></td>
        <td style="padding: 8px; border: 1px solid #ddd;">Sortiert nach Zeitstempel (neueste zuerst).</td>
      </tr>
      <tr>
        <td style="padding: 8px; border: 1px solid #ddd;"><code>-S</code></td>
        <td style="padding: 8px; border: 1px solid #ddd;">Sortiert nach Dateigröße (größte zuerst).</td>
      </tr>
      <tr>
        <td style="padding: 8px; border: 1px solid #ddd;"><code>-M</code></td>
        <td style="padding: 8px; border: 1px solid #ddd;">Sortiert nach letztem Änderungsdatum.</td>
      </tr>
      <tr>
        <td style="padding: 8px; border: 1px solid #ddd;"><code>-X</code></td>
        <td style="padding: 8px; border: 1px solid #ddd;">Sortiert nach Dateierweiterung.</td>
      </tr>
      <tr>
        <td style="padding: 8px; border: 1px solid #ddd;"><code>"*.(pattern)"</code></td>
        <td style="padding: 8px; border: 1px solid #ddd;">Filtert Dateien nach dem angegebenen Muster.</td>
      </tr>
    </tbody>
  </table>
</div>

Markdown

<div style="background-color: #f0f0f0; padding: 20px; border-radius: 8px;">
  <h2 style="color: #333; margin-top: 0;">Anwendungsbeispiele</h2>

  <ol style="padding-left: 20px; margin-top: 10px;">
    <li>
      <p><strong>Dateien im aktuellen Verzeichnis auflisten</strong></p>
      <pre style="background-color: #e0e0e0; padding: 10px; border-radius: 4px; font-family: monospace; overflow-x: auto;">./1s_new</pre>
    </li>
    <li>
      <p><strong>Alle Dateien anzeigen (inklusive versteckter)</strong></p>
      <pre style="background-color: #e0e0e0; padding: 10px; border-radius: 4px; font-family: monospace; overflow-x: auto;">./1s_new -a</pre>
    </li>
    <li>
      <p><strong>Detaillierte Dateiinformationen ausgeben</strong></p>
      <pre style="background-color: #e0e0e0; padding: 10px; border-radius: 4px; font-family: monospace; overflow-x: auto;">./1s_new -l</pre>
    </li>
    <li>
      <p><strong>Rekursive Auflistung eines Verzeichnisses ohne Threads</strong></p>
      <pre style="background-color: #e0e0e0; padding: 10px; border-radius: 4px; font-family: monospace; overflow-x: auto;">./1s_new -r /path/to/directory</pre>
    </li>
    <li>
      <p><strong>Rekursive Auflistung eines Verzeichnisses mit Threads</strong></p>
      <pre style="background-color: #e0e0e0; padding: 10px; border-radius: 4px; font-family: monospace; overflow-x: auto;">./1s_new -R /path/to/directory</pre>
    </li>
    <li>
      <p><strong>Sortierung nach Größe</strong></p>
      <pre style="background-color: #e0e0e0; padding: 10px; border-radius: 4px; font-family: monospace; overflow-x: auto;">./1s_new -S</pre>
    </li>
    <li>
      <p><strong>Sortierung nach letztem Änderungsdatum</strong></p>
      <pre style="background-color: #e0e0e0; padding: 10px; border-radius: 4px; font-family: monospace; overflow-x: auto;">./1s_new -M</pre>
    </li>
    <li>
      <p><strong>Dateien nach Erweiterung sortieren</strong></p>
      <pre style="background-color: #e0e0e0; padding: 10px; border-radius: 4px; font-family: monospace; overflow-x: auto;">./1s_new -X</pre>
    </li>
    <li>
      <p><strong>Nur bestimmte Dateien anzeigen (z. B. alle PNG-Dateien)</strong></p>
      <pre style="background-color: #e0e0e0; padding: 10px; border-radius: 4px; font-family: monospace; overflow-x: auto;">./1s_new "*.png"</pre>
    </li>
    <li>
      <p><strong>Rekursive Verarbeitung mit Threads und Filterung kombinieren</strong></p>
      <pre style="background-color: #e0e0e0; padding: 10px; border-radius: 4px; font-family: monospace; overflow-x: auto;">./1s_new -r "*.c"</pre>
    </li>
  </ol>
</div>
   
<h2>Lizenz</h2>

  <p style="margin-top: 10px;">Dieses Projekt steht unter der MIT-Lizenz. Mehr Details findest du in der Datei <a href="LICENSE">LICENSE</a> im Repository.</p> 
</div>

<div style="background-color: #f0f0f0; padding: 20px; border-radius: 8px; margin-top: 20px;">
  <h2 style="color: #333; margin-top: 0;">Authoren</h2>

  <div style="margin-top: 10px;">
    <ul style="list-style-type: none; padding-left: 0;">
      <li>Enrico Ebert</li>
      <li>Max Tremel</li>
      <li>Kristian Popov</li>
      <li>Zacharias Priller</li>
    </ul>
  </div>
</div>
