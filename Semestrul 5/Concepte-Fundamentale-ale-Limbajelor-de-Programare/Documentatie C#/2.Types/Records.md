# Records in C#

## Description

Records (introduced in C# 9.0) are reference types designed for immutable data models with value-based equality. They provide a concise syntax for creating types that primarily hold data. Records are ideal for DTOs (Data Transfer Objects), immutable data structures, and value objects.

### Key Features:
- **Value-based Equality**: Two records are equal if their values are equal
- **Immutability**: Designed to be immutable (can use `with` expressions)
- **Concise Syntax**: Positional records with compact declaration
- **Built-in Features**: Automatic implementation of `Equals`, `GetHashCode`, `ToString`
- **Inheritance**: Supports inheritance (record classes)
- **Record Structs**: Value-type records (C# 10.0+)

### Record vs Class:
- Records: Value-based equality, immutability-focused
- Classes: Reference equality by default, mutable by default

## Code Examples

### Example 1: Basic Record Definition

```csharp
using System;

// Traditional record syntax
record Person
{
    public string FirstName { get; init; }
    public string LastName { get; init; }
    public int Age { get; init; }
}

class Program
{
    static void Main()
    {
        Person person = new Person
        {
            FirstName = "John",
            LastName = "Doe",
            Age = 30
        };

        Console.WriteLine(person);
        Console.WriteLine($"Name: {person.FirstName} {person.LastName}, Age: {person.Age}");
    }
}
```

**Output:**
```
Person { FirstName = John, LastName = Doe, Age = 30 }
Name: John Doe, Age: 30
```

### Example 2: Positional Records

```csharp
using System;

// Positional record - compact syntax
record Point(int X, int Y);

record Student(string Name, int Id, double GPA);

class Program
{
    static void Main()
    {
        Point p1 = new Point(10, 20);
        Console.WriteLine(p1);
        Console.WriteLine($"X: {p1.X}, Y: {p1.Y}");

        Student student = new Student("Alice Smith", 12345, 3.85);
        Console.WriteLine(student);
    }
}
```

**Output:**
```
Point { X = 10, Y = 20 }
X: 10, Y: 20
Student { Name = Alice Smith, Id = 12345, GPA = 3.85 }
```

### Example 3: Value-based Equality

```csharp
using System;

record Person(string Name, int Age);

class PersonClass
{
    public string Name { get; set; }
    public int Age { get; set; }
}

class Program
{
    static void Main()
    {
        // Records - value-based equality
        Person p1 = new Person("John", 30);
        Person p2 = new Person("John", 30);

        Console.WriteLine("Records:");
        Console.WriteLine($"p1 == p2: {p1 == p2}");
        Console.WriteLine($"p1.Equals(p2): {p1.Equals(p2)}");

        // Classes - reference equality
        PersonClass c1 = new PersonClass { Name = "John", Age = 30 };
        PersonClass c2 = new PersonClass { Name = "John", Age = 30 };

        Console.WriteLine("\nClasses:");
        Console.WriteLine($"c1 == c2: {c1 == c2}");
        Console.WriteLine($"c1.Equals(c2): {c1.Equals(c2)}");
    }
}
```

**Output:**
```
Records:
p1 == p2: True
p1.Equals(p2): True

Classes:
c1 == c2: False
c1.Equals(c2): False
```

### Example 4: With Expressions (Non-destructive Mutation)

```csharp
using System;

record Person(string FirstName, string LastName, int Age);

class Program
{
    static void Main()
    {
        Person person1 = new Person("John", "Doe", 30);
        Console.WriteLine($"Original: {person1}");

        // Create a copy with modified Age
        Person person2 = person1 with { Age = 31 };
        Console.WriteLine($"Modified Age: {person2}");

        // Create a copy with modified FirstName
        Person person3 = person1 with { FirstName = "Jane" };
        Console.WriteLine($"Modified FirstName: {person3}");

        // Multiple modifications
        Person person4 = person1 with { FirstName = "Bob", Age = 25 };
        Console.WriteLine($"Multiple changes: {person4}");

        // Original is unchanged
        Console.WriteLine($"Original unchanged: {person1}");
    }
}
```

**Output:**
```
Original: Person { FirstName = John, LastName = Doe, Age = 30 }
Modified Age: Person { FirstName = John, LastName = Doe, Age = 31 }
Modified FirstName: Person { FirstName = Jane, LastName = Doe, Age = 30 }
Multiple changes: Person { FirstName = Bob, LastName = Doe, Age = 25 }
Original unchanged: Person { FirstName = John, LastName = Doe, Age = 30 }
```

### Example 5: Record Inheritance

```csharp
using System;

record Person(string Name, int Age);

record Employee(string Name, int Age, string Department, decimal Salary) : Person(Name, Age);

record Manager(string Name, int Age, string Department, decimal Salary, int TeamSize)
    : Employee(Name, Age, Department, Salary);

class Program
{
    static void Main()
    {
        Person person = new Person("John Doe", 30);
        Employee employee = new Employee("Jane Smith", 28, "Engineering", 75000m);
        Manager manager = new Manager("Bob Johnson", 45, "IT", 95000m, 10);

        Console.WriteLine(person);
        Console.WriteLine(employee);
        Console.WriteLine(manager);

        // Polymorphism works
        Person p = employee;
        Console.WriteLine($"\nPolymorphic: {p}");
    }
}
```

**Output:**
```
Person { Name = John Doe, Age = 30 }
Employee { Name = Jane Smith, Age = 28, Department = Engineering, Salary = 75000 }
Manager { Name = Bob Johnson, Age = 45, Department = IT, Salary = 95000, TeamSize = 10 }

Polymorphic: Employee { Name = Jane Smith, Age = 28, Department = Engineering, Salary = 75000 }
```

### Example 6: Record Structs

```csharp
using System;

// Record struct (value type)
record struct PointStruct(int X, int Y);

// Regular record (reference type)
record PointClass(int X, int Y);

class Program
{
    static void ModifyRecordStruct(PointStruct p)
    {
        p = new PointStruct(100, 100);
        Console.WriteLine($"Inside method: {p}");
    }

    static void ModifyRecordClass(PointClass p)
    {
        p = new PointClass(100, 100);
        Console.WriteLine($"Inside method: {p}");
    }

    static void Main()
    {
        // Record struct (value type)
        PointStruct ps = new PointStruct(10, 20);
        Console.WriteLine($"Before: {ps}");
        ModifyRecordStruct(ps);
        Console.WriteLine($"After: {ps} (unchanged - value type)\n");

        // Record class (reference type)
        PointClass pc = new PointClass(10, 20);
        Console.WriteLine($"Before: {pc}");
        ModifyRecordClass(pc);
        Console.WriteLine($"After: {pc} (unchanged - new instance)");
    }
}
```

**Output:**
```
Before: PointStruct { X = 10, Y = 20 }
Inside method: PointStruct { X = 100, Y = 100 }
After: PointStruct { X = 10, Y = 20 } (unchanged - value type)

Before: PointClass { X = 10, Y = 20 }
Inside method: PointClass { X = 100, Y = 100 }
After: PointClass { X = 10, Y = 20 } (unchanged - new instance)
```

### Example 7: Records with Methods

```csharp
using System;

record Rectangle(double Width, double Height)
{
    public double Area() => Width * Height;

    public double Perimeter() => 2 * (Width + Height);

    public bool IsSquare() => Width == Height;

    public void Display()
    {
        Console.WriteLine($"Rectangle: {Width}x{Height}");
        Console.WriteLine($"  Area: {Area():F2}");
        Console.WriteLine($"  Perimeter: {Perimeter():F2}");
        Console.WriteLine($"  Is Square: {IsSquare()}");
    }
}

class Program
{
    static void Main()
    {
        Rectangle rect1 = new Rectangle(5, 10);
        rect1.Display();

        Console.WriteLine();

        Rectangle rect2 = new Rectangle(7, 7);
        rect2.Display();
    }
}
```

**Output:**
```
Rectangle: 5x10
  Area: 50.00
  Perimeter: 30.00
  Is Square: False

Rectangle: 7x7
  Area: 49.00
  Perimeter: 28.00
  Is Square: True
```

### Example 8: Deconstruction

```csharp
using System;

record Person(string FirstName, string LastName, int Age);

record Point(int X, int Y);

class Program
{
    static void Main()
    {
        Person person = new Person("John", "Doe", 30);

        // Deconstruct record
        var (firstName, lastName, age) = person;
        Console.WriteLine($"Deconstructed: {firstName} {lastName}, {age} years old");

        Point point = new Point(15, 25);
        var (x, y) = point;
        Console.WriteLine($"Point coordinates: X={x}, Y={y}");
    }
}
```

**Output:**
```
Deconstructed: John Doe, 30 years old
Point coordinates: X=15, Y=25
```

## Key Points

- Records provide value-based equality by default
- Use `with` expressions for non-destructive mutations
- Positional syntax creates concise, immutable types
- Records automatically implement `Equals`, `GetHashCode`, `ToString`
- Record structs are value types; regular records are reference types
- Support inheritance (only between records)
- Ideal for DTOs, immutable data models, and value objects
- `init` accessors allow initialization but prevent later modification
- Records can have methods, properties, and custom behavior
- Deconstruction is automatically supported for positional records
