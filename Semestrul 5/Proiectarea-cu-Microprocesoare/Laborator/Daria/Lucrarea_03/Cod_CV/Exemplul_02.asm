dosseg

.model small;

.stack 100h

; aici se initializeaza
.data

;aici cod
.code 

main proc
                    MOV AH, 2
                    MOV DL, 'a'       ; caracterul de afisat            
                    ; putem folosi si MOV DL, 97
                    INT 21h            ; apel DOS pentru afisare
main endp

end main