; 2. Scrieți un program care calculează valoarea următoarei funcții, pentru un număr x pe 8 biți, hardcodat  în  program  (declarat  ca  variabilă  sau  constantă  în  secțiune  .data).  
; Paritatea numărului se va verifica prin utilizarea instrucțiunilor de rotire prin carry și a instrucțiunilor de salt condiționat. 
; f(x) = x^2 + x + 5    if x par
; f(x) = x^3 - x        if x impar


.model small

.stack 100h

.data
    X    db 3

.code

main proc

                   MOV  AX, @data         ; load data
                   MOV  DS, AX
                   MOV  AL, X
                   RCR  AL, 1
                   JC   impar

    par:           
                   MOV  AL, X
                   MUL  AL
                   ADD  AL, X
                   ADD  AL, 5
                   JMP  final

    impar:         
                   MOV  AL, X
                   MOV  BL, X
                   MUL  AL
                   MOV  BH, 0
                   MUL  BX
                   MOV  BL, X
                   MOV  BH, 0
                   SUB  AX, BX

    final:         
                   MOV  AH, 0
                   CALL print_number
                   MOV  AH, 4Ch           ; exit program
                   INT  21h
main endp

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

end main