# Test 2 PDSS

## Code Smells

### **Potrivește definiția cu numele mirosului de cod (Code Smell):**

**A.** Este dificil să reutilizați o clasă într-un alt proiect, deoarece clasa are multe dependențe care trebuie luate împreună.
**B.** La implementarea unei modificări a unui algoritm, apar frecvent erori neașteptate în zone aparent fără legătură.
**C.** O bază de cod este foarte complexă și greu de întreținut deoarece există multe abstracțiuni (interfețe) care nu sunt utilizate des.
**D.** Modificările nu sunt implementate localizat, într-un singur fișier; chiar și o schimbare mică necesită modificarea a cel puțin 10 fișiere.
**E.** Chiar și pentru 2 rânduri de cod schimbate, este nevoie de aproximativ 5 ore pentru a vedea rezultatul, din cauza unui proces foarte lent de compilare/build/deploy.

### **Potriviri:**

1. **Immobility (Imobilitate)** – \_\_\_
2. **Fragility (Fragilitate)** – \_\_\_
3. **Needless Complexity (Complexitate Inutilă)** – \_\_\_
4. **Rigidity (Rigiditate)** – \_\_\_
5. **Viscosity (Viscozitate)** – \_\_\_

---

### **Răspuns corect:**

- **A → 1. Immobility (Imobilitate)**
- **B → 2. Fragility (Fragilitate)**
- **C → 3. Needless Complexity (Complexitate Inutilă)**
- **D → 4. Rigidity (Rigiditate)**
- **E → 5. Viscosity (Viscozitate)**

---

## Exercițiu DIP + ISP – CampusService

O universitate a dezvoltat un sistem de gestionare a campusului intern, folosit de studenți, cadre didactice și personal administrativ. Sistemul are o clasă numită `CampusService` care se ocupă de diverse sarcini fără legătură între ele, cum ar fi:

- înregistrarea studenților
- programarea cursurilor
- procesarea plăților
- solicitările de întreținere

Această clasă se află într-o **bibliotecă partajată**, folosită de mai multe aplicații independente din cadrul universității. Multe dintre acestea sunt întreținute de departamente diferite sau de contractori externi.
**Orice modificare a interfeței clasei `CampusService` ar putea afecta multe aplicații externe.**

Pentru a reduce cuplarea și a îmbunătăți flexibilitatea, departamentul IT a decis să aplice:

- **Dependency Inversion Principle (DIP)**
- **Interface Segregation Principle (ISP)**

Au creat o serie de interfețe, fiecare reprezentând o responsabilitate specifică a clasei `CampusService`. Sistemele dependente folosesc acum **doar interfața relevantă pentru ele**.
Această abordare minimizează dependența lor de implementarea concretă a clasei `CampusService`.

> **Notă:** Pentru a folosi interfețele, codul clienților va trebui actualizat pentru a depinde de abstracții în loc să folosească direct clasa `CampusService`.

---

### **Codul inițial**

```java
public class CampusService {

    public void enrollStudentInCourse(Student student, Course course) {
        // Enrollment logic
    }

    public void scheduleCourse(Course course, TimeSlot timeSlot) {
        // Scheduling logic
    }

    public void processTuitionPayment(Student student, Payment payment) {
        // Payment processing logic
    }

    public void submitMaintenanceRequest(MaintenanceRequest request) {
        // Maintenance request logic
    }

    // ... other campus-related services ...
}

public class Student {
    private String studentId;
    private String name;
    // ... additional properties and methods ...
}

public class Course {
    private String courseId;
    private String title;
    // ... additional properties and methods ...
}
```

---

#### **Cod refactorizat cu DIP + ISP**

```java
public interface IEnrollmentService {
    void enrollStudentInCourse(Student student, Course course);
}

public interface ISchedulingService {
    void scheduleCourse(Course course, TimeSlot timeSlot);
}

public interface IPaymentService {
    void processTuitionPayment(Student student, Payment payment);
}

public interface IMaintenanceService {
    void submitMaintenanceRequest(MaintenanceRequest request);
}

public class CampusService implements
        IEnrollmentService,
        ISchedulingService,
        IPaymentService,
        IMaintenanceService {

    @Override
    public void enrollStudentInCourse(Student student, Course course) {
        // Enrollment logic
    }

    @Override
    public void scheduleCourse(Course course, TimeSlot timeSlot) {
        // Scheduling logic
    }

    @Override
    public void processTuitionPayment(Student student, Payment payment) {
        // Payment processing logic
    }

    @Override
    public void submitMaintenanceRequest(MaintenanceRequest request) {
        // Maintenance request logic
    }
}
```

---

### ❓ **Întrebarea**

Pe baza refactorizării de mai sus, selectați **două afirmații corecte**:

a) Această soluție îmbunătățește modularitatea și mentenabilitatea prin separarea dependențelor clienților de implementarea `CampusService` și permite clienților să depindă doar de interfețe.

b) Acest design este aliniat cu Principiul Responsabilității Unice (SRP), deoarece `CampusService` are acum o singură responsabilitate și este mai ușor de întreținut.

c) Soluția bazată pe interfețe ar necesita rescrierea codului clienților pentru a folosi noile interfețe, introducând o posibilă mare suprasarcină de dezvoltare pentru toate aplicațiile client.

d) Această abordare crește cuplarea între aplicațiile client și `CampusService`, deoarece mai multe aplicații folosesc aceeași clasă, ceea ce ar putea duce la mai multe conflicte.

e) Utilizarea interfețelor elimină necesitatea ca aplicațiile client să rescrie codul, deoarece acestea pot adopta noua structură fără nicio modificare.

---

### ✅ **Răspuns corect: a) și c)**

#### ✔️ **a) Corectă**

Refactorizarea permite aplicațiilor client să depindă de interfețe precum:

- `IEnrollmentService`
- `ISchedulingService`
- `IPaymentService`
- `IMaintenanceService`

Acestea sunt **abstracții** → deci exact ce cere DIP.
Fiecare client se cuplează doar cu ce are nevoie → ISP.

**Rezultat:**
✔ modularitate crescută
✔ mentenabilitate crescută
✔ cuplare redusă la minim

---

#### ❌ **b) Greșită**

Deși sistemul respectă DIP și ISP, clasa `CampusService` **NU** are acum o singură responsabilitate.

Ea **încă face 4 lucruri diferite**, doar că expune aceste responsabilități prin interfețe separate.
SRP = 0.
ISP = 100.

---

#### ✔️ **c) Corectă**

Enunțul chiar specifică:

> „Pentru a folosi interfețele, codul clienților va trebui actualizat…”

Deci clienții trebuie să schimbe:

```java
CampusService campus = new CampusService();
// devine
IEnrollmentService service = new CampusService();
```

Acest lucru poate reprezenta:

- timp de dezvoltare
- testare suplimentară
- refactorizare în mai multe aplicații

---

#### ❌ **d) Greșită**

Cuplarea **scade**, nu crește.

Înainte, toate aplicațiile dependente erau obligate să folosească **aceeași clasă mare**.
Acum, ele depind de **interfețe diferite**, deci cuplarea este mult mai mică.

---

#### ❌ **e) Greșită**

Exact opusul realității.

Interfețele **necesită modificări** în codul client.
Clienții nu pot adopta automat structura nouă fără schimbări.

---

## LSP && ISP

1. Enunțul întrebării
   O companie dezvoltă un sistem de automatizare care ar trebui să integreze perfect atât lucrătorii umani, cât și unitățile robotizate. Sistemul este conceput pentru a atribui sarcini, programa pauze și gestionarea energiei. Este esențial ca componenta de programare a sistemului să interacționeze cu lucrătorii și roboții printr-o interfață comună pentru a eficientiza atribuirea sarcinilor. Având în vedere contextul software-ului, analizați modul în care interfața Workable poate duce la încălcări ale principiului de segregare a interfeței (ISP) și ale principiului de înlocuire Liskov (LSP) cu implementările sale HumanWorker și RobotWorker. Cum ar putea aceste încălcări să afecteze alocarea sarcinilor sistemului de automatizare și funcționalitățile de management al energiei? Explicați și recomandați o abordare de refactorizare care s-ar alinia mai bine cu ISP și LSP, asigurându-vă că sistemul poate gestiona atât oamenii, cât și roboții în mod eficient.

```java
interface Workable {
    void work();
    void takeBreak();
    void recharge();
}

class HumanWorker implements Workable {
    public void work() { /* ... */ }
    public void takeBreak() { /* ... */ }
    public void recharge() { /* Humans don't "recharge" in the same way machines might. */ }
}

class RobotWorker implements Workable {
    public void work() { /* ... */ }
    public void takeBreak() { throw new UnsupportedOperationException(); }
    public void recharge() { /* ... */ }
}
```

2. Problema care apare

Interfața Workable amestecă responsabilități diferite (lucru, pauze, energie) și le impune tuturor implementărilor, încălcând ISP. Pentru oameni, recharge nu are sens; pentru roboți, takeBreak nu are sens, deci apar implementări „false” sau excepții. LSP este încălcat deoarece un client care primește un Workable și apelează takeBreak se așteaptă la un comportament valid, dar RobotWorker aruncă UnsupportedOperationException. În programatorul de sarcini asta înseamnă cod fragil, cu if-uri / instanceof și potențiale erori la rulare când se face scheduling unitar pentru oameni și roboți.

3. Soluția propusă

Segregăm Workable în abstractiuni mai mici, în funcție de capabilități: una pentru lucru, una pentru pauză, una pentru reîncărcare. Apoi fiecare tip de „worker” implementează doar ceea ce i se potrivește. Sistemul de automatizare primește dependențe pe aceste abstractiuni specifice: modulul de assignment lucrează cu Worker, modulul de programare pauze cu BreakTaker, modulul de management energie cu Rechargeable. Astfel, orice obiect care implementează o anumită abstractiune garantează că operațiile aferente sunt suportate, respectând LSP și ISP și eliminând metodele „goale” sau excepțiile.

```java
interface Worker {
    void work();
}

interface BreakTaker {
    void takeBreak();
}

interface Rechargeable {
    void recharge();
}

class HumanWorker implements Worker, BreakTaker {
    public void work() { /* ... */ }
    public void takeBreak() { /* humans take breaks */ }
}

class RobotWorker implements Worker, Rechargeable {
    public void work() { /* ... */ }
    public void recharge() { /* recharge battery */ }
}

// Exemple de clienți ai sistemului

class TaskScheduler {
    void assignTask(Worker worker) {
        worker.work();
    }
}

class BreakScheduler {
    void scheduleBreak(BreakTaker worker) {
        worker.takeBreak();
    }
}

class EnergyManager {
    void manageEnergy(Rechargeable unit) {
        unit.recharge();
    }
}
```

4. Cum e mai bună soluția propusă față de soluția inițială

Noua structură respectă ISP, deoarece fiecare tip (uman sau robot) implementează doar abstractiunile relevante pentru el. Respectă LSP, deoarece orice BreakTaker poate lua pauză fără excepții, iar orice Rechargeable poate fi reîncărcat corect. Sistemul de automatizare poate aloca sarcini, pauze și operații de energie în mod sigur și expresiv, fără if-uri speciale pentru tip sau metode care nu au sens pentru unii workeri.

## LoD

1. Enunțul întrebării
   O platformă de comerț electronic utilizează un model DTO (Data Transfer Object) pentru a transmite informații despre utilizator între diferite straturi ale aplicației. UserDTO este populat cu date din baza de date și apoi trimis la stratul UI pentru afișare. În metoda displayUser a clasei UserProfilePage, datele obiectului UserDTO sunt accesate pentru a afișa numele și e-mailul utilizatorului. Încalcă această metodă Legea lui Demeter? Motivați răspunsul având în vedere scopul DTO-urilor.

```java
public class UserDTO {
    private String name;
    private String email;

    // Constructor, getters and setters omitted for brevity
}

public class UserProfilePage {
    public void displayUser(UserDTO user) {
        System.out.println("Name: " + user.getName());
        System.out.println("Email: " + user.getEmail());
    }
}
```

2. Problema care apare

Nu există o încălcare reală a Legii lui Demeter aici. Legea interzice „navigarea” prin lanțuri de obiecte (a.b().c().d()), nu accesarea directă a proprietăților unui DTO primit ca parametru. DTO-ul este un container de date, nu un obiect incapsulat si bogat în comportament.

3. Soluția propusă

Explicația corectă: DTO-urile sunt create exact pentru a fi expuse și accesate direct prin getteri în straturi superioare. Sunt structuri de date plate, fără logică internă, fără invarianți complecși și fără referințe adânci. Accesarea lor nu rupe LoD deoarece UI lucrează cu un „prieten apropiat” (parametrul metodei) și nu creează cuplare în lanț.

Nu este nevoie de modificări. Folosirea getterelor unui DTO în stratul UI este conformă cu LoD.

## OCP

1. Enunțul întrebării
   Un sistem software de întreprindere utilizat în mai multe departamente necesită un instrument de raportare flexibil pentru a răspunde nevoilor de raportare variate și în creștere. Software-ul dispune în prezent de un ReportGenerator care se adresează vânzărilor, inventarului și raportării datelor privind performanța angajaților. Compania anticipează necesitatea unor tipuri de rapoarte suplimentare în viitorul apropiat. Reflectați asupra structurii actuale a ReportGenerator și a metodei sale de gestionare a diferitelor tipuri de rapoarte. Pe măsură ce întreprinderea anticipează necesitatea unor capacități de raportare mai diverse, ce aspecte ale designului actual ar trebui să ia în considerare echipa de dezvoltare în contextul principiului deschis/închis (OCP)? Discutați impactul potențial al adăugării de noi tipuri de rapoarte în cadrul implementării actuale asupra întreținerii și dezvoltării viitoare a instrumentului de raportare.

```java
class ReportGenerator {
    public void generateSalesReport(DataSet dataSet) {
        // Logic to generate sales report
    }

    public void generateInventoryReport(DataSet dataSet) {
        // Logic to generate inventory report
    }

    public void generateEmployeePerformanceReport(DataSet dataSet) {
        // Logic to generate employee performance report
    }

    // ... more report generation methods ...
}

class DataSet {
    // Holds data for reports
}
```

2. Problema care apare

ReportGenerator nu respectă OCP: pentru fiecare tip nou de raport trebuie modificată clasa (nouă metodă, logică nouă). Clasa crește continuu, devine „god class”, testele trebuie rerulate pentru toate rapoartele, iar schimbările pentru un raport pot afecta accidental pe altele. Nu poți adăuga rapoarte într-un modul separat fără să recompilezi și să redistribui întregul ReportGenerator.

3. Soluția propusă

Introducem o abstractiune de raport (Report), iar fiecare tip de raport devine o clasă separată care implementează o operație comună (generate). ReportGenerator devine doar un orchestrator care lucrează cu abstractiunea Report (eventual un factory/registru pentru crearea lor). Pentru un raport nou adăugăm doar o nouă clasă care implementează Report, fără să modificăm ReportGenerator.

```java
interface Report {
    void generate(DataSet dataSet);
}

class SalesReport implements Report {
    @Override
    public void generate(DataSet dataSet) {
        // Logic to generate sales report
    }
}

class InventoryReport implements Report {
    @Override
    public void generate(DataSet dataSet) {
        // Logic to generate inventory report
    }
}

class EmployeePerformanceReport implements Report {
    @Override
    public void generate(DataSet dataSet) {
        // Logic to generate employee performance report
    }
}

class ReportGenerator {
    public void generateReport(Report report, DataSet dataSet) {
        report.generate(dataSet);
    }
}
```

4. Cum e mai bună soluția propusă față de soluția inițială

ReportGenerator devine „închis la modificări” și „deschis la extensii”: pentru un nou tip de raport se creează o nouă implementare a abstractiunii Report, fără modificarea codului existent. Fiecare raport are propriul său loc, mai ușor de testat și întreținut, se pot adăuga rapoarte în module/plugin-uri noi, iar riscul de a rupe rapoarte existente atunci când adaugi unele noi scade semnificativ.
