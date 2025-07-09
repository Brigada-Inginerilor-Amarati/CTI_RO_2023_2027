-- L6.Ex1. Modificați interogarea de la Activitatea1 pentru a nu
-- include și studenții fără bursă.

SELECT s1.sid,s1.nume,s1.an,s1.bursa FROM Student s1
 WHERE s1.bursa <750 AND s1.bursa IS NOT NULL and s1.bursa <> 0
UNION
SELECT s2.sid,s2.nume,s2.an,s2.bursa FROM Student s2
 WHERE s2.bursa >900


-- L6.Ex2. Rescrieți interogarea anterioară ca să obțineți același
-- rezultat fără a folosi operații pe mulțimi.

SELECT 
    s.sid, 
    s.nume,
    s.an,
    s.bursa
FROM Student s WHERE (s.bursa < 750 AND s.bursa IS NOT NULL AND s.bursa <> 0) OR s.bursa > 900;


SELECT sid, nume, bursa FROM STUDENT
WHERE (bursa < 750 or bursa > 900) and bursa <> 0;

SELECT sid, nume, bursa FROM Student 
WHERE (bursa in(SELECT bursa FROM Student WHERE bursa < 750) or bursa in (SELECT bursa FROM Student WHERE bursa > 900)) and bursa <> 0;


-- L6.Ex3. Folosind reuniunea să se listeze toți studenții (sid,nume, an, bursa) care au bursa minimă împreună cu cei care au
-- bursa maximă. Obs. Cei care au bursa = 0 sau NULL se
-- consideră că nu au bursă.

SELECT
    s1.sid,
    s1.nume,
    s1.an,
    s1.bursa
FROM Student s1
WHERE s1.bursa <= ALL(SELECT bursa FROM Student WHERE bursa <> 0 AND bursa IS NOT NULL) AND s1.bursa <> 0
UNION
SELECT
    s2.sid,
    s2.nume,
    s2.an,
    s2.bursa
FROM Student s2
WHERE s2.bursa >= ALL(SELECT bursa FROM Student WHERE bursa IS NOT NULL);

-- L6.Ex4. Folosind intersecția să se listeze facultățile (fid,
-- nume, adr) care au cursuri și la etajul 1 și la etajul 2.

SELECT f1.fid, f1.nume, f1.adr FROM Facultate f1
    WHERE f1.fid in (SELECT c.fid FROM Curs c where c.sala in(SELECT s.cods FROM Sala s where s.etaj = 1))
INTERSECT
SELECT f2.fid, f2.nume, f2.adr FROM Facultate f2
    WHERE f2.fid in (SELECT c.fid FROM Curs c WHERE c.sala in(SELECT s.cods FROM Sala s WHERE s.etaj = 2));

SELECT
    f1.fid,
    f1.nume,
    f1.adr
FROM Facultate f1
WHERE f1.fid IN (SELECT c1.fid FROM Curs c1 WHERE sala IN(SELECT cods FROM Sala WHERE etaj = 1))
INTERSECT
SELECT
    f2.fid,
    f2.nume,
    f2.adr
FROM Facultate f2 JOIN Curs c2
                  ON f2.fid = c2.fid
                  JOIN Sala s
                  ON c2.sala = s.cods
WHERE s.etaj = 2;

-- L6.Ex5. Folosind intersecția să se listeze studenții (sid, nume,
-- an, bursa) nu au bursa (0 sau NULL) și au ore în sala A101.

SELECT 
    s1.sid,
    s1.nume,
    s1.an,
    s1.bursa
FROM Student s1
WHERE s1.bursa = 0 OR s1.bursa IS NULL
INTERSECT
SELECT 
    s2.sid,
    s2.nume,
    s2.an,
    s2.bursa
FROM Student s2
WHERE s2.sid IN (SELECT ct.sid FROM Contract ct WHERE ct.cid IN (SELECT c.cid FROM Curs c WHERE sala = 'A101'));

SELECT 
    s1.sid,
    s1.nume,
    s1.an,
    s1.bursa
FROM Student s1
WHERE s1.bursa = 0 OR s1.bursa IS NULL
INTERSECT
SELECT 
    s2.sid,
    s2.nume,
    s2.an,
    s2.bursa
FROM Student s2 JOIN Contract ct
                ON s2.sid = ct.sid
                JOIN Curs c
                ON ct.cid = c.cid
WHERE sala = 'A101';

-- L6.Ex6. Folosind diferența să se listeze studenții (sid, nume,
-- an, bursa) sunt înscriși facultatea care are numărul de telefon
-- '0256-403211' și nu au ore cu profesorul Ciprian Porumbescu.

SELECT 
    s1.sid,
    s1.nume,
    s1.an,
    s1.bursa
FROM Student s1 JOIN Facultate f1
                ON s1.fid = f1.fid
WHERE f1.tel = '0256-403211'
MINUS
SELECT 
    s2.sid,
    s2.nume,
    s2.an,
    s2.bursa
FROM Student s2 JOIN Contract ct
                ON ct.sid  = s2.sid
                JOIN Curs c
                ON ct.cid = c.cid
                JOIN Profesor p
                ON c.pid = p.pid
WHERE p.nume LIKE 'Ciprian Porumbescu';

-- asta de jos nu cred ca e bun

SELECT 
    s1.sid,
    s1.nume,
    s1.an,
    s1.bursa
FROM Student s1 JOIN Facultate f
                ON s1.fid = f.fid
WHERE f.tel = '0256-403211'
MINUS
SELECT 
    s2.sid,
    s2.nume,
    s2.an,
    s2.bursa
FROM Student s2 
WHERE s2.fid NOT IN (SELECT fid FROM Profesor WHERE nume = 'Ciprian Porumbescu');