import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.stream.Collectors;

/**
 * Practical Stream Examples
 * 
 * Real-world scenarios and practical applications of Java Streams
 */
public class StreamPracticalExamples {

    static class Employee {
        String name;
        String department;
        double salary;
        int yearsOfExperience;
        
        public Employee(String name, String department, double salary, int yearsOfExperience) {
            this.name = name;
            this.department = department;
            this.salary = salary;
            this.yearsOfExperience = yearsOfExperience;
        }
        
        public String getName() { return name; }
        public String getDepartment() { return department; }
        public double getSalary() { return salary; }
        public int getYearsOfExperience() { return yearsOfExperience; }
        
        @Override
        public String toString() {
            return String.format("%s (%s) - %.2f RON, %d years", 
                name, department, salary, yearsOfExperience);
        }
    }
    
    static class Transaction {
        String id;
        String type;  // DEBIT or CREDIT
        double amount;
        String date;
        
        public Transaction(String id, String type, double amount, String date) {
            this.id = id;
            this.type = type;
            this.amount = amount;
            this.date = date;
        }
        
        public String getId() { return id; }
        public String getType() { return type; }
        public double getAmount() { return amount; }
        public String getDate() { return date; }
    }

    public static void main(String[] args) {
        
        // ============= SCENARIO 1: Employee Management System =============
        
        List<Employee> employees = Arrays.asList(
            new Employee("Ana Popescu", "IT", 8000, 5),
            new Employee("Ion Ionescu", "IT", 12000, 8),
            new Employee("Maria Stan", "HR", 6000, 3),
            new Employee("Gheorghe Marin", "IT", 7000, 2),
            new Employee("Cristian Pavel", "Sales", 9000, 6),
            new Employee("Elena Dumitrescu", "Sales", 11000, 7),
            new Employee("Andrei Pop", "HR", 5500, 1),
            new Employee("Diana Radu", "IT", 9500, 4)
        );
        
        System.out.println("========== EMPLOYEE MANAGEMENT SYSTEM ==========\n");
        
        
        // 1. Find average salary by department
        System.out.println("1. Average Salary by Department:");
        Map<String, Double> avgSalaryByDept = employees.stream()
            .collect(Collectors.groupingBy(
                Employee::getDepartment,
                Collectors.averagingDouble(Employee::getSalary)
            ));
        
        avgSalaryByDept.forEach((dept, avg) -> 
            System.out.printf("   %s: %.2f RON%n", dept, avg));
        System.out.println();
        
        
        // 2. Find top 3 highest paid employees
        System.out.println("2. Top 3 Highest Paid Employees:");
        employees.stream()
                .sorted(Comparator.comparing(Employee::getSalary).reversed())
                .limit(3)
                .forEach(e -> System.out.println("   " + e));
        System.out.println();
        
        
        // 3. Find employees with salary above department average
        System.out.println("3. Employees with Above-Average Salary in Their Department:");
        
        employees.stream()
                .filter(e -> e.getSalary() > avgSalaryByDept.get(e.getDepartment()))
                .forEach(e -> System.out.printf("   %s: %.2f RON (avg: %.2f RON)%n", 
                    e.getName(), e.getSalary(), avgSalaryByDept.get(e.getDepartment())));
        System.out.println();
        
        
        // 4. Calculate total salary budget per department
        System.out.println("4. Total Salary Budget by Department:");
        Map<String, Double> totalBudget = employees.stream()
            .collect(Collectors.groupingBy(
                Employee::getDepartment,
                Collectors.summingDouble(Employee::getSalary)
            ));
        
        totalBudget.forEach((dept, total) -> 
            System.out.printf("   %s: %.2f RON%n", dept, total));
        System.out.println();
        
        
        // 5. Find most experienced employee in each department
        System.out.println("5. Most Experienced Employee by Department:");
        Map<String, Optional<Employee>> mostExperienced = employees.stream()
            .collect(Collectors.groupingBy(
                Employee::getDepartment,
                Collectors.maxBy(Comparator.comparing(Employee::getYearsOfExperience))
            ));
        
        mostExperienced.forEach((dept, emp) -> 
            emp.ifPresent(e -> System.out.printf("   %s: %s (%d years)%n", 
                dept, e.getName(), e.getYearsOfExperience())));
        System.out.println();
        
        
        // 6. Give 10% raise to IT employees with >3 years experience
        System.out.println("6. IT Employees Eligible for 10% Raise (>3 years):");
        List<Employee> eligibleForRaise = employees.stream()
            .filter(e -> e.getDepartment().equals("IT"))
            .filter(e -> e.getYearsOfExperience() > 3)
            .collect(Collectors.toList());
        
        eligibleForRaise.forEach(e -> 
            System.out.printf("   %s: %.2f RON -> %.2f RON%n", 
                e.getName(), e.getSalary(), e.getSalary() * 1.1));
        System.out.println();
        
        
        // ============= SCENARIO 2: Banking Transactions =============
        
        List<Transaction> transactions = Arrays.asList(
            new Transaction("T001", "CREDIT", 5000, "2024-01-15"),
            new Transaction("T002", "DEBIT", 2000, "2024-01-16"),
            new Transaction("T003", "CREDIT", 3000, "2024-01-17"),
            new Transaction("T004", "DEBIT", 1500, "2024-01-18"),
            new Transaction("T005", "CREDIT", 10000, "2024-01-19"),
            new Transaction("T006", "DEBIT", 500, "2024-01-20"),
            new Transaction("T007", "DEBIT", 7000, "2024-01-21"),
            new Transaction("T008", "CREDIT", 2500, "2024-01-22")
        );
        
        System.out.println("\n========== BANKING TRANSACTIONS ==========\n");
        
        
        // 1. Calculate account balance
        System.out.println("1. Account Balance:");
        double balance = transactions.stream()
            .mapToDouble(t -> t.getType().equals("CREDIT") ? t.getAmount() : -t.getAmount())
            .sum();
        System.out.printf("   Current balance: %.2f RON%n", balance);
        System.out.println();
        
        
        // 2. Total credits and debits
        System.out.println("2. Total Credits and Debits:");
        Map<String, Double> totals = transactions.stream()
            .collect(Collectors.groupingBy(
                Transaction::getType,
                Collectors.summingDouble(Transaction::getAmount)
            ));
        
        totals.forEach((type, total) -> 
            System.out.printf("   Total %s: %.2f RON%n", type, total));
        System.out.println();
        
        
        // 3. Find largest transaction
        System.out.println("3. Largest Transaction:");
        transactions.stream()
                   .max(Comparator.comparing(Transaction::getAmount))
                   .ifPresent(t -> System.out.printf("   %s: %s %.2f RON on %s%n", 
                       t.getId(), t.getType(), t.getAmount(), t.getDate()));
        System.out.println();
        
        
        // 4. Find all large transactions (> 5000)
        System.out.println("4. Large Transactions (> 5000 RON):");
        transactions.stream()
                   .filter(t -> t.getAmount() > 5000)
                   .forEach(t -> System.out.printf("   %s: %s %.2f RON on %s%n", 
                       t.getId(), t.getType(), t.getAmount(), t.getDate()));
        System.out.println();
        
        
        // 5. Average transaction amount by type
        System.out.println("5. Average Transaction Amount by Type:");
        Map<String, Double> avgByType = transactions.stream()
            .collect(Collectors.groupingBy(
                Transaction::getType,
                Collectors.averagingDouble(Transaction::getAmount)
            ));
        
        avgByType.forEach((type, avg) -> 
            System.out.printf("   %s: %.2f RON%n", type, avg));
        System.out.println();
        
        
        // ============= SCENARIO 3: Text Processing =============
        
        System.out.println("\n========== TEXT PROCESSING ==========\n");
        
        String text = "Java Streams provide a functional approach to processing collections " +
                     "of objects. They make it easier to write clean and concise code. " +
                     "Streams can perform complex data processing operations efficiently.";
        
        
        // 1. Word frequency
        System.out.println("1. Word Frequency (words with >5 chars):");
        Map<String, Long> wordFrequency = Arrays.stream(text.toLowerCase().split("\\W+"))
            .filter(word -> word.length() > 5)
            .collect(Collectors.groupingBy(
                word -> word,
                Collectors.counting()
            ));
        
        wordFrequency.entrySet().stream()
                    .sorted(Map.Entry.<String, Long>comparingByValue().reversed())
                    .forEach(entry -> System.out.printf("   %s: %d times%n", 
                        entry.getKey(), entry.getValue()));
        System.out.println();
        
        
        // 2. Find longest word
        System.out.println("2. Longest Word:");
        Arrays.stream(text.split("\\W+"))
             .max(Comparator.comparing(String::length))
             .ifPresent(word -> System.out.println("   " + word + " (" + word.length() + " chars)"));
        System.out.println();
        
        
        // 3. Count words starting with specific letters
        System.out.println("3. Words Starting with 'c' or 'p' (case-insensitive):");
        long count = Arrays.stream(text.toLowerCase().split("\\W+"))
                          .filter(word -> word.startsWith("c") || word.startsWith("p"))
                          .distinct()
                          .count();
        System.out.println("   Count: " + count);
        System.out.println();
        
        
        // ============= SCENARIO 4: Data Validation =============
        
        System.out.println("\n========== DATA VALIDATION ==========\n");
        
        List<String> emails = Arrays.asList(
            "ana.popescu@gmail.com",
            "ion@yahoo.com",
            "invalid-email",
            "maria.stan@company.ro",
            "gheorghe@",
            "cristian.pavel@outlook.com",
            "@domain.com"
        );
        
        
        // 1. Filter valid emails
        System.out.println("1. Valid Emails:");
        List<String> validEmails = emails.stream()
            .filter(email -> email.matches("^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$"))
            .collect(Collectors.toList());
        
        validEmails.forEach(email -> System.out.println("   ✓ " + email));
        System.out.println();
        
        
        // 2. Group by domain
        System.out.println("2. Valid Emails Grouped by Domain:");
        Map<String, List<String>> byDomain = validEmails.stream()
            .collect(Collectors.groupingBy(email -> email.substring(email.indexOf('@') + 1)));
        
        byDomain.forEach((domain, domainEmails) -> {
            System.out.println("   " + domain + ":");
            domainEmails.forEach(e -> System.out.println("     - " + e));
        });
        System.out.println();
        
        
        // 3. Invalid emails
        System.out.println("3. Invalid Emails:");
        emails.stream()
             .filter(email -> !email.matches("^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$"))
             .forEach(email -> System.out.println("   ✗ " + email));
    }
}

