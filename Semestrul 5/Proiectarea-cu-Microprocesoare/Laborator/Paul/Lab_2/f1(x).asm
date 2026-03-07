;1. Scrieți un program care calculează valoarea următoarei funcții, pentru un număr x pe 8 biți, hardcodat  în  program  (declarat  ca  variabilă  sau  constantă  în  secțiune  .data).
;Paritatea numărului se va verifica prin împărțire la 2 și verificarea restului, folosind instrucțiunea DIV. 
; f(x) = x^2        if x par
; f(x) = x^3 / 3    if x impar

.model small

.stack 100h

.data
    X    db 7

.code

main proc

                   MOV  AX, @data         ; load data
                   MOV  DS, AX

                   MOV  AL, X
                   MOV  BL, 2
                   DIV  BL                ; AL = AX / BL     AH = AX % BL

                   CMP  AH, 0
                   JNZ  impar

    par:           
                   MOV  AL, X
                   MUL  AL
                   JMP  final

    impar:         
                   MOV  AL, X
                   CBW
                   MOV  BL, X
                   MUL  AX
                   MOV  BH, 0
                   MUL  BX
                   MOV  BX, 3
                   DIV  BX

    final:         
    ; Result is in AL (or AX if larger)
    ; Convert AL to AX for printing
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