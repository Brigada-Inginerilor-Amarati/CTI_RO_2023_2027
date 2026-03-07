# Lab_2

1. Presupunând că doresc să ridic la pătrat numărul salvat în registrul AL, este corect să scriu
instrucțiunea MUL AL, AL? Explicați.

Nu este corect sa scriem instructiunea asa, MUL ia doar un argument, urmand ca acesta sa fie inmultit cu AL.
Corect ar fi sa folosim MUL AL, astfel va avea loc ridicarea la pătrat a numărului din AL.

2. Care este secvența de instrucțiuni necesară pentru calcularea cubului numărului salvat în
registrul AL?

MOV BL, AL
MUL AL
MUL BL

3. Cum pot sa înmulțesc cu 8 conținutul registrului AL folosind doar o instrucțiune de
deplasare?

SHL AL, 3 -> shift left AL cu 3 biti este identic cu inmultirea cu 2^3 = 8

4. Dacă rezultatul ultimei instrucțiuni artimetice executate de procesor a fost -5, care va fi
valoarea flag-urilor ZF și SF? Dar dacă rezultatul a fost 0?

ZF = 0
SF = 1 (numarul este negativ, sign flag este primul bit din registru)

5. Care este instrucțiunea care decrementează registrul CX automat la fiecare pas și poate fi
folosită pentru a implementa o structură de tip for?

LOOP

6. În urma execuției instrucțiunii CMP AL, BL, ce flag-uri se vor poziționa pe valoarea 1,
dacă AL și BL sunt egale? Dar în situația în care AL < BL?

AL == BL -> ZF = 1
AL < BL -> CF = 1

Se face in spate o scadere intre AL si BL, dar nu se modifica niciun registru.

7. Ce instrucțiuni de salt se pot folosi pentru a sări la eticheta E0 în situația în care rezultatul
ultimei instrucțiuni aritmetice executate de procesor a fost zero?

JZ = Jump if Zero
JE = Jump if Equal
JG = Jump if Greater
