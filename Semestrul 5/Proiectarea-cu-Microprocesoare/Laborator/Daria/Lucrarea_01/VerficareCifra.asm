; A - B + C - D
; verificare daca nr introdus este cifra
dosseg
.model small;
.stack 100h
.data
    A DB 0
    B DB 0
    C DB 0
    D DB 0
    X DW 7
    n1 DB "Introduceti primul numar:$"
    n2 DB "Introduceti al doilea numar:$"
    n3 DB "Introduceti al treilea numar:$"
    n4 DB "Introduceti al patrulea numar:$"
    invalid_character_string DB "Nu este cifra.$"
    result DB "Rezultatul este: $"
.code;

new_line proc
    MOV AH, 2
    MOV DL, 10;
    INT 21H
    ret
new_line endp

main proc;
    MOV  AX, @data;
    MOV  DS, AX;
    MOV AH, 9
    MOV DX, OFFSET n1
    INT 21H
    MOV AH, 1;
    INT 21H
    SUB AL, 30H
    CMP AL, 9
    JG invalid_character
    MOV A, AL
    CALL new_line
    ;

    MOV AH, 9
    MOV DX, OFFSET n2
    INT 21H
    MOV AH, 1
    INT 21H
    SUB AL, 30H
    CMP AL, 9
    JG invalid_character
    MOV B, AL
    CALL new_line
    ;

    MOV AH, 9
    MOV DX, OFFSET n3
    INT 21H
    MOV AH, 1
    INT 21H
    SUB AL, 30H
    CMP AL, 9
    JG invalid_character
    MOV C, AL
    CALL new_line
    ;

    MOV AH, 9
    MOV DX, OFFSET n4
    INT 21H
    MOV AH, 1
    INT 21H
    SUB AL, 30H
    CMP AL, 9
    JG invalid_character
    MOV D, AL
    CALL new_line
    ;

    MOV AH, 9
    MOV DX, OFFSET result
    INT 21H
    ;
    MOV AL, A
    SUB AL, B
    ;
    ADD AL, C
    ;
    SUB AL, D
    ;
    ADD AL, 30H

    MOV AH, 2;
    MOV DL, AL;
    INT 21h
    MOV AH, 4Ch;
    INT 21h;

    invalid_character: CALL new_line
    MOV AH,9
    MOV DX, OFFSET invalid_character_string
    INT 21H

main endp;
end main