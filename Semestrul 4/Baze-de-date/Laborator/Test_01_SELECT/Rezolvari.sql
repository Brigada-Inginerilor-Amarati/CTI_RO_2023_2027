--Poze grile/IMG-20250302-WA0002.jpg
--Inregistrare 3 : sid SMP007, media : 6.75
--Inregistrare 5 : sid SIN008, media 5.75

SELECT sid, media FROM Student WHERE bursa is NULL or bursa = 0;

--Poze grile/IMG-20250302-WA0003.jpg
-- 2 : CRS14	Limbaje de asamblare
-- 3 : CRS25	Programare

SELECT cid, titlu FROM Curs WHERE titlu LIKE '%e';

-- Poze grile/IMG-20250302-WA0038.jpg
-- 3: SAC005	Florin Crainicu
-- 5: SMP002	Zana Abacu

SELECT sid, nume FROM Student WHERE an=2;

--Poze grile/IMG-20250302-WA0040.jpg
-- 2: Ionela Zebra	ING
-- 5: Rodica Tudoran	ET

SELECT nume, fid FROM Student 
    WHERE extract(YEAR FROM SYSDATE) - extract(YEAR FROM datan) < 21;

SELECT *FROM Student
    WHERE months_between(SYSDATE, datan) / 12 < 21;

--Poze grile/IMG-20250302-WA0042.jpg
-- 1 : SAC001	Emanuel Petrescu
-- 3 : SME002	Grigore Toma

SELECT sid, nume FROM Student WHERE datan LIKE '%2002';

-- sau

SELECT sid, nume FROM Student WHERE extract(year from datan) LIKE '2002';

-- Poze grile/2025/3.png
-- 2 : Nadia Olaru	AC
-- 3 : Vasile Luca	ET

SELECT nume, fid FROM Student 
    WHERE EXTRACT(YEAR FROM datan) = 2003;