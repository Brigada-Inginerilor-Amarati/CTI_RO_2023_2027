-- Oracle APEX 22.2.2 SQL
-- Schema: BD_Universitate
-- DAN.PESCARU@CS.UPT.RO

drop table Contract cascade constraints;
drop table Curs cascade constraints;
drop table Sala cascade constraints;
drop table Profesor cascade constraints;
drop table Student cascade constraints;
drop table Facultate cascade constraints;

CREATE TABLE Facultate(
fid CHAR (3) NOT NULL,  --id facultate
nume VARCHAR2 (40),     --nume facultate
adr VARCHAR2 (40),      --adresa facultate
tel VARCHAR2 (12),      --telefon principal facultate 
CONSTRAINT facult_pk PRIMARY KEY(fid)
);

CREATE TABLE Student(
sid CHAR(6) NOT NULL,   --id student = numar matricol
cnp CHAR (13),          --cod numeric personal
nume VARCHAR2(40) NOT NULL, --numele studentului
datan DATE,             --data nasterii
adr VARCHAR2 (40),      --adresa student
an NUMBER(1) NOT NULL,  --anul de studiu (1,2,3,4, in cazuri particulare 5,6)
media NUMBER (4,2),     --media anuala a ultimului an absolvit
bursa NUMBER (5,0),     --bursa actuala
fid CHAR (3) NOT NULL , --id facultate din care face parte studentul
CONSTRAINT stud_pk PRIMARY KEY(sid),
CONSTRAINT facult_fk  FOREIGN KEY (fid) REFERENCES Facultate(fid) on delete cascade
);


CREATE TABLE Profesor(
pid CHAR (6) NOT NULL,  --id profesor
cnp CHAR (13),          --cod numeric personal
nume VARCHAR2 (40),     --numele profesorului
datan DATE,             --data nasterii
fid CHAR (3) NOT NULL,  --id facultate din care face parte
grad varchar2(4) NOT NULL, -- grad didactic
CONSTRAINT prof_pk PRIMARY KEY(pid),
CONSTRAINT pfacult_fk  FOREIGN KEY (fid) REFERENCES Facultate(fid) on delete cascade,
CONSTRAINT pgradedidactiveexistent_ck CHECK(grad IN ('as', 'sl', 'conf', 'prof')) -- asistent, lector, sef de lucrari, conferentiar, profesor
);

CREATE TABLE Sala(
cods CHAR (4) NOT NULL, --cod sala
etaj NUMBER (2),        --etaj
nrlocuri NUMBER (3),    --numar maxim de locuri in sala
CONSTRAINT sala_pk PRIMARY KEY(cods)
);

CREATE TABLE Curs(
cid CHAR (5) NOT NULL,  --id curs
titlu VARCHAR2 (32) NOT NULL, --titlu curs
fid CHAR (3) NOT NULL,  --id facultate care pune la dispozitie cursul
an number(1), -- anul in care se tine cursul, daca este optional anul e null (ex. pedagogie)
semestru number (2) NOT NULL, --semestrul cand se tine cursul, sem 1 si 2 sunt in anul 1, sem 3 si 4 sunt in anul 2 sem 5 si 6 sunt etc.
pid CHAR (6),           --id profesor titular
zi VARCHAR2 (8),        --ziua din saptamana in care are loc cursul
ora NUMBER (2),         --ora la care are loc cursul
sala CHAR (4),          --codul salii in care are loc cursul
CONSTRAINT crs_pk PRIMARY KEY(cid),
CONSTRAINT cfacult_fk  FOREIGN KEY (fid) REFERENCES Facultate(fid) on delete cascade,
CONSTRAINT crssala_fk  FOREIGN KEY (sala) REFERENCES Sala(cods) on delete cascade,
CONSTRAINT crsprof_fk  FOREIGN KEY (pid) REFERENCES Profesor(pid) on delete cascade
);

CREATE TABLE Contract(
nrc NUMBER (5) NOT NULL,--numar contract
sid CHAR (6) NOT NULL,  --id student care a semnat contractul
cid CHAR(5) NOT NULL,   --id curs pentru care s-a facut contractul
an NUMBER (4) NOT NULL, --anul caledndaristic in care s-a semnat contractul (ex. 2023 pt anul scolar 2023/2024)
semestru NUMBER (1),    --semestrul cand are loc cursul pentu care s-a semnat contractul
nota NUMBER (4,2),      --nota finala la cursul contractat in anul in care s-a semnat contractul
CONSTRAINT contr_pk PRIMARY KEY(nrc),
CONSTRAINT constd_fk  FOREIGN KEY (sid) REFERENCES Student(sid) on delete cascade,
CONSTRAINT concrs_fk  FOREIGN KEY (cid) REFERENCES Curs(cid) on delete cascade
);