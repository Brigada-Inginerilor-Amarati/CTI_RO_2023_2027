; 1. Scrieți un program în limbajul de asamblare x86 care citește un șir de caractere, format 
; doar din litere mici, de la tastatură și afișează același șir scris doar cu litere mari. 

dosseg

.model small

.stack 100h

; aici se initializeaza
.data
        buffer DB 100 DUP('$')                  ; buffer pentru sirul de caractere

;aici cod
.code

; Procedura pentru linie noua
new_line proc
        MOV AH, 2
        MOV DL, 13                              ; CR
        INT 21H
        MOV DL, 10                              ; LF
        INT 21H
        ret
new_line endp

main proc
        ; Initializare segment de date
        MOV AX, @data
        MOV DS, AX

        ; Citire sir de caractere
        MOV SI, OFFSET buffer                    ; SI indica inceputul buffer-ului

read_loop:
        MOV AH, 1                               ; functia DOS pentru citire caracter
        INT 21H                            
        
        CMP AL, 0Dh                             ; verificam daca e Enter (carriage return)
        JE end_read                             
        
        ; Convertim litera mica in litera mare
        CMP AL, 'a'                            
        JB store_char                          
        CMP AL, 'z'                           
        JA store_char               
        SUB AL, 20h                      

store_char:
        MOV [SI], AL                          
        INC SI                                 
        JMP read_loop                       

end_read:
        MOV BYTE PTR [SI], '$'                  ; adaugam terminator '$' pentru DOS
        CALL new_line                           
        
        ; Afisare sirul convertit
        MOV AH, 9                               ; functia DOS pentru afisare string
        MOV DX, OFFSET buffer
        INT 21H
        CALL new_line
        
        MOV AH, 4Ch                             
        INT 21h

main endp

end main