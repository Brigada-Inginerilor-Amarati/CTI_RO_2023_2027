; . Scrieți un program care consideră 3 numere a, b și c hardcodate, reprezentând coeficienții
; ecuației de gradul II, 𝑎𝑥ଶ + 𝑏𝑥 + 𝑐 = 0, și calculează valoarea determinantului ∆ (delta).

dosseg
.model small
.stack 100h
.data
a db 1
b db 6
c db 3
b2 dw 0
ac dw 0 
delta db 0
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
MOV AX, @DATA ; copiere AX- in>Segmentul de date
MOV DS, AX  

MOV AH, 0 ; resetare AH
MOV AL, b
MUL b
; AX -> b^2

MOV b2, AX

MOV AH, 0
MOV AL, a
MUL c

MOV BL, 4
MUL BL

MOV ac, AX



MOV AX, b2
SUB AX, ac

CALL afisare_num



MOV AH, 4Ch
INT 21h



main endp
end main
