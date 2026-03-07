; 6. Scrieți un program care calculează n! pentru n declarat în program, 2<=n<5.

.model small

.stack 100h

.data
    N         DB 5
    FACTORIAL DW 1
.code

main proc
                      CALL init
                      CALL compute_factorial
                      MOV  AX, FACTORIAL
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
                      MOV  CX, 0                ; digit counter
                      MOV  BX, 10               ; divisor

    extract_digits:   
                      MOV  DX, 0                ; clear DX for division
                      DIV  BX                   ; AX = AX / 10, DX = AX % 10
                      PUSH DX                   ; save digit on stack
                      INC  CX                   ; increment digit count
                      CMP  AX, 0                ; check if more digits remain
                      JNZ  extract_digits       ; if yes, continue

    print_digits:     
                      POP  DX                   ; get digit from stack
                      ADD  DL, 30h              ; convert to ASCII
                      MOV  AH, 02h              ; DOS print character function
                      INT  21h
                      LOOP print_digits         ; repeat for all digits
                      POP  CX
                      RET
print_number endp


compute_factorial proc
                      MOV  CL, N
                      MOV  AX, FACTORIAL
    loop_factorial:   
                      MUL  CL
                      LOOP loop_factorial
                      MOV  FACTORIAL, AX
                      RET
compute_factorial endp

end main