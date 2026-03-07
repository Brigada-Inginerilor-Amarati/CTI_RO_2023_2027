dosseg
.model small
.stack 100h
.data

N DB 14
max EQU 100
fibo DB max DUP(?)
count DB 0
vector_imp DB max DUP(?)
count_imp DB 0

msg1 db "Numerele fibonnaci: $"
msg2 db "Numerele impare: $"

.code

afisare_num proc
PUSH AX
PUSH BX
PUSH DX
PUSH CX


MOV BX, 10
XOR CX, CX 

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

    POP CX
    POP DX
    POP BX
    POP AX
    RET
afisare_num endp


space proc
MOV AH, 2
MOV DL, 32
INT 21h
ret
space endp


new_line proc
MOV AH, 2
MOV DL, 10
INT 21h
ret
new_line endp

main proc
MOV AX, @data       ; load DATA in AX
MOV DS, AX              ; mutam AX in data segment
LEA SI, fibo
; afiseaza 0


MOV AH, 09h
MOV DX, OFFSET msg1
INT 21h

MOV AH, 0

MOV BYTE PTR [si], 0
MOV AH, 2
MOV DL, [si]
ADD DL, '0'
INT 21h
INC SI
CALL space
MOV BYTE PTR[si], 1
MOV AH, 2
MOV DL, [si]
ADD DL, '0'
INT 21h
INC SI
CALL space
MOV  BYTE PTR[si], 1
MOV AH, 2
MOV DL, [si]
ADD DL, '0'
INT 21h
INC SI
CALL space


MOV CH, 0
MOV CL, N         ; mutam numarul 3 in counter
   ;  bagam in source index adresas primului element din fibo
SUB CL, 3
MOV count_imp, 0
LEA DI, vector_imp


LOOP_FIBO:
     MOV AH, 0
     mov AL, [si]   ; bagam in AL memoria de la index
     ADD AL, [si-1]
     ADD AL, [si-2]
     MOV [si], AL
     MOV DL, [si]
     
     MOV AL, [si]
     TEST AL, 1
     JZ CONTINUE
     MOV [DI], AL
     INC DI
     INC count_imp
     
   
     
     CONTINUE:
    MOV AL, [si]
    MOV AH, 0

    CALL afisare_num
    CALL space
    

   
    
    
    INC SI
     
    loop LOOP_FIBO
     
     
     
 CALL new_line
     MOV CH, 0
     MOV CL, count_imp
     
     MOV AH, 09h
MOV DX, OFFSET msg2
INT 21h

LOOP_IMP:
    SUB DI, CX
    MOV AL, [DI]
    MOV AH, 0
    CALL afisare_num
    CALL space
    ADD DI, CX
    LOOP LOOP_IMP

 
 
     
    
MOV AH, 4Ch
INT 21h
main endp
end main⏎   
    