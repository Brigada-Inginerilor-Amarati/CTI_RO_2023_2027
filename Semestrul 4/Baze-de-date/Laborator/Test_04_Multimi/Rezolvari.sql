-- Laborator\Test_04_Multimi\IMG-20250302-WA0013.jpg

-- 3 : ING	Inginerie
-- 6 : SC	Stiinte ale Comunicarii

SELECT
    f1.fid,
    f1.nume
FROM Facultate f1
WHERE f1.fid IN (SELECT s.fid FROM Student s WHERE substr(s.adr,instr(s.adr,',') + 1) LIKE 'H%')
UNION
SELECT
    f2.fid,
    f2.nume
FROM Facultate f2
WHERE f2.fid IN (SELECT p.fid FROM Profesor p WHERE grad = 'prof');

SELECT
    f1.fid,
    f1.nume
FROM Facultate f1 JOIN Student s 
                  ON f1.fid = s.fid
WHERE substr(s.adr, instr(s.adr, ',') + 1) LIKE 'H%'
UNION
SELECT
    f2.fid,
    f2.nume
FROM Facultate f2 JOIN Profesor p
                  ON f2.fid = p.fid
WHERE p.grad = 'prof';


-- Laborator\Test_04_Multimi\IMG-20250302-WA0014.jpg

-- 2 : CRS10	1
-- 5 : CRS16	1
SELECT
    c1.cid,
    c1.an
FROM Curs c1 JOIN Facultate f
             ON c1.fid = f.fid
WHERE f.fid = 'AC'
MINUS
SELECT
    c2.cid,
    c2.an
FROM Curs c2 JOIN Profesor p
             ON c2.pid = p.pid
WHERE p.grad = 'conf';

-- Laborator\Test_04_Multimi\IMG-20250302-WA0015.jpg

-- la fel cu poza 80

-- 2 : CRS13	Logica fuzzy

-- 4 : CRS18	Logica digitala

SELECT
    c1.cid,
    c1.titlu
FROM Curs c1 
WHERE c1.pid IN (SELECT p.pid FROM Profesor p WHERE substr(p.nume, instr(p.nume, ' ') + 1) LIKE 'P%')
INTERSECT
SELECT
    c2.cid,
    c2.titlu
FROM Curs c2 
WHERE c2.fid IN (SELECT f.fid FROM Facultate f WHERE f.fid IN (SELECT s.fid FROM Student s WHERE s.media >= 9));


-- Laborator\Test_04_Multimi\IMG-20250302-WA0016.jpg

-- poza 265 verificare

-- 2 : CRS06	1
-- 5 : CRS25	2

SELECT
    c1.cid,
    c1.an
FROM Curs c1 JOIN Profesor p
             ON c1.pid = p.pid
WHERE p.grad = 'prof'
MINUS
SELECT
    c2.cid,
    c2.an
FROM Curs c2 JOIN Facultate f
             ON c2.fid = f.fid
WHERE f.fid = 'AC';

-- Laborator\Test_04_Multimi\IMG-20250302-WA0078.jpg

SELECT
    p1.pid,
    p1.fid
FROM Profesor p1 
WHERE p1.datan < '01/01/1980'
MINUS
SELECT
    p2.pid,
    p2.fid
FROM Profesor p2 
WHERE p2.grad = 'conf'

-- poza 81

-- nu s bune raspunsurile lor

SELECT
    s1.sid,
    s1.nume,
    s1.media
FROM Student s1
WHERE s1.media NOT BETWEEN 6 AND 7.8
INTERSECT
SELECT
    s2.sid,
    s2.nume,
    s2.media
FROM Student s2 JOIN Contract ct
                ON s2.sid = ct.sid
WHERE ct.an = 2021; 

SELECT
    s2.sid,
    s2.nume,
    s2.media
FROM Student s2 JOIN Contract ct
                ON s2.sid = ct.sid
WHERE ct.an = 2021
MINUS
SELECT
    s1.sid,
    s1.nume,
    s1.media
FROM Student s1
WHERE s1.media BETWEEN 6 AND 7.8


-- Laborator\Test_04_Multimi\IMG-20250302-WA0082.jpg


-- CID	TITLU
-- CRS10	Limbaje de programare
-- CRS11	Sisteme web
-- CRS14	Limbaje de asamblare
-- CRS16	Electrotehnica
-- CRS20	Sistem expert

SELECT
    c1.cid,
    c1.titlu
FROM Curs c1
WHERE c1.fid = 'AC'
MINUS
SELECT
    c2.cid,
    c2.titlu
FROM Curs c2
WHERE c2.zi = 'Luni';

-- Laborator\Test_04_Multimi\IMG-20250302-WA0083.jpg

SELECT
    ct1.nrc,
    ct1.semestru
FROM Contract ct1
WHERE ct1.nota >= 8 
UNION
SELECT
    ct2.nrc,
    ct2.semestru
FROM Contract ct2 
WHERE ct2.semestru = 2;

-- 85

SELECT
    s1.sid,
    s1.nume
FROM Student s1
WHERE s1.bursa = 0 OR s1.bursa IS NULL
UNION
SELECT
    s2.sid,
    s2.nume
FROM Student s2
WHERE s2.media < 6.5;