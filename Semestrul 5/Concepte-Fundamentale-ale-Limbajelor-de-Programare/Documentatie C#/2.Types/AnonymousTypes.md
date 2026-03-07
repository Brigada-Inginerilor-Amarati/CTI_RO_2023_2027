# Anonymous Types in C#

## Description

Anonymous types provide a convenient way to encapsulate a set of read-only properties into a single object without having to explicitly define a type first. They are commonly used in LINQ queries to create temporary objects that hold a subset of data from a larger dataset.

### Key Features:
- **No Explicit Definition**: Compiler generates the type automatically
- **Read-only Properties**: Properties are immutable (get-only)
- **Type Inference**: Must use `var` keyword for declaration
- **Structural Equality**: Two anonymous types are equal if they have the same property names and types
- **Limited Scope**: Cannot return anonymous types from methods (without using dynamic or object)
- **Object Initializer Syntax**: Created using `new { }` syntax

### Common Use Cases:
- LINQ query projections
- Temporary data containers
- Grouping related data without creating formal types

## Code Examples

### Example 1: Basic Anonymous Type

```csharp
using System;

class Program
{
    static void Main()
    {
        // Create an anonymous type
        var person = new { Name = "Alice", Age = 30, City = "New York" };

        Console.WriteLine($"Name: {person.Name}");
        Console.WriteLine($"Age: {person.Age}");
        Console.WriteLine($"City: {person.City}");
        Console.WriteLine($"Type: {person.GetType().Name}");

        // Properties are read-only
        // person.Age = 31; // ERROR: Property is read-only
    }
}
```

**Output:**
```
Name: Alice
Age: 30
City: New York
Type: <>f__AnonymousType0`3
```

### Example 2: Multiple Anonymous Objects

```csharp
using System;

class Program
{
    static void Main()
    {
        var product1 = new { Id = 1, Name = "Laptop", Price = 999.99 };
        var product2 = new { Id = 2, Name = "Mouse", Price = 29.99 };
        var product3 = new { Id = 3, Name = "Keyboard", Price = 79.99 };

        Console.WriteLine("Products:");
        Console.WriteLine($"  {product1.Id}. {product1.Name} - ${product1.Price}");
        Console.WriteLine($"  {product2.Id}. {product2.Name} - ${product2.Price}");
        Console.WriteLine($"  {product3.Id}. {product3.Name} - ${product3.Price}");

        // Check if same type
        Console.WriteLine($"\nSame type: {product1.GetType() == product2.GetType()}");
    }
}
```

**Output:**
```
Products:
  1. Laptop - $999.99
  2. Mouse - $29.99
  3. Keyboard - $79.99

Same type: True
```

### Example 3: Arrays of Anonymous Types

```csharp
using System;

class Program
{
    static void Main()
    {
        var students = new[]
        {
            new { Name = "Alice", Grade = 'A', Score = 95 },
            new { Name = "Bob", Grade = 'B', Score = 85 },
            new { Name = "Charlie", Grade = 'A', Score = 92 },
            new { Name = "David", Grade = 'C', Score = 75 }
        };

        Console.WriteLine("Student Records:");
        foreach (var student in students)
        {
            Console.WriteLine($"  {student.Name}: Grade {student.Grade} ({student.Score}%)");
        }

        Console.WriteLine($"\nTotal students: {students.Length}");
    }
}
```

**Output:**
```
Student Records:
  Alice: Grade A (95%)
  Bob: Grade B (85%)
  Charlie: Grade A (92%)
  David: Grade C (75%)

Total students: 4
```

### Example 4: Anonymous Types with LINQ

```csharp
using System;
using System.Linq;

class Student
{
    public string Name { get; set; }
    public int Age { get; set; }
    public string Major { get; set; }
    public double GPA { get; set; }
}

class Program
{
    static void Main()
    {
        var students = new[]
        {
            new Student { Name = "Alice", Age = 20, Major = "Computer Science", GPA = 3.8 },
            new Student { Name = "Bob", Age = 22, Major = "Mathematics", GPA = 3.5 },
            new Student { Name = "Charlie", Age = 21, Major = "Computer Science", GPA = 3.9 },
            new Student { Name = "David", Age = 23, Major = "Physics", GPA = 3.6 }
        };

        // Project to anonymous type
        var studentSummary = students.Select(s => new
        {
            s.Name,
            s.Major,
            Status = s.GPA >= 3.7 ? "Honors" : "Regular"
        });

        Console.WriteLine("Student Summary:");
        foreach (var s in studentSummary)
        {
            Console.WriteLine($"  {s.Name} ({s.Major}) - {s.Status}");
        }
    }
}
```

**Output:**
```
Student Summary:
  Alice (Computer Science) - Honors
  Bob (Mathematics) - Regular
  Charlie (Computer Science) - Honors
  David (Physics) - Regular
```

### Example 5: Grouping with Anonymous Types

```csharp
using System;
using System.Linq;

class Employee
{
    public string Name { get; set; }
    public string Department { get; set; }
    public decimal Salary { get; set; }
}

class Program
{
    static void Main()
    {
        var employees = new[]
        {
            new Employee { Name = "Alice", Department = "IT", Salary = 75000 },
            new Employee { Name = "Bob", Department = "HR", Salary = 60000 },
            new Employee { Name = "Charlie", Department = "IT", Salary = 80000 },
            new Employee { Name = "David", Department = "HR", Salary = 65000 },
            new Employee { Name = "Eve", Department = "IT", Salary = 70000 }
        };

        // Group by department and calculate stats
        var departmentStats = employees
            .GroupBy(e => e.Department)
            .Select(g => new
            {
                Department = g.Key,
                EmployeeCount = g.Count(),
                AverageSalary = g.Average(e => e.Salary),
                TotalSalary = g.Sum(e => e.Salary)
            });

        Console.WriteLine("Department Statistics:");
        foreach (var dept in departmentStats)
        {
            Console.WriteLine($"\n{dept.Department}:");
            Console.WriteLine($"  Employees: {dept.EmployeeCount}");
            Console.WriteLine($"  Average Salary: ${dept.AverageSalary:N2}");
            Console.WriteLine($"  Total Salary: ${dept.TotalSalary:N2}");
        }
    }
}
```

**Output:**
```
Department Statistics:

IT:
  Employees: 3
  Average Salary: $75,000.00
  Total Salary: $225,000.00

HR:
  Employees: 2
  Average Salary: $62,500.00
  Total Salary: $125,000.00
```

### Example 6: Nested Anonymous Types

```csharp
using System;

class Program
{
    static void Main()
    {
        var order = new
        {
            OrderId = 12345,
            Customer = new
            {
                Name = "John Doe",
                Email = "john@example.com"
            },
            Items = new[]
            {
                new { Product = "Laptop", Quantity = 1, Price = 999.99 },
                new { Product = "Mouse", Quantity = 2, Price = 29.99 }
            },
            OrderDate = DateTime.Now
        };

        Console.WriteLine($"Order #{order.OrderId}");
        Console.WriteLine($"Date: {order.OrderDate:yyyy-MM-dd HH:mm}");
        Console.WriteLine($"\nCustomer:");
        Console.WriteLine($"  Name: {order.Customer.Name}");
        Console.WriteLine($"  Email: {order.Customer.Email}");

        Console.WriteLine($"\nItems:");
        decimal total = 0;
        foreach (var item in order.Items)
        {
            decimal itemTotal = item.Quantity * (decimal)item.Price;
            Console.WriteLine($"  {item.Product} x{item.Quantity} = ${itemTotal:F2}");
            total += itemTotal;
        }

        Console.WriteLine($"\nTotal: ${total:F2}");
    }
}
```

**Output:**
```
Order #12345
Date: 2025-10-07 14:30

Customer:
  Name: John Doe
  Email: john@example.com

Items:
  Laptop x1 = $999.99
  Mouse x2 = $59.98

Total: $1059.97
```

### Example 7: Anonymous Types with Property Inference

```csharp
using System;

class Program
{
    static void Main()
    {
        string Name = "Alice";
        int Age = 30;
        string City = "New York";

        // Property names inferred from variable names
        var person1 = new { Name, Age, City };

        Console.WriteLine("Person (inferred properties):");
        Console.WriteLine($"  Name: {person1.Name}");
        Console.WriteLine($"  Age: {person1.Age}");
        Console.WriteLine($"  City: {person1.City}");

        // Explicit property names
        var person2 = new { FirstName = Name, YearsOld = Age, Location = City };

        Console.WriteLine("\nPerson (explicit properties):");
        Console.WriteLine($"  FirstName: {person2.FirstName}");
        Console.WriteLine($"  YearsOld: {person2.YearsOld}");
        Console.WriteLine($"  Location: {person2.Location}");
    }
}
```

**Output:**
```
Person (inferred properties):
  Name: Alice
  Age: 30
  City: New York

Person (explicit properties):
  FirstName: Alice
  YearsOld: 30
  Location: New York
```

### Example 8: Equality of Anonymous Types

```csharp
using System;

class Program
{
    static void Main()
    {
        var person1 = new { Name = "Alice", Age = 30 };
        var person2 = new { Name = "Alice", Age = 30 };
        var person3 = new { Name = "Bob", Age = 30 };

        Console.WriteLine("Equality Testing:");
        Console.WriteLine($"person1 == person2: {person1.Equals(person2)}");
        Console.WriteLine($"person1 == person3: {person1.Equals(person3)}");

        Console.WriteLine($"\nperson1.GetHashCode(): {person1.GetHashCode()}");
        Console.WriteLine($"person2.GetHashCode(): {person2.GetHashCode()}");
        Console.WriteLine($"person3.GetHashCode(): {person3.GetHashCode()}");

        Console.WriteLine($"\nperson1.ToString(): {person1.ToString()}");
        Console.WriteLine($"person2.ToString(): {person2.ToString()}");
    }
}
```

**Output:**
```
Equality Testing:
person1 == person2: True
person1 == person3: False

person1.GetHashCode(): -1658835809
person2.GetHashCode(): -1658835809
person3.GetHashCode(): -1658835851

person1.ToString(): { Name = Alice, Age = 30 }
person2.ToString(): { Name = Alice, Age = 30 }
```

### Example 9: Using Anonymous Types for Data Transformation

```csharp
using System;
using System.Linq;

class Product
{
    public int Id { get; set; }
    public string Name { get; set; }
    public decimal Price { get; set; }
    public int Stock { get; set; }
}

class Program
{
    static void Main()
    {
        var products = new[]
        {
            new Product { Id = 1, Name = "Laptop", Price = 999.99m, Stock = 5 },
            new Product { Id = 2, Name = "Mouse", Price = 29.99m, Stock = 50 },
            new Product { Id = 3, Name = "Keyboard", Price = 79.99m, Stock = 0 },
            new Product { Id = 4, Name = "Monitor", Price = 299.99m, Stock = 10 }
        };

        // Transform to simplified view
        var productView = products.Select(p => new
        {
            p.Name,
            p.Price,
            Availability = p.Stock > 0 ? "In Stock" : "Out of Stock",
            Value = p.Price * p.Stock
        });

        Console.WriteLine("Product Inventory:");
        foreach (var p in productView)
        {
            Console.WriteLine($"{p.Name,-15} ${p.Price,7:F2}  {p.Availability,-12} Value: ${p.Value,8:F2}");
        }

        var totalValue = productView.Sum(p => p.Value);
        Console.WriteLine($"\nTotal Inventory Value: ${totalValue:F2}");
    }
}
```

**Output:**
```
Product Inventory:
Laptop           $999.99  In Stock     Value: $4999.95
Mouse             $29.99  In Stock     Value: $1499.50
Keyboard          $79.99  Out of Stock Value:     $0.00
Monitor          $299.99  In Stock     Value: $2999.90

Total Inventory Value: $9499.35
```

## Key Points

- Anonymous types are compiler-generated reference types
- Properties are read-only (immutable)
- Must use `var` keyword for declaration
- Created using object initializer syntax: `new { Property = value }`
- Commonly used in LINQ queries for projections
- Two anonymous objects are equal if properties and values match
- Cannot return anonymous types from methods without using `dynamic` or `object`
- Compiler generates `Equals`, `GetHashCode`, and `ToString` methods
- Property names can be inferred from variable names
- Useful for temporary data structures without formal type definitions
- Arrays of anonymous types require all elements to have the same structure
