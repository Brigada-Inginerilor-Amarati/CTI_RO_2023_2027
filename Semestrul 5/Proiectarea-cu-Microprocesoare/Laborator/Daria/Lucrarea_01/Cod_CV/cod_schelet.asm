dosseg

.model small           ; prin această instrucțiune se selectează modelul de memorie folosit


.data ; reprezintă secțiunea de declarare a datelor
; aici se declară variabilele și constantele folosite în program
    ; A DB 0              ; declararea variabilei A de tip byte inițializată cu 0
    ; B DB 0              ; declararea variabilei B de tip byte inițializată cu 0
    ; C DB 0              ; declararea variabilei C de tip byte inițializată cu 0
    ; X DW 7              ; declararea variabilei X de tip word inițializată cu 7
    ; n1 DB "Introduceti primul numar:$"   ; mesaj pentru primul număr
    ; n2 DB "Introduceti al doilea numar:$" ; mesaj pentru al doilea număr
    ; n3 DB "Introduceti al treilea numar:$" ; mesaj pentru al treilea număr
    ; result DB "Rezultatul este: $"        ; mesaj pentru afișarea rezultatului

.code ; reprezintă secțiunea în care se scrie codul sursă al programului

; new_line proc
;     MOV AH, 2          ; funcția DOS pentru afișarea unui caracter
;     MOV DL, 10         ; codul ASCII pentru newline
;     INT 21H            ; apelarea întreruperii DOS
;     ret
; new_line endp

main proc ; proc este cuvântul cheie pentru începerea unei proceduri
; codul sursă din main 
main endp ; endp este cuvântul cheie care semnifică finalul unei proceduri

end main 