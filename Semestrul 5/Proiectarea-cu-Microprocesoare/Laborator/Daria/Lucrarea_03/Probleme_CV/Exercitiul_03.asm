; 3. Scrieți un program care citește un șir de caractere de la tastatură și afișează un nou șir 
; format doar din vocalele șirului inițial, în ordinea în care au fost găsite în șirul inițial.

dosseg

.model small

.stack 100h

; aici se initializeaza
.data
        buffer DB 100 DUP('$')                  
        vowels DB 100 DUP('$')                 

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

        ; Citire sir de caractere
        MOV SI, OFFSET buffer                    ; SI indica inceputul buffer-ului

read_loop:
        MOV AH, 1                               ; functia DOS pentru citire caracter
        INT 21H                                
        
        CMP AL, 0Dh                             ; verificam daca e Enter (carriage return)
        JE end_read                             
        
        MOV [SI], AL                            
        INC SI                                  
        JMP read_loop                           

end_read:
        MOV BYTE PTR [SI], '$'                  
        CALL new_line

        ; Extragere vocale din sir
        MOV SI, OFFSET buffer                    ; SI indica inceputul buffer-ului
        MOV DI, OFFSET vowels                    ; DI indica inceputul buffer-ului pentru vocale

extract_vowels:
        MOV AL, [SI]                            ; incarcam caracterul din buffer
        CMP AL, '$'                             
        JE end_extract                           
        
        CMP AL, 'a'
        JE save_vowel
        CMP AL, 'e'
        JE save_vowel
        CMP AL, 'i'
        JE save_vowel
        CMP AL, 'o'
        JE save_vowel
        CMP AL, 'u'
        JE save_vowel
        CMP AL, 'A'
        JE save_vowel
        CMP AL, 'E'
        JE save_vowel
        CMP AL, 'I'
        JE save_vowel
        CMP AL, 'O'
        JE save_vowel
        CMP AL, 'U'
        JE save_vowel
        
        ; Nu e vocala, trecem la urmatorul caracter
        JMP next_char

save_vowel:
        ; E vocala, o salvam
        MOV [DI], AL                            ; salvam vocala
        INC DI                                  ; trecem la pozitia urmatoare in buffer-ul de vocale

next_char:
        INC SI                                  ; trecem la urmatorul caracter din buffer
        JMP extract_vowels

end_extract:
        MOV BYTE PTR [DI], '$'                  ; adaugam terminator '$' pentru DOS

        ; Afisare sirul cu vocale
        MOV AH, 9                               ; functia DOS pentru afisare string
        MOV DX, OFFSET vowels
        INT 21H
        CALL new_line
        
        MOV AH, 4Ch                             ; terminare program
        INT 21h

main endp

end main 