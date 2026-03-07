# Soluții Detaliate - Test 2 PDSS

Acest document prezintă soluții complete cu motivații detaliate pentru exercițiile din Test 2 PDSS.

---

## 1. Code Smells - Potrivirea Definițiilor

### Enunțul exercițiului

Potrivește definiția cu numele mirosului de cod (Code Smell):

**A.** Este dificil să reutilizați o clasă într-un alt proiect, deoarece clasa are multe dependențe care trebuie luate împreună.

**B.** La implementarea unei modificări a unui algoritm, apar frecvent erori neașteptate în zone aparent fără legătură.

**C.** O bază de cod este foarte complexă și greu de întreținut deoarece există multe abstracțiuni (interfețe) care nu sunt utilizate des.

**D.** Modificările nu sunt implementate localizat, într-un singur fișier; chiar și o schimbare mică necesită modificarea a cel puțin 10 fișiere.

**E.** Chiar și pentru 2 rânduri de cod schimbate, este nevoie de aproximativ 5 ore pentru a vedea rezultatul, din cauza unui proces foarte lent de compilare/build/deploy.

### Răspunsuri și motivații

#### **A → 1. Immobility (Imobilitate)**

**Motivație:**

Immobility (Imobilitate) se referă la dificultatea de a reutiliza cod într-un alt context sau proiect din cauza dependențelor multiple și complexe.

**Caracteristici:**
- Clasa are multe dependențe strâns cuplate
- Nu poate fi extrasă și reutilizată fără a aduce toate dependențele
- Dependențele sunt specifice unui context particular

**Exemplu:**
```java
// Clasă imobilă - nu poate fi reutilizată fără toate dependențele
class OrderProcessor {
    private DatabaseConnection db;
    private EmailService email;
    private PaymentGateway payment;
    private LoggingService logger;
    private ConfigurationManager config;
    // ... multe alte dependențe specifice proiectului
}
```

**Soluție:** Reducerea dependențelor prin dependency injection și dependențe de abstractiuni.

---

#### **B → 2. Fragility (Fragilitate)**

**Motivație:**

Fragility (Fragilitate) se referă la tendința codului de a se strica în locuri neașteptate când se face o modificare aparent simplă.

**Caracteristici:**
- Modificări mici cauzează erori în zone aparent neconectate
- Codul este fragil și imprevizibil
- Testele trebuie rulate pentru întreg sistemul la orice modificare

**Exemplu:**
```java
// Modificarea unei metode afectează alte părți ale sistemului
class UserService {
    public void updateUser(User user) {
        // Modificare aici poate afecta:
        // - OrderService
        // - NotificationService
        // - ReportGenerator
        // etc.
    }
}
```

**Soluție:** Reducerea cuplării, respectarea SRP, izolarea responsabilităților.

---

#### **C → 3. Needless Complexity (Complexitate Inutilă)**

**Motivație:**

Needless Complexity (Complexitate Inutilă) apare când există abstracțiuni sau structuri complexe care nu sunt necesare pentru cerințele actuale.

**Caracteristici:**
- Multe interfețe sau clase abstracte nefolosite
- Design over-engineered pentru cerințele actuale
- Complexitate adăugată fără beneficiu real

**Exemplu:**
```java
// Complexitate inutilă - multe interfețe nefolosite
interface IRepository<T> { }
interface IReadRepository<T> extends IRepository<T> { }
interface IWriteRepository<T> extends IRepository<T> { }
interface ICacheRepository<T> extends IReadRepository<T> { }
// ... dar în practică se folosește doar o clasă simplă
```

**Soluție:** YAGNI (You Aren't Gonna Need It) - adaugă complexitate doar când este necesară.

---

#### **D → 4. Rigidity (Rigiditate)**

**Motivație:**

Rigidity (Rigiditate) se referă la dificultatea de a face modificări localizate - chiar și schimbări mici necesită modificări în multe locuri.

**Caracteristici:**
- O modificare mică necesită schimbări în multe fișiere
- Codul este rigid și rezistent la schimbări
- Modificările nu sunt localizate

**Exemplu:**
```java
// O modificare a structurii User necesită schimbări în:
// - UserService.java
// - UserController.java
// - UserRepository.java
// - UserDTO.java
// - UserValidator.java
// - UserMapper.java
// ... și multe altele
```

**Soluție:** Respectarea OCP, reducerea cuplării, folosirea de abstractiuni stabile.

---

#### **E → 5. Viscosity (Viscozitate)**

**Motivație:**

Viscosity (Viscozitate) se referă la dificultatea de a face modificări corecte - procesul de build/deploy este atât de lent încât dezvoltatorii evită să facă modificări sau aleg soluții mai rapide dar mai puțin corecte.

**Caracteristici:**
- Procesul de compilare/build/deploy este foarte lent
- Dezvoltatorii evită refactorizări din cauza timpului
- Se preferă soluții "quick fixes" în loc de soluții corecte

**Exemplu:**
```java
// Viscosity - proces lent de build
// - Compilare: 30 minute
// - Teste: 45 minute
// - Deploy: 1 oră
// Total: ~2.5 ore pentru a vedea rezultatul unei modificări
```

**Soluție:** Optimizarea procesului de build, testare incrementală, CI/CD eficient.

---

## 2. DIP + ISP – CampusService

### Enunțul problemei

O universitate a dezvoltat un sistem de gestionare a campusului intern, folosit de studenți, cadre didactice și personal administrativ. Sistemul are o clasă numită `CampusService` care se ocupă de diverse sarcini fără legătură între ele:

- înregistrarea studenților
- programarea cursurilor
- procesarea plăților
- solicitările de întreținere

Această clasă se află într-o **bibliotecă partajată**, folosită de mai multe aplicații independente. **Orice modificare a interfeței clasei `CampusService` ar putea afecta multe aplicații externe.**

### Analiza problemei

**Codul inițial:**

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
```

**Probleme identificate:**

1. **Încălcarea DIP**: Clienții depind direct de implementarea concretă `CampusService`, nu de abstractiuni.
2. **Încălcarea ISP**: Clienții sunt forțați să depindă de toate metodele, chiar dacă folosesc doar una.
3. **Cuplare puternică**: Modificările în `CampusService` afectează toți clienții.
4. **Instabilitate**: Clasa se modifică frecvent, afectând aplicațiile externe.

### Soluția propusă

**Codul refactorizat:**

```java
// Interfețe segregate - fiecare cu o responsabilitate specifică
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

// Implementare concretă - implementează toate interfețele
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

// Exemple de clienți - depind doar de interfețele necesare
class StudentEnrollmentApp {
    private final IEnrollmentService enrollmentService;

    StudentEnrollmentApp(IEnrollmentService enrollmentService) {
        this.enrollmentService = enrollmentService;
    }

    void enrollStudent(Student student, Course course) {
        enrollmentService.enrollStudentInCourse(student, course);
    }
}

class CourseSchedulingApp {
    private final ISchedulingService schedulingService;

    CourseSchedulingApp(ISchedulingService schedulingService) {
        this.schedulingService = schedulingService;
    }

    void scheduleCourse(Course course, TimeSlot timeSlot) {
        schedulingService.scheduleCourse(course, timeSlot);
    }
}

class PaymentProcessingApp {
    private final IPaymentService paymentService;

    PaymentProcessingApp(IPaymentService paymentService) {
        this.paymentService = paymentService;
    }

    void processPayment(Student student, Payment payment) {
        paymentService.processTuitionPayment(student, payment);
    }
}
```

### Analiza afirmațiilor

#### ✔️ **a) Corectă**

**Motivație:**

Această soluție îmbunătățește modularitatea și mentenabilitatea prin:

1. **Separarea dependențelor**: Clienții depind de interfețe (abstracțiuni), nu de implementarea concretă.
2. **DIP respectat**: Modulele de nivel înalt (aplicațiile client) depind de abstractiuni (`IEnrollmentService`, etc.), nu de detaliile (`CampusService`).
3. **ISP respectat**: Fiecare client depinde doar de interfața relevantă pentru el.
4. **Cuplare redusă**: Modificările în `CampusService` nu afectează clienții dacă interfețele rămân stabile.

**Rezultat:**
- ✔ Modularitate crescută
- ✔ Mentenabilitate crescută
- ✔ Cuplare redusă la minim

---

#### ❌ **b) Greșită**

**Motivație:**

Deși sistemul respectă DIP și ISP, clasa `CampusService` **NU** are acum o singură responsabilitate.

**Argumente:**
- Ea **încă face 4 lucruri diferite**: enrollment, scheduling, payment, maintenance
- Doar că expune aceste responsabilități prin interfețe separate
- SRP = 0 (nu respectă Single Responsibility Principle)
- ISP = 100 (respectă Interface Segregation Principle)

**Concluzie:** DIP și ISP nu rezolvă automat problema SRP. Pentru a respecta SRP, ar trebui să separăm `CampusService` în clase separate (ex: `EnrollmentService`, `SchedulingService`, etc.).

---

#### ✔️ **c) Corectă**

**Motivație:**

Soluția bazată pe interfețe necesită rescrierea codului clienților.

**Argumente:**

1. **Enunțul specifică explicit:**
   > "Pentru a folosi interfețele, codul clienților va trebui actualizat pentru a depinde de abstracții în loc să folosească direct clasa `CampusService`."

2. **Modificări necesare în clienți:**
   ```java
   // Înainte
   CampusService campus = new CampusService();
   campus.enrollStudentInCourse(student, course);

   // După refactorizare
   IEnrollmentService service = new CampusService();
   service.enrollStudentInCourse(student, course);
   ```

3. **Efort de migrare:**
   - Timp de dezvoltare pentru actualizarea tuturor aplicațiilor client
   - Testare suplimentară pentru a verifica că modificările funcționează corect
   - Refactorizare în mai multe aplicații (potențial multe)
   - Risc de introducere de bug-uri în timpul migrării

**Concluzie:** Este un efort semnificativ, dar necesar pentru a obține beneficiile pe termen lung.

---

#### ❌ **d) Greșită**

**Motivație:**

Cuplarea **scade**, nu crește.

**Argumente:**

1. **Înainte de refactorizare:**
   - Toate aplicațiile dependente erau obligate să folosească **aceeași clasă mare** (`CampusService`)
   - Orice modificare în `CampusService` afecta toate aplicațiile
   - Cuplare puternică și instabilitate

2. **După refactorizare:**
   - Aplicațiile depind de **interfețe diferite** (`IEnrollmentService`, `ISchedulingService`, etc.)
   - Fiecare aplicație depinde doar de ceea ce folosește efectiv
   - Modificările într-o interfață afectează doar clienții acelei interfețe
   - Cuplare redusă semnificativ

**Concluzie:** Cuplarea este mult mai mică după refactorizare.

---

#### ❌ **e) Greșită**

**Motivație:**

Exact opusul realității.

**Argumente:**

1. **Interfețele necesită modificări**: Clienții trebuie să modifice codul pentru a folosi noile interfețe.

2. **Nu este automat**: Clienții nu pot adopta automat structura nouă fără schimbări.

3. **Migrare necesară**: Este necesar un proces de migrare pentru toate aplicațiile client.

**Concluzie:** Afirmația este complet falsă.

---

## 3. LSP && ISP – Workable Interface

### Enunțul problemei

O companie dezvoltă un sistem de automatizare care ar trebui să integreze perfect atât lucrătorii umani, cât și unitățile robotizate. Sistemul este conceput pentru a atribui sarcini, programa pauze și gestionarea energiei.

**Codul problematic:**

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

### Analiza problemei

**De ce încalcă ISP?**

1. **Interfață prea mare**: `Workable` amestecă trei responsabilități diferite (lucru, pauze, energie).
2. **Dependențe forțate**: Clienții sunt forțați să depindă de toate metodele, chiar dacă folosesc doar una.
3. **Implementări incomplete**: 
   - `HumanWorker.recharge()` nu are sens pentru oameni
   - `RobotWorker.takeBreak()` aruncă excepție

**De ce încalcă LSP?**

1. **Substituție nesigură**: Un client care primește un `Workable` și apelează `takeBreak()` se așteaptă la un comportament valid, dar `RobotWorker` aruncă `UnsupportedOperationException`.
2. **Contract încălcat**: Subtipul (`RobotWorker`) nu respectă contractul interfeței de bază (`Workable`).
3. **Comportament neașteptat**: Tipul static este același, dar comportamentul diferă la runtime.

**Impact asupra sistemului:**

- Cod fragil cu `if-uri` / `instanceof` pentru a verifica tipul
- Potențiale erori la rulare când se face scheduling unitar pentru oameni și roboți
- Dificultate în gestionarea corectă a pauzelor și energiei

### Soluția propusă

**Codul refactorizat:**

```java
// Interfețe segregate - fiecare cu o responsabilitate specifică
interface Worker {
    void work();
}

interface BreakTaker {
    void takeBreak();
}

interface Rechargeable {
    void recharge();
}

// Implementări concrete - implementează doar ceea ce este relevant
class HumanWorker implements Worker, BreakTaker {
    public void work() {
        // Logică pentru lucru uman
        performTask();
        logWorkHours();
    }

    public void takeBreak() {
        // Oamenii pot lua pauze
        rest();
        refresh();
    }
}

class RobotWorker implements Worker, Rechargeable {
    public void work() {
        // Logică pentru lucru robot
        executeTask();
        updateStatus();
    }

    public void recharge() {
        // Roboții pot fi reîncărcați
        connectToPower();
        chargeBattery();
        updateBatteryLevel();
    }
}

// Clienți ai sistemului - depind doar de abstractiunile necesare
class TaskScheduler {
    void assignTask(Worker worker) {
        // Poate atribui sarcini atât oamenilor, cât și roboților
        worker.work();
    }

    void assignTasksToWorkers(List<Worker> workers) {
        for (Worker worker : workers) {
            assignTask(worker);
        }
    }
}

class BreakScheduler {
    void scheduleBreak(BreakTaker worker) {
        // Programează pauze doar pentru cei care pot lua pauze
        worker.takeBreak();
    }

    void scheduleBreaksForHumans(List<BreakTaker> workers) {
        for (BreakTaker worker : workers) {
            scheduleBreak(worker);
        }
    }
}

class EnergyManager {
    void manageEnergy(Rechargeable unit) {
        // Gestionează energia doar pentru unitățile reîncărcabile
        if (needsRecharge(unit)) {
            unit.recharge();
        }
    }

    void manageEnergyForRobots(List<Rechargeable> units) {
        for (Rechargeable unit : units) {
            manageEnergy(unit);
        }
    }
}

// Sistem de automatizare complet
class AutomationSystem {
    private TaskScheduler taskScheduler;
    private BreakScheduler breakScheduler;
    private EnergyManager energyManager;

    void runWorkCycle(List<Worker> workers, List<BreakTaker> humans, List<Rechargeable> robots) {
        // Atribuire sarcini
        taskScheduler.assignTasksToWorkers(workers);

        // Programare pauze pentru oameni
        breakScheduler.scheduleBreaksForHumans(humans);

        // Management energie pentru roboți
        energyManager.manageEnergyForRobots(robots);
    }
}
```

### Avantajele soluției

1. **Respectă ISP**: Fiecare tip implementează doar abstractiunile relevante pentru el.
2. **Respectă LSP**: Orice `BreakTaker` poate lua pauză fără excepții, iar orice `Rechargeable` poate fi reîncărcat corect.
3. **Siguranță**: Sistemul poate aloca sarcini, pauze și operații de energie în mod sigur.
4. **Claritate**: Codul este mai expresiv și ușor de înțeles.
5. **Fără if-uri speciale**: Nu mai sunt necesare verificări de tip sau metode care nu au sens.

---

## 4. LoD – UserDTO

### Enunțul problemei

O platformă de comerț electronic utilizează un model DTO (Data Transfer Object) pentru a transmite informații despre utilizator între diferite straturi ale aplicației. `UserDTO` este populat cu date din baza de date și apoi trimis la stratul UI pentru afișare.

**Codul:**

```java
public class UserDTO {
    private String name;
    private String email;

    // Constructor, getters and setters omitted for brevity
    public String getName() { return name; }
    public String getEmail() { return email; }
}

public class UserProfilePage {
    public void displayUser(UserDTO user) {
        System.out.println("Name: " + user.getName());
        System.out.println("Email: " + user.getEmail());
    }
}
```

### Analiza problemei

**Întrebare:** Încalcă această metodă Legea lui Demeter?

**Răspuns:** **NU**, nu încalcă Legea lui Demeter.

### Motivația răspunsului

**Ce spune Legea lui Demeter?**

Legea lui Demeter interzice **"navigarea" prin lanțuri de obiecte** (ex: `a.b().c().d()`), nu accesarea directă a proprietăților unui obiect primit ca parametru.

**De ce nu încalcă LoD?**

1. **Accesare directă**: `UserProfilePage` accesează direct proprietățile unui DTO primit ca parametru (`user.getName()`, `user.getEmail()`).

2. **Nu există lanț de apeluri**: Nu există un lanț de tipul `user.getCustomer().getAddress().getCity()`.

3. **DTO este un "prieten apropiat"**: Parametrul metodei este considerat un "prieten apropiat" conform LoD.

4. **Scopul DTO-urilor**: DTO-urile sunt create exact pentru a fi expuse și accesate direct prin getteri în straturi superioare.

**Caracteristicile DTO-urilor:**

- **Structuri de date plate**: Fără logică internă complexă
- **Fără invarianți complecși**: Doar containere de date
- **Fără referințe adânci**: Nu conțin obiecte complexe care necesită navigare
- **Scop specific**: Transmitere de date între straturi

**Exemplu de încălcare LoD (pentru comparație):**

```java
// Aceasta AR încălca LoD
public void displayUser(UserDTO user) {
    // Lanț de apeluri - încalcă LoD
    System.out.println("City: " + user.getAddress().getCity().getName());
    System.out.println("Country: " + user.getAddress().getCountry().getCode());
}
```

### Soluția

**Nu este nevoie de modificări.**

Folosirea getterelor unui DTO în stratul UI este **conformă cu LoD** și reprezintă practica corectă pentru DTO-uri.

**Recomandare:**

Dacă ai nevoie de accesare mai complexă, consideră:
- Adăugarea de metode helper în DTO (ex: `getFullAddress()`)
- Folosirea unui mapper pentru transformarea DTO-ului în obiecte de prezentare
- Evitarea lanțurilor de apeluri prin delegare

---

## 5. OCP – ReportGenerator

### Enunțul problemei

Un sistem software de întreprindere utilizat în mai multe departamente necesită un instrument de raportare flexibil pentru a răspunde nevoilor de raportare variate și în creștere. Software-ul dispune în prezent de un `ReportGenerator` care se adresează vânzărilor, inventarului și raportării datelor privind performanța angajaților.

**Codul problematic:**

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

### Analiza problemei

**De ce încalcă OCP?**

1. **Modificare necesară pentru extindere**: Pentru a adăuga un nou tip de raport, trebuie să modifici clasa `ReportGenerator` (adăugare metodă nouă).

2. **Clasă "god class"**: Clasa crește continuu cu fiecare nou tip de raport.

3. **Testare dificilă**: Testele trebuie rerulate pentru toate rapoartele la orice modificare.

4. **Risc de bug-uri**: Schimbările pentru un raport pot afecta accidental pe altele.

5. **Nu poți extinde**: Nu poți adăuga rapoarte într-un modul separat fără să recompilezi și să redistribui întregul `ReportGenerator`.

**Probleme concrete:**

- Instabilitate: Clasa se modifică frecvent
- Scalabilitate redusă: Clasa crește necontrolat
- Mentenabilitate dificilă: Logica pentru fiecare raport este amestecată
- Testabilitate redusă: Nu poți testa rapoarte independent

### Soluția propusă

**Codul refactorizat:**

```java
// Abstractiunea pentru rapoarte
interface Report {
    void generate(DataSet dataSet);
    String getReportName();
    ReportFormat getFormat();
}

// Implementări concrete pentru fiecare tip de raport
class SalesReport implements Report {
    @Override
    public void generate(DataSet dataSet) {
        // Logică specifică pentru raport de vânzări
        List<Sale> sales = extractSales(dataSet);
        calculateTotals(sales);
        formatSalesReport(sales);
        exportReport();
    }

    @Override
    public String getReportName() {
        return "Sales Report";
    }

    @Override
    public ReportFormat getFormat() {
        return ReportFormat.PDF;
    }

    private List<Sale> extractSales(DataSet dataSet) { /* ... */ }
    private void calculateTotals(List<Sale> sales) { /* ... */ }
    private void formatSalesReport(List<Sale> sales) { /* ... */ }
    private void exportReport() { /* ... */ }
}

class InventoryReport implements Report {
    @Override
    public void generate(DataSet dataSet) {
        // Logică specifică pentru raport de inventar
        List<InventoryItem> items = extractInventory(dataSet);
        calculateStockLevels(items);
        formatInventoryReport(items);
        exportReport();
    }

    @Override
    public String getReportName() {
        return "Inventory Report";
    }

    @Override
    public ReportFormat getFormat() {
        return ReportFormat.EXCEL;
    }

    private List<InventoryItem> extractInventory(DataSet dataSet) { /* ... */ }
    private void calculateStockLevels(List<InventoryItem> items) { /* ... */ }
    private void formatInventoryReport(List<InventoryItem> items) { /* ... */ }
    private void exportReport() { /* ... */ }
}

class EmployeePerformanceReport implements Report {
    @Override
    public void generate(DataSet dataSet) {
        // Logică specifică pentru raport de performanță angajați
        List<Employee> employees = extractEmployees(dataSet);
        calculatePerformanceMetrics(employees);
        formatPerformanceReport(employees);
        exportReport();
    }

    @Override
    public String getReportName() {
        return "Employee Performance Report";
    }

    @Override
    public ReportFormat getFormat() {
        return ReportFormat.PDF;
    }

    private List<Employee> extractEmployees(DataSet dataSet) { /* ... */ }
    private void calculatePerformanceMetrics(List<Employee> employees) { /* ... */ }
    private void formatPerformanceReport(List<Employee> employees) { /* ... */ }
    private void exportReport() { /* ... */ }
}

// ReportGenerator - orchestrator, rămâne neschimbat la adăugarea de rapoarte noi
class ReportGenerator {
    public void generateReport(Report report, DataSet dataSet) {
        try {
            System.out.println("Generating: " + report.getReportName());
            report.generate(dataSet);
            System.out.println("Report generated successfully in " + report.getFormat() + " format");
        } catch (Exception e) {
            handleReportError(report, e);
        }
    }

    public void generateReports(List<Report> reports, DataSet dataSet) {
        for (Report report : reports) {
            generateReport(report, dataSet);
        }
    }

    private void handleReportError(Report report, Exception e) {
        // Error handling logic
        System.err.println("Error generating " + report.getReportName() + ": " + e.getMessage());
    }
}

// Factory pentru crearea rapoartelor
class ReportFactory {
    public static Report createReport(ReportType type) {
        switch (type) {
            case SALES:
                return new SalesReport();
            case INVENTORY:
                return new InventoryReport();
            case EMPLOYEE_PERFORMANCE:
                return new EmployeePerformanceReport();
            default:
                throw new IllegalArgumentException("Unknown report type: " + type);
        }
    }
}

// Exemplu: Adăugare nou tip de raport (fără modificarea ReportGenerator)
class FinancialReport implements Report {
    @Override
    public void generate(DataSet dataSet) {
        // Logică pentru raport financiar
        List<Transaction> transactions = extractTransactions(dataSet);
        calculateFinancialMetrics(transactions);
        formatFinancialReport(transactions);
        exportReport();
    }

    @Override
    public String getReportName() {
        return "Financial Report";
    }

    @Override
    public ReportFormat getFormat() {
        return ReportFormat.EXCEL;
    }

    private List<Transaction> extractTransactions(DataSet dataSet) { /* ... */ }
    private void calculateFinancialMetrics(List<Transaction> transactions) { /* ... */ }
    private void formatFinancialReport(List<Transaction> transactions) { /* ... */ }
    private void exportReport() { /* ... */ }
}

// Utilizare
class ReportService {
    private ReportGenerator reportGenerator;

    void generateAllReports(DataSet dataSet) {
        List<Report> reports = Arrays.asList(
            new SalesReport(),
            new InventoryReport(),
            new EmployeePerformanceReport(),
            new FinancialReport() // Nou raport adăugat fără modificarea ReportGenerator
        );

        reportGenerator.generateReports(reports, dataSet);
    }
}
```

### Avantajele soluției

1. **Respectă OCP**: `ReportGenerator` rămâne neschimbat când apare un nou tip de raport.

2. **Extensibilitate**: Noi rapoarte se adaugă prin noi clase care implementează `Report`, nu prin modificarea codului existent.

3. **Scalabilitate**: Logica fiecărui raport este izolată; clasa centrală nu crește necontrolat.

4. **Mentenabilitate**: Fiecare raport poate fi modificat, testat și înlocuit independent.

5. **Testabilitate**: Fiecare raport poate fi testat independent.

6. **Modularitate**: Rapoarte noi pot fi adăugate în module/plugin-uri noi.

7. **Risc redus**: Riscul de a rupe rapoarte existente atunci când adaugi unele noi scade semnificativ.

---

## Concluzie

Exercițiile din Test 2 PDSS acoperă aspecte importante ale designului software:

1. **Code Smells**: Recunoașterea și înțelegerea problemelor comune în design
2. **DIP + ISP**: Aplicarea principiilor pentru reducerea cuplării și îmbunătățirea modularității
3. **LSP + ISP**: Asigurarea substituției sigure și segregarea interfețelor
4. **LoD**: Înțelegerea când accesarea directă este acceptabilă (DTO-uri)
5. **OCP**: Design extensibil fără modificarea codului existent

Respectarea acestor principii și evitarea code smells conduce la:
- Cod mai ușor de înțeles și de menținut
- Sistem mai flexibil și extensibil
- Testare mai ușoară
- Reducerea riscului de bug-uri
- Îmbunătățirea colaborării în echipă

