                                                      # Sistem de casă inteligent 

  # Pașii de compilare ai aplicației:
  
1. Conectează placa ESP32 la laptop utilizând cablul USB.
2. Deschide Arduino IDE și Notepad++ și încarcă codul sursă specific.
3. În Arduino IDE selectează "Fișier" -> "Preferințe", iar în caseta "Setarea URL-urilor aditionale pentru managerul de placă", introdu urmatoarea adresa URL:       "https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json" și apasă butonul "OK" pentru a salva setările.
4. Selectează placa corectă: Mergi la "Instrumente" -> "Placă" și selectează "Wemos D1 Mini ESP32".
5. Selectează portul COM corespunzător plăcii ESP32 din meniul "Instrumente" -> "Port". 
6. În meniul "Instrumente", găsește și selectează opțiunea "ESP32 Sketch Data Upload" pentru a se încărca conținutul paginii web pe placa ESP32.
7. Verifică codul: Apasă butonul de "Verificare". Aceasta va verifica dacă codul tău are erori de sintaxă sau alte probleme.
8. Dacă nu există erori, încarcă codul pe placa ESP32: Apasă butonul de "Încărcare" pentru a încărca codul pe placa ESP32 conectată.
9. Dupa încărcare utilizatorul se va conecta de pe telefon la rețeaua Wi-Fi "Smart home" și va introduce parola "12345678".
10. Într-un browser web, utilizatorii pot introduce adresa IP a plăcii ESP32, 192.168.4.1 pentru a accesa pagina web.
11. În interfața aplicației, utilizatorii pot monitoriza și controla diferite aspecte ale sistemului de casă inteligent.
12. Utilizatorii pot accesa butonul de setări pentru a introduce detaliile rețelei Wi-Fi dorite și se va genera o nouă adresă IP pe care utilizatorul o poate folosi pentru a se conecta în continuare la sistemul de casă inteligent.

      # Pașii de instalare și lansare a aplicației
# Pașii pentru instalarea și lansarea aplicației Arduino IDE 1.8.19:

1. Accesează site-ul oficial Arduino (https://www.arduino.cc) și navighează la secțiunea "Software".
2. Descarcă versiunea potrivită pentru sistemul de operare pe care îl utilizezi (Windows, Mac sau Linux).
3. După ce descărcarea este completă, deschide fișierul de instalare.
4. Urmează instrucțiunile de instalare afișate pe ecran și selectează opțiunile potrivite pentru setările dorite.
5. Așteaptă finalizarea procesului de instalare. Poate dura câteva minute în funcție de viteza sistemului tău.
6. După ce instalarea este completă, lansează aplicația Arduino IDE.
7.După configurare, ești pregătit să începi să dezvolți și să încarci codul pe plăcile Arduino.

# Pașii pentru instalarea și lansarea aplicației Notepad++:

1. Accesează site-ul oficial Notepad++ (https://notepad-plus-plus.org/downloads) într-un browser web.
2. Navighează la secțiunea "Download" a paginii.
3. Caută versiunea "Notepad++ Installer" și dă clic pe linkul de descărcare pentru a descărca fișierul de instalare.
4. După finalizarea descărcării, deschide fișierul de instalare.
5. Urmează instrucțiunile de instalare afișate pe ecran și selectează opțiunile dorite pentru configurarea inițială.
6. Așteaptă finalizarea procesului de instalare. Aceasta poate dura câteva momente în funcție de viteza sistemului tău.
7. După instalare, lansează aplicația Notepad++ făcând dublu clic pe pictograma aplicației de pe desktop.

# Pașii de instalare pentru ESP32 Filesystem Uploader și placa ESP32 în Arduino IDE:

1. Deschide Arduino IDE pe computerul tău.
2. În Arduino IDE selectează "Fișier" -> "Preferințe", iar în caseta "Setarea URL-urilor aditionale pentru managerul de placă", introdu urmatoarea adresa URL: "https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json"
Apasă pe butonul "OK" pentru a salva modificările.
3. Navighează la meniul "Instrumente" din bara de meniu și selectează "Placă" -> "Gestionare placă" pentru a deschide Managerul de plăci.
4. În căutarea din Managerul de plăci, introdu "esp32" în câmpul de căutare.
Așteaptă ca rezultatele să se încarce, apoi găsește opțiunea "esp32" de la Espressif Systems și selecteaz-o.
5. Apasă pe butonul "Instalare" pentru a instala suportul pentru placa ESP32 în Arduino IDE.
7. După finalizarea instalării, închide Managerul de plăci.
8. Accesează meniul "Instrumente" din bara de meniu și selectează "ESP32 Sketch Data Upload".
9. Așteaptă ca ESP32 Filesystem Uploader să se descarce și să se instaleze în Arduino IDE.
10. După finalizarea instalării, poți utiliza opțiunea "ESP32 Sketch Data Upload" pentru a încărca fișierele sistemului de fișiere pe placa ESP32.
11. Pentru adăugarea plăcii esp32 selectează "Instrumente" din bara de meniu și selectează "Placă" și adaugă "Wemos D1 Mini ESP32".

      

