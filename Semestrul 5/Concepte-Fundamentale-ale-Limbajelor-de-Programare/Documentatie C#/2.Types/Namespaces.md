# Namespaces in C#

## Description

Namespaces are used to organize code and prevent naming conflicts. They provide a way to group related classes, interfaces, structs, enums, and delegates into logical units.

### Key Features:
- **Organization**: Group related types together
- **Name Resolution**: Prevent naming conflicts between types
- **Hierarchical Structure**: Can be nested for better organization
- **Using Directives**: Import namespaces to simplify code

## Code Examples

### Example 1: Basic Namespace Declaration

```csharp
using System;

// Define a namespace
namespace MyCompany.ProjectA
{
    public class Product
    {
        public string Name { get; set; }
        public decimal Price { get; set; }

        public void Display()
        {
            Console.WriteLine($"Product: {Name}, Price: ${Price}");
        }
    }
}

// Using the namespace
class Program
{
    static void Main()
    {
        MyCompany.ProjectA.Product product = new MyCompany.ProjectA.Product
        {
            Name = "Laptop",
            Price = 999.99m
        };

        product.Display();
    }
}
```

**Output:**
```
Product: Laptop, Price: $999.99
```

### Example 2: Using Directive

```csharp
using System;
using MyCompany.ProjectA;  // Import namespace

namespace MyCompany.ProjectA
{
    public class Customer
    {
        public string Name { get; set; }
        public int Id { get; set; }
    }
}

class Program
{
    static void Main()
    {
        // No need for fully qualified name
        Customer customer = new Customer
        {
            Id = 1,
            Name = "John Doe"
        };

        Console.WriteLine($"Customer ID: {customer.Id}, Name: {customer.Name}");
    }
}
```

**Output:**
```
Customer ID: 1, Name: John Doe
```

### Example 3: Nested Namespaces

```csharp
using System;
using MyCompany.ProjectA.Models;
using MyCompany.ProjectA.Services;

namespace MyCompany.ProjectA.Models
{
    public class Order
    {
        public int OrderId { get; set; }
        public string Product { get; set; }
    }
}

namespace MyCompany.ProjectA.Services
{
    public class OrderService
    {
        public void ProcessOrder(Order order)
        {
            Console.WriteLine($"Processing Order #{order.OrderId}: {order.Product}");
        }
    }
}

class Program
{
    static void Main()
    {
        Order order = new Order
        {
            OrderId = 101,
            Product = "Keyboard"
        };

        OrderService service = new OrderService();
        service.ProcessOrder(order);
    }
}
```

**Output:**
```
Processing Order #101: Keyboard
```

### Example 4: Namespace Alias

```csharp
using System;
using Proj = MyCompany.ProjectA;  // Namespace alias

namespace MyCompany.ProjectA
{
    public class Employee
    {
        public string Name { get; set; }
        public string Department { get; set; }

        public void ShowInfo()
        {
            Console.WriteLine($"{Name} works in {Department}");
        }
    }
}

class Program
{
    static void Main()
    {
        // Using alias
        Proj.Employee emp = new Proj.Employee
        {
            Name = "Alice Smith",
            Department = "Engineering"
        };

        emp.ShowInfo();
    }
}
```

**Output:**
```
Alice Smith works in Engineering
```

### Example 5: Resolving Name Conflicts

```csharp
using System;

namespace CompanyA
{
    public class Logger
    {
        public void Log(string message)
        {
            Console.WriteLine($"[CompanyA Logger] {message}");
        }
    }
}

namespace CompanyB
{
    public class Logger
    {
        public void Log(string message)
        {
            Console.WriteLine($"[CompanyB Logger] {message}");
        }
    }
}

class Program
{
    static void Main()
    {
        // Fully qualified names to avoid conflict
        CompanyA.Logger loggerA = new CompanyA.Logger();
        CompanyB.Logger loggerB = new CompanyB.Logger();

        loggerA.Log("Testing from Company A");
        loggerB.Log("Testing from Company B");
    }
}
```

**Output:**
```
[CompanyA Logger] Testing from Company A
[CompanyB Logger] Testing from Company B
```

### Example 6: Global Namespace

```csharp
using System;

// Class in global namespace
public class GlobalHelper
{
    public static void Help()
    {
        Console.WriteLine("Global helper method");
    }
}

namespace MyApp
{
    public class Helper
    {
        public static void Help()
        {
            Console.WriteLine("MyApp helper method");
        }
    }

    class Program
    {
        static void Main()
        {
            // Access global namespace explicitly
            global::GlobalHelper.Help();

            // Access local namespace
            Helper.Help();
        }
    }
}
```

**Output:**
```
Global helper method
MyApp helper method
```

## Key Points

- Namespaces organize code and prevent naming conflicts
- Use `using` directive to avoid writing fully qualified names
- Namespaces can be nested for hierarchical organization
- Aliases can simplify long namespace names
- The `global::` keyword accesses the global namespace
- Multiple namespaces can contain types with the same name
