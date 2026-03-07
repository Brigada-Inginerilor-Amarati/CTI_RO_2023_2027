# Soluții Detaliate - Principiile S.O.L.I.D

Acest document prezintă soluții complete cu motivații detaliate pentru exercițiile despre principiile S.O.L.I.D.

---

## 1. DIP - Dependency Inversion Principle

### Enunțul problemei

Un instrument de raportare este utilizat într-o suită de software financiar pentru a genera diferite tipuri de rapoarte bazate pe date dintr-o bază de date SQL. Instrumentul de raportare este construit pentru a funcționa exclusiv cu baza de date SQL folosind instanțierea directă a conexiunii la baza de date în cadrul claselor de raport. Această alegere de design a făcut dificilă adaptarea instrumentului pentru utilizarea cu alte tipuri de baze de date sau surse de date pe care suita financiară dorește să le suporte.

**Codul problematic:**

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

### Analiza problemei

**De ce încalcă DIP?**

Dependency Inversion Principle spune că:

- **Modulele de nivel înalt nu ar trebui să depindă de modulele de nivel jos. Ambele ar trebui să depindă de abstractiuni.**
- **Abstractiunile nu ar trebui să depindă de detalii. Detaliile ar trebui să depindă de abstractiuni.**

În codul problematic:

1. **Dependență directă de implementare concretă**: `FinancialReportGenerator` depinde direct de `SQLDatabaseConnection`, o clasă concretă, nu de o abstractiune.
2. **Cuplare puternică**: Clasa de raportare este strâns legată de detaliile tehnice SQL, ceea ce face imposibilă utilizarea altor surse de date fără modificări.
3. **Violarea inversiunii dependențelor**: Modulul de nivel înalt (raportare) depinde de modulul de nivel jos (acces la date SQL).

**Probleme concrete:**

- **Mentenabilitate redusă**: Orice schimbare în structura bazei de date sau în logica de acces necesită modificări în clasa de raportare.
- **Flexibilitate limitată**: Nu poate fi folosit cu NoSQL, API-uri REST, fișiere CSV sau alte surse de date.
- **Testabilitate dificilă**: Nu poate fi testat fără o bază de date reală; nu poate injecta mock-uri sau stub-uri.
- **Încălcarea Single Responsibility**: Clasa combină logica de raportare cu detaliile de acces la date.

### Soluția propusă

**Strategia de refactorizare:**

Introducem o abstractiune (`FinancialDataSource`) care definește contractul pentru obținerea datelor. `FinancialReportGenerator` depinde de această abstractiune și primește implementarea concretă prin dependency injection.

**Motivația pentru soluție:**

1. **Respectă DIP**: Modulul de nivel înalt (`FinancialReportGenerator`) depinde acum de o abstractiune (`FinancialDataSource`), nu de o implementare concretă.
2. **Inversiunea dependențelor**: Detaliile (implementările concrete) depind de abstractiune, nu invers.
3. **Flexibilitate maximă**: Poate accepta orice sursă de date care implementează interfața.
4. **Testabilitate**: Poate injecta mock-uri în teste.

**Codul refactorizat:**

```java
// Abstractiunea - interfața stabilă
interface FinancialDataSource {
    List<FinancialRecord> getMonthlyRecords();
}

// Implementare concretă pentru SQL
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

// Clasa de raportare - depinde de abstractiune
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

// Implementare pentru API REST
class ApiFinancialDataSource implements FinancialDataSource {
    private final RestClient restClient;

    public ApiFinancialDataSource(RestClient restClient) {
        this.restClient = restClient;
    }

    @Override
    public List<FinancialRecord> getMonthlyRecords() {
        // Apel API, transformare în FinancialRecord etc.
        String response = restClient.get("/api/financial/monthly");
        return parseFinancialRecords(response);
    }
}

// Implementare pentru NoSQL
class NoSqlFinancialDataSource implements FinancialDataSource {
    private final MongoDatabase database;

    public NoSqlFinancialDataSource(MongoDatabase database) {
        this.database = database;
    }

    @Override
    public List<FinancialRecord> getMonthlyRecords() {
        // Query MongoDB, transformare etc.
        return database.getCollection("financial_data")
            .find(eq("month", getCurrentMonth()))
            .map(this::toFinancialRecord)
            .collect(Collectors.toList());
    }
}
```

### Avantajele soluției

1. **Respectă DIP**: `FinancialReportGenerator` depinde de abstractiune (`FinancialDataSource`), nu de detaliile implementării.
2. **Flexibilitate**: Poate schimba sau adăuga surse de date fără a modifica clasa de raport.
3. **Mentenabilitate**: Logica de acces la date este izolată în implementări separate.
4. **Testabilitate**: Poate injecta un `FinancialDataSource` mock în teste.
5. **Extensibilitate**: Noi surse de date pot fi adăugate prin noi clase care implementează interfața.

---

## 2. LoD - Law of Demeter (Legea lui Demeter)

### Enunțul problemei

Într-o aplicație de comerț electronic, clasa `OrderProcessor` are o metodă care calculează prețul total al comenzii, inclusiv taxele, accesând adresa obiectului `Customer` pentru a determina cota de impozitare. Încalcă Line A din metoda `calculateTotal(Order order)` Legea lui Demeter?

**Codul problematic:**

```java
class OrderProcessor {
    float calculateTotal(Order order) {
        float taxRate = order.getCustomer().getAddress().getTaxRate(); // Line A
        // calculate total with taxRate
    }
    // ... other methods ...
}
```

### Analiza problemei

**Ce spune Legea lui Demeter?**

Legea lui Demeter (LoD), cunoscută și ca "Principiul cunoașterii minime", spune că:

- **Un obiect ar trebui să comunice doar cu prietenii săi direcți.**
- **Nu ar trebui să "vorbească cu străinii"** - adică să acceseze obiecte prin lanțuri de referințe.

**De ce încalcă LoD?**

Linia A (`order.getCustomer().getAddress().getTaxRate()`) încalcă LoD prin:

1. **Lanț de apeluri**: `OrderProcessor` accesează `Customer` prin `Order`, apoi `Address` prin `Customer`, apoi `getTaxRate()` prin `Address`.
2. **Cuplare puternică**: `OrderProcessor` trebuie să cunoască structura internă a `Order`, `Customer` și `Address`.
3. **Fragilitate**: Dacă structura internă a `Customer` sau `Address` se schimbă, `OrderProcessor` trebuie modificat.

**Probleme concrete:**

- **Fragilitate**: Orice schimbare în structura `Customer` sau `Address` afectează `OrderProcessor`.
- **Cuplare puternică**: `OrderProcessor` depinde de detalii despre cum `Customer` stochează `Address`.
- **Testabilitate dificilă**: Trebuie să mock-uiești întreg lanțul de obiecte.
- **Încălcarea încapsulării**: Expune structura internă a obiectelor.

### Soluția propusă

**Strategia de refactorizare:**

Delegăm progresiv responsabilitatea: fiecare clasă expune metode care ascund detaliile interne. `Order` expune `getTaxRate()`, `Customer` expune `getTaxRate()`, astfel încât `OrderProcessor` să vorbească doar cu `Order`.

**Motivația pentru soluție:**

1. **Respectă LoD**: `OrderProcessor` comunică doar cu `Order`, nu traversează structuri interne.
2. **Încapsulare îmbunătățită**: Detaliile despre cum se calculează tax rate-ul rămân în clasele respective.
3. **Stabilitate**: Schimbările în structura internă nu afectează `OrderProcessor`.
4. **Testabilitate**: Poate testa `OrderProcessor` cu un mock simplu al `Order`.

**Codul refactorizat:**

```java
// Clasa Address - știe detaliile despre tax rate
class Address {
    private float taxRate;

    public float getTaxRate() {
        return taxRate;
    }
}

// Clasa Customer - delegă către Address
class Customer {
    private Address address;

    public float getTaxRate() {
        return address.getTaxRate();
    }
}

// Clasa Order - delegă către Customer
class Order {
    private Customer customer;

    public float getTaxRate() {
        return customer.getTaxRate();
    }

    // Alte metode ale Order...
}

// OrderProcessor - comunică doar cu Order
class OrderProcessor {
    float calculateTotal(Order order) {
        float taxRate = order.getTaxRate();  // respectă LoD
        float subtotal = order.getSubtotal();
        return subtotal * (1 + taxRate);
    }
}
```

### Avantajele soluției

1. **Respectă LoD**: Elimină complet lanțurile de apeluri.
2. **Încapsulare**: Fiecare clasă gestionează propriile detalii interne.
3. **Stabilitate**: `OrderProcessor` rămâne decuplat de structura internă.
4. **Testabilitate**: Poate testa cu mock-uri simple.
5. **Extensibilitate**: Poate adăuga logici noi (ex: taxe speciale) fără a afecta `OrderProcessor`.

---

## 3. ISP & LSP - Interface Segregation Principle & Liskov Substitution Principle

### Enunțul problemei

O bibliotecă de software este în curs de dezvoltare pentru a gestiona operațiunile de documente pentru diferite tipuri de imprimante din cadrul unei organizații. Biblioteca va fi utilizată de diferiți clienți din cadrul infrastructurii software a companiei, inclusiv sisteme de management al documentelor, instrumente automate de generare a rapoartelor și servicii de imprimare manuală.

Cum încalcă interfața `Printer` și implementările sale atât ISP, cât și LSP?

**Codul problematic:**

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

### Analiza problemei

**De ce încalcă ISP (Interface Segregation Principle)?**

ISP spune că:

- **Clienții nu ar trebui să fie forțați să depindă de interfețe pe care nu le folosesc.**
- **O interfață mare ar trebui împărțită în interfețe mai mici, specifice nevoilor clienților.**

În codul problematic:

1. **Interfață prea mare**: `Printer` conține trei operații, dar multe imprimante nu le suportă pe toate.
2. **Dependențe forțate**: Clienții care doar printează sunt forțați să depindă de `fax()` și `scan()`.
3. **Implementări incomplete**: `PrintOnlyPrinter` trebuie să implementeze metode pe care nu le suportă.

**De ce încalcă LSP (Liskov Substitution Principle)?**

LSP spune că:

- **Obiectele unei clase derivate trebuie să poată înlocui obiectele clasei de bază fără a afecta corectitudinea programului.**
- **Subtipurile trebuie să fie substituibile pentru tipurile lor de bază.**

În codul problematic:

1. **Substituție nesigură**: Înlocuirea unui `AllInOnePrinter` cu un `PrintOnlyPrinter` poate duce la `UnsupportedOperationException`.
2. **Contract încălcat**: Clientul se așteaptă ca toate metodele să funcționeze, dar `PrintOnlyPrinter` aruncă excepții.
3. **Comportament neașteptat**: Tipul static este același, dar comportamentul diferă la runtime.

**Probleme concrete:**

- **Clienții forțați**: Clienții care doar printează trebuie să cunoască metode irelevante.
- **Fără garanții**: Clienții care folosesc `fax()`/`scan()` nu pot garanta că orice `Printer` suportă aceste operații.
- **Excepții la runtime**: Substituția poate duce la erori neașteptate.

### Soluția propusă

**Strategia de refactorizare:**

Segregăm interfața în mai multe interfețe mici, specifice capabilităților: `Printable`, `Scannable`, `Faxable`. Pentru dispozitive multifuncționale definim o interfață compusă (`MultiFunctionDevice`).

**Motivația pentru soluție:**

1. **Respectă ISP**: Fiecare interfață este mică și specifică unei responsabilități.
2. **Respectă LSP**: Orice obiect transmis ca `Printable` garantează că `print()` funcționează.
3. **Claritate**: Clienții depind doar de ceea ce folosesc efectiv.
4. **Siguranță**: Nu mai există metode care aruncă excepții pentru operații nesuportate.

**Codul refactorizat:**

```java
// Interfețe segregate - fiecare cu o responsabilitate
interface Printable {
    void print(Document d);
}

interface Scannable {
    void scan(Document d);
}

interface Faxable {
    void fax(Document d);
}

// Interfață compusă pentru dispozitive multifuncționale
interface MultiFunctionDevice extends Printable, Scannable, Faxable { }

// Implementare pentru dispozitiv multifuncțional
class AllInOnePrinter implements MultiFunctionDevice {
    public void print(Document d) {
        // Implementare print
    }

    public void scan(Document d) {
        // Implementare scan
    }

    public void fax(Document d) {
        // Implementare fax
    }
}

// Implementare pentru imprimantă simplă
class PrintOnlyPrinter implements Printable {
    public void print(Document d) {
        // Implementare print
    }
}

// Clienți - depind doar de ceea ce folosesc
class ReportGenerator {
    private final Printable printer;

    ReportGenerator(Printable printer) {
        this.printer = printer;
    }

    void generateAndPrint(Document d) {
        // Generare raport
        printer.print(d);
    }
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
        // Procesare document
        printer.print(d);
    }
}

class FaxService {
    private final Faxable faxDevice;

    FaxService(Faxable faxDevice) {
        this.faxDevice = faxDevice;
    }

    void sendFax(Document d) {
        faxDevice.fax(d);
    }
}
```

### Avantajele soluției

1. **Respectă ISP**: Fiecare client depinde doar de abstractiunile necesare.
2. **Respectă LSP**: Substituția între implementări ale aceleiași abstractiuni este sigură.
3. **Claritate**: Codul este mai clar despre ce capabilități sunt necesare.
4. **Siguranță**: Nu mai există excepții neașteptate pentru operații nesuportate.
5. **Flexibilitate**: Clienții pot combina capabilități diferite după nevoie.

---

## 4. OCP - Open/Closed Principle

### Enunțul problemei

O platformă populară de comerț electronic caută să-și extindă opțiunile de plată datorită cererii clienților pentru diferite metode de plată. Echipa de dezvoltare are sarcina de a integra aceste noi metode în sistemul de procesare a plăților existent, care acceptă în prezent plățile cu cardul de credit, PayPal și transferurile bancare.

**Codul problematic:**

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
}
```

### Analiza problemei

**Ce spune OCP (Open/Closed Principle)?**

OCP spune că:

- **Entitățile software ar trebui să fie deschise pentru extindere, dar închise pentru modificare.**
- **Ar trebui să poți adăuga funcționalități noi fără a modifica codul existent.**

**De ce încalcă OCP?**

În codul problematic:

1. **Modificare necesară pentru extindere**: Pentru a adăuga o nouă metodă de plată, trebuie să modifici:
   - `PaymentProcessor` (adăugare case în switch)
   - `PaymentType` enum (adăugare nouă valoare)
2. **"God Switch"**: Clasa centrală devine un switch gigant care crește continuu.
3. **Risc de bug-uri**: Modificările în switch pot introduce bug-uri în metodele existente.
4. **Testare dificilă**: Trebuie să testezi întreg switch-ul pentru fiecare modificare.

**Probleme concrete:**

- **Instabilitate**: Clasa se modifică frecvent, afectând toți clienții.
- **Risc crescut**: Orice modificare poate introduce bug-uri în metodele existente.
- **Scalabilitate redusă**: Clasa crește necontrolat cu fiecare nouă metodă de plată.
- **Mentenabilitate dificilă**: Logica pentru fiecare metodă de plată este amestecată.

### Soluția propusă

**Strategia de refactorizare:**

Introducem o abstractiune `PaymentMethod` cu o operație `process()`. Pentru fiecare tip de plată avem o implementare separată. `PaymentProcessor` folosește o mapare de la `PaymentType` la `PaymentMethod` sau un factory pattern.

**Motivația pentru soluție:**

1. **Respectă OCP**: `PaymentProcessor` rămâne neschimbat când apare o nouă metodă de plată.
2. **Extensibilitate**: Noi metode de plată se adaugă prin noi clase, nu prin modificarea celor existente.
3. **Izolare**: Logica fiecărei metode de plată este izolată în propria clasă.
4. **Testabilitate**: Fiecare metodă de plată poate fi testată independent.

**Codul refactorizat:**

```java
// Abstractiunea pentru metode de plată
interface PaymentMethod {
    void process(PaymentDetails details);
}

// Implementări concrete pentru fiecare tip de plată
class CreditCardPayment implements PaymentMethod {
    public void process(PaymentDetails details) {
        // Logică specifică pentru card de credit
        validateCreditCard(details);
        chargeCreditCard(details);
        logTransaction(details);
    }

    private void validateCreditCard(PaymentDetails details) { /* ... */ }
    private void chargeCreditCard(PaymentDetails details) { /* ... */ }
    private void logTransaction(PaymentDetails details) { /* ... */ }
}

class PaypalPayment implements PaymentMethod {
    public void process(PaymentDetails details) {
        // Logică specifică pentru PayPal
        authenticatePaypal(details);
        processPaypalPayment(details);
        sendConfirmation(details);
    }

    private void authenticatePaypal(PaymentDetails details) { /* ... */ }
    private void processPaypalPayment(PaymentDetails details) { /* ... */ }
    private void sendConfirmation(PaymentDetails details) { /* ... */ }
}

class BankTransferPayment implements PaymentMethod {
    public void process(PaymentDetails details) {
        // Logică specifică pentru transfer bancar
        validateBankAccount(details);
        initiateTransfer(details);
        notifyBank(details);
    }

    private void validateBankAccount(PaymentDetails details) { /* ... */ }
    private void initiateTransfer(PaymentDetails details) { /* ... */ }
    private void notifyBank(PaymentDetails details) { /* ... */ }
}

// PaymentProcessor - rămâne neschimbat la adăugarea de noi metode
class PaymentProcessor {
    private final Map<PaymentType, PaymentMethod> methods;

    public PaymentProcessor(Map<PaymentType, PaymentMethod> methods) {
        this.methods = methods;
    }

    public void processPayment(PaymentDetails paymentDetails) {
        PaymentMethod method = methods.get(paymentDetails.getType());
        if (method == null) {
            throw new UnsupportedOperationException(
                "Unsupported payment type: " + paymentDetails.getType()
            );
        }
        method.process(paymentDetails);
    }
}

// Factory pentru configurarea PaymentProcessor
class PaymentProcessorFactory {
    public static PaymentProcessor createDefault() {
        Map<PaymentType, PaymentMethod> methods = new HashMap<>();
        methods.put(PaymentType.CREDIT_CARD, new CreditCardPayment());
        methods.put(PaymentType.PAYPAL, new PaypalPayment());
        methods.put(PaymentType.BANK_TRANSFER, new BankTransferPayment());
        return new PaymentProcessor(methods);
    }
}

// Exemplu: Adăugare nouă metodă de plată (fără modificarea PaymentProcessor)
class CryptocurrencyPayment implements PaymentMethod {
    public void process(PaymentDetails details) {
        // Logică pentru plată cu criptomonedă
        validateWallet(details);
        processCryptoTransaction(details);
        updateBlockchain(details);
    }

    private void validateWallet(PaymentDetails details) { /* ... */ }
    private void processCryptoTransaction(PaymentDetails details) { /* ... */ }
    private void updateBlockchain(PaymentDetails details) { /* ... */ }
}

// Configurare cu noua metodă (fără modificarea PaymentProcessor)
class ExtendedPaymentProcessorFactory {
    public static PaymentProcessor createWithCrypto() {
        Map<PaymentType, PaymentMethod> methods = new HashMap<>();
        methods.put(PaymentType.CREDIT_CARD, new CreditCardPayment());
        methods.put(PaymentType.PAYPAL, new PaypalPayment());
        methods.put(PaymentType.BANK_TRANSFER, new BankTransferPayment());
        methods.put(PaymentType.CRYPTO, new CryptocurrencyPayment()); // Nouă metodă
        return new PaymentProcessor(methods);
    }
}
```

### Avantajele soluției

1. **Respectă OCP**: `PaymentProcessor` rămâne neschimbat când apare o nouă metodă de plată.
2. **Scalabilitate**: Logica fiecărei metode este izolată; clasa centrală nu crește necontrolat.
3. **Mentenabilitate**: Fiecare metodă poate fi modificată, testată și înlocuită independent.
4. **Claritate**: Designul folosește polimorfism în loc de cod procedural cu switch.
5. **Testabilitate**: Fiecare metodă de plată poate fi testată independent.

---

## 5. SRP - Single Responsibility Principle

### Enunțul problemei

Imaginați-vă o clasă dintr-o aplicație web de întreprindere care face parte dintr-un pachet responsabil cu gestionarea interacțiunilor utilizatorilor și a operațiunilor legate de gestionarea utilizatorilor. Această clasă a suferit modificări frecvente în ultima vreme, deoarece se ocupă de operațiunile de autentificare, autorizare și gestionare a profilului utilizatorilor.

**Codul problematic:**

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

### Analiza problemei

**Ce spune SRP (Single Responsibility Principle)?**

SRP spune că:

- **O clasă ar trebui să aibă un singur motiv pentru a se schimba.**
- **O clasă ar trebui să aibă o singură responsabilitate.**

**De ce încalcă SRP?**

În codul problematic:

1. **Multe responsabilități**: Clasa gestionează:
   - Autentificare (login/logout)
   - Autorizare (permisiuni)
   - Management de profil
   - Lifecycle de utilizator (register/delete)
2. **Multe motive de schimbare**: Clasa se modifică din cauza:
   - Schimbări în politici de securitate
   - Schimbări în reguli de profil
   - Schimbări în reguli de înregistrare
   - Schimbări în reguli de autorizare
3. **Instabilitate**: Orice modificare poate afecta toți clienții, chiar și cei care nu folosesc funcționalitatea modificată.

**Probleme concrete:**

- **Cuplare puternică**: Clienții care doar autentifică utilizatori sunt forțați să depindă de toate celelalte funcționalități.
- **Testabilitate dificilă**: Trebuie să mock-uiești toate dependențele, chiar dacă testezi doar o funcționalitate.
- **Risc de bug-uri**: Modificările într-o funcționalitate pot afecta alte funcționalități.
- **Mentenabilitate dificilă**: Codul devine greu de înțeles și de modificat.

### Soluția propusă

**Strategia de refactorizare:**

Definim mai multe interfețe înguste care descriu capabilitățile de care au nevoie clienții: una pentru autentificare, una pentru autorizare, una pentru profil, una pentru administrarea utilizatorilor. `UserController` implementează aceste interfețe, dar clienții depind doar de abstractiunile relevante.

**Motivația pentru soluție:**

1. **Respectă SRP**: Fiecare interfață reprezintă o singură responsabilitate.
2. **Izolare**: Clienții depind doar de ceea ce folosesc efectiv.
3. **Stabilitate**: Modificările într-o responsabilitate nu afectează clienții altor responsabilități.
4. **Testabilitate**: Poate testa fiecare responsabilitate independent.

**Codul refactorizat:**

```java
// Interfețe segregate - fiecare cu o responsabilitate
interface AuthenticationApi {
    boolean authenticateUser(String username, String password);
    void logoutUser(User user);
}

interface AuthorizationApi {
    boolean authorizeUser(User user, Action action);
}

interface UserProfileApi {
    void updateUserProfile(User user, UserProfile profile);
    UserProfile getUserProfile(User user);
}

interface UserManagementApi {
    void registerNewUser(UserData data);
    void deleteUser(User user);
}

// Implementare concretă - poate implementa toate interfețele
class UserController implements AuthenticationApi,
                                 AuthorizationApi,
                                 UserProfileApi,
                                 UserManagementApi {

    // Implementare pentru AuthenticationApi
    @Override
    public boolean authenticateUser(String username, String password) {
        // Logică de autentificare
        User user = findUserByUsername(username);
        if (user == null) {
            return false;
        }
        return verifyPassword(user, password);
    }

    @Override
    public void logoutUser(User user) {
        // Logică de logout
        invalidateSession(user);
        clearUserCache(user);
    }

    // Implementare pentru AuthorizationApi
    @Override
    public boolean authorizeUser(User user, Action action) {
        // Logică de autorizare
        return checkUserPermissions(user, action);
    }

    // Implementare pentru UserProfileApi
    @Override
    public void updateUserProfile(User user, UserProfile profile) {
        // Logică de actualizare profil
        validateProfile(profile);
        saveUserProfile(user, profile);
        notifyProfileUpdate(user);
    }

    @Override
    public UserProfile getUserProfile(User user) {
        // Logică de obținere profil
        return loadUserProfile(user);
    }

    // Implementare pentru UserManagementApi
    @Override
    public void registerNewUser(UserData data) {
        // Logică de înregistrare
        validateUserData(data);
        User newUser = createUser(data);
        sendWelcomeEmail(newUser);
    }

    @Override
    public void deleteUser(User user) {
        // Logică de ștergere
        validateDeletion(user);
        deleteUserData(user);
        notifyUserDeletion(user);
    }

    // Metode helper private
    private User findUserByUsername(String username) { /* ... */ }
    private boolean verifyPassword(User user, String password) { /* ... */ }
    private void invalidateSession(User user) { /* ... */ }
    private void clearUserCache(User user) { /* ... */ }
    private boolean checkUserPermissions(User user, Action action) { /* ... */ }
    private void validateProfile(UserProfile profile) { /* ... */ }
    private void saveUserProfile(User user, UserProfile profile) { /* ... */ }
    private void notifyProfileUpdate(User user) { /* ... */ }
    private UserProfile loadUserProfile(User user) { /* ... */ }
    private void validateUserData(UserData data) { /* ... */ }
    private User createUser(UserData data) { /* ... */ }
    private void sendWelcomeEmail(User user) { /* ... */ }
    private void validateDeletion(User user) { /* ... */ }
    private void deleteUserData(User user) { /* ... */ }
    private void notifyUserDeletion(User user) { /* ... */ }
}

// Clienți - depind doar de abstractiunile necesare
class LoginPage {
    private final AuthenticationApi authApi;

    LoginPage(AuthenticationApi authApi) {
        this.authApi = authApi;
    }

    void login(String username, String password) {
        if (authApi.authenticateUser(username, password)) {
            showDashboard();
        } else {
            showError("Invalid credentials");
        }
    }

    void logout(User user) {
        authApi.logoutUser(user);
        redirectToLogin();
    }
}

class AdminPanel {
    private final UserManagementApi userManagementApi;

    AdminPanel(UserManagementApi api) {
        this.userManagementApi = api;
    }

    void removeUser(User user) {
        if (confirmDeletion()) {
            userManagementApi.deleteUser(user);
            showSuccessMessage("User deleted");
        }
    }

    void registerUser(UserData data) {
        userManagementApi.registerNewUser(data);
        showSuccessMessage("User registered");
    }
}

class ProfilePage {
    private final UserProfileApi profileApi;

    ProfilePage(UserProfileApi profileApi) {
        this.profileApi = profileApi;
    }

    void displayProfile(User user) {
        UserProfile profile = profileApi.getUserProfile(user);
        renderProfile(profile);
    }

    void updateProfile(User user, UserProfile newProfile) {
        profileApi.updateUserProfile(user, newProfile);
        showSuccessMessage("Profile updated");
    }
}

class SecurityService {
    private final AuthenticationApi authApi;
    private final AuthorizationApi authzApi;

    SecurityService(AuthenticationApi authApi, AuthorizationApi authzApi) {
        this.authApi = authApi;
        this.authzApi = authzApi;
    }

    boolean canPerformAction(String username, String password, Action action) {
        if (!authApi.authenticateUser(username, password)) {
            return false;
        }
        User user = getUserByUsername(username);
        return authzApi.authorizeUser(user, action);
    }
}
```

### Avantajele soluției

1. **Respectă SRP**: Fiecare interfață reprezintă o singură responsabilitate.
2. **Izolare**: Clienții depind doar de ceea ce folosesc efectiv.
3. **Stabilitate**: Modificările într-o responsabilitate nu afectează clienții altor responsabilități.
4. **Testabilitate**: Poate testa fiecare responsabilitate independent.
5. **Extensibilitate**: Poate adăuga noi responsabilități prin noi interfețe fără a afecta cele existente.

**Notă importantă:**

Pentru a beneficia de această structură, toți clienții direcți care foloseau `UserController` trebuie modificați ca să depindă de noile interfețe, nu de clasa concretă. Este un efort inițial de migrare, dar după aceea evoluția și izolarea schimbărilor (mai ales cele de securitate) devin mult mai ușor de controlat.

---

## Concluzie

Principiile S.O.L.I.D. sunt fundamentale pentru crearea de software de calitate, mentenabil și extensibil. Fiecare principiu adresează aspecte specifice ale designului:

- **SRP**: O clasă ar trebui să aibă o singură responsabilitate.
- **OCP**: Software-ul ar trebui să fie deschis pentru extindere, dar închis pentru modificare.
- **LSP**: Subtipurile trebuie să fie substituibile pentru tipurile lor de bază.
- **ISP**: Clienții nu ar trebui să fie forțați să depindă de interfețe pe care nu le folosesc.
- **DIP**: Modulele de nivel înalt nu ar trebui să depindă de modulele de nivel jos. Ambele ar trebui să depindă de abstractiuni.

Respectarea acestor principii conduce la:

- Cod mai ușor de înțeles și de menținut
- Sistem mai flexibil și extensibil
- Testare mai ușoară
- Reducerea riscului de bug-uri
- Îmbunătățirea colaborării în echipă
