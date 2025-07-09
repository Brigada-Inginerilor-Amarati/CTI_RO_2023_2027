-- Laborator 7

-- activitate 1

-- la count null nu se calculeaza

SELECT COUNT(*) AS nrStud,
 COUNT(bursa) AS nrBurse,
 COUNT(DISTINCT bursa) AS nrNiveluriBurse
 FROM Student;

 -- activitate 2

 SELECT MIN(bursa) AS bmin, MAX(bursa) AS bmax
 FROM Student
 WHERE bursa > 0;

 -- activitate 3

 SELECT trunc(variance(media),2) AS varianta,
 trunc(avg(media),2) - trunc(stddev(media),2) AS m1,
 trunc(avg(media),2) + trunc(stddev(media),2) AS m2
 FROM Student;

 -- activitate 4

 SELECT an AS anStudiu, COUNT(*) AS nrStudAn
 FROM Student
 GROUP BY an
 HAVING COUNT(*) > 3;

-- L7.Ex1. Să se calculeze numărul de studenți care nu au bursă
-- și au media peste 7.50.

SELECT COUNT(*) AS nrStudenti
FROM Student
WHERE (bursa = 0 OR bursa IS NULL) AND media > 7.5

-- L7.Ex2. Să se calculeze numărul de studenți care au ore cu
-- profesorul 'Luca Caragiale'.

SELECT COUNT(DISTINCT s.sid) AS nrStudenti
FROM Student s JOIN Contract ct
               ON s.sid = ct.sid
               JOIN Curs c
               ON ct.cid = c.cid
               JOIN Profesor p
               ON c.pid = p.pid
WHERE p.nume = 'Luca Caragiale';

-- L7.Ex3. Să se calculeze numărul total de studenți care au ore
-- la etajul 1 (încărcarea sălilor de la etajul 1), indiferent de
-- facultate si de zi.

SELECT COUNT(DISTINCT s.sid) AS nrStudenti
FROM Student s JOIN Contract ct
               ON s.sid = ct.sid
               JOIN Curs c
               ON ct.cid = c.cid
               JOIN Sala s
               ON c.sala = s.cods
WHERE s.etaj = 1;

-- L7.Ex4. Să se afișeze data nașterii celui mai tânăr și celui mai
-- bătrân student din anul 2.

SELECT MIN(datan) as celMaiTanar, MAX(datan) as celMaiBatran
FROM Student 
WHERE an = 2;

-- L7.Ex5. Să se calculeze suma și media burselor pe fiecare an
-- de studiu la fiecare facultate. Se vor afișa numele facultății, anul
-- de studiu, suma și media burselor.

SELECT SUM(s.bursa) AS sumaBurse,
       trunc(AVG(s.bursa), 2) AS medieBurse,
       s.an,
       (SELECT nume FROM Facultate WHERE fid = s.fid) as numeFacultate
FROM Student s
GROUP BY s.an, s.fid
ORDER BY an;


SELECT 
    f.nume, 
    s.an,
    SUM(s.bursa) AS sumaBurse,
    trunc(AVG(s.bursa), 2) AS medieBurse
FROM Student s

-- L7.Ex6. Să se afișeze bursa minimă (>0), medie și maximă a
-- tuturor studenților care au ore in ziua de 'Luni', indiferent de curs.

SELECT 
    MIN(s.bursa) AS minBursa,
    AVG(s.bursa) AS avgBursa,
    MAX(s.bursa) AS maxBursa
FROM Student s JOIN Contract ct
               ON s.sid = ct.sid
               JOIN Curs c
               ON ct.cid = c.cid
WHERE c.zi = 'Luni' AND s.bursa > 0;

-- L7.Ex7. Folosind subinterogări și agregări să se afișeze toți
-- studenții cu bursa peste bursa medie din universitate.

SELECT 
    AVG(s.bursa) as medieBurse
FROM Student s 
WHERE s.bursa > 0

SELECT DISTINCT * FROM Student st WHERE st.bursa > (SELECT 
                                             AVG(s.bursa) as medieBurse
                                             FROM Student s 
                                             WHERE s.bursa > 0);

-- L7.Ex8. Să se calculeze intervalul de normalitate a mediilor
-- pentru fiecare facultate în parte. Se va afișa numele fiecărei
-- facultăți precum și pragurile de jos și de sus a intervalului de
-- normalitate pentru mediile studenților din acea facultate.

SELECT trunc(variance(s.media), 2) AS varianta,
    trunc(avg(s.media), 2) - trunc(stddev(s.media), 2) AS m1,
    trunc(avg(s.media), 2) + trunc(stddev(s.media), 2) AS m2,
    f.nume
FROM Student s JOIN Facultate f
               ON s.fid = f.fid
GROUP BY f.nume;

-- L7.Ex9. Folosind subinterogări și agregări să se afișeze toți
-- studenții care au medii în afara intervalului de normalitate a
-- mediilor pe universitate.

SELECT
    s.nume,
    s.media
FROM Student s
WHERE s.media NOT BETWEEN (SELECT trunc(avg(s.media), 2) - trunc(stddev(s.media), 2) AS m1 FROM Student s) AND (SELECT trunc(avg(s.media), 2) + trunc(stddev(s.media), 2) AS m2 FROM Student s);
-- Laborator 7

-- activitate 1

-- la count null nu se calculeaza

SELECT COUNT(*) AS nrStud,
 COUNT(bursa) AS nrBurse,
 COUNT(DISTINCT bursa) AS nrNiveluriBurse
 FROM Student;

 -- activitate 2

 SELECT MIN(bursa) AS bmin, MAX(bursa) AS bmax
 FROM Student
 WHERE bursa > 0;

 -- activitate 3

 SELECT trunc(variance(media),2) AS varianta,
 trunc(avg(media),2) - trunc(stddev(media),2) AS m1,
 trunc(avg(media),2) + trunc(stddev(media),2) AS m2
 FROM Student;

 -- activitate 4

 SELECT an AS anStudiu, COUNT(*) AS nrStudAn
 FROM Student
 GROUP BY an
 HAVING COUNT(*) > 3;

-- L7.Ex1. Să se calculeze numărul de studenți care nu au bursă
-- și au media peste 7.50.

SELECT COUNT(*) AS nrStudenti
FROM Student
WHERE (bursa = 0 OR bursa IS NULL) AND media > 7.5

-- L7.Ex2. Să se calculeze numărul de studenți care au ore cu
-- profesorul 'Luca Caragiale'.

SELECT COUNT(DISTINCT s.sid) AS nrStudenti
FROM Student s JOIN Contract ct
               ON s.sid = ct.sid
               JOIN Curs c
               ON ct.cid = c.cid
               JOIN Profesor p
               ON c.pid = p.pid
WHERE p.nume = 'Luca Caragiale';

-- L7.Ex3. Să se calculeze numărul total de studenți care au ore
-- la etajul 1 (încărcarea sălilor de la etajul 1), indiferent de
-- facultate si de zi.

SELECT COUNT(DISTINCT s.sid) AS nrStudenti
FROM Student s JOIN Contract ct
               ON s.sid = ct.sid
               JOIN Curs c
               ON ct.cid = c.cid
               JOIN Sala s
               ON c.sala = s.cods
WHERE s.etaj = 1;

-- L7.Ex4. Să se afișeze data nașterii celui mai tânăr și celui mai
-- bătrân student din anul 2.

SELECT MIN(datan) as celMaiTanar, MAX(datan) as celMaiBatran
FROM Student 
WHERE an = 2;

-- L7.Ex5. Să se calculeze suma și media burselor pe fiecare an
-- de studiu la fiecare facultate. Se vor afișa numele facultății, anul
-- de studiu, suma și media burselor.

SELECT SUM(s.bursa) AS sumaBurse,
       trunc(AVG(s.bursa), 2) AS medieBurse,
       s.an,
       (SELECT nume FROM Facultate WHERE fid = s.fid) as numeFacultate
FROM Student s
GROUP BY s.an, s.fid
ORDER BY an;


-- SELECT 
--     f.nume, 
--     s.an,
--     SUM(s.bursa) AS sumaBurse,
--     trunc(AVG(s.bursa), 2) AS medieBurse
-- FROM Student s

-- L7.Ex6. Să se afișeze bursa minimă (>0), medie și maximă a
-- tuturor studenților care au ore in ziua de 'Luni', indiferent de curs.

SELECT 
    MIN(s.bursa) AS minBursa,
    AVG(s.bursa) AS avgBursa,
    MAX(s.bursa) AS maxBursa
FROM Student s JOIN Contract ct
               ON s.sid = ct.sid
               JOIN Curs c
               ON ct.cid = c.cid
WHERE c.zi = 'Luni' AND s.bursa > 0;

-- L7.Ex7. Folosind subinterogări și agregări să se afișeze toți
-- studenții cu bursa peste bursa medie din universitate.

SELECT 
    AVG(s.bursa) as medieBurse
FROM Student s 
WHERE s.bursa > 0

SELECT DISTINCT * FROM Student st WHERE st.bursa > (SELECT 
                                             AVG(s.bursa) as medieBurse
                                             FROM Student s 
                                             WHERE s.bursa > 0);

-- L7.Ex8. Să se calculeze intervalul de normalitate a mediilor
-- pentru fiecare facultate în parte. Se va afișa numele fiecărei
-- facultăți precum și pragurile de jos și de sus a intervalului de
-- normalitate pentru mediile studenților din acea facultate.

SELECT trunc(variance(s.media), 2) AS varianta,
    trunc(avg(s.media), 2) - trunc(stddev(s.media), 2) AS m1,
    trunc(avg(s.media), 2) + trunc(stddev(s.media), 2) AS m2,
    f.nume
FROM Student s JOIN Facultate f
               ON s.fid = f.fid
GROUP BY f.nume;

-- L7.Ex9. Folosind subinterogări și agregări să se afișeze toți
-- studenții care au medii în afara intervalului de normalitate a
-- mediilor pe universitate.

SELECT
    s.nume,
    s.media
FROM Student s
WHERE s.media NOT BETWEEN (SELECT trunc(avg(s.media), 2) - trunc(stddev(s.media), 2) AS m1 FROM Student s) AND (SELECT trunc(avg(s.media), 2) + trunc(stddev(s.media), 2) AS m2 FROM Student s);
