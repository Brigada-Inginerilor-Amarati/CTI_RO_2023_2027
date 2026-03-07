; 2. Scrieți un program care citește, pe rând, două șiruri de caractere de la tastatură și le 
; salvează în două variabile msg1 și msg2. Finalul fiecărui șir de caractere va fi semnalat 
; prin caracterul special $, care va fi salvat pe ultima poziție din fiecare șir. Programul 
; va crea și va afișa pe ecran un nou șir obținut prin concatenarea celor două.

dosseg

.model small

.stack 100h

; aici se initializeaza
.data
        msg1 DB 100 DUP('$')                   
        msg2 DB 100 DUP('$')                    
        result DB 200 DUP('$')                 

;aici cod
.code

; Procedura pentru linie noua
new_line proc
        MOV AH, 2
        MOV DL, 13                              ; Carriage Return
        INT 21H
        MOV DL, 10                              ; Line Feed
        INT 21H
        ret
new_line endp

main proc
        ; Initializare segment de date
        MOV AX, @data
        MOV DS, AX

        ; Citire primul sir (msg1)
        MOV SI, OFFSET msg1
read_msg1:
        MOV AH, 1                               ; functia DOS pentru citire caracter
        INT 21H                                 
        
        CMP AL, '$'                           
        JE end_msg1                             
        
        MOV [SI], AL                            ; stocam caracterul in msg1
        INC SI                                  
        JMP read_msg1                            

end_msg1:
        MOV BYTE PTR [SI], '$'                  ; adaugam terminator '$'
        CALL new_line

        ; Citire al doilea sir (msg2)
        MOV SI, OFFSET msg2
read_msg2:
        MOV AH, 1                               ; functia DOS pentru citire caracter
        INT 21H                               
        
        CMP AL, '$'                             
        JE end_msg2                            
        
        MOV [SI], AL                            ; stocam caracterul in msg2
        INC SI                                  
        JMP read_msg2                           

end_msg2:
        MOV BYTE PTR [SI], '$'                  ; adaugam terminator '$'
        CALL new_line

        ; Concatenare: copiem msg1 in result (fara '$')
        MOV SI, OFFSET msg1
        MOV DI, OFFSET result
copy_msg1:
        MOV AL, [SI]
        CMP AL, '$'                             
        JE copy_msg2                            
        MOV [DI], AL                           
        INC SI
        INC DI
        JMP copy_msg1

        ; Concatenare: copiem msg2 in result (fara '$')
copy_msg2:
        MOV SI, OFFSET msg2
copy_msg2_loop:
        MOV AL, [SI]
        CMP AL, '$'                             
        JE end_concatenate                      
        MOV [DI], AL                           
        INC SI
        INC DI
        JMP copy_msg2_loop

end_concatenate:
        MOV BYTE PTR [DI], '$'                  ; adaugam terminator '$' la final

        ; Afisare sirul concatenat
        MOV AH, 9                               ; functia DOS pentru afisare string
        MOV DX, OFFSET result
        INT 21H
        CALL new_line
        
        MOV AH, 4Ch                             ; terminare program
        INT 21h

main endp

end main 
