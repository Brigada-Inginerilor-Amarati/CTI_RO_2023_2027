.model small

.stack 100h

.data
    msg_a DB 'Introduceti a: $'
    msg_b DB 'Introduceti b: $'
    a DB 0
    b DB 0
    a_orig DB 0
    b_orig DB 0
    msg_cmmdc DB 'Cel mai mare divizor comun (cmmdc) este: $'
    msg_cmmmc DB 'Cel mai mic multiplu comun (cmmmc) este: $'
    cmmdc DB 0
    cmmmc DW 0

.code

main proc
                   MOV  AX, @data
                   MOV  DS, AX

                   ; Print "Introduceti a: "
                   LEA  DX, msg_a
                   MOV  AH, 09h
                   INT  21h

                   ; Read first number
                   CALL read_number
                   MOV  a, AL
                   MOV  a_orig, AL

                   ; Print newline
                   MOV  DL, 0Dh        ; carriage return
                   MOV  AH, 02h
                   INT  21h
                   MOV  DL, 0Ah        ; line feed
                   MOV  AH, 02h
                   INT  21h

                   ; Print "Introduceti b: "
                   LEA  DX, msg_b
                   MOV  AH, 09h
                   INT  21h

                   ; Read second number
                   CALL read_number
                   MOV  b, AL
                   MOV  b_orig, AL

                   ; Print newline
                   MOV  DL, 0Dh
                   MOV  AH, 02h
                   INT  21h
                   MOV  DL, 0Ah
                   MOV  AH, 02h
                   INT  21h

                   ; Calculate GCD using successive subtractions
                   MOV  AL, a
                   MOV  BL, b

    gcd_loop:      
                   CMP  AL, BL
                   JE   gcd_done
                   
                   CMP  AL, BL
                   JA   a_greater
                   
                   SUB  BL, AL
                   JMP  gcd_loop

    a_greater:     
                   SUB  AL, BL
                   JMP  gcd_loop

    gcd_done:      
                   MOV  cmmdc, AL

                   ; Print GCD message
                   LEA  DX, msg_cmmdc
                   MOV  AH, 09h
                   INT  21h

                   ; Print GCD
                   XOR  AH, AH
                   MOV  AL, cmmdc
                   CALL print_number

                   ; Print newline
                   MOV  DL, 0Dh
                   MOV  AH, 02h
                   INT  21h
                   MOV  DL, 0Ah
                   MOV  AH, 02h
                   INT  21h

                   ; Calculate LCM = (a * b) / gcd
                   XOR  AH, AH
                   MOV  AL, a_orig
                   MOV  BL, b_orig
                   MUL  BL
                   
                   MOV  BL, cmmdc
                   XOR  BH, BH
                   XOR  DX, DX
                   DIV  BX
                   MOV  cmmmc, AX

                   ; Print LCM message
                   LEA  DX, msg_cmmmc
                   MOV  AH, 09h
                   INT  21h

                   ; Print LCM
                   MOV  AX, cmmmc
                   CALL print_number

                   ; Print newline
                   MOV  DL, 0Dh
                   MOV  AH, 02h
                   INT  21h
                   MOV  DL, 0Ah
                   MOV  AH, 02h
                   INT  21h

                   MOV  AH, 4Ch
                   INT  21h
main endp

read_number proc
                   PUSH BX
                   PUSH CX
                   XOR  BX, BX         ; number

    read_loop:     
                   MOV  AH, 01h        ; DOS function to read character with echo
                   INT  21h
                   
                   CMP  AL, 0Dh        ; enter signal
                   JE   read_done   
                   
                   SUB  AL, 30h      
                   
                   ; BX = BX * 10 + digit
                   MOV  CL, AL         ; save digit
                   MOV  AX, BX
                   MOV  BX, 10
                   MUL  BX             ; AX = BX * 10
                   MOV  BX, AX
                   XOR  CH, CH
                   ADD  BX, CX         ; BX = BX + digit
                   
                   JMP  read_loop

    read_done:     
                   MOV  AX, BX       
                   POP  CX
                   POP  BX
                   RET
read_number endp

print_number proc
    ; Input: AX contains the number to print
                   PUSH CX
                   PUSH AX
                   MOV  CX, 0
                   MOV  BX, 10

    extract_digits:
                   XOR  DX, DX
                   DIV  BX
                   PUSH DX
                   INC  CX
                   CMP  AX, 0
                   JNZ  extract_digits

    print_digits:  
                   POP  DX
                   ADD  DL, 30h
                   MOV  AH, 02h
                   INT  21h
                   LOOP print_digits
                   POP  AX
                   POP  CX
                   RET
print_number endp

end main
