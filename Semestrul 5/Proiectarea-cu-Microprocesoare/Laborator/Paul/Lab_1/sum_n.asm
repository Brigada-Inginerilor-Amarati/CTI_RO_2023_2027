;2. Scrieți un program în limbajul de asamblare x86, care afișează pe ecran suma primelor N numere naturale, pentru un N pe 8 biți de valoare mică, hardcodat în program (declarat în secțiunea .data ca o variabilă sau o constantă).  

.model small

.stack 100h

.data
    N    DB 10
    S    DB 0

.code

main proc

                   mov  AX, @data         ; load data
                   mov  DS, AX

                   mov  DL, N             ; load N

                   mov  CH, 0             ; init counter
                   mov  CL, N

                   mov  BL, S             ; load S

    sum:           
                   add  BL, CL
                   loop sum

                   mov  DL, BL
                   call print_number

                   mov  AH, 4Ch           ; exit program
                   int  21h
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