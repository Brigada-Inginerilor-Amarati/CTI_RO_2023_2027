# Manager Test Project

This project contains a Java implementation of a Manager class that works with Car and Person entities, along with comprehensive tests.

## Project Structure

```
Test_01/
├── pom.xml                          # Maven configuration
├── src/
│   ├── main/java/
│   │   ├── Car.java                 # Car entity class
│   │   ├── Person.java              # Person entity class
│   │   ├── Manager.java             # Main Manager class with stream operations
│   │   ├── NoSuchPersonException.java # Custom exception
│   │   └── CarsProvider.java        # Test data provider
│   └── test/java/
│       └── ManagerTest.java          # Comprehensive test suite
└── target/                          # Maven build output directory
```

## Classes

### Manager

The main class that contains methods for processing car data using Java Streams:

- `firstMethod()`: Returns a map of owners to their cars
- `secondMethod(int year)`: Returns distinct first names of owners of cars with faceLifts in specified year
- `thirdMethod()`: Returns full name of owner of newest black car
- `forthMethod(String brand)`: Returns average age of owners of cars with specified brand
- `fifthMethod(int year)`: Returns count of cars created after specified year and sets faceLifted flag
- `sixthMethod(String brand, String color)`: Returns owner of oldest car for specified brand and color
- `seventhMethod()`: Returns cars grouped by color

### Supporting Classes

- **Car**: Represents a car with brand, color, year, faceLifted flag, and owner
- **Person**: Represents a person with firstName, lastName, and age
- **NoSuchPersonException**: Custom exception for cases where a person is not found
- **CarsProvider**: Provides test data for the test suite

## Running Tests

To run the tests, use Maven:

```bash
mvn test
```

To compile the project:

```bash
mvn compile
```

## Requirements

- Java 17+
- Maven 3.6+
- JUnit 4.13.2
