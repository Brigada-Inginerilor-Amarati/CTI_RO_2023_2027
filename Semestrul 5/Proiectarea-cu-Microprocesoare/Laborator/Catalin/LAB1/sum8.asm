dosseg
.model small
.stack 100h
.data

n DB 10
suma DB 0
buffer db '00$'

.code
main proc

MOV AX, @DATA
MOV DS, AX

MOV AL, n
MOV CL, AL

LOOP_SUMA:
    MOV AL, n
    ADD [suma], AL
    SUB [n], 1
loop LOOP_SUMA

MOV AL, [suma]
xor ah, ah
mov bl, 10
div bl

add al, 30h
mov [buffer], al

add ah, 30h
mov [buffer+1], ah

mov dx, offset buffer
mov ah, 9
int 21h

 mov ah, 4Ch
    int 21h
main endp
end main