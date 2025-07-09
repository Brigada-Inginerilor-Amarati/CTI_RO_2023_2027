-- p1
SELECT * FROM Student
WHERE 
    fid = 'AC'
    and
    media < (SELECT media from Student where cnp = '1050404304578');

-- p2
SELECT
    s.*,
    f.fid
FROM Student s JOIN Facultate f
                ON s.fid = f.fid
WHERE s.bursa <= ALL
      (SELECT bursa FROM Student 
       WHERE bursa IS NOT NULL AND bursa != 0) AND f.fid = 'AC';


SELECT DISTINCT
    bursa,
    fid
FROM Student
WHERE bursa <= ALL(SELECT bursa FROM Student WHERE bursa is NOT NULL and bursa <> 0) and bursa <> 0 and fid = 'AC';

-- p3

SELECT *
FROM Curs
WHERE sala in (SELECT cods FROM Sala WHERE nrlocuri > 100);

-- p4

SELECT *
FROM Sala
WHERE cods in(SELECT sala FROM Curs WHERE fid = 'MEC' ) AND cods in (SELECT sala FROM Curs WHERE fid = 'AC');

--p5
SELECT *
FROM Student s1,
(SELECT * FROM Student) s2
    where s1.bursa = s2.bursa AND s1.media = s2.media AND s1.sid <> s2.sid;



SELECT s1.* FROM Student s1 WHERE EXISTS (SELECT * FROM Student s2 where s2.bursa = s1.bursa AND s2.media = s1.media AND s2.sid <> s1.sid);

-- p6

SELECT
    f.fid,
    f.nume
FROM Facultate f
WHERE EXISTS (
    SELECT * FROM Student s 
    WHERE s.fid = f.fid 
    AND s.bursa >= ALL(SELECT bursa FROM Student WHERE bursa IS NOT NULL AND bursa != 0)
);