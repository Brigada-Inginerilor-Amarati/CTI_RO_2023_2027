# Proiectarea Detaliata a Sistemelor Software (PDSS)

This repository serves as the central hub for the "Detailed Design of Software Systems" course. It contains laboratory exercises, student projects, and course materials.

## Repository Structure

- **`Laborator/`**: Contains laboratory work organized by student (Paul, Daria, Maya) and common PDF resources.
- **`Curs/`**: Lecture notes and course PDFs.

## Topics Covered

- **Clean Code Principles**: Emphasizing readable, maintainable, and robust code.
- **Java Streams API**: Functional programming concepts in Java for efficient data processing.
- **Software Design Patterns**: Practical application of design patterns in software architecture.

## Getting Started

### Prerequisites

- **Java 17**: Required for all projects.
- **Maven**: Build automation tool.

### Building and Running

This project uses Maven for build management. You can use the CLI or your preferred IDE (IntelliJ IDEA, Eclipse, VS Code).

#### CLI Commands

Navigate to a specific lab directory (e.g., `Laborator/Paul/streams-exercise`) and run:

```bash
# Build the project
mvn clean install

# Run tests
mvn test

# Run a specific test class
mvn test -Dtest=StudentRepositoryTest
```

#### IDE Setup

Open the root `Laborator` folder or specific student folders as a Maven project in your IDE. Ensure your project SDK is set to Java 17.

## Resources

- Course materials and references are available in the `Laborator/PDF` and `Curs` directories.
- See `CLAUDE.md` for AI assistant guidelines specific to this repository.
