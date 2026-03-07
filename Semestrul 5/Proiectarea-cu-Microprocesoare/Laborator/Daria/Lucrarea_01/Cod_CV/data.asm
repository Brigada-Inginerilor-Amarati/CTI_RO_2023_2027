

.data 
    nume_variabila db 0 ; am declarat o variabilă cu numele nume_variabila, cu lungimea de un byte (8 biți) și valoarea inițială 0

    nume1 db ? ; am declarat o variabilă cu numele nume1, cu lungimea de un byte și valoare inițială necunoscută 

    nume2 dw 5 ; am declarat o variabilă cu numele nume2, cu lungimea de de doi bytes (16 biți – word) și valoarea inițială 5

    nume3 dd 117 ; variabila nume3 cu lungimea dublu-cuvânt (double-word), adică 32 biți și valoarea inițială 117 în zecimal 

    nume4 dq 0 ; variabila nume4 cu lungimea quad-word, adică de 4 ori lungimea unui cuvânt, însemnând 8 bytes = 64 biți și valoarea inițială 0 

    vect db 1,2,3,4,5 ; se definește un vector de 5 elemente de tip byte, elementele având valorile inițiale 1, 2, 3, 4 și 5 
    
    ; Valorile numerice pot fi specificate în binar, hexazecimal sau zecimal: 
    
    A db 05h ; se declară o variabilă A pe un byte, care conține valoarea 05h, h fiind sufixul pentru hexazecimal. 

    B db 5 ; se declară o variabile B pe un byte, care conține valoarea 5 în zecimal, deci este egală cu variabila A de mai sus. 

    C db 00000101b ; valoarea variabilei C este egală cu variabilele A și B declarate mai sus, doar ca valoarea ei a fost specificată în binar prin sufixul b

    ; Pentru a defini <n> elemente cu valoarea <x> se poate folosi sintaxa <n> DUP(<x>). De 
    ; exemplu, un vector de 5 elemente cu toate valorile inițiale 0, se poate defini: 
    vect db 5 dup(0) 

    ;Constantele se declară folosind cuvântul cheie EQU: 
    
    L EQU 10 
    PI EQU 3.1415 
    INT_DOS EQU 21h ; această constantă poate fi folosită pentru întreruperea INT 21h
