dosseg

.model small;

.stack 100h

; aici se initializeaza
.data


;aici cod
.code 

main proc

            MOV AX, 17
            MOV BL, 4

            DIV BL       ; se executa AL = AX / BL   -> AL = 17 / 4
                         ; catul este in AL, iar restul in AH

        

main endp

end main