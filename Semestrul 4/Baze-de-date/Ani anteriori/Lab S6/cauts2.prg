SET TALK OFF
DO WHILE.T
CLEAR
TEXT
Va rugam tastati una dintre urmatoarele optiuni:
1 - Adaugare inregistrari
2 - Modificare inregistrare data prin CodAngajat
3 - Listare fisier
4 - Afisare primele NumarIntreg inregistrari
5 - Stergere angajat dat prin nume
6 - Eliminare inregistrari marcate pentru stergere
7 - Revalidare inregistrare data prin numarul inregistrarii
8 - Marire salar pentru angajatii cu o anumita vechime
9 - Afisare angajati selectati prin salar
F - Listare fisier filtrat
T - Incheiere program
ENDTEXT

WAIT TO R
IF.NOT..R$`123456789FfTt`
?`FUNCTIA` + R + `INEXISTENTA`
WAIT 
LOOP
ENDIF

DO CASE
CASE R=`1`
APPEND BLANK



