import java.util.Arrays;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * Stream Basics - Introduction to Java Streams
 * 
 * Streams provide a functional approach to process collections of objects.
 * They allow you to write declarative code (what to do) instead of imperative code (how to do it).
 */
public class StreamBasics {

    public static void main(String[] args) {
        
        // ============= 1. CREATING STREAMS =============
        
        // From a collection
        List<String> names = Arrays.asList("Ana", "Maria", "Ion", "Gheorghe", "Cristian");
        Stream<String> streamFromList = names.stream();
        
        // From array
        String[] arrayNames = {"Ana", "Maria", "Ion"};
        Stream<String> streamFromArray = Arrays.stream(arrayNames);
        
        // Using Stream.of()
        Stream<String> streamOf = Stream.of("Ana", "Maria", "Ion");
        
        // Generate infinite stream (use limit!)
        Stream<Integer> infiniteStream = Stream.iterate(0, n -> n + 1).limit(10);
        
        // Generate random numbers
        Stream<Double> randomStream = Stream.generate(Math::random).limit(5);
        
        
        // ============= 2. INTERMEDIATE OPERATIONS (lazy evaluation) =============
        
        List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        
        // FILTER - selects elements based on a condition
        System.out.println("=== FILTER ===");
        numbers.stream()
               .filter(n -> n % 2 == 0)  // only even numbers
               .forEach(n -> System.out.print(n + " "));  // Output: 2 4 6 8 10
        System.out.println("\n");
        
        
        // MAP - transforms each element
        System.out.println("=== MAP ===");
        names.stream()
             .map(String::toUpperCase)  // convert to uppercase
             .forEach(System.out::println);  // ANA, MARIA, ION, GHEORGHE, CRISTIAN
        System.out.println();
        
        
        // SORTED - sorts the elements
        System.out.println("=== SORTED ===");
        names.stream()
             .sorted()  // natural order
             .forEach(System.out::println);
        System.out.println();
        
        
        // DISTINCT - removes duplicates
        System.out.println("=== DISTINCT ===");
        List<Integer> duplicates = Arrays.asList(1, 2, 2, 3, 3, 3, 4, 5, 5);
        duplicates.stream()
                  .distinct()
                  .forEach(n -> System.out.print(n + " "));  // 1 2 3 4 5
        System.out.println("\n");
        
        
        // LIMIT - limits the number of elements
        System.out.println("=== LIMIT ===");
        numbers.stream()
               .limit(5)
               .forEach(n -> System.out.print(n + " "));  // 1 2 3 4 5
        System.out.println("\n");
        
        
        // SKIP - skips the first n elements
        System.out.println("=== SKIP ===");
        numbers.stream()
               .skip(5)
               .forEach(n -> System.out.print(n + " "));  // 6 7 8 9 10
        System.out.println("\n");
        
        
        // PEEK - performs an action on each element (mainly for debugging)
        System.out.println("=== PEEK ===");
        numbers.stream()
               .peek(n -> System.out.println("Processing: " + n))
               .filter(n -> n > 5)
               .forEach(n -> System.out.println("Filtered: " + n));
        System.out.println();
        
        
        // ============= 3. TERMINAL OPERATIONS (trigger stream execution) =============
        
        // FOREACH - performs an action for each element
        System.out.println("=== FOREACH ===");
        names.stream().forEach(System.out::println);
        System.out.println();
        
        
        // COLLECT - converts stream to a collection
        System.out.println("=== COLLECT ===");
        List<String> uppercaseNames = names.stream()
                                          .map(String::toUpperCase)
                                          .collect(Collectors.toList());
        System.out.println(uppercaseNames);
        System.out.println();
        
        
        // COUNT - counts the elements
        System.out.println("=== COUNT ===");
        long count = numbers.stream()
                           .filter(n -> n > 5)
                           .count();
        System.out.println("Numbers greater than 5: " + count);  // 5
        System.out.println();
        
        
        // REDUCE - reduces elements to a single value
        System.out.println("=== REDUCE ===");
        Optional<Integer> sum = numbers.stream()
                                      .reduce((a, b) -> a + b);
        sum.ifPresent(s -> System.out.println("Sum: " + s));  // 55
        
        int sumWithIdentity = numbers.stream()
                                    .reduce(0, (a, b) -> a + b);
        System.out.println("Sum with identity: " + sumWithIdentity);  // 55
        System.out.println();
        
        
        // MIN/MAX - finds minimum/maximum element
        System.out.println("=== MIN/MAX ===");
        Optional<Integer> min = numbers.stream().min(Integer::compare);
        Optional<Integer> max = numbers.stream().max(Integer::compare);
        min.ifPresent(m -> System.out.println("Min: " + m));  // 1
        max.ifPresent(m -> System.out.println("Max: " + m));  // 10
        System.out.println();
        
        
        // ANYMATCH, ALLMATCH, NONEMATCH - checking predicates
        System.out.println("=== MATCHING ===");
        boolean anyGreaterThan5 = numbers.stream().anyMatch(n -> n > 5);
        boolean allPositive = numbers.stream().allMatch(n -> n > 0);
        boolean noneNegative = numbers.stream().noneMatch(n -> n < 0);
        
        System.out.println("Any number > 5? " + anyGreaterThan5);  // true
        System.out.println("All positive? " + allPositive);  // true
        System.out.println("None negative? " + noneNegative);  // true
        System.out.println();
        
        
        // FINDFIRST, FINDANY - finds an element
        System.out.println("=== FIND ===");
        Optional<Integer> firstEven = numbers.stream()
                                            .filter(n -> n % 2 == 0)
                                            .findFirst();
        firstEven.ifPresent(n -> System.out.println("First even: " + n));  // 2
        System.out.println();
        
        
        // ============= 4. CHAINING OPERATIONS =============
        System.out.println("=== CHAINING ===");
        List<String> result = names.stream()
                                  .filter(name -> name.length() > 3)  // names longer than 3 chars
                                  .map(String::toUpperCase)           // convert to uppercase
                                  .sorted()                           // sort alphabetically
                                  .collect(Collectors.toList());      // collect to list
        
        System.out.println("Filtered, mapped and sorted: " + result);
    }
}

