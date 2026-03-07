dosseg

.model small;

.stack 100h

; aici se initializeaza
.data

                    ch1 db 'a'                  ; variabila pe un byte, retine caracterul 'a' prin codul ASCII (97) sau 0x61 hexaa
                    ch2 db '1'                  ; variabila pe un byte, retine caracterul '1' prin codul ASCII (49) sau 0x31 hexaa
                    ch3 db 1                    ; variabila pe un byte, retine valoarea numerica 1
                    ch4 db '?'                  ; variabila pe un byte, retine caracterul '?' prin codul ASCII (63) sau 0x3F hexaa
;aici cod
.code 

print_char proc
                    ; afiseaza caracterul din AL
                    MOV DL, AL        ; muta caracterul din AL in DL pentru a fi afisat
                    MOV AH, 02h       ; functia 02h - afisare caracter
                    INT 21h
                    ret
print_char endp

main proc
                    ; Initializare segment de date
                    MOV AX, @data
                    MOV DS, AX

                    MOV AL, ch1       ; incarca in AL caracterul 'a'
                    CALL print_char    ; afiseaza caracterul din AL

                    MOV AL, ch2       ; incarca in AL caracterul '1'
                    CALL print_char    ; afiseaza caracterul din AL

                    MOV AL, ch3       ; incarca in AL valoarea numerica 1 (caracterul SOH)
                    ADD AL, 30h       ; converteste valoarea numerica in caracter (1 -> '1')
                    CALL print_char    ; afiseaza caracterul din AL

                    MOV AL, ch4       ; incarca in AL caracterul '?'
                    CALL print_char    ; afiseaza caracterul din AL
                    
                    MOV AH, 4Ch       ; terminare program
                    INT 21h
main endp

end main