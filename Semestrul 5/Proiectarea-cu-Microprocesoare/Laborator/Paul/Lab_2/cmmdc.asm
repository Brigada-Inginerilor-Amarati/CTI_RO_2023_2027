; 3.  Scrieți  un  program  care  calculează  cel  mai  mare  divizor  comun  (cmmdc)  prin  scăderi succesive pentru două numere pe câte 8 biți, a și b, hardcodate în program.
; La final, calculați și cel mai mic multiplu comun (cmmmc) al celor două numere. 
; Algoritmul în C de la care puteți pleca este:
; while (a != b) { 
;       If (a > b)  
;             a = a – b; 
;       else  
;            b = b – a; 
;         } 
;cmmdc = a; 
;cmmmc = (a * b) / cmmdc;

.model small

.stack 100h

.data
    A     DB 10
    B     DB 15
    A_ORIG DB 0
    B_ORIG DB 0
    CMMDC DB 0
    CMMMC DB 0
.code

main proc
                   CALL init
                   CALL compute_cmmdc

                   MOV  AX, 0
                   MOV  AL, CMMDC
                   CALL print_number

                   MOV  AH, 02h
                   MOV  DL, ' '           ; space character
                   INT  21h

                   MOV  AX, 0
                   MOV  AL, CMMMC
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


compute_cmmdc proc
    ; Save original values for CMMMC calculation
                   MOV  AL, A
                   MOV  A_ORIG, AL
                   MOV  AL, B
                   MOV  B_ORIG, AL

    start_loop:
                   MOV  AL, A
                   MOV  BL, B
                   CMP  AL, BL
                   JZ   finish_cmmdc
                   JGE  a_greater
    b_greater:
                   MOV  AL, B
                   MOV  BL, A
                   SUB  AL, BL
                   MOV  B, AL
                   LOOP start_loop
    a_greater:
                   MOV  AL, A
                   MOV  BL, B
                   SUB  AL, BL
                   MOV  A, AL
                   LOOP start_loop
    finish_cmmdc:
                   MOV  CMMDC, AL
                   MOV  AL, A_ORIG
                   MOV  BL, B_ORIG
                   MUL  BL
                   MOV  BL, CMMDC
                   DIV  BL
                   MOV  CMMMC, AL

                   RET

compute_cmmdc endp

end main