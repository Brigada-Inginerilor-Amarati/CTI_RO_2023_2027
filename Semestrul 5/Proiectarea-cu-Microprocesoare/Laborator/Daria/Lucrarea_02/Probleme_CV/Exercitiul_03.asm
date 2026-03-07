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
    a DB 20
    b DB 16
    a_orig DB ?
    b_orig DB ?
    cmmdc DB ?
    cmmmc DW ?

.code

main proc

                   MOV  AX, @data         ; load data
                   MOV  DS, AX            

                   MOV  AL, a
                   MOV  a_orig, AL
                   MOV  AL, b
                   MOV  b_orig, AL

                   MOV  AL, a
                   MOV  BL, b

    gcd_loop:      
                   CMP  AL, BL            ; while (a != b)
                   JE   gcd_done
                   
                   CMP  AL, BL            ; if (a > b)
                   JA   a_greater
                   
                   SUB  BL, AL            ; else: b = b - a
                   JMP  gcd_loop

    a_greater:     
                   ; a = a - b
                   SUB  AL, BL
                   JMP  gcd_loop

    gcd_done:      
                   MOV  cmmdc, AL         ; cmmdc = a

                   ; cmmdc
                   XOR  AH, AH
                   CALL print_number

                   ; space
                   MOV  DL, ' '
                   MOV  AH, 02h
                   INT  21h

                   ;  CMMMC = (a * b) / cmmdc
                   XOR  AH, AH
                   MOV  AL, a_orig
                   MOV  BL, b_orig
                   MUL  BL               
                   
                   MOV  BL, cmmdc
                   XOR  BH, BH       
                   XOR  DX, DX           ; asta trb sa fie 0 ca daca avem resturi de la operatiile anterioare ne iese rez gresit
                   DIV  BX               
                   MOV  cmmmc, AX

                   ; cmmmc
                   MOV  AX, cmmmc
                   CALL print_number

                   MOV  AH, 4Ch           ; exit program
                   INT  21h
main endp

print_number proc
    ; Input: AX contains the number to print
    ; Destroys: AX, BX, CX, DX
                   PUSH CX
                   PUSH AX
                   MOV  CX, 0             ; digit counter
                   MOV  BX, 10            ; divisor

    extract_digits:
                   XOR  DX, DX            ; clear DX for division
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
                   POP  AX
                   POP  CX
                   RET
print_number endp

end main