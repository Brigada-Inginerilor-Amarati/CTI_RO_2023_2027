# Interfaces in C#

## Description

Interfaces define a contract that classes or structs must implement. They contain declarations for methods, properties, events, and indexers without implementation (prior to C# 8.0). Interfaces enable polymorphism and support multiple inheritance.

### Key Features:
- **Contract Definition**: Specify what members a type must implement
- **Multiple Inheritance**: A class can implement multiple interfaces
- **Polymorphism**: Different types can be treated through a common interface
- **Loose Coupling**: Dependencies on abstractions rather than concrete types
- **Default Implementation**: C# 8.0+ allows default interface methods

### Naming Convention:
- Interface names typically start with 'I' (e.g., `IComparable`, `IEnumerable`)

## Code Examples

### Example 1: Basic Interface Definition

```csharp
using System;

interface IShape
{
    double CalculateArea();
    double CalculatePerimeter();
    void Display();
}

class Circle : IShape
{
    public double Radius { get; set; }

    public Circle(double radius)
    {
        Radius = radius;
    }

    public double CalculateArea()
    {
        return Math.PI * Radius * Radius;
    }

    public double CalculatePerimeter()
    {
        return 2 * Math.PI * Radius;
    }

    public void Display()
    {
        Console.WriteLine($"Circle - Radius: {Radius:F2}");
        Console.WriteLine($"  Area: {CalculateArea():F2}");
        Console.WriteLine($"  Perimeter: {CalculatePerimeter():F2}");
    }
}

class Rectangle : IShape
{
    public double Width { get; set; }
    public double Height { get; set; }

    public Rectangle(double width, double height)
    {
        Width = width;
        Height = height;
    }

    public double CalculateArea()
    {
        return Width * Height;
    }

    public double CalculatePerimeter()
    {
        return 2 * (Width + Height);
    }

    public void Display()
    {
        Console.WriteLine($"Rectangle - {Width:F2}x{Height:F2}");
        Console.WriteLine($"  Area: {CalculateArea():F2}");
        Console.WriteLine($"  Perimeter: {CalculatePerimeter():F2}");
    }
}

class Program
{
    static void Main()
    {
        IShape circle = new Circle(5);
        IShape rectangle = new Rectangle(4, 6);

        circle.Display();
        Console.WriteLine();
        rectangle.Display();
    }
}
```

**Output:**
```
Circle - Radius: 5.00
  Area: 78.54
  Perimeter: 31.42

Rectangle - 4.00x6.00
  Area: 24.00
  Perimeter: 20.00
```

### Example 2: Multiple Interface Implementation

```csharp
using System;

interface IMovable
{
    void Move(int x, int y);
}

interface IDrawable
{
    void Draw();
}

interface IResizable
{
    void Resize(double scale);
}

class GameObject : IMovable, IDrawable, IResizable
{
    public int X { get; set; }
    public int Y { get; set; }
    public double Size { get; set; }

    public GameObject(int x, int y, double size)
    {
        X = x;
        Y = y;
        Size = size;
    }

    public void Move(int x, int y)
    {
        X += x;
        Y += y;
        Console.WriteLine($"Moved to ({X}, {Y})");
    }

    public void Draw()
    {
        Console.WriteLine($"Drawing at ({X}, {Y}) with size {Size:F2}");
    }

    public void Resize(double scale)
    {
        Size *= scale;
        Console.WriteLine($"Resized to {Size:F2}");
    }
}

class Program
{
    static void Main()
    {
        GameObject obj = new GameObject(10, 20, 1.0);

        obj.Draw();
        obj.Move(5, -3);
        obj.Resize(1.5);
        obj.Draw();
    }
}
```

**Output:**
```
Drawing at (10, 20) with size 1.00
Moved to (15, 17)
Resized to 1.50
Drawing at (15, 17) with size 1.50
```

### Example 3: Interface Properties

```csharp
using System;

interface IEmployee
{
    string Name { get; set; }
    int Id { get; }
    decimal Salary { get; set; }

    void DisplayInfo();
}

class Employee : IEmployee
{
    public string Name { get; set; }
    public int Id { get; }
    public decimal Salary { get; set; }

    public Employee(int id, string name, decimal salary)
    {
        Id = id;
        Name = name;
        Salary = salary;
    }

    public void DisplayInfo()
    {
        Console.WriteLine($"ID: {Id}");
        Console.WriteLine($"Name: {Name}");
        Console.WriteLine($"Salary: ${Salary:N2}");
    }
}

class Program
{
    static void Main()
    {
        IEmployee emp = new Employee(101, "Alice Johnson", 75000m);
        emp.DisplayInfo();

        Console.WriteLine("\nAfter raise:");
        emp.Salary *= 1.1m;
        emp.DisplayInfo();
    }
}
```

**Output:**
```
ID: 101
Name: Alice Johnson
Salary: $75,000.00

After raise:
ID: 101
Name: Alice Johnson
Salary: $82,500.00
```

### Example 4: Interface Inheritance

```csharp
using System;

interface IAnimal
{
    string Name { get; set; }
    void MakeSound();
}

interface IMammal : IAnimal
{
    void Feed();
}

interface IPet : IAnimal
{
    string Owner { get; set; }
    void Play();
}

class Dog : IMammal, IPet
{
    public string Name { get; set; }
    public string Owner { get; set; }

    public Dog(string name, string owner)
    {
        Name = name;
        Owner = owner;
    }

    public void MakeSound()
    {
        Console.WriteLine($"{Name} barks: Woof! Woof!");
    }

    public void Feed()
    {
        Console.WriteLine($"Feeding {Name} with dog food");
    }

    public void Play()
    {
        Console.WriteLine($"{Owner} is playing fetch with {Name}");
    }
}

class Program
{
    static void Main()
    {
        Dog dog = new Dog("Buddy", "John");

        dog.MakeSound();
        dog.Feed();
        dog.Play();
    }
}
```

**Output:**
```
Buddy barks: Woof! Woof!
Feeding Buddy with dog food
John is playing fetch with Buddy
```

### Example 5: Explicit Interface Implementation

```csharp
using System;

interface IFirst
{
    void Display();
}

interface ISecond
{
    void Display();
}

class MyClass : IFirst, ISecond
{
    // Explicit implementation for IFirst
    void IFirst.Display()
    {
        Console.WriteLine("IFirst.Display() implementation");
    }

    // Explicit implementation for ISecond
    void ISecond.Display()
    {
        Console.WriteLine("ISecond.Display() implementation");
    }

    // Public method
    public void Display()
    {
        Console.WriteLine("MyClass.Display() implementation");
    }
}

class Program
{
    static void Main()
    {
        MyClass obj = new MyClass();

        // Calls public method
        obj.Display();

        // Calls IFirst implementation
        IFirst first = obj;
        first.Display();

        // Calls ISecond implementation
        ISecond second = obj;
        second.Display();
    }
}
```

**Output:**
```
MyClass.Display() implementation
IFirst.Display() implementation
ISecond.Display() implementation
```

### Example 6: Default Interface Methods (C# 8.0+)

```csharp
using System;

interface ILogger
{
    void Log(string message);

    // Default implementation
    void LogError(string message)
    {
        Console.WriteLine($"[ERROR] {message}");
    }

    void LogWarning(string message)
    {
        Console.WriteLine($"[WARNING] {message}");
    }
}

class ConsoleLogger : ILogger
{
    public void Log(string message)
    {
        Console.WriteLine($"[INFO] {message}");
    }

    // Can override default implementation
    public void LogError(string message)
    {
        Console.ForegroundColor = ConsoleColor.Red;
        Console.WriteLine($"[CUSTOM ERROR] {message}");
        Console.ResetColor();
    }
}

class Program
{
    static void Main()
    {
        ILogger logger = new ConsoleLogger();

        logger.Log("Application started");
        logger.LogWarning("Low memory");
        logger.LogError("Connection failed");
    }
}
```

**Output:**
```
[INFO] Application started
[WARNING] Low memory
[CUSTOM ERROR] Connection failed
```
(Note: The error message would appear in red in the console)

### Example 7: Polymorphism with Interfaces

```csharp
using System;
using System.Collections.Generic;

interface IPaymentMethod
{
    string Name { get; }
    void ProcessPayment(decimal amount);
}

class CreditCard : IPaymentMethod
{
    public string Name => "Credit Card";
    public string CardNumber { get; set; }

    public CreditCard(string cardNumber)
    {
        CardNumber = cardNumber;
    }

    public void ProcessPayment(decimal amount)
    {
        Console.WriteLine($"Processing ${amount:F2} via {Name} (****{CardNumber.Substring(CardNumber.Length - 4)})");
    }
}

class PayPal : IPaymentMethod
{
    public string Name => "PayPal";
    public string Email { get; set; }

    public PayPal(string email)
    {
        Email = email;
    }

    public void ProcessPayment(decimal amount)
    {
        Console.WriteLine($"Processing ${amount:F2} via {Name} ({Email})");
    }
}

class Cash : IPaymentMethod
{
    public string Name => "Cash";

    public void ProcessPayment(decimal amount)
    {
        Console.WriteLine($"Processing ${amount:F2} via {Name}");
    }
}

class Program
{
    static void Main()
    {
        List<IPaymentMethod> payments = new List<IPaymentMethod>
        {
            new CreditCard("1234567890123456"),
            new PayPal("user@example.com"),
            new Cash()
        };

        decimal amount = 99.99m;

        foreach (IPaymentMethod payment in payments)
        {
            payment.ProcessPayment(amount);
        }
    }
}
```

**Output:**
```
Processing $99.99 via Credit Card (****3456)
Processing $99.99 via PayPal (user@example.com)
Processing $99.99 via Cash
```

### Example 8: Interface with Indexers

```csharp
using System;

interface IContainer<T>
{
    T this[int index] { get; set; }
    int Count { get; }
    void Add(T item);
}

class SimpleContainer<T> : IContainer<T>
{
    private T[] items = new T[10];
    private int count = 0;

    public T this[int index]
    {
        get
        {
            if (index < 0 || index >= count)
                throw new IndexOutOfRangeException();
            return items[index];
        }
        set
        {
            if (index < 0 || index >= count)
                throw new IndexOutOfRangeException();
            items[index] = value;
        }
    }

    public int Count => count;

    public void Add(T item)
    {
        if (count < items.Length)
        {
            items[count++] = item;
        }
    }
}

class Program
{
    static void Main()
    {
        IContainer<string> container = new SimpleContainer<string>();

        container.Add("Apple");
        container.Add("Banana");
        container.Add("Cherry");

        Console.WriteLine($"Container has {container.Count} items:");
        for (int i = 0; i < container.Count; i++)
        {
            Console.WriteLine($"  [{i}] = {container[i]}");
        }

        container[1] = "Blueberry";
        Console.WriteLine($"\nAfter modification: [{1}] = {container[1]}");
    }
}
```

**Output:**
```
Container has 3 items:
  [0] = Apple
  [1] = Banana
  [2] = Cherry

After modification: [1] = Blueberry
```

## Key Points

- Interfaces define contracts without implementation (except default methods in C# 8.0+)
- A class can implement multiple interfaces (multiple inheritance)
- Interfaces enable polymorphism and loose coupling
- Interface members are public by default
- Explicit interface implementation resolves naming conflicts
- Interfaces can inherit from other interfaces
- Cannot instantiate interfaces directly
- Interfaces can contain methods, properties, events, and indexers
- Use interfaces to depend on abstractions, not concrete types
- Naming convention: prefix with 'I' (e.g., `IComparable`)
