
🚢 Battleship C++ (SFML)
Ein klassisches Schiffe-Versenken-Spiel in C++, visualisiert mit der SFML-Bibliothek. Das Spiel verfügt über eine grafische Klick-Oberfläche sowie eine integrierte, grafisch nachgebildete Konsole für Texteingaben und -ausgaben.
Zusätzlich bietet das Spiel ein Spiel-Archiv und einen Replay-Modus, um vergangene Partien Schritt für Schritt Revue passieren zu lassen.
🛠️ Voraussetzungen & Installation
Um das Spiel zu kompilieren, benötigen Sie einen C++ Compiler (unterstützt mindestens C++17) und die SFML-Bibliothek.
1. Abhängigkeiten installieren
Linux (Ubuntu/Debian):
```bash
sudo apt-get update
sudo apt-get install libsfml-dev build-essential
```
macOS (via Homebrew):
```bash
brew install sfml
```
2. Kompilieren
Das Projekt wird über ein standardmäßiges `Makefile` im Root-Verzeichnis gebaut. Öffnen Sie Ihr Terminal im Hauptordner und führen Sie aus:
```bash
make
```
Hinweis: Falls Sie die temporären Build-Dateien bereinigen möchten, nutzen Sie `make clean`.
3. Starten
Nach dem erfolgreichen Build befindet sich das Binary direkt im Root-Ordner. Starten Sie das Spiel mit:
```bash
./Battleship
```
🎮 Features & Steuerung
Das Spiel bündelt zwei Steuerungsarten in einer einzigen SFML-Oberfläche:
Grafischer Klick-Modus: Platzieren Sie Ihre Schiffe und feuern Sie auf das gegnerische Feld direkt per Mausklick.
Integrierter Konsolen-Modus: Nutzen Sie die im SFML-Fenster eingebaute Grafik-Konsole. Sie können per Tastatur Befehle und Koordinaten (z. B. `A05`) eingeben; Textausgaben des Spiels werden dort direkt hineingeschrieben.
Archiv & Replay: Jedes beendete Spiel wird automatisch im Archiv abgelegt. Über das Hauptmenü können Sie alte Partien laden und Spielzug für Spielzug im Replay-Modus abspielen.
🏗️ Projekt-Architektur
Da die Konsole eine reine SFML-Grafikkomponente ist, teilt sich das Projekt intern wie folgt auf:
Model (Spiellogik): Verwaltet das Koordinatensystem, Schiffs-Zustände, Treffervalidierung und die Replay-Engine. Völlig isoliert von Grafiken.
View (SFML-Rendering): Zeichnet das Spielfeld, die Buttons und die Custom-Konsole (inklusive Font-Rendering und Text-Input-Handling für die Tastatur).
Controller: Verarbeitet Mausklicks sowie die in der SFML-Konsole abgeschickten Text-Befehle und reicht sie an die Spiellogik weiter.
📁 Ordnerstruktur
```text
.
├── Engine/         # Quelldateien für die Spiellogik
├── UI/             # Quelldateien für das User-Interface
├── Assets/         # Schriftarten (Fonts), Texturen und Sounds
├── ...             # Noch hinzuzufügen
├── Makefile        # Build-Konfiguration für den Compiler
└── README.md       # Diese Dokumentation
```