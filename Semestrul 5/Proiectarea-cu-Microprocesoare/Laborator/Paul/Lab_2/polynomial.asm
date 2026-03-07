; 5. Scrieți un program care consideră 3 numere a, b și c hardcodate, reprezentând coeficienții ecuației de gradul II, 𝑎𝑥ଶ +𝑏𝑥+𝑐 =0, și calculează valoarea determinantului ∆ (delta).
; ∆ = b*b - 4*a*c
.model small

.stack 100h

.data
    A     DB 1
    B     DB 6
    C     DB 9
    DELTA DW 0
.code


main proc
                   CALL init
                   CALL compute_delta
                   CALL print_number
                   CALL finish
main endp


init proc
                   MOV  AX, @data
                   MOV  DS, AX
                   RET
init endp


finish proc
                   MOV  AH, 4Ch
                   INT  21h
                   RET
finish endp


print_number proc
    ; Input: AX contains the number to print
    ; Destroys: AX, BX, CX, DX
                   PUSH CX
                   MOV  CX, 0             ; digit counter
                   MOV  BX, 10            ; divisor

    extract_digits:
                   MOV  DX, 0             ; clear DX for division
                   DIV  BX                ; AX = AX / 10, DX = AX % 10
                   PUSH DX                ; save digit on stack
                   INC  CX                ; increment digit count
                   CMP  AX, 0             ; check if more digits remain
                   JNZ  extract_digits    ; if yes, continue

    print_digits:  
                   POP  DX                ; get digit from stack
                   ADD  DL, 30h           ; convert to ASCII
                   MOV  AH, 02h           ; DOS print character function
                   INT  21h
                   LOOP print_digits      ; repeat for all digits
                   POP  CX
                   RET
print_number endp


compute_delta proc
                   MOV  AL, A
                   MOV  BL, C
                   MUL  BL                ; compute A*C
                   MOV  BL, 4
                   MUL  BL                ; compute 4*A*C
                   MOV  DELTA, AX         ; store 4*A*C in DELTA

                   MOV  AL, B
                   MOV  BL, B
                   MUL  BL                ; load B*B in AX
                   SUB  AX, DELTA         ; compute B*B - 4*A*C

                   RET
compute_delta endp

end main