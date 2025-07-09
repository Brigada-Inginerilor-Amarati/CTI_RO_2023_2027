-- Laborator\Test_03_Subquerry\IMG-20250302-WA0006.jpg

-- 1 : Comunicare	CRS04

-- 4 : Logica digitala	CRS18

SELECT
    titlu,
    cid
FROM Curs 
WHERE (fid = 'AC' or fid = 'ET') AND
                                    zi = (SELECT DISTINCT zi FROM Curs WHERE titlu = 'Fizica');

SELECT
    titlu,
    cid,
    zi
FROM Curs
WHERE (fid = 'AC' OR fid = 'ET') AND zi = ANY(SELECT zi FROM Curs WHERE titlu = 'Fizica');

SELECT
    titlu,
    cid,
    zi
FROM Curs
WHERE (fid = 'AC' OR fid = 'ET') AND zi IN (SELECT zi FROM Curs WHERE titlu = 'Fizica');

-- Laborator\Test_03_Subquerry\IMG-20250302-WA0018.jpg

-- 2 : Henri Coanda	6/19/1968

-- 4 : Elisa Zamfirescu	12/1/1986

SELECT
    nume,
    datan
FROM Profesor
WHERE (fid = 'MEC' OR fid = 'AC') AND
                                        datan < (SELECT datan FROM Profesor WHERE nume = 'Raul Brad');

-- 1 : Grigore Toma	SME002

-- 5 : Amalia Butan	SMP003

SELECT
    nume,
    sid
FROM Student 
WHERE an = 1 AND
                fid not in 
                (
                    SELECT fid FROM Profesor
                                WHERE pid = (       -- sau in loc de = merge in
                                    SELECT pid FROM Curs 
                                                WHERE titlu = 'Limbaje de programare'
                                )
                );

-- Laborator\Test_03_Subquerry\IMG-20250302-WA0019.jpg

-- querry la fel ca sus

-- 2 : Marius Lucaciu	SME003

-- 3 : Zana Apreotesi	SME011

-- Laborator\Test_03_Subquerry\IMG-20250302-WA0020.jpg

-- 1 : Floare Elisa	SME009

-- 5 : Fancois Branza	SME008

SELECT
    nume,
    sid
FROM Student s
WHERE fid = 'MEC' AND
                       EXISTS(
                                SELECT nrc FROM Contract c      -- sau c.sid
                                            WHERE s.sid = c.sid
                       );

-- Laborator\Test_03_Subquerry\IMG-20250302-WA0021.jpg

-- la fel ca sus

-- Laborator\Test_03_Subquerry\IMG-20250302-WA0022.jpg

-- 3 : Nadia Olaru	8.75

-- 6 : Mitica Macelaru	7.25

SELECT
    nume,
    media
FROM Student 
WHERE fid = 'AC' AND 
                    media > (SELECT media FROM Student WHERE nume = 'Emanuel Petrescu');


-- Laborator\Test_03_Subquerry\IMG-20250302-WA0060.jpg

-- 2 : Management si Transporturi	MPT

-- 3 : Inginerie	ING

SELECT
    nume,
    fid
FROM Facultate f
WHERE NOT EXISTS(
                    SELECT media FROM Student s WHERE media < 5.5 AND f.fid = s.fid
                );