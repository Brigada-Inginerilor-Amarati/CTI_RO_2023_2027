dosseg
.model small
.stack 100h
.data

fibo db 0,1,1,0,0,0,0   ; 7 valori

.code

space proc
MOV AH, 2
MOV DL, 32
INT 21h
ret
space endp


main proc
MOV AX, @data       ; load DATA in AX
MOV DS, AX              ; mutam AX in data segment
LEA SI, fibo     
; afiseaza 0

MOV AH, 2
MOV DL, [SI]
ADD DL, 30h
INT 21h
CALL space

MOV AH, 2
MOV DL, [SI +1]
ADD DL, 30h
INT 21h
CALL space

MOV AH, 2
MOV DL, [SI +2]
ADD DL, 30h
INT 21h
CALL space

MOV CX, 4               ; mutam numarul 3 in counter
   ;  bagam in source index adresas primului element din fibo
add si, 3               ; mergem la indexul 3
MOV AH, 2


LOOP_FIBO:
     mov AL, [si]   ; bagam in AL memoria de la index
     ADD AL, [si-1]
     ADD AL, [si-2]
     MOV [si], AL
     MOV DL, [si]
     ADD DL, 30h
     INT 21h
     CALL space
     ADD si, 1
    loop LOOP_FIBO
    
MOV AH, 4Ch
INT 21h
main endp
end main