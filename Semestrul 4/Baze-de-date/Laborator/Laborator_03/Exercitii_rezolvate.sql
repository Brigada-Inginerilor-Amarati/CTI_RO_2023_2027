-- Exercitiul 1
SELECT *FROM Student
    where nume like '%u';

-- Exercitiul 2
SELECT 
    substr(nume, instr(nume, ' ') + 1) as nume,
    substr(nume, 1, instr(nume, ' ') - 1) as prenume,
    an
FROM Student;

-- Exercitiul 3
SELECT
    nume,
    substr(nume, 1, instr(nume, ' ') - 1) as prenume,
    length(substr(nume, 1, instr(nume, ' ') - 1)) as lungimePrenume
FROM Student
    where length(substr(nume, 1, instr(nume, ' ') - 1)) >= 7;

-- Exercitiul 4
SELECT
    nume, 
    an,
    datan
FROM Student
    where EXTRACT(year from datan) = EXTRACT(year from sysdate) - 20;

SELECT
    nume,
    an,
    datan
FROM Student
    WHERE extract(year FROM SYSDATE) - extract(year FROM datan) = 20;

-- Exercitiul 5
SELECT * FROM Student
    where EXTRACT(month from datan) = EXTRACT(month from sysdate);

-- Exercitiul 6
SELECT * FROM Student 
    WHERE TRIM(BURSA) IS NULL OR TRIM(BURSA) = '-';

SELECT * FROM Student
    where bursa is NULL or bursa=0;     -- nu au bursa

SELECT * FROM Student
    where bursa is NULL;        -- bursa este necompletata



-- Exercitiul 7
SELECT nume, an, nvl(cnp, 'CNP necompletat') as CNP FROM Student
    WHERE an = 2;

-- Exercitiul 8
SELECT nume, cnp, an FROM Student where substr(cnp, 1, 1) in ('2', '4', '6');
SELECT nume, cnp, an FROM Student where substr(cnp, 1, 1) in ('1', '3', '5');

SELECT
    nume,
    cnp,
    an
FROM Student
    WHERE cnp LIKE '2%';

-- Exercitiul 9
SELECT nume, an, 
    CASE 
        WHEN substr(cnp, 1, 1) in ('1', '3', '5') THEN 'Baieti'
        WHEN substr(cnp, 1, 1) in ('2', '4', '6') THEN 'Fete'
        ELSE 'Nedeterminat'
    END AS grup
FROM Student;

SELECT
    nume,
    an,
    CASE 
        WHEN cnp LIKE '2%' THEN 'fete'
        WHEN cnp LIKE '1%' THEN 'baieti'
        ELSE 'Others'
    END as Grup
FROM Student;