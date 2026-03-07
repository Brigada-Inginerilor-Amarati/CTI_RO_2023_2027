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

main proc;
        MOV  AX, @data;
        MOV  DS, AX;
        MOV AH, 9
        MOV DX, OFFSET n1
        INT 21H
        MOV AH, 1;
        INT 21H
        MOV A, AL
        CALL new_line
        ;
        MOV AH, 9
        MOV DX, OFFSET n2
        INT 21H
        MOV AH, 1
        INT 21H
        MOV B, AL
        CALL new_line
        ;
        MOV AH, 9
        MOV DX, OFFSET n3
        INT 21H
        MOV AH, 1
        INT 21H
        MOV C, AL
        CALL new_line
        ;
        MOV AH, 9
        MOV DX, OFFSET result
        INT 21H
        ;
        MOV AL, A
        ADD AL, B
        ;
        SUB AL, C
        ;
        MOV AH, 2;
        MOV DL, AL;
        INT 21h
        MOV AH, 4Ch;
        INT 21h;
        main endp;

end main