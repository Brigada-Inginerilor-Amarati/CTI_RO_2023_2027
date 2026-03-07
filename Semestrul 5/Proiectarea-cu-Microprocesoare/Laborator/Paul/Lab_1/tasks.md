# Lab_1

1. Care sunt registrele de uz general ale procesorului 8086 și ce denumiri au ele?

AX = Accumulator
BX = Base
CX = Counter
DX = Data
SP = Stack Pointer
BP = Base Pointer
SI = Source Index
DI = Destination Index
SS = Stack Segment
DS = Data Segment
CS = Code Segment
ES = Extra Segment

2. Specificați numărul de biți ai fiecărui registru, dintre următoarele: AX, CL, BH, AL, DX.

AX = 16 biți
CL = 8 biți
BH = 8 biți
AL = 8 biți
DX = 16 biți

3. Cum se declară variabila D pe 16 biți cu valoarea inițială 1?

D dw 1

4. Cum se declară o variabilă X pe 8 biți cu valoarea inițială necunoscută?

X db ?

5. Pot să adun direct două variabile X și Y pe câte 8 biți fiecare, dacă ambele au fost
decalarate în secțiunea .data a programului, folosind instrucțiunea ADD X, Y?

Nu. Operarea directă asupra a două variabile declarate de programator este interzisă.

6. Dați exemplu de un registru segment pe 16 biți și explicați rolul acestuia.

SS = Stack Segment -> Tine un pointer spre segmentul de stivă care este folosit pentru a stoca datele temporare.
DS = Data Segment -> Tine un pointer spre segmentul de date care este folosit pentru a stoca datele de date.
CS = Code Segment -> Tine un pointer spre segmentul de cod care este folosit pentru a stoca codul.
ES = Extra Segment -> Tine un pointer spre segmentul extra care este folosit pentru a stoca datele extra.

7. Care este numele registrului pe 16 biți în care se salvează adresa de început din memorie a
segmentului de stivă?

SP = Stack Pointer

8. Care dintre următoarele instrucțiuni poziționează indicatorii de condiție: ADD AL, BH;
MOV AL, A; SUB AL, Y?

MOV AL, A -> nu pozitioneaza, restul da

9. În urma apelării întreruperii INT 21H cu serviciul de citire al unei taste de la tastatură, în
care registru al procesorului va fi stocat codul tastei și câți biți are acest registru?

AH = 8 biți

10. Considerând că folosim întreruperea INT 21H cu serviciul de afișare a unui caracter pe
ecran, în care registru al procesorului trebuie sa salvăm data ce se dorește a fi afișată, înainte
de a apela întreruperea? Pe câți biți este acel registru?

DL = 8 biți

11. Care este acronimul utilizat pentru numele registrului care conține adresa instrucțiunii
următoare celei care este executată de către microprocesor? Ce înseamnă acesta?

IP = Instruction Pointer -> in momentul unui context switch, IP este folosit pentru a stoca adresa instrucțiunii care este executată de către microprocesor, stiind apoi la ce adresa trebuie sa se intoarca procesul
