;Scrieți un program care calculează n! pentru n declarat în program, 2<=n<5.

dosseg
.model small
.stack 100h
.data
n db 4
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
MOV AX, @DATA ; copiere AX->Segmentul de date
MOV DS, AX  
MOV CH, 0
MOV CL, n
MOV AX, 1

LOOP_N:
MOV BL, CL
CMP CL, 1
JZ DONE
MUL BL

LOOP LOOP_N



DONE:
CALL afisare_num
MOV AH, 4Ch
INT 21h



main endp
end main
