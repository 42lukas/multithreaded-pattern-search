# Multithreaded Pattern Search

Dieses Projekt implementiert eine parallele Mustersuche in mehreren Textdateien. Ziel ist es, die Leistung durch Thread-basierte Verarbeitung zu erhöhen. Jeder Thread durchsucht eigenständig Dateien nach einem vorgegebenen Textmuster. Das Projekt basiert vollständig auf den formalen Anforderungen der Aufgabenstellung (HWR Berlin, WiSe 2025).

---

## Projektbeschreibung

Das Programm durchsucht etwa 20 Textdateien in einem Verzeichnis (`./ToSearch`). Die Dateien werden automatisch erkannt und in eine einfach verkettete Liste eingetragen. Mehrere Threads (4 bis 8, im Header definiert) arbeiten diese Liste parallel ab.

Jeder Knoten der Liste enthält:
- Dateiname  
- Mutex  
- Threadnummer (0 = unreserviert)  
- Ergebniswert der Suche (1 = Muster gefunden, 0 = nicht gefunden)  
- Zeiger auf den nächsten Knoten  

Jeder Thread schreibt eigene Statusmeldungen in eine individuelle Protokolldatei im Ordner `logs/`.

---

## Kompilieren und Ausführen

### Voraussetzungen
- macOS: clang oder gcc (Standardinstallation)  
- Windows: gcc mit MSYS2, Git Bash oder WSL  
- POSIX Threads müssen unterstützt werden

### Kompilieren

`make`

### Programm ausführen

`make run`

### Bereinigen

`make clean`

... entfernt:
- Programmbinary
- Objektdateien
- Logdateien

---

## Funktionsübersicht

### main()
- Initialisiert globale Ressourcen  
- Erzeugt ein Array von Threads  
- Startet Threads mit der Funktion `ThrdFunc()`  
- Wartet auf das Ende aller Threads  
- Ruft abschließend `finish()` auf  

### init()
- Initialisiert globale Variablen  
- Ruft `GenList()` auf  

### finish()
- Ruft `ShowList()` auf  
- Gibt die verkettete Liste frei  

### GenList()
- Öffnet das Verzeichnis `./ToSearch`  
- Liest Dateinamen aus  
- Ruft für jeden Validen Eintrag `Add2List()` auf  

### Add2List()
- Reserviert Speicherplatz für einen neuen Knoten  
- Initialisiert den Knoten  
- Fügt ihn am Ende der Liste ein  

### Search()
- Öffnet eine Datei  
- Sucht Zeile für Zeile nach einem vorgegebenen Muster  
- Rückgabewert 1 = gefunden, 0 = nicht gefunden  

### ThrdFunc(void* arg)
- Jeder Thread läuft diese Funktion einmal durch  
- Versucht, Knoten zu reservieren  
- Führt für reservierte Dateien die Suche aus  
- Schreibt Meldungen in eigene Logdatei  

### ShowList()
- Gibt alle Knoten mit allen Komponenten lesbar aus  

---

## Konfiguration

Globale Parameter werden in der Datei `include/search.h` festgelegt:

- Anzahl der Threads  
- Suchmuster  
- Struct-Definition des Listenknotens  
- Globale Variablen (z. B. Kopf der Liste)  
- Prototypen aller Funktionen  

---

## Hinweise

- Die Anzahl und Namen der Dateien dürfen im Programm nicht fest eincodiert sein.  
- Jeder Thread muss seine eigene Protokolldatei erzeugen.  
- Es dürfen nur POSIX-konforme Thread-Funktionen verwendet werden.  
- Das Programm darf nie auf freie Mutexes warten. Wenn blockiert: überspringen.  

---

## Lizenz

Dieses Projekt dient ausschließlich als Studien- und Übungsprojekt im Rahmen der Lehrveranstaltung Betriebssysteme (HWR Berlin, WiSe 2025).

## Autoren

Lukas Karsten <br>
Nasser Mohamad