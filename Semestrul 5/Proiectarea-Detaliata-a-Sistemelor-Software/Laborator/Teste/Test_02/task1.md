# Test 2 PDSS

## DIP

1. Un instrument de raportare este utilizat într-o suită de software financiar pentru a genera diferite tipuri de rapoarte bazate pe date dintr-o bază de date SQL. Instrumentul de raportare este construit pentru a funcționa exclusiv cu baza de date SQL folosind instanțierea directă a conexiunii la baza de date în cadrul claselor de raport. Această alegere de design a făcut dificilă adaptarea instrumentului pentru utilizarea cu alte tipuri de baze de date sau surse de date pe care suita financiară dorește să le suporte. Evaluați abordarea clasei FinancialReportGenerator cu privire la obținerea datelor în contextul DIP. Ce probleme prezintă această abordare pentru mentenabilitatea și flexibilitatea instrumentului de raportare, mai ales că suita de software începe să încorporeze surse de date mai diverse? Propuneți o soluție de refactorizare care să permită instrumentului de raportare să accepte diferite tipuri de surse de date, respectând în același timp DIP.

```java
class FinancialReportGenerator {
    private SQLDatabaseConnection databaseConnection;

    public FinancialReportGenerator() {
        this.databaseConnection = new SQLDatabaseConnection();
    }

    public void generateMonthlyReport() {
        List<FinancialRecord> records = databaseConnection.query(
            "SELECT * FROM financial_data WHERE month=current_month"
        );
        // ... report generation logic ...
    }
}

class SQLDatabaseConnection {
    public List<FinancialRecord> query(String sqlQuery) {
        // ... logic to execute SQL query and return results ...
    }
}
```

2. Problema care apare

Clasa FinancialReportGenerator depinde direct de concretul SQLDatabaseConnection, nu de o abstractiune. Încalcă DIP, este puternic cuplată la SQL și la detaliul modulului de acces la date. Orice schimbare de sursă de date (NoSQL, API, fișier) cere modificarea clasei de raport, ceea ce afectează mentenabilitatea, flexibilitatea și testarea (nu poți injecta ușor un mock/fake).

3. Soluția propusă

Introducem o abstractiune pentru sursa de date (de ex. interfața DataSource sau FinancialRecordRepository) care definește operațiile necesare raportului (de ex. `List<FinancialRecord> getMonthlyRecords()` sau, mai generic, `query`). FinancialReportGenerator depinde de această abstractiune și primește implementarea concretă prin constructor (dependency injection). Implementări diferite (SQLDatabaseConnection, NoSqlDatabaseConnection, ApiDataSource etc.) pot fi adăugate fără a modifica logica de raportare.

Codul pe scurt al soluției propuse

```java
interface FinancialDataSource {
    List<FinancialRecord> getMonthlyRecords();
}

class SqlFinancialDataSource implements FinancialDataSource {
    private SQLDatabaseConnection connection;

    public SqlFinancialDataSource(SQLDatabaseConnection connection) {
        this.connection = connection;
    }

    @Override
    public List<FinancialRecord> getMonthlyRecords() {
        return connection.query(
            "SELECT * FROM financial_data WHERE month=current_month"
        );
    }
}

class FinancialReportGenerator {
    private final FinancialDataSource dataSource;

    // Dependency injection: depinde de abstractiune, nu instanțiază concretul
    public FinancialReportGenerator(FinancialDataSource dataSource) {
        this.dataSource = dataSource;
    }

    public void generateMonthlyReport() {
        List<FinancialRecord> records = dataSource.getMonthlyRecords();
        // ... report generation logic ...
    }
}
```

Pentru altă sursă de date definim:

```java
class ApiFinancialDataSource implements FinancialDataSource {
    @Override
    public List<FinancialRecord> getMonthlyRecords() {
        // apel API, transformare în FinancialRecord etc.
    }
}
```

4. Cum e mai bună soluția propusă față de soluția inițială

1) Respectă DIP: FinancialReportGenerator depinde de o abstractiune stabilă (FinancialDataSource), nu de detaliul SQLDatabaseConnection.
2) Flexibilitate: poți schimba sau adăuga surse de date fără a modifica clasa de raport, doar furnizând altă implementare a interfeței.
3) Mentenabilitate: logica de acces la date este izolată în implementări separate; modificările de query sau tehnologie nu ating codul de raportare.
4) Testabilitate: poți injecta un FinancialDataSource fake în teste, fără infrastructură reală de bază de date.

## LoD

1. Enunțul întrebării

Într-o aplicație de comerț electronic, clasa OrderProcessor are o metodă care calculează prețul total al comenzii, inclusiv taxele, accesând adresa obiectului Customer pentru a determina cota de impozitare. De asemenea, clasa Order este o clasă complexă, încapsulată, care oferă multe funcționalități pe lângă metoda de getCustomer().Încalcă Line A din metoda calculateTotal(Order order) Legea lui Demeter? Explicați de ce și cum ați modifica codul pentru a respecta Legea lui Demeter.

```java
class OrderProcessor {
    float calculateTotal(Order order) {
        float taxRate = order.getCustomer().getAddress().getTaxRate(); // Line A
        // calculate total with taxRate
    }
    // ... other methods ...
}
```

2. Problema care apare

Da, Line A încalcă Legea lui Demeter prin lanțul Order → Customer → Address. Soluția parțială propusă anterior muta problema în Order, dar tot încălca LoD deoarece Order apela intern customer.getAddress().getTaxRate().

3. Soluția propusă

Delegăm progresiv responsabilitatea: Order expune getTaxRate(), iar Customer expune și el getTaxRate(), astfel încât nici Order, nici OrderProcessor să nu traverseze structuri interne. Address rămâne ultima entitate care știe implementarea. În final, OrderProcessor vorbește doar cu Order.

```java
class Address {
    public float getTaxRate() {
        return taxRate;
    }
}

class Customer {
    private Address address;

    public float getTaxRate() {
        return address.getTaxRate();
    }
}

class Order {
    private Customer customer;

    public float getTaxRate() {
        return customer.getTaxRate();
    }
}

class OrderProcessor {
    float calculateTotal(Order order) {
        float taxRate = order.getTaxRate();  // respectă LoD
        // calculate total with taxRate
    }
}
```

4. Cum e mai bună soluția propusă față de soluția inițială

Soluția elimină complet lanțurile de apel, respectând strict Legea lui Demeter. Fiecare clasă își gestionează propriile detalii interne prin delegare, OrderProcessor rămâne decuplat de structura internă a Customer și Address, iar codul devine mai stabil și mai ușor de extins.

## ISP && LSP

1. Enunțul întrebării (exact așa cum l-ai primit)
   O bibliotecă de software este în curs de dezvoltare pentru a gestiona operațiunile de documente pentru diferite tipuri de imprimante din cadrul unei organizații. Biblioteca va fi utilizată de diferiți clienți din cadrul infrastructurii software a companiei, inclusiv sisteme de management al documentelor, instrumente automate de generare a rapoartelor și servicii de imprimare manuală. În contextul oferit, cum încalcă potențial interfața Printer și implementările sale de către clasele AllInOnePrinter și PrintOnlyPrinter atât principiul de segregare a interfeței (ISP), cât și principiul de substituție Liskov (LSP)? Luați în considerare modul în care clienții interfeței Printer ar putea fi afectați. Explicați și propuneți o strategie de refactorizare care să rezolve încălcările, luând în considerare diferitele nevoi ale clienților interfeței.

```java
interface Printer {
    void print(Document d);
    void fax(Document d);
    void scan(Document d);
}

class AllInOnePrinter implements Printer {
    public void print(Document d) { /* ... */ }
    public void fax(Document d)   { /* ... */ }
    public void scan(Document d)  { /* ... */ }
}

class PrintOnlyPrinter implements Printer {
    public void print(Document d) { /* ... */ }
    public void fax(Document d)   { throw new UnsupportedOperationException(); }
    public void scan(Document d)  { throw new UnsupportedOperationException(); }
}
```

2. Problema care apare

ISP este încălcat pentru că interfața Printer obligă toate implementările și toți clienții să depindă de operații (fax, scan) pe care multe imprimante și mulți clienți nu le folosesc.

LSP este încălcat pentru că un client care lucrează cu un Printer se așteaptă ca toate metodele să funcționeze conform contractului; înlocuirea unui AllInOnePrinter cu un PrintOnlyPrinter poate duce la UnsupportedOperationException la rulare, deși tipul static este același, deci substituția nu este sigură.

Clienții care folosesc doar print() sunt forțați să cunoască metode irelevante, iar clienții care folosesc fax()/scan() nu pot avea garanția că orice Printer primit chiar suportă acele operații.

3. Soluția propusă

Segregăm interfața în mai multe abstractiuni mici, specifice capabilităților: Printable, Scannable, Faxable. Pentru dispozitive multifuncționale definim fie o interfață compusă (MultiFunctionDevice extinde cele trei), fie un obiect care compune aceste capabilități.

Astfel:

1. imprimantele doar cu print implementează doar Printable;
2. clienții care au nevoie strict de print depind doar de Printable;
3. clienții care au nevoie de fax/scan specifică explicit combinația de capabilități necesare;
4. nu mai există metode care aruncă UnsupportedOperationException doar pentru că nu sunt suportate de dispozitiv.

```java
interface Printable {
    void print(Document d);
}

interface Scannable {
    void scan(Document d);
}

interface Faxable {
    void fax(Document d);
}

// Dispozitiv multifuncțional
interface MultiFunctionDevice extends Printable, Scannable, Faxable { }

class AllInOnePrinter implements MultiFunctionDevice {
    public void print(Document d) { /* ... */ }
    public void scan(Document d)  { /* ... */ }
    public void fax(Document d)   { /* ... */ }
}

// Imprimantă doar pentru print
class PrintOnlyPrinter implements Printable {
    public void print(Document d) { /* ... */ }
}

// Exemple de clienți
class ReportGenerator {
    private final Printable printer;
    ReportGenerator(Printable printer) { this.printer = printer; }
    void generateAndPrint(Document d) { printer.print(d); }
}

class DocumentWorkflowService {
    private final Printable printer;
    private final Scannable scanner;

    DocumentWorkflowService(Printable p, Scannable s) {
        this.printer = p;
        this.scanner = s;
    }

    void process(Document d) {
        scanner.scan(d);
        printer.print(d);
    }
}
```

4. Cum e mai bună soluția propusă față de soluția inițială

Noua structură respectă ISP, deoarece fiecare client și fiecare clasă implementează sau depinde doar de abstractiunile strict necesare (Printable, Scannable, Faxable).

Respectă și LSP, deoarece orice obiect transmis ca Printable garantează că operația print este validă, fără a exista metode care „nu sunt suportate” în contractul lui; substituția între implementări ale aceleiași abstractiuni nu mai introduce excepții neașteptate la rulare.

Clienții devin mai clari și mai siguri: codul pentru raportare folosește doar Printable, iar serviciile complexe cer explicit combinația de capabilități necesară, evitând surprizele de tip PrintOnlyPrinter care „pretinde” că este Printer complet, dar nu poate faxa sau scana.

## OCP

1. Enunțul întrebării

O platformă populară de comerț electronic caută să-și extindă opțiunile de plată datorită cererii clienților pentru diferite metode de plată. Echipa de dezvoltare are sarcina de a integra aceste noi metode în sistemul de procesare a plăților existent, care acceptă în prezent plățile cu cardul de credit, PayPal și transferurile bancare. Având în vedere planurile de extindere ale platformei de comerț electronic, discutați designul actual a clasei PaymentProcessor în raport cu principiul deschis/închis (OCP). Ce considerații ar trebui luat în considerare pentru viitoarele integrări? Cum ar putea designul actual influența ușurința întreținerii viitoare și scalabilitatea sistemului de procesare a plăților?

```java
class PaymentProcessor {
    public void processPayment(PaymentDetails paymentDetails) {
        switch (paymentDetails.getType()) {
            case CREDIT_CARD:
                // Process credit card payment
                break;
            case PAYPAL:
                // Process PayPal payment
                break;
            case BANK_TRANSFER:
                // Process bank transfer
                break;
            // ... other payment types ...
        }
    }
}

enum PaymentType {
    CREDIT_CARD, PAYPAL, BANK_TRANSFER // ... other payment types ...
}

class PaymentDetails {
    private PaymentType type;
    // ... other details ...

    // ... setters and getters ...
}
```

2. Problema care apare

Designul actual încalcă OCP: de fiecare dată când adăugăm o metodă nouă de plată trebuie să modificăm PaymentProcessor (switch-ul) și enum-ul PaymentType. Clasa centrală devine un „god switch”, crește în complexitate, riscul de bug-uri crește și testarea devine mai greoaie. Sistemul nu este deschis pentru extindere prin adăugare de cod nou, ci cere modificarea celui existent.

3. Soluția propusă

Introducem o abstractiune PaymentMethod (sau PaymentHandler) cu o operație process(PaymentDetails). Pentru fiecare tip de plată avem o implementare separată. PaymentProcessor nu mai conține un switch, ci primește o mapare de la PaymentType la PaymentMethod (sau folosește chiar un factory/strategies injectate). La adăugarea unui nou tip de plată definim o nouă clasă care implementează abstractiunea, fără să modificăm PaymentProcessor.

```java
interface PaymentMethod {
    void process(PaymentDetails details);
}

class CreditCardPayment implements PaymentMethod {
    public void process(PaymentDetails details) {
        // logic credit card
    }
}

class PaypalPayment implements PaymentMethod {
    public void process(PaymentDetails details) {
        // logic PayPal
    }
}

class BankTransferPayment implements PaymentMethod {
    public void process(PaymentDetails details) {
        // logic bank transfer
    }
}

class PaymentProcessor {
    private final Map<PaymentType, PaymentMethod> methods;

    public PaymentProcessor(Map<PaymentType, PaymentMethod> methods) {
        this.methods = methods;
    }

    public void processPayment(PaymentDetails paymentDetails) {
        PaymentMethod method = methods.get(paymentDetails.getType());
        if (method == null) {
            throw new UnsupportedOperationException("Unsupported payment type");
        }
        method.process(paymentDetails);
    }
}
```

La adăugarea unui nou tip, creăm NewPaymentMethod care implementează PaymentMethod și îl înregistrăm în mapă, fără schimbări în PaymentProcessor.

4. Cum e mai bună soluția propusă față de soluția inițială

1) Respectă OCP: PaymentProcessor rămâne neschimbat când apare o nouă metodă de plată; extinderea se face prin noi clase care implementează PaymentMethod.
2) Scalabilitate: logica fiecărei plăți este izolată; clasa centrală nu crește necontrolat cu noi ramuri de switch.
3) Mentenabilitate: fiecare metodă de plată poate fi modificată, testată și înlocuită independent; se pot configura ușor metode diferite în funcție de țară, magazin etc.
4) Claritate: designul folosește polimorfism și abstractiuni în loc de cod procedural cu switch, făcând sistemul de procesare a plăților mai ușor de înțeles și extins.

## SRP

1. Enunțul întrebării
   Imaginați-vă o clasă dintr-o aplicație web de întreprindere care face parte dintr-un pachet responsabil cu gestionarea interacțiunilor utilizatorilor și a operațiunilor legate de gestionarea utilizatorilor. Această clasă a suferit modificări frecvente în ultima vreme, deoarece se ocupă de operațiunile de autentificare, autorizare și gestionare a profilului utilizatorilor. Echipa anticipează că mai multe operațiuni privind securitatea și prelucrarea datelor utilizatorilor vor fi adăugate în curând. Clasa este în prezent structurată după cum urmează:
   Având în vedere diversele responsabilități conținute în clasa UserController, evaluați structura acesteia în termeni de SRP. Respectă această clasă SRP și ce complicații ar putea apărea din structura sa actuală? Furnizați o strategie de refactorizare care ar putea rezolva orice problemă, luând în considerare schimbările viitoare anticipate de echipă.

```java
class UserController {

    // Handles user authentication
    public boolean authenticateUser(String username, String password) { ... }

    // Authorizes a user for a given action
    public boolean authorizeUser(User user, Action action) { ... }

    // Updates user profile details
    public void updateUserProfile(User user, UserProfile profile) { ... }

    // Logs out the user
    public void logoutUser(User user) { ... }

    // Registers a new user
    public void registerNewUser(UserData data) { ... }

    // Deletes a user
    public void deleteUser(User user) { ... }
}
```

2. Problema care apare

Clasa nu respectă SRP: amestecă autentificare, autorizare, management de profil și lifecycle de utilizator. Are mai multe „motive de schimbare”: politici de securitate, reguli de profil, reguli de înregistrare etc. Pe măsură ce se adaugă operații noi, clasa crește, devine instabilă, iar orice modificare poate rupe clienți care nici măcar nu folosesc acea funcționalitate.

3. Soluția propusă

Definim mai multe abstractiuni înguste (interfețe) care descriu capabilitățile de care au nevoie clienții: una pentru autentificare, una pentru autorizare, una pentru profil, una pentru administrarea utilizatorilor. UserController implementează aceste interfețe, dar clienții nu mai depind de clasa concretă, ci doar de abstractiunea relevantă pentru ei. Când adăugăm noi operații, putem crea o interfață nouă (sau extinde pe una existentă) fără ca toți clienții să fie afectați; cei care nu au nevoie de noua capabilitate nici nu văd metoda nouă.

```java
interface AuthenticationApi {
    boolean authenticateUser(String username, String password);
    void logoutUser(User user);
}

interface AuthorizationApi {
    boolean authorizeUser(User user, Action action);
}

interface UserProfileApi {
    void updateUserProfile(User user, UserProfile profile);
}

interface UserManagementApi {
    void registerNewUser(UserData data);
    void deleteUser(User user);
}

// Implementare concretă
class UserController implements AuthenticationApi,
                                 AuthorizationApi,
                                 UserProfileApi,
                                 UserManagementApi {

    @Override
    public boolean authenticateUser(String username, String password) { /* ... */ }

    @Override
    public void logoutUser(User user) { /* ... */ }

    @Override
    public boolean authorizeUser(User user, Action action) { /* ... */ }

    @Override
    public void updateUserProfile(User user, UserProfile profile) { /* ... */ }

    @Override
    public void registerNewUser(UserData data) { /* ... */ }

    @Override
    public void deleteUser(User user) { /* ... */ }
}

// Clienți
class LoginPage {
    private final AuthenticationApi authApi;
    LoginPage(AuthenticationApi authApi) { this.authApi = authApi; }

    void login(String u, String p) {
        authApi.authenticateUser(u, p);
    }
}

class AdminPanel {
    private final UserManagementApi userManagementApi;
    AdminPanel(UserManagementApi api) { this.userManagementApi = api; }

    void removeUser(User user) {
        userManagementApi.deleteUser(user);
    }
}
```

4. Cum e mai bună soluția propusă față de soluția inițială

Acum SRP este mult mai bine respectat la nivel de contract: fiecare client lucrează cu o abstractiune care reflectă un singur set de responsabilități (AuthenticationApi, UserProfileApi etc.), nu cu „sacul” UserController. Adăugarea unei noi operații (de exemplu resetPassword) se poate face printr-o nouă interfață PasswordApi sau prin extinderea uneia existente, iar clienții care nu depind de acea abstractiune nu trebuie modificați.

Caveat important: pentru a beneficia de această structură, toți clienții direcți care foloseau UserController trebuie modificați ca să depindă de noile interfețe (AuthenticationApi, UserProfileApi etc.), nu de clasa concretă. Este un efort inițial de migrare, dar după aceea evoluția și izolarea schimbărilor (mai ales cele de securitate) devin mult mai ușor de controlat.
