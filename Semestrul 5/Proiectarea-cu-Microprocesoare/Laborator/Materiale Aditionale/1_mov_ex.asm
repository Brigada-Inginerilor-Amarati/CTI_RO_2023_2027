
.model small  ;modelul de memorie folosit

.data         ;declarare a datelor 

C EQU 15      ;constanta

var1 db 12    ;lungimea de 1byte

var2 db ?     ;valoarea initiala necunoscuta



.code       

main proc    ;inceperea unei proceduri
    
    mov ax,@data    ;incarcarea segmentului de date
    mov ds,ax
    
    mov var2,C      ;d,s
    
    mov al,var1
    mov ah,var2
    
    mov var2,al
    mov var1,ah
    
main endp

end