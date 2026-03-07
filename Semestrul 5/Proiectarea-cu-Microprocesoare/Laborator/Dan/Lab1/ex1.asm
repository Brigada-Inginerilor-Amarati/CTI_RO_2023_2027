;1. Pornind de la programul Aritmetic1 dat ca exemplu, scrieți un nou program care afișează pe
;ecran primii 7 termeni din seria Fibonacci, considerând primii 3 termeni ca fiind: 0, 1, 1. Se
;va folosi întreruperea INT 21H doar pentru afișare, adaugând 30h la fiecare cifră pe care doriți
;să o afișați, înainte de apelarea întreruperii

dosseg
.model small ; prin această instrucțiune se selectează modelul de memorie folosit
.stack 100h ;declararea segmentului stivă
.data ; reprezintă secțiunea de declarare a datelor
    f1 DB 0
    f2 DB 1
.code ; reprezintă secțiunea în care se scrie codul sursă al programului
new_line proc
    MOV AH, 02h
    MOV DL, 10 ; valoarea hexa 0x0A (în zecimal 10) corespunde codului ASCII al caracterului special LF – line feed, corespunzător lui '\n' (new line character) din C
    INT 21H
    ret
new_line endp
print_number proc
    mov ah, 02h       ; print char function
    add dl, 30h
    int 21h
    call new_line
    ret
print_number endp
main proc ; proc este cuvântul cheie pentru începerea unei proceduri
    MOV AX, @data ; instrucțiuni implicite pentru încărcarea segmentului de date
    MOV DS, AX

    MOV DL, f1
    call print_number

    MOV DL, f2
    call print_number

    MOV BL, f1
    MOV BH, f2

    mov CL, 5

fib_loop:
    MOV DL, BL
    ADD DL, BH
    MOV CH, DL
    call print_number

    MOV DL, CH
    MOV BL, BH
    MOV BH, DL
    DEC CL
    JNZ fib_loop

    MOV AH, 4Ch
    INT 21h    
main endp ; endp este cuvântul cheie care semnifică finalul unei proceduri
end main