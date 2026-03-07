dosseg

.model small

.stack 100h

.data
        A DB 0
        B DB 0
        C DB 0
        X DW 7                                          ; declararea variabilei X de tip word inițializată cu 7 
        n1 DB "Introduceti primul numar:$"
        n2 DB "Introduceti al doilea numar:$"
        n3 DB "Introduceti al treilea numar:$"
        result DB "Rezultatul este: $"

.code

new_line proc
        MOV AH, 2                        ; funcția DOS pentru afișarea unui caracter
        MOV DL, 10;                     ; codul ASCII pentru newline
        INT 21H                        ; apelarea întreruperii DOS
        ret                            ; returnează la adresa de după CALL
new_line endp

main proc

        MOV  AX, @data                  ; incarcarea segmentului de date în registrul AX

        MOV  DS, AX                     ; inițializarea registrului DS cu segmentul de date

        ; citirea primului numar 
        MOV AH, 9                       ; funcția DOS pentru afișarea unui mesaj
        MOV DX, OFFSET n1               ; incarcarea offset-ului mesajului n1 în registrul DX
        INT 21H                         ; apelarea întreruperii DOS
        MOV AH, 1                       ; funcția DOS pentru citirea unui caracter      
        INT 21H                         ; apelarea întreruperii DOS si afisarea caracterului la ecran

        MOV A, AL                       ; mutarea valorii citite in registrul A
        CALL new_line
        
        ; citirea celui de-al doilea numar
        MOV AH, 9                       ; funcția DOS pentru afișarea unui mesaj
        MOV DX, OFFSET n2               ; incarcarea offset-ului mesajului n2 în registrul DX
        INT 21H                         ; apelarea întreruperii DOS
        MOV AH, 1                       ; funcția DOS pentru citirea unui caracter      
        INT 21H                         ; apelarea întreruperii DOS si afisarea caracterului la ecran

        MOV B, AL                       ; mutarea valorii citite in registrul B
        CALL new_line
        
        ; citirea celui de-al treilea numar        
        MOV AH, 9                       ; funcția DOS pentru afișarea unui mesaj
        MOV DX, OFFSET n3               ; incarcarea offset-ului mesajului n3 în registrul DX
        INT 21H                         ; apelarea întreruperii DOS
        MOV AH, 1                       ; funcția DOS pentru citirea unui caracter      
        INT 21H                         ; apelarea întreruperii DOS si afisarea caracterului la ecran

        MOV C, AL                       ; mutarea valorii citite in registrul C
        CALL new_line
        
        ; afisarea rezultatului
        MOV AH, 9                       ; funcția DOS pentru afișarea unui mesaj
        MOV DX, OFFSET result
        INT 21H
        
        ; calcularea rezultatului
        MOV AL, A                       ; mutarea valorii din registrul A in registrul AL
        ADD AL, B                       ; adaugarea valorii din registrul B in registrul AL
        SUB AL, C                       ; scaderea valorii din registrul C in registrul AL
        
        ; afisarea rezultatului
        MOV AH, 2                       ; funcția DOS pentru afișarea unui caracter
        MOV DL, AL;                     ; rezultatul este copiat in registrul DL
        INT 21h                         ; apelarea întreruperii DOS si afisarea caracterului la ecran
        MOV AH, 4Ch                     ; funcția DOS pentru terminarea programului
        INT 21h                         ; apelarea întreruperii DOS si terminarea programului
main endp

end main