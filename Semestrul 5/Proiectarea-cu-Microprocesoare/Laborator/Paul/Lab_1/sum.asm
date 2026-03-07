.model small ; prin această instrucțiune se selectează modelul de memorie folosit 
.stack 100h ;declararea segmentului stivă 
.data                                              ; reprezintă secțiunea de declarare a datelor
    A      DB 0
    B      DB 0
    C      DB 0
    D      DB 0
    X      DW 7
    n1     DB "Introduceti primul numar:$"
    n2     DB "Introduceti al doilea numar:$"
    n3     DB "Introduceti al treilea numar:$"
    n4     DB "Introduceti al patrulea numar:$"
    result DB "Rezultatul este:$"

.code                                        ; reprezintă secțiunea în care se scrie codul sursă al programului

main proc                                    ; proc este cuvântul cheie pentru începerea unei proceduri
                   MOV  AX, @data            ; instrucțiuni implicite pentru încărcarea segmentului de date
                   MOV  DS, AX
    ; citirea primului număr de la tastatură
                   MOV  AH, 9
                   MOV  DX, OFFSET n1
                   INT  21h
                   MOV  AH, 1                ; serviciu de citire asociat întreruperii INT 21H – Keyboard input with echo
                   INT  21H
                   SUB  AL, 30h
                   MOV  A, AL
                   CALL new_line
    ; citirea celui de-al doilea număr de la tastatură
                   MOV  AH, 9
                   MOV  DX, OFFSET n2
                   INT  21h
                   MOV  AH, 1
                   INT  21H
                   SUB  AL, 30h
                   MOV  B, AL
                   CALL new_line
    ; citirea celui de-al treilea număr de la tastatură
                   MOV  AH, 9
                   MOV  DX, OFFSET n3
                   INT  21h
                   MOV  AH, 1
                   INT  21H
                   SUB  AL, 30h
                   MOV  C, AL
                   CALL new_line
    ; citirea celui de-al patrulea număr de la tastatură
                   MOV  AH, 9
                   MOV  DX, OFFSET n4
                   INT  21h
                   MOV  AH, 1
                   INT  21H
                   SUB  AL, 30h
                   MOV  D, AL
                   CALL new_line
    ; afisarea liniei “Rezultatul este:” pe ecran
                   MOV  AH, 9
                   MOV  DX, OFFSET result
                   INT  21h
    ; calculul sumei A + B
                   MOV  AH,0
                   MOV  AL, A                ; primul număr A este mutat în registrul AL pe 8 biți
                   ADD  AL, B                ; rezultatul sumei A+B se află în registrul AL pe 8 biți
    ; adunarea lui C din rezultat
                   ADD  AL, C
    ; adunarea lui D din rezultat
                   ADD  AL, D
    ; afișarea rezultatului pe ecran
                   CALL print_number
                   MOV  AH, 4Ch
                   INT  21h
main endp                                    ; endp este cuvântul cheie care semnifică finalul unei proceduri

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

new_line proc
                   MOV  AH, 2
                   MOV  DL,  10              ;  valoarea  hexa  0x0A  (în  zecimal  10)  corespunde  codului  ASCII  al caracterului special LF – line feed, corespunzător lui ‘\n’ (new line character) din C
                   INT  21H
                   ret
new_line endp


end main