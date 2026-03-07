; 4. Scrieți un program care calculează primii N termeni ai seriei Fibonacci (0 1 1 2 3 5 ...),  pentru un număr N hardcodat în program, însă salvează într-un vector doar termenii care sunt  numere impare: 1 1 3 5 13 21 55 89 233... .

.model small

.stack 100h

.data
    N         EQU 20
    vec       DW  N DUP(0)
    odd_count DW  ?
.code

main proc
                      CALL init
                      CALL compute_fibonacci
                      CALL print_vector
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

compute_fibonacci proc

                      MOV  vec[0], 1
                      MOV  vec[2], 1

                      MOV  SI, 4
                      MOV  DI, 2
                      MOV  CX, N
                      SUB  CX, 2

                      MOV  AX, 1
                      MOV  BX, 1

    fib_loop:         
    
                      MOV  DX, AX
                      ADD  DX, BX

   
                      TEST DX, 1
                      JZ   skip_even

    
                      MOV  vec[SI], DX
                      ADD  SI, 2
                      INC  DI

    skip_even:        
                      MOV  AX, BX
                      MOV  BX, DX

                      LOOP fib_loop

                      MOV  odd_count, DI
                      RET
compute_fibonacci endp

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

print_vector proc
                      MOV  SI, 0                ; Index into array (SI = 0, 2, 4, ... for words)
                      MOV  CX, odd_count        ; Loop counter (number of odd elements stored)
    
    print_loop:       
                      MOV  AX, vec[SI]          ; Load word from array
    
    ; Print the number in AX
                      CALL print_number
    
    ; Print space or newline separator
                      MOV  AL, A
                      MOV  BL, B
    
                      ADD  SI, 2                ; Move to next word (words are 2 bytes)
                      LOOP print_loop
    
                      RET
print_vector endp

end main