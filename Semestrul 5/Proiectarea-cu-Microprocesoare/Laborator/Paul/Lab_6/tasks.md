# Lab_6

1. Care sunt valorile de BaudRate acceptate de circuitul 8250? Precizati la ce linii se realizeaza
setarea BaudRate în codul exemplu de transmitere seriala.

300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200 si mai rar 230400

Se seteaza la liniile 18-20 prin serviciul AH = 8 al interruptiei ISERIAL, unde AL contine configuratia.

2. Ce reprezintă codul specificat la liniile 22-24 din codul de transmitere seriala.

MOV AH, 4
MOV AL, 01H
INT ISERIAL

Acest cod activează semnalul DTR (Data Terminal Ready). Valoarea 01H setează bitul corespunzător DTR pe 1, indicând perifericului intenția de a iniția o conexiune.

3. Ce verifica codul de la liniile 52-58 din codul de transmisie seriala? Ce se întâmpla când
verificarea nu reușește? Dar când reușește?

Verifică dacă semnalul CTS (Clear To Send) este activ. Se citește statusul (AH=3), se aplică o mască (AND AH, 10H) pentru a izola bitul CTS.

Dacă verificarea nu reușește (CTS inactiv): Programul sare înapoi la eticheta CHECK_CTS1 și așteaptă într-o buclă infinită până când perifericul este gata.

Dacă reușește: Programul continuă și transmite octetul.

4. De ce valoarea de la linia 40 din codul de recepție caracter este 03h. Va mai funcționa codul dacă
utilizam valoarea 02h? Explicați.

Valoarea este 03H (binar 0000 0011) pentru a activa RTS (bitul 1) menținând simultan DTR activ (bitul 0).

Cu 02h: Codul ar activa RTS dar ar dezactiva DTR (binar 0000 0010). Acest lucru ar întrerupe sesiunea de comunicație, deoarece DTR trebuie menținut activ pe toată durata conexiunii.

5. Ce realizeaza codul de la liniile 30-31 din codul de recepție caracter?

MOV AX, 1000
INT IWAIT

Realizează o buclă de întârziere (Wait) software, așteptând o perioadă determinată de valoarea din AX.

6. Se pot lega mai multe dispozitive (mai mult de 2) pe aceleași linii în cadrul prototlului serial
RS232? Explicati.

Nu, standardul RS232 este un protocol punct-la-punct (Point-to-Point). Cablajul prezentat (TXD la RXD, RTS la CTS etc.) conectează o singură placă Modulo Z3 la un singur PC/periferic. Nu există mecanism de adresare pentru dispozitive multiple pe aceleași fire.

7. Ce realizeaza codul de la liniile 51-52 din codul de recepție? Dar codul de la liniile 54-56 ?

51-52: Afișează pe LCD șirul de caractere definit la INTR_CHAR ("Receptie CH:..") folosind întreruperea IDIS_STR.

54-56: Afișează efectiv octetul recepționat (salvat anterior în variabila char_to_send / char_to_display) pe LCD la o poziție specifică, folosind IDIS_BYTE.

8. Scrieți secvența de cod pentru dezactivare DTR? Ce se întâmpla dacă dezactivam DTR?

MOV AH, 4
MOV AL, 00H  ; Dezactiveaza toti bitii de control (DTR=0)
INT ISERIAL (sau INT 14H)

Efect: Placa Modulo Z3 semnalizează perifericului încheierea sesiunii de comunicație.

9. Scrieți secvența de cod de inițializare a interfetei seriale cu următoarea configuratie: Baudrate
1200, fără paritate, 2 biti de stop, 7 biti de date.

MOV AH, 8          ; Functia de initializare
MOV AL, XXh        ; XX = Valoarea hexa calculata pentru 1200 baud, 7N2
INT ISERIAL        ; Apel intrerupere
