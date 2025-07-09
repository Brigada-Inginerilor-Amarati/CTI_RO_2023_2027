-- Laborator\Test_05_agregarea_datelor\IMG-20250302-WA0008.jpg

-- 5 rows

-- 2025	4.84
-- 2024	7.02
-- 2021	7.13
-- 2023	6.81
-- 2022	7.15

SELECT
    an,
    trunc(avg(nota), 2)
FROM Contract
WHERE semestru = 2
GROUP BY an

-- Laborator\Test_05_agregarea_datelor\IMG-20250302-WA0009.jpg

-- 2025	.34
-- 2024	3.42
-- 2021	2.38
-- 2022	4.07
-- 2023	3.88

SELECT
    an,
    trunc(variance(nota), 2)
FROM Contract 
WHERE semestru = 1
GROUP BY an

-- Laborator\Test_05_agregarea_datelor\IMG-20250302-WA0011.jpg

-- SUM(NRLOCURI)	ETAJ
-- 1775	        1
-- 544	            2
-- 490	            3

SELECT
    sum(nrlocuri),
    etaj
FROM Sala
GROUP by etaj

-- Laborator\Test_05_agregarea_datelor\IMG-20250302-WA0065.jpg

-- 17

SELECT
    count(titlu)
FROM Curs
WHERE semestru = 1

-- Laborator\Test_05_agregarea_datelor\IMG-20250302-WA0066.jpg

-- 18

SELECT
    count(sid) as nrStudenti
FROM Student
WHERE media >= 7 AND media <= 9

-- Laborator\Test_05_agregarea_datelor\IMG-20250302-WA0067.jpg

-- GRAD	    COUNT(PID)
-- conf	        7
-- prof	        7
-- as	        8

SELECT
    grad,
    count(pid)
FROM Profesor
GROUP BY grad
HAVING count(pid) > 5 

-- Laborator\Test_05_agregarea_datelor\IMG-20250302-WA0069.jpg


-- MIN(DATAN)
-- 11/18/2000

SELECT
    min(datan)
FROM Student


-- Laborator\Test_05_agregarea_datelor\IMG-20250302-WA0208.jpg

-- e si mai sus de fapt

-- 17

SELECT
    count(cid)
FROM Curs
WHERE semestru = 1