;2. Scrieți un program în limbajul de asamblare x86, care afișează pe ecran suma primelor N 
;numere naturale, pentru un N pe 8 biți de valoare mică, hardcodat în program (declarat în 
;secțiunea .data ca o variabilă sau o constantă). 

dosseg
.model small
.stack 100h
.data
    N EQU 12
    iter DB 0
    sum DB 0
.code
new_line proc
    MOV AH, 02h
    MOV DL, 10
    INT 21H
    ret
new_line endp

print_number proc
    push ax
    push bx
    push cx
    push dx

    mov ax, 0
    mov al, dl       ; AL = number to print
    mov cx, 0        ; digit count

    ; Convert to decimal digits (reverse order)
convert_loop:
    mov bl, 10
    div bl           ; AL / 10 → AL = quotient, AH = remainder
    push ax          ; save quotient+remainder
    mov ah, 0
    inc cx
    test al, al
    jnz convert_loop

    ; Print digits (reverse the order from stack)
print_loop:
    pop ax
    mov dl, ah
    add dl, '0'
    mov ah, 02h
    int 21h
    loop print_loop

    call new_line

    pop dx
    pop cx
    pop bx
    pop ax
    ret
print_number endp

main proc
    MOV AX, @data
    MOV DS, AX

    MOV BL, iter
    MOV CL, sum

inc_loop:
    ADD CL, BL
    CMP BL, N
    JE finished
    INC BL
    JMP inc_loop

finished:
    MOV DL, CL
    call print_number
    MOV AH, 4Ch
    INT 21h
main endp
end main