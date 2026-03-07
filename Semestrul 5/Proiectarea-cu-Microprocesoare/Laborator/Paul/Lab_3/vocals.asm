; 3.  Scrieți un program care citește un șir de caractere de la tastatură și afișează un nou șir format doar din vocalele șirului inițial, în ordinea în care au fost găsite în șirul inițial.

.model small

.stack 100h

.data
    buffer       DB 100 DUP('$')
    vocals       DB 'aeiouAEIOU$'
    vocal_buffer DB 100 DUP('$')
    prompt       DB 'Introduceti un sir de caractere: $'
    newline      DB 0Dh, 0Ah, '$'                           ; CRLF
.code

main proc
                    CALL init

                    MOV  SI, OFFSET prompt
                    CALL print_string

                    MOV  SI, OFFSET buffer
                    CALL read_string
                    CALL print_newline

                    CALL add_vocals
                    MOV  SI, OFFSET vocal_buffer
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
                     
                    MOV  CX, 0                      ; Contor pentru lungimea sirului

    read_loop:      
                    MOV  AH, 1                      ; Functie DOS: citeste caracter
                    INT  21h                        ; Rezultat in AL (afiseaza automat pe ecran)

                    CMP  AL, 0Dh                    ; Verifica daca e Enter (carriage return)
                    JE   end_read                   ; Daca da, termina citirea

                    MOV  [SI], AL                   ; Stocheaza caracterul in buffer
                    INC  SI                         ; Trece la pozitia urmatoare
                    INC  CX                         ; Incrementeaza contorul
                    JMP  read_loop

    end_read:       
                    MOV  BYTE PTR [SI], '$'         ; Adauga terminator '$' pentru DOS
                    RET
read_string endp


print_string proc
                    MOV  AH, 9                      ; Functie DOS: afiseaza sir
                    MOV  DX, SI                     ; DX indica sirul
                    INT  21h                        ; Sirul trebuie sa se termine cu '$'
                    RET
print_string endp


print_newline proc
                    MOV  AH, 9
                    MOV  DX, OFFSET newline
                    INT  21h
                    RET
print_newline endp


add_vocals proc
                    MOV  SI, OFFSET buffer
                    MOV  DI, OFFSET vocal_buffer

    loop_vocals:    
                    MOV  AL, [SI]
                    CMP  AL, '$'
                    JZ   end_loop_vocals
                    CALL add_vocal
                    INC  SI
                    JMP  loop_vocals
    end_loop_vocals:
                    MOV  BYTE PTR [DI], '$'
                    RET
add_vocals endp


add_vocal proc
    ; if the current letter is in the vocals string, add it to the vocal_buffer
                    MOV  BX, OFFSET vocals
                    MOV  AL, [SI]
    loop_vocal:     
                    MOV  AH, [BX]
                    CMP  AH, '$'                    ; if there is no match for the vocals, exit the loop
                    JZ   end_loop_vocal
                    CMP  AH, AL                     ; check for vocal matches
                    JNZ  increment_index
                    MOV  [DI], AL
                    INC  DI
    increment_index:
                    INC  BX
                    JMP  loop_vocal

    end_loop_vocal: 
                    RET

add_vocal endp

end main