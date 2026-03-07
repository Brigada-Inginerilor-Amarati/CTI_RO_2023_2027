# Simulare Joc de Cruce (4 Jucători)

## Descriere Generală
Acest proiect reprezintă o simulare în consolă a jocului de cărți **Cruce** (o variantă a jocului 66 jucată în 4 persoane). Aplicația gestionează fluxul complet al unei partide: de la formarea echipelor și împărțirea cărților, până la faza de licitație, jocul celor 6 ture și calculul final al punctajelor.

Scopul proiectului este de a modela logica și regulile stricte ale jocului folosind principii moderne de programare orientată pe obiecte în C#.

---

## Arhitectura Codului & Explicații
Proiectul este structurat în clase cu responsabilități bine definite, pentru a menține codul modular și ușor de întreținut.

### 1. Modelarea Datelor (`Carte` și `Culoare`)
- **De ce așa?** Am ales să definesc `Culoare` ca un `enum` (Roșu, Dubă, Verde, Ghindă) și nu ca string, pentru a evita erorile de scriere și pentru a face verificările (ex: `c.Culoare == tromf`) mult mai rapide și sigure.
- Clasa `Carte` încapsulează atât valoarea (Număr) cât și suita, fiind obiectul fundamental vehiculat în listele de `Carti` ale jucătorilor.

### 2. Entitatea `Jucator`
Această clasă reține starea fiecărui participant:
- **EchipaOriginală**: Este crucială pentru calculul final, știind că jucătorii din Echipa 1 (index 0 și 2) colaborează contra Echipei 2.
- **Metoda `PuneCarte`**: Am inclus logica de interacțiune cu consola aici. Metoda validează inputul utilizatorului, asigurându-se că nu se introduc indecși invalizi și că utilizatorul vede mereu ce cărți are în mână.

### 3. Logica Jocului (`Joc`)
Aceasta este clasa "Controller" care gestionează regulile complexe.
- **GestioneazaTureJoc**: Este inima simulării. Iterează de 6 ori (numărul de ture), gestionează ordinea jucătorilor (care se schimbă în funcție de cine câștigă tura anterioară) și colectează cărțile de pe masă.
- **Validarea Regulilor**: Am implementat verificări stricte în bucla de joc:
  - *Rule*: Dacă ai culoarea cerută, ești obligat să o dai.
  - *Rule*: Dacă nu o ai, ești obligat să tai cu tromf (dacă ai).
  - Folosirea `do-while` asigură că jucătorul nu poate trece mai departe până nu joacă o carte validă.
- **Anunțurile (40/20)**: Funcțiile `VerificaAnunt40` și `VerificaAnunt20` scanează mâna jucătorului la momentul oportun pentru a acorda automat punctele bonus, respectând regula că anunțul se face doar când ești la rând.

### 4. Programul Principal (`Program`)
- Folosește LINQ (`Where`, `Select`, `First`, `Sum`) pentru operații eficiente pe colecții. De exemplu, calculul punctajului total exclude automat cărțile de 9 (`c.Numar != 9`) printr-o simplă filtrare.
- Logica de **Puncte Mari** și penalizări: La final, programul verifică dacă echipa care a câștigat licitația și-a atins obiectivul. Dacă nu, aplică penalizarea corespunzătoare conform regulamentului.

---

## Decizii de Implementare
1.  **Gestionarea atuurilor (Tromf)**:
    - Am ales varianta de regulament "Cruce în 4 clasic", unde tromful este dat de prima carte jucată de câștigătorul licitației. Aceasta simplifică fluxul față de variantele unde tromful se alege verbal.

2.  **Structuri de Date**:
    - Am folosit `List<Carte>` pentru flexibilitate (adăugare/ștergere ușoară).
    - `Tuple<Jucator, Jucator>` pentru echipe, deoarece o echipă este o pereche fixă și imuabilă pe durata jocului.

3.  **Algoritmul de Câștig**:
    - Funcția `DeterminaCastigatorulTurei` filtrează cărțile de pe masă. Mai întâi caută tromfi. Dacă există, cel mai mare tromf câștigă. Dacă nu, cea mai mare carte de culoarea primei cărți jucate câștigă. Această logică stratificată reflectă fidel realitatea jocului.

## Concluzie
Proiectul demonstrează utilizarea conceptelor de OOP (încapsulare, abstractizare) combinată cu logică algoritmică pentru validarea constrângerilor unui joc real. Codul este robust la inputuri greșite și oferă o experiență transparentă prin mesaje detaliate în consolă.
