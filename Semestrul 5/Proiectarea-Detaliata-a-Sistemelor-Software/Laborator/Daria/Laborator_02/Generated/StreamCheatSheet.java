import java.util.Arrays;
import java.util.Collection;
import java.util.Comparator;
import java.util.IntSummaryStatistics;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.OptionalDouble;
import java.util.Set;
import java.util.TreeSet;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

/**
 * Java Streams Cheat Sheet
 * 
 * Quick reference for all common stream operations.
 * Use this as a quick lookup guide!
 */
public class StreamCheatSheet {

    public static void main(String[] args) {
        
        List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        List<String> names = Arrays.asList("Ana", "Ion", "Maria", "Gheorghe", "Cristian");
        
        System.out.println("========== JAVA STREAMS CHEAT SHEET ==========\n");
        
        // ============= CREATING STREAMS =============
        System.out.println("=== Creating Streams ===");
        
        // From collection
        Stream<String> stream1 = names.stream();
        
        // From array
        Stream<String> stream2 = Arrays.stream(new String[]{"a", "b", "c"});
        
        // From values
        Stream<String> stream3 = Stream.of("a", "b", "c");
        
        // Empty stream
        Stream<String> stream4 = Stream.empty();
        
        // Infinite streams (use limit!)
        Stream<Integer> stream5 = Stream.iterate(0, n -> n + 1).limit(5);
        Stream<Double> stream6 = Stream.generate(Math::random).limit(5);
        
        // IntStream, DoubleStream, LongStream
        IntStream intStream = IntStream.range(1, 10);          // 1 to 9
        IntStream intStream2 = IntStream.rangeClosed(1, 10);   // 1 to 10
        
        System.out.println("✓ Streams created\n");
        
        
        // ============= INTERMEDIATE OPERATIONS (Lazy) =============
        System.out.println("=== Intermediate Operations ===");
        
        // FILTER - keep elements matching condition
        List<Integer> evens = numbers.stream()
                                    .filter(n -> n % 2 == 0)
                                    .collect(Collectors.toList());
        System.out.println("filter(n -> n % 2 == 0): " + evens);
        
        
        // MAP - transform elements
        List<String> uppercase = names.stream()
                                     .map(String::toUpperCase)
                                     .collect(Collectors.toList());
        System.out.println("map(String::toUpperCase): " + uppercase);
        
        
        // FLATMAP - flatten nested structures
        List<List<Integer>> nested = Arrays.asList(
            Arrays.asList(1, 2),
            Arrays.asList(3, 4),
            Arrays.asList(5, 6)
        );
        List<Integer> flattened = nested.stream()
                                       .flatMap(Collection::stream)
                                       .collect(Collectors.toList());
        System.out.println("flatMap: " + flattened);
        
        
        // SORTED - sort elements
        List<Integer> sorted = numbers.stream()
                                     .sorted(Comparator.reverseOrder())
                                     .collect(Collectors.toList());
        System.out.println("sorted(reverseOrder): " + sorted);
        
        
        // DISTINCT - remove duplicates
        List<Integer> distinct = Arrays.asList(1, 2, 2, 3, 3, 3).stream()
                                       .distinct()
                                       .collect(Collectors.toList());
        System.out.println("distinct: " + distinct);
        
        
        // LIMIT - take first n elements
        List<Integer> limited = numbers.stream()
                                      .limit(3)
                                      .collect(Collectors.toList());
        System.out.println("limit(3): " + limited);
        
        
        // SKIP - skip first n elements
        List<Integer> skipped = numbers.stream()
                                      .skip(7)
                                      .collect(Collectors.toList());
        System.out.println("skip(7): " + skipped);
        
        
        // PEEK - perform action (for debugging)
        numbers.stream()
              .peek(n -> System.out.print(n + " "))
              .filter(n -> n > 5)
              .forEach(n -> {}); // triggers stream
        System.out.println("(peek demo)");
        
        
        // TAKEWHILE & DROPWHILE (Java 9+)
        List<Integer> taken = numbers.stream()
                                    .takeWhile(n -> n < 5)
                                    .collect(Collectors.toList());
        System.out.println("takeWhile(n < 5): " + taken);
        
        System.out.println();
        
        
        // ============= TERMINAL OPERATIONS (Eager) =============
        System.out.println("=== Terminal Operations ===");
        
        // COLLECT - collect to collection
        List<Integer> list = numbers.stream().collect(Collectors.toList());
        Set<Integer> set = numbers.stream().collect(Collectors.toSet());
        System.out.println("collect(toList): " + list);
        
        
        // FOREACH - perform action on each element
        System.out.print("forEach: ");
        numbers.stream().limit(5).forEach(n -> System.out.print(n + " "));
        System.out.println();
        
        
        // COUNT - count elements
        long count = numbers.stream().filter(n -> n > 5).count();
        System.out.println("count (n > 5): " + count);
        
        
        // REDUCE - reduce to single value
        Optional<Integer> sum = numbers.stream().reduce((a, b) -> a + b);
        int sumWithIdentity = numbers.stream().reduce(0, (a, b) -> a + b);
        System.out.println("reduce (sum): " + sum.orElse(0));
        
        
        // MIN / MAX - find min/max
        Optional<Integer> min = numbers.stream().min(Integer::compare);
        Optional<Integer> max = numbers.stream().max(Integer::compare);
        System.out.println("min: " + min.orElse(0) + ", max: " + max.orElse(0));
        
        
        // ANYMATCH / ALLMATCH / NONEMATCH - check conditions
        boolean anyEven = numbers.stream().anyMatch(n -> n % 2 == 0);
        boolean allPositive = numbers.stream().allMatch(n -> n > 0);
        boolean noneNegative = numbers.stream().noneMatch(n -> n < 0);
        System.out.println("anyMatch(even): " + anyEven);
        System.out.println("allMatch(positive): " + allPositive);
        System.out.println("noneMatch(negative): " + noneNegative);
        
        
        // FINDFIRST / FINDANY - find element
        Optional<Integer> first = numbers.stream().filter(n -> n > 5).findFirst();
        Optional<Integer> any = numbers.stream().filter(n -> n > 5).findAny();
        System.out.println("findFirst (n > 5): " + first.orElse(0));
        
        
        // TOARRAY - convert to array
        Integer[] array = numbers.stream().toArray(Integer[]::new);
        System.out.println("toArray: " + Arrays.toString(array));
        
        System.out.println();
        
        
        // ============= COLLECTORS =============
        System.out.println("=== Collectors ===");
        
        // toList, toSet, toCollection
        List<String> list1 = names.stream().collect(Collectors.toList());
        Set<String> set1 = names.stream().collect(Collectors.toSet());
        TreeSet<String> treeSet = names.stream().collect(Collectors.toCollection(TreeSet::new));
        System.out.println("toList: " + list1);
        
        
        // toMap - create map
        Map<String, Integer> nameLength = names.stream()
                                               .collect(Collectors.toMap(
                                                   name -> name,
                                                   String::length
                                               ));
        System.out.println("toMap: " + nameLength);
        
        
        // groupingBy - group elements
        Map<Integer, List<String>> byLength = names.stream()
                                                   .collect(Collectors.groupingBy(String::length));
        System.out.println("groupingBy(length): " + byLength);
        
        
        // groupingBy with counting
        Map<Integer, Long> countByLength = names.stream()
                                                .collect(Collectors.groupingBy(
                                                    String::length,
                                                    Collectors.counting()
                                                ));
        System.out.println("groupingBy with counting: " + countByLength);
        
        
        // partitioningBy - split into two groups
        Map<Boolean, List<Integer>> partitioned = numbers.stream()
                                                        .collect(Collectors.partitioningBy(n -> n > 5));
        System.out.println("partitioningBy(n > 5): " + partitioned);
        
        
        // joining - concatenate strings
        String joined = names.stream().collect(Collectors.joining(", "));
        String joinedWithBrackets = names.stream().collect(Collectors.joining(", ", "[", "]"));
        System.out.println("joining: " + joined);
        System.out.println("joining with prefix/suffix: " + joinedWithBrackets);
        
        
        // summarizingInt/Double/Long - statistics
        IntSummaryStatistics stats = numbers.stream()
                                           .collect(Collectors.summarizingInt(Integer::intValue));
        System.out.println("summarizingInt: " + stats);
        
        
        // summing, averaging
        int total = numbers.stream().collect(Collectors.summingInt(Integer::intValue));
        double avg = numbers.stream().collect(Collectors.averagingInt(Integer::intValue));
        System.out.println("summingInt: " + total + ", averagingInt: " + avg);
        
        System.out.println();
        
        
        // ============= PRIMITIVE STREAMS =============
        System.out.println("=== Primitive Streams ===");
        
        // mapToInt, mapToDouble, mapToLong
        int sumInt = names.stream().mapToInt(String::length).sum();
        OptionalDouble avgDouble = names.stream().mapToInt(String::length).average();
        System.out.println("mapToInt sum: " + sumInt);
        System.out.println("mapToInt average: " + avgDouble.orElse(0));
        
        
        // IntStream operations
        IntStream.range(1, 5).forEach(n -> System.out.print(n + " "));
        System.out.println("(IntStream.range)");
        
        IntStream.rangeClosed(1, 5).forEach(n -> System.out.print(n + " "));
        System.out.println("(IntStream.rangeClosed)");
        
        System.out.println();
        
        
        // ============= COMMON PATTERNS =============
        System.out.println("=== Common Patterns ===");
        
        // Pattern 1: Filter + Map + Collect
        List<String> result1 = names.stream()
                                   .filter(name -> name.length() > 3)
                                   .map(String::toUpperCase)
                                   .collect(Collectors.toList());
        System.out.println("Filter + Map + Collect: " + result1);
        
        
        // Pattern 2: Sort + Limit
        List<Integer> top3 = numbers.stream()
                                   .sorted(Comparator.reverseOrder())
                                   .limit(3)
                                   .collect(Collectors.toList());
        System.out.println("Sort + Limit (top 3): " + top3);
        
        
        // Pattern 3: Group and Count
        Map<Integer, Long> lengthFrequency = names.stream()
                                                  .collect(Collectors.groupingBy(
                                                      String::length,
                                                      Collectors.counting()
                                                  ));
        System.out.println("Group and Count: " + lengthFrequency);
        
        
        // Pattern 4: Find max/min with custom comparator
        Optional<String> longest = names.stream()
                                       .max(Comparator.comparing(String::length));
        System.out.println("Longest name: " + longest.orElse("N/A"));
        
        
        // Pattern 5: Check conditions
        boolean hasLongName = names.stream().anyMatch(name -> name.length() > 7);
        System.out.println("Has name > 7 chars: " + hasLongName);
        
        System.out.println();
        
        
        // ============= COMPARATORS =============
        System.out.println("=== Comparators ===");
        
        // Natural order
        List<String> sorted1 = names.stream()
                                   .sorted()
                                   .collect(Collectors.toList());
        System.out.println("Natural order: " + sorted1);
        
        
        // Reverse order
        List<String> sorted2 = names.stream()
                                   .sorted(Comparator.reverseOrder())
                                   .collect(Collectors.toList());
        System.out.println("Reverse order: " + sorted2);
        
        
        // Custom comparator
        List<String> sorted3 = names.stream()
                                   .sorted(Comparator.comparing(String::length))
                                   .collect(Collectors.toList());
        System.out.println("By length: " + sorted3);
        
        
        // Multiple comparators
        List<String> sorted4 = names.stream()
                                   .sorted(Comparator.comparing(String::length)
                                                    .thenComparing(Comparator.naturalOrder()))
                                   .collect(Collectors.toList());
        System.out.println("By length then alphabetically: " + sorted4);
        
        System.out.println();
        
        
        // ============= OPTIONAL HANDLING =============
        System.out.println("=== Optional Handling ===");
        
        Optional<String> optional = names.stream().findFirst();
        
        // ifPresent
        optional.ifPresent(name -> System.out.println("ifPresent: " + name));
        
        // orElse
        String value1 = optional.orElse("default");
        System.out.println("orElse: " + value1);
        
        // orElseGet
        String value2 = optional.orElseGet(() -> "default from supplier");
        System.out.println("orElseGet: " + value2);
        
        // map
        Optional<Integer> length = optional.map(String::length);
        System.out.println("map: " + length.orElse(0));
        
        // filter
        Optional<String> filtered = optional.filter(name -> name.length() > 3);
        System.out.println("filter: " + filtered.orElse("N/A"));
        
        System.out.println();
        
        
        System.out.println("========================================");
        System.out.println("✓ Cheat sheet complete!");
        System.out.println("Use this as a quick reference guide.");
        System.out.println("========================================");
    }
}

