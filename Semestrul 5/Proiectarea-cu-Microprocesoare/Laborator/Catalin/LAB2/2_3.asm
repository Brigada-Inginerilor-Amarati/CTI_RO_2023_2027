dosseg
.model small
.stack 100h
.data

a db 10
b db 5
cmmdc db ?
cmmmc db ?
mult db ?

.code

new_line proc
MOV AH, 2
MOV DL, 10
INT 21h
ret
new_line endp

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

main proc
mov AX, @DATA
mov DS, AX

MOV AL, a
MOV BL, b

main_loop:
CMP AL, BL
JE FINAL
JL BIGGER
SUB AL, BL
JMP main_loop


BIGGER:
SUB BL, AL
JMP main_loop


FINAL:
MOV AH, 0
MOV cmmdc, AL

MOV AL, cmmdc

CALL afisare_num
CALL new_line


MOV AL, a
MOV AH, 0
MOV BX, b
MUL BL
MOV BL, cmmdc
DIV BL
CALL afisare_num
CALL new_line


MOV AH, 4Ch
INT 21h


main endp
end main