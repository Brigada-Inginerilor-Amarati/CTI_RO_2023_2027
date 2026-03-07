; 1. Pornind de la programul Aritmetic1 dat ca exemplu, scrieți un nou program care afișează pe ecran primii 7 termeni din seria Fibonacci, considerând primii 3 termeni ca fiind: 0, 1, 1.
; Se va folosi întreruperea INT 21H doar pentru afișare, adaugând 30h la fiecare cifră pe care doriți să o afișați, înainte de apelarea întreruperii.

.model small

.stack 100h

.code

main proc
                 mov  bl, 0           ; store A in BL
                 mov  bh, 1           ; store B in BH

                 mov  dl, bl          ; print A
                 call print_number

                 mov  dl, bh          ; print B
                 call print_number

                 mov  cx, 5           ; init the counter to 5

    fib_loop:    

                 mov  dl, bl          ; store A
                 add  dl, bh          ; store C = A + B
                 mov  dh, dl          ; store C in DH
                 call print_number

                 mov  bl, bh          ; A = B
                 mov  bh, dh          ; B = C

                 loop fib_loop        ; run the loop until cx = 0
      
                 mov  ah, 4Ch         ; exit program
                 int  21h

main endp

print_number proc
                 add  dl, 30h
                 mov  ah, 02h
                 int  21h
                 call print_space
                 ret
print_number endp

print_space proc
                 mov  dl, ' '
                 mov  ah, 02h
                 int  21h
                 ret
print_space endp

end main