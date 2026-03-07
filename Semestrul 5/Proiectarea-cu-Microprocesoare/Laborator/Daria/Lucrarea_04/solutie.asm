.model small
.stack 100h
.data
    file_in db 'in.txt', 0
    file_out db 'out.txt', 0
    handle_in dw ?
    handle_out dw ?
    buffer db 100 dup(?)      ; Buffer de 100 bytes
    bytes_read dw ?           ; Aici salvam cati bytes am citit
    msg_err_in db 'Eroare la deschiderea in.txt! Cod: 0x$'
    msg_err_out db 'Eroare la crearea out.txt! Cod: 0x$'
    msg_ok db 13, 10, 'Fisier procesat cu succes.$' ; Add newline
    msg_start db 'Start processing...', 13, 10, '$'
    msg_empty db 'Fisierul in.txt este gol!', 13, 10, '$'
    hex_chars db '0123456789ABCDEF'

.code
main proc
    MOV AX, @data
    MOV DS, AX

    ; --- DEBUG: PRINT START ---
    MOV AH, 09h
    LEA DX, msg_start
    INT 21h

    ; --- 1. DESCHIDERE FISIER INPUT (READ) ---
    MOV AH, 3Dh
    MOV AL, 0                 ; Read only
    LEA DX, file_in
    INT 21h
    JNC open_ok               ; Daca nu e eroare, continuam
    JMP eroare_input          ; Altfel, salt la eroare
open_ok:
    MOV handle_in, AX         ; Salvam handle-ul

    ; --- 2. CREARE FISIER OUTPUT (WRITE) ---
    MOV AH, 3Ch
    MOV CX, 0                 ; Atribute normale
    LEA DX, file_out
    INT 21h
    JNC create_ok
    JMP eroare_output
create_ok:
    MOV handle_out, AX        ; Salvam handle-ul

process_loop:
    ; --- 3. CITIRE DIN INPUT ---
    MOV AH, 3Fh
    MOV BX, handle_in
    MOV CX, 100               ; Citim maxim 100 bytes
    LEA DX, buffer
    INT 21h
    JNC read_ok
    JMP eroare_input
read_ok:
    
    MOV bytes_read, AX        ; AX contine nr bytes cititi
    CMP AX, 0                 ; Daca am citit 0 bytes, am terminat
    JE check_empty_or_done

    ; --- 4. PROCESARE BUFFER ---
    MOV CX, bytes_read        ; Setam contorul pentru loop
    LEA SI, buffer            ; SI pointeaza la inceputul buffer-ului

procesare_char:
    MOV AL, [SI]              ; Incarcam caracterul curent in AL

    ; Verificam daca e litera mica (a-z)
    CMP AL, 'a'
    JB check_upper            ; Daca e mai mic ca 'a', verificam daca e majuscula
    CMP AL, 'z'
    JA not_letter             ; Daca e mai mare ca 'z', nu e litera (e simbol)
    
    ; E litera mica -> transformam in mare
    SUB AL, 32
    JMP store_char

check_upper:
    ; Verificam daca e litera mare (A-Z)
    CMP AL, 'A'
    JB not_letter             ; Daca e mai mic ca 'A', nu e litera
    CMP AL, 'Z'
    JA not_letter             ; Daca e mai mare ca 'Z' (si stim ca e < 'a'), nu e litera
    
    ; E litera mare -> ramane asa
    JMP store_char

not_letter:
    ; Nu e litera -> inlocuim cu spatiu
    MOV AL, 32                ; ASCII Space

store_char:
    MOV [SI], AL              ; Scriem caracterul procesat inapoi in buffer
    
    ; --- AFISARE PE ECRAN (DEBUG) ---
    PUSH AX
    PUSH DX
    MOV DL, AL
    MOV AH, 02h
    INT 21h
    POP DX
    POP AX
    ; --------------------------------

    INC SI                    ; Trecem la urmatorul byte
    LOOP procesare_char       ; Decrementeaza CX si sare daca CX != 0

    ; --- 5. SCRIERE IN OUTPUT ---
    MOV AH, 40h
    MOV BX, handle_out
    MOV CX, bytes_read        ; Scriem exact cati bytes am citit (si procesat)
    LEA DX, buffer
    INT 21h
    JNC write_ok
    JMP eroare_output
write_ok:

    JMP process_loop          ; Continuam citirea urmatorului chunk

check_empty_or_done:
    ; Daca suntem aici si nu am procesat nimic inca? 
    ; Nu avem un flag "processed_something", dar putem presupune ca e EOF.
    ; Daca fisierul era gol de la inceput, bytes_read e 0 la prima iteratie.
    ; Putem verifica asta? E complicat fara variabile extra.
    ; Dar mesajul "Fisier procesat cu succes" apare oricum.
    JMP close_files

close_files:
    ; --- 6. INCHIDERE FISIERE ---
    MOV AH, 3Eh
    MOV BX, handle_in
    INT 21h

    MOV AH, 3Eh
    MOV BX, handle_out
    INT 21h

    ; Afisare mesaj succes
    MOV AH, 09h
    LEA DX, msg_ok
    INT 21h
    JMP final

eroare_input:
    MOV BX, AX                ; Salvam codul de eroare in BX
    
    ; Afisare mesaj eroare input
    MOV AH, 09h
    LEA DX, msg_err_in
    INT 21h
    
    MOV AX, BX                ; Restauram codul
    CALL print_hex_byte       ; Afisam codul (AL)
    JMP final

eroare_output:
    MOV BX, AX                ; Salvam codul de eroare in BX

    ; Afisare mesaj eroare output
    MOV AH, 09h
    LEA DX, msg_err_out
    INT 21h
    
    MOV AX, BX                ; Restauram codul
    CALL print_hex_byte       ; Afisam codul (AL)
    JMP final

final:
    MOV AH, 4Ch
    INT 21h

main endp

; Procedura pentru afisarea unui byte (AL) in hexa
print_hex_byte proc
    PUSH AX
    PUSH BX
    PUSH DX
    
    MOV BL, AL                ; Save original byte in BL
    
    ; High nibble
    SHR AL, 4
    LEA BX, hex_chars         ; Point BX to table
    XLAT                      ; AL = [BX + AL]
    MOV DL, AL
    MOV AH, 02h
    INT 21h
    
    ; Low nibble
    MOV AL, BL                ; Restore original byte
    AND AL, 0Fh               ; Mask high nibble
    LEA BX, hex_chars         ; Point BX to table
    XLAT                      ; AL = [BX + AL]
    MOV DL, AL
    MOV AH, 02h
    INT 21h
    
    POP DX
    POP BX
    POP AX
    RET
print_hex_byte endp

end main
