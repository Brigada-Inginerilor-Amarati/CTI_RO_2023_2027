; 1. Pornind de la programul Aritmetic1 dat ca exemplu, 
; scrieți un nou program care afișează pe ecran primii 7 termeni din seria Fibonacci, 
; considerând primii 3 termeni ca fiind: 0, 1, 1.
; Se va folosi întreruperea INT 21H doar pentru afișare, 
; adaugând 30h la fiecare cifră pe care doriți să o afișați, înainte de apelarea întreruperii.

dosseg
.model small
.stack 100h
.data
    anteprecedent DB 0
    precedent DB 1
    curent DB 1
    N DB 5
.code

; new_line proc
;     MOV AH, 2
;     MOV DL, 10;
;     INT 21H
;     ret
; new_line endp

; print_char proc
;     MOV AH, 2
;     MOV DL, AL
;     INT 21h
; print_char endp
print_number proc
                 add  dl, 30h
                 mov  ah, 02h
                 int  21h
                 call print_space
                 ret
print_number endp

print_space proc
                 mov  dl, ' '
                 mov  ah, 02h
                 int  21h
                 ret
print_space endp

main proc
    MOV AX, @data
    MOV DS, AX

    MOV AL, anteprecedent
    CALL print_char

    MOV AL, precedent
    CALL print_char

    MOV CX, N

    LBL_FOR:
        MOV AL, anteprecedent

        ADD AL, precedent
        ADD AL, 30h

       ;MOV curent, AL
        MOV AH, 2
        MOV DL, AL
        INT 21h
        ;CALL print_char

        MOV AL, precedent
        MOV anteprecedent, AL

        MOV AL, curent
        MOV precedent, AL

        LOOP LBL_FOR


    MOV AH, 4Ch;
    INT 21h; 

main endp
end main