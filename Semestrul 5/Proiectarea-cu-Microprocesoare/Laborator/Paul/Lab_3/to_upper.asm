; 1.  Scrieți un program în limbajul de asamblare x86 care citește un șir de caractere, format doar din litere mici, de la tastatură și afișează același șir scris doar cu litere mari.

.model small

.stack 100h

.data
    buffer  DB 100 DUP('$')                            ; Buffer pentru sir de caractere
    prompt  DB 'Introduceti un sir de caractere: $'
    newline DB 0Dh, 0Ah, '$'                           ; Carriage return + line feed
.code

main proc
                     CALL init
                
    ; Afiseaza prompt
                     MOV  AH, 9
                     MOV  DX, OFFSET prompt
                     INT  21h

    ; Citeste si converteste sirul
                     CALL read_and_convert

    ; Afiseaza newline
                     MOV  AH, 9
                     MOV  DX, OFFSET newline
                     INT  21h

    ; Afiseaza sirul cu litere mari
                     CALL print_string

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


read_and_convert proc
                     MOV  SI, OFFSET buffer     ; SI indica inceputul buffer-ului
                     MOV  CX, 0                 ; Contor pentru lungimea sirului

    read_loop:       
                     MOV  AH, 1                 ; Functie DOS: citeste caracter
                     INT  21h                   ; Rezultat in AL (afiseaza automat pe ecran)

                     CMP  AL, 0Dh               ; Verifica daca e Enter (carriage return)
                     JE   end_read              ; Daca da, termina citirea

    ; Converteste litera mica in litera mare
                     CMP  AL, 'a'               ; Verifica daca e >= 'a'
                     JB   store_char            ; Daca e < 'a', nu e litera mica
                     CMP  AL, 'z'               ; Verifica daca e <= 'z'
                     JA   store_char            ; Daca e > 'z', nu e litera mica
                     SUB  AL, 20h               ; Converteste in litera mare (a-A = 32 = 20h)

    store_char:      
                     MOV  [SI], AL              ; Stocheaza caracterul in buffer
                     INC  SI                    ; Trece la pozitia urmatoare
                     INC  CX                    ; Incrementeaza contorul
                     JMP  read_loop

    end_read:        
                     MOV  BYTE PTR [SI], '$'    ; Adauga terminator '$' pentru DOS
                     RET
read_and_convert endp


print_string proc
                     MOV  AH, 9                 ; Functie DOS: afiseaza sir
                     MOV  DX, OFFSET buffer     ; DX indica sirul
                     INT  21h                   ; Sirul trebuie sa se termine cu '$'
                     RET
print_string endp

end main