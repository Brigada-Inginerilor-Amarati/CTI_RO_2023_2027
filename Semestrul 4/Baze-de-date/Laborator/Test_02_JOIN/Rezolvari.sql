-- Laborator\Test_02_JOIN\IMG-20250302-WA0001.jpg

-- 2: Ciprian Porumbescu	Sisteme web
-- 5 : Cristina Papura	Logica fuzzy

SELECT
    p.nume as Nume_Profesor,
    c.titlu as Titlu_Curs,
    s.nrlocuri as Nr_locuri_Sala
FROM Profesor p JOIN Curs c
                ON p.pid = c.pid
                JOIN Sala s
                ON c.sala = s.cods
WHERE s.nrlocuri >= 50 AND s.nrlocuri <= 250;

-- Laborator\Test_02_JOIN\IMG-20250302-WA0025.jpg

-- 3 : SAC002	Psihologia copilului
-- 5 : SAC004	Logica digitala

SELECT
    s.sid as ID_Student,
    c.titlu as Titlu_Curs,
    sl.etaj as Etaj_Curs
FROM Student s JOIN Contract ct
               ON s.sid = ct.sid
               JOIN Curs c
               ON ct.cid = c.cid
               JOIN Sala sl
               ON c.sala = sl.cods
WHERE sl.etaj = 2 OR sl.etaj = 3
ORDER BY s.sid;

-- Laborator\Test_02_JOIN\IMG-20250302-WA0026.jpg

-- la fel ca prima problema rezolvata, dar alte linii selectate

-- Laborator\Test_02_JOIN\IMG-20250302-WA0028.jpg

-- 2 : PSC001	0256-404011
-- 4 : PET001	0256-403381

SELECT 
    p.nume as Nume_Profesor,
    p.pid as ID_profesor,
    f.tel as Telefon_Contact_Facultate
FROM Profesor p JOIN Facultate f
                ON p.fid = f.fid
WHERE p.nume NOT LIKE 'C%';
   
-- Laborator\Test_02_JOIN\IMG-20250302-WA0029.jpg

-- 1 : SAC006	Florian Belu
-- 4 : SAC004	Nadia Olaru

SELECT 
    s.sid as ID_Student,
    s.nume as Nume_Student,
    p.pid as ID_Profesor
FROM Student s JOIN Contract ct
               ON s.sid = ct.sid
               JOIN Curs c
               ON c.cid = ct.cid
               JOIN Profesor p
               ON c.pid = p.pid
WHERE p.pid = 'PAC001';


-- Laborator\Test_02_JOIN\IMG-20250302-WA0030.jpg

-- 2 : SME010	Programare
-- 3 : SMP005	Relatii publice

SELECT
    s.sid as ID_Student,
    c.titlu as Titlu_Curs,
    c.zi as Zi_Curs
FROM Student s JOIN Contract ct
               ON s.sid = ct.sid
               JOIN Curs c
               ON c.cid = ct.cid
WHERE c.zi NOT LIKE 'Luni' AND c.zi != 'Vineri';

-- Laborator\Test_02_JOIN\IMG-20250302-WA0032.jpg

-- 4 : Rodica Tudoran	Electrotehnica
-- 5 : Grigore Toma	Mecanica

SELECT
    s.nume as Nume_Student,
    f.nume as Nume_Facultate,
    s.bursa as Bursa
FROM Student s JOIN Facultate f
               ON s.fid = f.fid
WHERE s.bursa > 500;

-- Laborator\Test_02_JOIN\IMG-20250302-WA0033.jpg

-- se repeta mai sus