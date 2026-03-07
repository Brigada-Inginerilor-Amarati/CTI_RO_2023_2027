.model small
.stack 100h

.data
    file_in    db 'test.txt', 0
    file_out   db 'output.txt', 0
    handle_in  dw ?
    handle_out dw ?
    buffer     db 100 dup(?)                       ; Buffer de 100 bytes
    bytes_read dw ?                                ; Aici salvam cati bytes am citit
    msg_err    db 'Eroare la fisier!$'
    msg_ok     db 'Fisier procesat cu succes.$'

.code

    ; --- Procedura pentru deschiderea fisierului de input ---
open_input_file proc
                            MOV  AH, 3Dh
                            MOV  AL, 0                      ; Read only
                            LEA  DX, file_in
                            INT  21h
                            JC   error_handler              ; Salt la eroare daca Carry Flag = 1
                            MOV  handle_in, AX              ; Salvam handle-ul
                            ret
open_input_file endp

    ; --- Procedura pentru crearea fisierului de output ---
create_output_file proc
                            MOV  AH, 3Ch
                            MOV  CX, 0                      ; Atribute normale
                            LEA  DX, file_out
                            INT  21h
                            JC   error_handler
                            MOV  handle_out, AX             ; Salvam handle-ul
                            ret
create_output_file endp

    ; --- Procedura pentru citirea din fisierul de input ---
read_from_input proc
                            MOV  AH, 3Fh
                            MOV  BX, handle_in
                            MOV  CX, 100                    ; Cati bytes sa citeasca
                            LEA  DX, buffer
                            INT  21h
                            JC   error_handler
                            MOV  bytes_read, AX             ; Numarul de bytes cititi efectiv
                            ret
read_from_input endp

    ; --- Procedura pentru procesarea buffer-ului ---
process_buffer proc
    ; Aici vine logica de procesare a buffer-ului.
    ; SI = offset buffer, CX = bytes_read
    ; ...
                            MOV  SI, OFFSET buffer
                            MOV  CX, bytes_read
    process_loop:           
                            MOV  AL, [SI]

    ; transforma literele mici in litere mari

                            CMP  AL, 'a'
                            JL   check_special_character

                            CMP  AL, 'z'
                            JG   check_special_character

                            SUB  AL, 20h

                            MOV  [SI], AL

                            JMP  loop_conversion

    check_special_character:
                            CMP  AL, 0Dh                    ; Verifica daca e carriage return
                            JE   loop_conversion

                            CMP  AL, 'A'
                            JL   loop_conversion

                            CMP  AL, 'Z'
                            JG   loop_conversion

                            MOV  AL, ' '                    ; Inlocuieste cu spatiu

    loop_conversion:        
                            MOV  [SI], AL
                            INC  SI
                            LOOP process_loop

                            ret
process_buffer endp

    ; --- Procedura pentru scrierea in fisierul de output ---
write_to_output proc
                            MOV  AH, 40h
                            MOV  BX, handle_out
                            MOV  CX, bytes_read
                            LEA  DX, buffer
                            INT  21h
                            JC   error_handler
                            ret
write_to_output endp

    ; --- Procedura pentru inchiderea fisierelor ---
close_files proc
                            MOV  AH, 3Eh
                            MOV  BX, handle_in
                            INT  21h
    
                            MOV  AH, 3Eh
                            MOV  BX, handle_out
                            INT  21h
                            ret
close_files endp

main proc
                            MOV  AX, @data
                            MOV  DS, AX
    
                            CALL open_input_file
                            CALL create_output_file
                            CALL read_from_input
                            CALL process_buffer
                            CALL write_to_output
                            CALL close_files
    
    ; Mesaj de succes
                            MOV  AH, 09h
                            LEA  DX, msg_ok
                            INT  21h
                            JMP  final

    error_handler:          
                            MOV  AH, 09h
                            LEA  DX, msg_err
                            INT  21h

    final:                  
                            MOV  AX, 4C00h
                            INT  21h
main endp

end main
