; 2.  Scrieți un program care citește, pe rând, două șiruri de caractere de la tastatură și le salvează în două variabile msg1 și msg2. Finalul fiecărui șir de caractere va fi semnalat prin caracterul special $, care va fi salvat pe ultima poziție din fiecare șir. Programul va crea și va afișa pe ecran un nou șir obținut prin concatenarea celor două.

.model small

.stack 100h

.data
    buffer_a      DB 100 DUP('$')                            ; Buffer pentru sir de caractere
    buffer_b      DB 100 DUP('$')                            ; Buffer pentru sir de caractere
    buffer_concat DB 100 DUP('$')                            ; Buffer pentru sir de caractere
    prompt        DB 'Introduceti un sir de caractere: $'
    newline       DB 0Dh, 0Ah, '$'                           ; Carriage return + line feed
.code

main proc
                  CALL init

                  MOV  SI, OFFSET prompt
                  CALL print_string

                  MOV  SI, OFFSET buffer_a
                  CALL read_string

                  MOV  SI, OFFSET prompt
                  CALL print_string

                  MOV  SI, OFFSET buffer_b
                  CALL read_string

                  CALL concat
                  CALL print_newline
                  
                  MOV  SI, OFFSET buffer_concat
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


read_string proc
                     
                  MOV  CX, 0                       ; Contor pentru lungimea sirului

    read_loop:    
                  MOV  AH, 1                       ; Functie DOS: citeste caracter
                  INT  21h                         ; Rezultat in AL (afiseaza automat pe ecran)

                  CMP  AL, 0Dh                     ; Verifica daca e Enter (carriage return)
                  JE   end_read                    ; Daca da, termina citirea

                  MOV  [SI], AL                    ; Stocheaza caracterul in buffer
                  INC  SI                          ; Trece la pozitia urmatoare
                  INC  CX                          ; Incrementeaza contorul
                  JMP  read_loop

    end_read:     
                  MOV  BYTE PTR [SI], '$'          ; Adauga terminator '$' pentru DOS
                  RET
read_string endp


print_string proc
                  MOV  AH, 9                       ; Functie DOS: afiseaza sir
                  MOV  DX, SI                      ; DX indica sirul
                  INT  21h                         ; Sirul trebuie sa se termine cu '$'
                  RET
print_string endp


print_newline proc
    ; Afiseaza newline
                  MOV  AH, 9
                  MOV  DX, OFFSET newline
                  INT  21h
                  RET
print_newline endp


concat proc
    ; Copiere buffer_a in buffer_concat
                  MOV  SI, OFFSET buffer_a         ; SI = sursa (buffer_a)
                  MOV  DI, OFFSET buffer_concat    ; DI = destinatie (buffer_concat)

    copy_a:       
                  MOV  AL, [SI]                    ; Citeste caracter din buffer_a
                  CMP  AL, '$'                     ; Verifica daca e terminator
                  JE   start_copy_b                ; Daca da, treci la buffer_b

                  MOV  [DI], AL                    ; Copiaza caracterul in buffer_concat
                  INC  SI                          ; Trece la urmatorul caracter sursa
                  INC  DI                          ; Trece la urmatoarea pozitie destinatie
                  JMP  copy_a

    start_copy_b: 
                  MOV  SI, OFFSET buffer_b         ; SI = sursa (buffer_b)

    copy_b:       
                  MOV  AL, [SI]                    ; Citeste caracter din buffer_b
                  CMP  AL, '$'                     ; Verifica daca e terminator
                  JE   end_concat                  ; Daca da, termina

                  MOV  [DI], AL                    ; Copiaza caracterul in buffer_concat
                  INC  SI                          ; Trece la urmatorul caracter sursa
                  INC  DI                          ; Trece la urmatoarea pozitie destinatie
                  JMP  copy_b

    end_concat:   
                  MOV  BYTE PTR [DI], '$'          ; Adauga terminator la final
                  RET
concat endp

end main