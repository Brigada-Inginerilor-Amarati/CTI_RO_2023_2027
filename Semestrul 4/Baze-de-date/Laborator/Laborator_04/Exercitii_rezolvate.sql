-- Activitate 1

SELECT s.sid, s.nume, s.an, f.nume as Facultate
    FROM Student s, Facultate f
    WHERE s.fid = f.fid AND an < 3;

-- Exercitiul 1
-- Sa se listeze toti profesorii impreuna cu datele despre facultatea de care apartin

-- cu JOIN explicit

SELECT
    p.nume,
    p.datan,
    f.fid,
    f.nume
FROM Profesor p JOIN Facultate f
                ON p.fid = f.fid;

-- cu INNER JOIN

SELECT
    p.nume as Profesor,
    p.datan as Data_Nasterii,
    f.fid as ID_Facultate,
    f.nume as Facultate
FROM Profesor INNER JOIN Facultate f
                ON p.fid = f.fid;

-- cred ca asta merge cu orice tip de join

-- Exercitiul 2
--Să se listeze toate cursurile de după amiază (>12:00) împreună cu numărul de locuri ale sălii unde se desfășoară.
-- merge cu orice tip de join

SELECT
    c.titlu as Titlu_Curs,
    c.cid as ID_Curs,
    s.nrlocuri as NrLocuri_Sala
FROM Curs c JOIN Sala s
            ON c.sala = s.cods
WHERE c.ora > 12;

-- Exercitiul 3
-- sa se listeze toate cursurile care se tin la etajul 1(in orice sala de la etajul 1)
-- merge cu orice tip de join

SELECT
    c.titlu as Titlu_Curs,
    s.etaj as Etaj_Sala
FROM Curs c JOIN Sala s
            ON c.sala = s.cods
WHERE s.etaj = 1;

-- Exercitiul 4
-- Să se listeze toate cursurile care se țin în ziua curenta
-- împreună cu numele profesorilor care le susțin. Denumirea zilei
-- curente fără diacritice se poate afla folosind funcția TO-CHAR:
-- trim(convert(to_char(SYSDATE, 'Day', 'NLS_DATE_LANGUAGE = Romanian'),'US7ASCII'))
-- merge cu orice tip de join

SELECT
    c.titlu as Titlu_Curs,
    p.nume as Nume_Profesor
FROM Curs c JOIN Profesor p
            ON c.pid = p.pid
WHERE c.zi = trim(convert(to_char(SYSDATE, 'Day', 'NLS_DATE_LANGUAGE = Romanian'),'US7ASCII'));

-- Exercitiul 5
-- Să se listeze studenții cu informații despre cursurile
-- (titlu si sala) la care au nota mai mică sau egală cu 8.

SELECT
    s.nume as Nume_Student,
    c.titlu as Titlu_Curs,
    c.sala as Sala_Curs
FROM Contract ct JOIN Curs c
                 ON ct.cid = c.cid 
                 JOIN Student s
                 ON s.sid = ct.sid
WHERE ct.nota >= 8;

-- Exercitiul 6
-- Să se listeze toți studenții care nu au nici un contract
-- de studii semnat, ordonați după an și nume.

SELECT
    s.nume
FROM Student s LEFT OUTER JOIN Contract ct
                 ON s.sid = ct.sid
WHERE ct.   nrc IS NULL
ORDER BY s.an, s.nume;

-- Exercitiul 7
-- Să se listeze toți studenții care au cel puțin un
-- contract de studii semnat, ordonați după numele de familie (obs.
-- în BD sunt în format “prenume nume_familie”).

SELECT DISTINCT
    s.nume
FROM Student s LEFT OUTER JOIN Contract ct
                ON s.sid = ct.sid
WHERE ct.nrc is NOT NULL
ORDER BY  substr(s.nume, instr(s.nume, ' ') + 1);

-- Exercitiul 8
-- Să se listeze toți studenții care au cursuri în ziua de ’Luni’.\

SELECT DISTINCT
    s.nume,
    c.zi
FROM Contract ct JOIN Student s
                 ON s.sid = ct.sid
                 JOIN Curs c
                 ON c.cid = ct.cid
WHERE c.zi = 'Luni';

-- Exercitiul 9
-- Să se listeze toți studenții care au cursuri într-o sală
-- cu mai puțin de 200 de locuri indiferent de zi, ordonați după anul
-- nașterii și nume.

SELECT DISTINCT
    s.nume,
    s.datan
FROM Student s JOIN Contract ct
               ON s.sid = ct.sid
               JOIN Curs c
               ON ct.cid = c.cid
               JOIN Sala sl
               ON c.sala = sl.cods
WHERE sl.nrlocuri < 200
ORDER BY extract(year from datan), s.nume;