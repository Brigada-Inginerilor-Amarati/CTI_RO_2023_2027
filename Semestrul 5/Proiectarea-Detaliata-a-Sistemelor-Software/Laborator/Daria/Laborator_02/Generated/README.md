# Java Streams - Comprehensive Learning Guide

This folder contains a complete guide to understanding and mastering Java Streams API.

## 📚 Files Overview

### 1. **StreamBasics.java**

**Start here!** This file covers all fundamental stream operations:

- Creating streams (from collections, arrays, Stream.of, generate, iterate)
- **Intermediate operations**: filter, map, sorted, distinct, limit, skip, peek
- **Terminal operations**: forEach, collect, count, reduce, min/max, anyMatch/allMatch/noneMatch, findFirst/findAny
- Chaining operations

**Key Learning Points:**

- Understand the difference between intermediate (lazy) and terminal (eager) operations
- Learn how to chain operations together
- Practice with simple filtering, mapping, and collecting

---

### 2. **StreamCollectors.java**

Advanced collection and grouping operations:

- Basic collectors: toList(), toSet(), toCollection()
- **toMap()**: Creating maps from streams
- **groupingBy()**: Grouping elements by criteria
  - With counting
  - With summing
  - With averaging
- **partitioningBy()**: Splitting into two groups
- **joining()**: String concatenation
- Statistical collectors
- Multi-level grouping
- Custom reductions

**Key Learning Points:**

- Master the Collectors utility class
- Understand grouping and partitioning
- Learn to perform aggregate operations

---

### 3. **StreamAdvanced.java**

Complex and advanced stream operations:

- **flatMap()**: Flattening nested structures (lists of lists, arrays in objects)
- **Primitive streams**: IntStream, DoubleStream, LongStream
  - range(), rangeClosed()
  - mapToInt(), mapToDouble(), mapToLong()
  - summaryStatistics()
- **Optional handling** with streams
- Complex filtering and sorting
- **takeWhile() & dropWhile()** (Java 9+)
- **Parallel streams** for performance
- Custom comparators
- Finding and matching operations

**Key Learning Points:**

- Work with nested data structures
- Use primitive streams for better performance
- Understand parallel processing
- Master complex sorting scenarios

---

### 4. **StreamPracticalExamples.java**

Real-world scenarios and applications:

- **Employee Management System**
  - Calculate average salary by department
  - Find top performers
  - Salary analysis and budgeting
- **Banking Transactions**
  - Calculate balances
  - Analyze transaction patterns
  - Find anomalies
- **Text Processing**
  - Word frequency analysis
  - Finding patterns
  - Text statistics
- **Data Validation**
  - Email validation
  - Filtering invalid data
  - Grouping by patterns

**Key Learning Points:**

- Apply streams to real business problems
- Combine multiple operations for complex queries
- Practice data analysis with streams

---

### 5. **StreamExercises.java**

Practice exercises with solutions:

- 10 Regular exercises (beginner to intermediate)
- 5 Challenge exercises (advanced)
- Solutions included (commented out)

**How to use:**

1. Try to solve each exercise on your own
2. Uncomment the solution to check your answer
3. Run the verification code to see the results

---

## 🎯 Learning Path

### Beginner (Day 1-2)

1. Start with **StreamBasics.java**
2. Run it and understand each example
3. Try modifying the examples
4. Complete exercises 1-5 in **StreamExercises.java**

### Intermediate (Day 3-4)

1. Study **StreamCollectors.java**
2. Learn grouping and partitioning
3. Review **StreamPracticalExamples.java** (Employee and Banking scenarios)
4. Complete exercises 6-10 in **StreamExercises.java**

### Advanced (Day 5-7)

1. Master **StreamAdvanced.java**
2. Understand flatMap and parallel streams
3. Study all **StreamPracticalExamples.java** scenarios
4. Complete all challenge exercises
5. Create your own examples!

---

## 🔑 Key Concepts

### Stream Pipeline

```java
collection.stream()           // Source
    .filter(...)             // Intermediate operation (lazy)
    .map(...)                // Intermediate operation (lazy)
    .sorted(...)             // Intermediate operation (lazy)
    .collect(...)            // Terminal operation (triggers execution)
```

### Most Common Operations

**Filtering & Selecting:**

- `filter(predicate)` - keep elements matching condition
- `distinct()` - remove duplicates
- `limit(n)` - take first n elements
- `skip(n)` - skip first n elements

**Transforming:**

- `map(function)` - transform each element
- `flatMap(function)` - flatten nested structures
- `sorted()` - sort elements
- `peek(consumer)` - perform action (mainly debugging)

**Collecting:**

- `collect(Collectors.toList())` - to list
- `collect(Collectors.toSet())` - to set
- `collect(Collectors.groupingBy(...))` - group by key
- `collect(Collectors.joining(...))` - join strings

**Reducing:**

- `count()` - count elements
- `reduce(...)` - reduce to single value
- `min/max(comparator)` - find min/max
- `sum()` - sum (for primitive streams)
- `average()` - average (for primitive streams)

**Matching & Finding:**

- `anyMatch(predicate)` - check if any matches
- `allMatch(predicate)` - check if all match
- `noneMatch(predicate)` - check if none matches
- `findFirst()` - find first element
- `findAny()` - find any element

---

## 💡 Best Practices

1. **Use method references** when possible: `map(String::toUpperCase)` instead of `map(s -> s.toUpperCase())`

2. **Prefer streams for complex operations**, but simple loops are fine for simple tasks

3. **Don't reuse streams** - they can only be consumed once

4. **Use parallel streams carefully** - not always faster, especially for small datasets

5. **Handle Optional properly** - use `ifPresent()`, `orElse()`, `orElseGet()`

6. **Chain operations logically** - put cheap operations (like filter) before expensive ones (like sorted)

7. **Use primitive streams** (IntStream, DoubleStream) for better performance with numbers

---

## 🚀 Quick Reference

### Creating Streams

```java
List<String> list = Arrays.asList("a", "b", "c");
list.stream()                              // from collection
Arrays.stream(array)                       // from array
Stream.of("a", "b", "c")                   // from values
Stream.iterate(0, n -> n + 1).limit(10)    // infinite stream
IntStream.range(1, 10)                     // range of ints
```

### Common Patterns

```java
// Filter and collect
list.stream()
    .filter(s -> s.length() > 3)
    .collect(Collectors.toList());

// Map and collect
list.stream()
    .map(String::toUpperCase)
    .collect(Collectors.toList());

// Group by
list.stream()
    .collect(Collectors.groupingBy(String::length));

// Sum
numbers.stream()
    .mapToInt(Integer::intValue)
    .sum();

// Average
numbers.stream()
    .mapToDouble(Double::doubleValue)
    .average();
```

---

## 📖 Additional Resources

- Oracle Java Streams Tutorial: https://docs.oracle.com/javase/tutorial/collections/streams/
- Java 8 Stream API Documentation: https://docs.oracle.com/javase/8/docs/api/java/util/stream/Stream.html
- Practice more with the exercises in **StreamExercises.java**!

---

## 🎓 Tips for Success

1. **Run each file** and observe the output
2. **Modify the examples** to see what happens
3. **Break the code** intentionally to understand errors
4. **Write your own examples** based on your interests
5. **Complete all exercises** - practice is key!
6. **Compare your solutions** with the provided ones
7. **Ask questions** when something is unclear

---

**Good luck with your Java Streams journey! 🚀**

Remember: Streams are about expressing WHAT you want to do, not HOW to do it. Think declaratively!
