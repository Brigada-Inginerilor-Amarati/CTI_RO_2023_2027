import java.util.Arrays;
import java.util.Comparator;
import java.util.IntSummaryStatistics;
import java.util.List;
import java.util.Optional;
import java.util.OptionalDouble;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

/**
 * Advanced Stream Operations
 * 
 * This file covers more complex stream operations including:
 * - flatMap for nested structures
 * - Primitive streams (IntStream, DoubleStream, LongStream)
 * - Optional handling
 * - Complex filtering and sorting
 */
public class StreamAdvanced {

    static class Course {
        String name;
        List<String> students;
        
        public Course(String name, String... students) {
            this.name = name;
            this.students = Arrays.asList(students);
        }
        
        public String getName() { return name; }
        public List<String> getStudents() { return students; }
    }
    
    static class Person {
        String name;
        int age;
        Optional<String> email;
        List<String> phoneNumbers;
        
        public Person(String name, int age, String email, String... phones) {
            this.name = name;
            this.age = age;
            this.email = Optional.ofNullable(email);
            this.phoneNumbers = Arrays.asList(phones);
        }
        
        public String getName() { return name; }
        public int getAge() { return age; }
        public Optional<String> getEmail() { return email; }
        public List<String> getPhoneNumbers() { return phoneNumbers; }
    }

    public static void main(String[] args) {
        
        // ============= 1. FLATMAP - Flattening nested structures =============
        
        System.out.println("=== flatMap() - Flattening Lists ===");
        
        List<Course> courses = Arrays.asList(
            new Course("PDSS", "Ana", "Ion", "Maria"),
            new Course("POO", "Ana", "Gheorghe", "Cristian"),
            new Course("BD", "Ion", "Maria", "Andrei")
        );
        
        // Get all unique students across all courses
        Set<String> allStudents = courses.stream()
                                        .flatMap(course -> course.getStudents().stream())
                                        .collect(Collectors.toSet());
        System.out.println("All unique students: " + allStudents);
        System.out.println();
        
        
        // Count total enrollments (with duplicates)
        long totalEnrollments = courses.stream()
                                      .flatMap(course -> course.getStudents().stream())
                                      .count();
        System.out.println("Total enrollments: " + totalEnrollments);
        System.out.println();
        
        
        // ============= 2. FLATMAP with Arrays =============
        
        System.out.println("=== flatMap() with Arrays ===");
        
        List<String> sentences = Arrays.asList(
            "Java streams are powerful",
            "Learn functional programming",
            "Master stream operations"
        );
        
        // Get all words from all sentences
        List<String> allWords = sentences.stream()
                                        .flatMap(sentence -> Arrays.stream(sentence.split(" ")))
                                        .collect(Collectors.toList());
        System.out.println("All words: " + allWords);
        System.out.println();
        
        
        // Get unique words (case-insensitive)
        Set<String> uniqueWords = sentences.stream()
                                          .flatMap(sentence -> Arrays.stream(sentence.split(" ")))
                                          .map(String::toLowerCase)
                                          .collect(Collectors.toSet());
        System.out.println("Unique words: " + uniqueWords);
        System.out.println();
        
        
        // ============= 3. PRIMITIVE STREAMS =============
        
        System.out.println("=== Primitive Streams ===");
        
        // IntStream
        IntStream intStream = IntStream.range(1, 10);  // 1 to 9
        System.out.println("IntStream range(1, 10): " + intStream.boxed().collect(Collectors.toList()));
        
        IntStream intStreamClosed = IntStream.rangeClosed(1, 10);  // 1 to 10
        System.out.println("IntStream rangeClosed(1, 10): " + intStreamClosed.boxed().collect(Collectors.toList()));
        
        
        // mapToInt, mapToDouble, mapToLong
        List<String> numbers = Arrays.asList("1", "2", "3", "4", "5");
        
        int sum = numbers.stream()
                        .mapToInt(Integer::parseInt)
                        .sum();
        System.out.println("Sum: " + sum);
        
        OptionalDouble average = numbers.stream()
                                       .mapToInt(Integer::parseInt)
                                       .average();
        average.ifPresent(avg -> System.out.println("Average: " + avg));
        
        
        IntSummaryStatistics stats = numbers.stream()
                                           .mapToInt(Integer::parseInt)
                                           .summaryStatistics();
        System.out.println("Statistics: " + stats);
        System.out.println();
        
        
        // ============= 4. OPTIONAL HANDLING =============
        
        System.out.println("=== Optional with Streams ===");
        
        List<Person> people = Arrays.asList(
            new Person("Ana", 25, "ana@email.com", "0721111111", "0722222222"),
            new Person("Ion", 30, null, "0733333333"),
            new Person("Maria", 28, "maria@email.com", "0744444444")
        );
        
        // Get all emails (filtering out empty optionals)
        List<String> emails = people.stream()
                                   .map(Person::getEmail)
                                   .filter(Optional::isPresent)
                                   .map(Optional::get)
                                   .collect(Collectors.toList());
        System.out.println("Emails: " + emails);
        
        
        // Better approach with flatMap
        List<String> emailsBetter = people.stream()
                                         .map(Person::getEmail)
                                         .flatMap(Optional::stream)  // Java 9+
                                         .collect(Collectors.toList());
        System.out.println("Emails (flatMap): " + emailsBetter);
        System.out.println();
        
        
        // ============= 5. COMPLEX FILTERING AND SORTING =============
        
        System.out.println("=== Complex Filtering ===");
        
        List<Integer> nums = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
        
        // Multiple filter conditions
        List<Integer> filtered = nums.stream()
                                    .filter(n -> n > 3)
                                    .filter(n -> n < 10)
                                    .filter(n -> n % 2 == 0)
                                    .collect(Collectors.toList());
        System.out.println("Filtered (>3, <10, even): " + filtered);
        System.out.println();
        
        
        System.out.println("=== Complex Sorting ===");
        
        // Sort people by age, then by name
        List<Person> sortedPeople = people.stream()
                                         .sorted(Comparator.comparing(Person::getAge)
                                                          .thenComparing(Person::getName))
                                         .collect(Collectors.toList());
        
        System.out.println("Sorted by age then name:");
        sortedPeople.forEach(p -> System.out.println("  " + p.getName() + " - " + p.getAge()));
        System.out.println();
        
        
        // ============= 6. FLATMAP with Complex Objects =============
        
        System.out.println("=== flatMap() with Phone Numbers ===");
        
        // Get all phone numbers from all people
        List<String> allPhones = people.stream()
                                      .flatMap(person -> person.getPhoneNumbers().stream())
                                      .collect(Collectors.toList());
        System.out.println("All phone numbers: " + allPhones);
        System.out.println();
        
        
        // ============= 7. TAKEWHILE & DROPWHILE (Java 9+) =============
        
        System.out.println("=== takeWhile() & dropWhile() ===");
        
        List<Integer> ordered = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8);
        
        // takeWhile - take elements while condition is true
        List<Integer> taken = ordered.stream()
                                    .takeWhile(n -> n < 5)
                                    .collect(Collectors.toList());
        System.out.println("takeWhile(n < 5): " + taken);  // [1, 2, 3, 4]
        
        // dropWhile - drop elements while condition is true
        List<Integer> dropped = ordered.stream()
                                      .dropWhile(n -> n < 5)
                                      .collect(Collectors.toList());
        System.out.println("dropWhile(n < 5): " + dropped);  // [5, 6, 7, 8]
        System.out.println();
        
        
        // ============= 8. PARALLEL STREAMS =============
        
        System.out.println("=== Parallel Streams ===");
        
        List<Integer> largeList = IntStream.rangeClosed(1, 1000)
                                          .boxed()
                                          .collect(Collectors.toList());
        
        // Sequential stream
        long startSeq = System.currentTimeMillis();
        long sumSeq = largeList.stream()
                              .mapToLong(Integer::longValue)
                              .sum();
        long endSeq = System.currentTimeMillis();
        
        // Parallel stream
        long startPar = System.currentTimeMillis();
        long sumPar = largeList.parallelStream()
                              .mapToLong(Integer::longValue)
                              .sum();
        long endPar = System.currentTimeMillis();
        
        System.out.println("Sequential: " + sumSeq + " (time: " + (endSeq - startSeq) + "ms)");
        System.out.println("Parallel: " + sumPar + " (time: " + (endPar - startPar) + "ms)");
        System.out.println();
        
        
        // ============= 9. CUSTOM COMPARATORS =============
        
        System.out.println("=== Custom Comparators ===");
        
        // Sort by name length, then alphabetically
        List<String> names = Arrays.asList("Ana", "Ion", "Gheorghe", "Maria", "Cristian", "Iza");
        
        List<String> sortedNames = names.stream()
                                       .sorted(Comparator.comparing(String::length)
                                                        .thenComparing(Comparator.naturalOrder()))
                                       .collect(Collectors.toList());
        System.out.println("Sorted by length then alphabetically: " + sortedNames);
        
        
        // Reverse order
        List<String> reverseSorted = names.stream()
                                         .sorted(Comparator.reverseOrder())
                                         .collect(Collectors.toList());
        System.out.println("Reverse alphabetical: " + reverseSorted);
        System.out.println();
        
        
        // ============= 10. FINDING AND MATCHING =============
        
        System.out.println("=== Finding and Matching ===");
        
        // Find first element matching condition
        Optional<Person> firstAdult = people.stream()
                                           .filter(p -> p.getAge() >= 18)
                                           .findFirst();
        firstAdult.ifPresent(p -> System.out.println("First adult: " + p.getName()));
        
        
        // Find any (useful in parallel streams)
        Optional<Person> anyAdult = people.parallelStream()
                                         .filter(p -> p.getAge() >= 18)
                                         .findAny();
        anyAdult.ifPresent(p -> System.out.println("Any adult: " + p.getName()));
        
        
        // Check if any/all/none match
        boolean anyOver30 = people.stream().anyMatch(p -> p.getAge() > 30);
        boolean allAdults = people.stream().allMatch(p -> p.getAge() >= 18);
        boolean noneUnder18 = people.stream().noneMatch(p -> p.getAge() < 18);
        
        System.out.println("Any over 30? " + anyOver30);
        System.out.println("All adults? " + allAdults);
        System.out.println("None under 18? " + noneUnder18);
    }
}

