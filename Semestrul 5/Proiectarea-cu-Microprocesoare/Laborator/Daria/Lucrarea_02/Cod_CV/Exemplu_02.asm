dosseg

.model small;

.stack 100h

; aici se initializeaza
.data


;aici cod
.code 

main proc

            MOV AL, X
            MUL AL       ; se executa AX = AL * AL   -> AX = X * X
                         ; rezultatul este in AX, iar daca este mai mare decat 255
                         ; atunci AH va fi diferit de 0

            MUL AL       ; se executa AX = AL * AL   -> AX = X * X * X * X
                         ; rezultatul este in AX, iar daca este mai mare decat 255
                         ; atunci AH va fi diferit de 0

        

main endp

end main