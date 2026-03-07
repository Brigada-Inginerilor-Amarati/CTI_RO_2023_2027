dosseg
.model small;
.stack 100h
.data
    A DB 0
    B DB 0
    C DB 0
    X DW 7
    n1 DB "Introduceti primul numar:$"
    n2 DB "Introduceti al doilea numar:$"
    n3 DB "Introduceti al treilea numar:$"
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
    MOV A, AL
    CALL new_line
    ;
    MOV AH, 9
    MOV DX, OFFSET n2
    INT 21H
    MOV AH, 1
    INT 21H
    SUB AL, 30H
    MOV B, AL
    CALL new_line
    ;
    MOV AH, 9
    MOV DX, OFFSET n3
    INT 21H
    MOV AH, 1
    INT 21H
    SUB AL, 30H
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
    ADD AL, C
    ;
    ADD AL, 30H
    MOV AH, 2;
    MOV DL, AL;
    INT 21h
    MOV AH, 4Ch;
    INT 21h;
    main endp;
end main