dosseg
.model small
.stack 100h

.data

x DB 0

msg1 db "Numarul este par: $"
msg2 db "Numarul este impar: $"

.code
; salvam registre pe stiva pentru afisare numar 16 biti
afisare_num proc
PUSH AX
PUSH BX
PUSH DX
PUSH CX

MOV CX, 0
MOV BX, 10

stack_convert_loop:
XOR DX, DX
DIV BX
PUSH DX
INC CX
CMP AX, 0
JNE stack_convert_loop


print_loop:
POP DX
ADD DL, 30h
MOV AH, 2
INT 21h
LOOP print_loop

    POP DX
    POP CX
    POP BX
    POP AX
    RET
afisare_num endp

; metoda citire numar
read proc
MOV AH, 01h ; AH, 01H apeleaza citirea de la tastatura cu echo
INT 21h
SUB AL, 30h
MOV x, AL
ret
read endp

afisare proc
MOV AH, 2
MOV AL, x
ADD AL, 30h
MOV DL, AL
INT 21h
ret
afisare endp

new_line proc
MOV AH, 2
MOV DL, 10
INT 21h
ret
new_line endp

main proc
MOV AX, @DATA
MOV DS, AX

CALL read
CALL new_line
CALL afisare
CALL new_line


;aflare paritate
MOV AL, x
MOV AH, 0
MOV BL, 2
DIV BL

CMP AH, 0
JE X_2 ; numarul este par -> x^2
JMP X_3


X_3: ; numarul este impar -> x^3/3
MOV AH, 09h
MOV DX, OFFSET msg2
INT 21H
MOV AL, x
CBW
MUL AX        
MOV BX, x
MOV BH, 0
MUL BX       
MOV CX, 3
DIV CX        
CALL afisare_num
JMP FINAL


X_2:
MOV AH, 09h
MOV DX, OFFSET msg1
INT 21H
MOV AL, x
MUL AL
CALL afisare_num


FINAL:
MOV AH, 4Ch
INT 21h

main endp
end main
