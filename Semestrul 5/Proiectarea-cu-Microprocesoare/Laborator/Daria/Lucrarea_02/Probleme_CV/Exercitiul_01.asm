;1. Scrieți un program care calculează valoarea următoarei funcții, pentru un număr x pe 8 biți, 
;hardcodat  în  program  (declarat  ca  variabilă  sau  constantă  în  secțiune  .data).
;Paritatea numărului se va verifica prin împărțire la 2 și verificarea restului, folosind instrucțiunea DIV. 
; f(x) = x^2        if x par
; f(x) = x^3 / 3    if x impar

dosseg

.model small;

.stack 100h

; aici se initializeaza
.data

        X DB 4                                  ; numarul x hardcodat
        RESULT DB 0                             ; variabila pentru rezultat
        
        msg_x DB "x = $"
        msg_par DB "x este par$"
        msg_impar DB "x este impar$"
        msg_result DB "f(x) = $"
        
;aici cod
.code 

; Procedura pentru linie noua
new_line proc
        MOV AH, 2
        MOV DL, 13                              ; Carriage Return
        INT 21H
        MOV DL, 10                              ; Line Feed
        INT 21H
        ret
new_line endp

; Procedura pentru afisarea unui numar
; Input: AX = numarul de afisat
print_number proc
        PUSH CX
        PUSH BX
        PUSH AX
        MOV CX, 0                               ; contor pentru cifre
        MOV BX, 10                              ; baza 10

extract_digits:
        XOR DX, DX                              ; curatam DX pentru DIV
        DIV BX                                  ; AX = AX / 10, DX = AX % 10
        PUSH DX                                 ; salvam cifra pe stiva
        INC CX                                  ; incrementam contorul
        CMP AX, 0                               ; verificam daca mai avem cifre
        JNZ extract_digits                      ; daca da, continuam

print_digits:
        POP DX                                  ; extragem cifra din stiva
        ADD DL, 30h                             ; convertim in ASCII ('0' = 30h)
        MOV AH, 02h                             ; functia DOS pentru afisare caracter
        INT 21H
        LOOP print_digits                       ; repetam pentru toate cifrele
        
        POP AX
        POP BX
        POP CX
        ret
print_number endp

main proc
        MOV AX, @data
        MOV DS, AX

        ; Afisare mesaj pentru x
        MOV AH, 9
        MOV DX, OFFSET msg_x
        INT 21H
        XOR AH, AH
        MOV AL, X
        CALL print_number
        CALL new_line

        MOV AL, X                               ; incarcam x in AL
        MOV BL, 2                               ; divisorul pentru paritate

        XOR AH, AH                              ; curatam AH pentru DIV

        DIV BL                                  ; AL = AL / 2, AH = AL % 2

        CMP AH, 0                               ; verificam restul
        JE EVEN                                 ; daca restul e 0, x e par
        
        ; x impar
        MOV AH, 9
        MOV DX, OFFSET msg_impar
        INT 21H
        CALL new_line
        
        MOV AL, X                               ; reincarcam x in AL
        MOV BL, AL                              ; copiem x in BL pentru inmultire
        MUL BL                                  ; AL = x * x
        MOV BL, X                               ; reincarcam x in BL
        MUL BL                                  ; AL = x^2 * x = x^3
        MOV BL, 3                               ; pregatim impartirea la 3
        XOR AH, AH                              ; curatam AH pentru DIV
        DIV BL                                  ; AL = x^3 / 3

        JMP STORE_RESULT

EVEN:
        MOV AH, 9
        MOV DX, OFFSET msg_par
        INT 21H
        CALL new_line
        
        MOV AL, X                               ; reincarcam x in AL
        MOV BL, AL                              ; copiem x in BL pentru inmultire
        MUL BL                                  ; AL = x * x = x^2

STORE_RESULT:
        MOV RESULT, AL                         ; salvam rezultatul
        
        ; Afisare rezultat
        MOV AH, 9
        MOV DX, OFFSET msg_result
        INT 21H
        XOR AH, AH
        MOV AL, RESULT
        CALL print_number
        CALL new_line
        
        MOV AX, 4C00h                           ; terminare program
        INT 21h

main endp

end main

