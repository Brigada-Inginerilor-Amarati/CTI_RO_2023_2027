dosseg

.model small;

.stack 100h

; aici se initializeaza
.data


;aici cod
.code 

main proc

            MOV AL, 1
            MOV BL, 7
            MUL BL       ; se executa AX = AL * BL   -> AX = 1 * 7 = 7 < 255 incape in AL
                         ; deci AL = 7, iar AH = 0
            
            MUL 5        ; se executa AX = AL * 5   -> AX = 7 * 5 = 35 < 255 incape in AL
                         ; deci AL = 35, iar AH = 0

        

main endp

end main