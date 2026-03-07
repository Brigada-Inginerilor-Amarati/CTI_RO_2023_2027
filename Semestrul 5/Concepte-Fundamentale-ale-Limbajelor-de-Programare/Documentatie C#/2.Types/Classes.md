# Classes in C#

## Description

Classes are reference types that define the blueprint for objects. They encapsulate data (fields and properties) and behavior (methods) into a single unit. Classes support object-oriented programming principles like inheritance, polymorphism, and encapsulation.

### Key Features:
- **Encapsulation**: Bundle data and methods together
- **Inheritance**: Derive from other classes
- **Polymorphism**: Override methods and use virtual functions
- **Access Modifiers**: Control visibility (public, private, protected, internal)
- **Constructors**: Initialize objects
- **Properties**: Provide controlled access to fields

## Code Examples

### Example 1: Basic Class Definition

```csharp
using System;

class Person
{
    // Fields
    private string name;
    private int age;

    // Constructor
    public Person(string name, int age)
    {
        this.name = name;
        this.age = age;
    }

    // Method
    public void Introduce()
    {
        Console.WriteLine($"Hi, I'm {name} and I'm {age} years old.");
    }
}

class Program
{
    static void Main()
    {
        Person person = new Person("Alice", 30);
        person.Introduce();
    }
}
```

**Output:**
```
Hi, I'm Alice and I'm 30 years old.
```

### Example 2: Properties and Auto-Properties

```csharp
using System;

class BankAccount
{
    // Auto-implemented properties
    public string AccountNumber { get; set; }
    public string Owner { get; set; }

    // Property with backing field
    private decimal balance;
    public decimal Balance
    {
        get { return balance; }
        private set
        {
            if (value >= 0)
                balance = value;
        }
    }

    public BankAccount(string accountNumber, string owner, decimal initialBalance)
    {
        AccountNumber = accountNumber;
        Owner = owner;
        Balance = initialBalance;
    }

    public void Deposit(decimal amount)
    {
        Balance += amount;
        Console.WriteLine($"Deposited ${amount}. New balance: ${Balance}");
    }

    public void Withdraw(decimal amount)
    {
        if (amount <= Balance)
        {
            Balance -= amount;
            Console.WriteLine($"Withdrew ${amount}. New balance: ${Balance}");
        }
        else
        {
            Console.WriteLine("Insufficient funds!");
        }
    }
}

class Program
{
    static void Main()
    {
        BankAccount account = new BankAccount("123456", "John Doe", 1000m);
        Console.WriteLine($"Account: {account.AccountNumber}, Owner: {account.Owner}");
        account.Deposit(500m);
        account.Withdraw(200m);
        Console.WriteLine($"Final Balance: ${account.Balance}");
    }
}
```

**Output:**
```
Account: 123456, Owner: John Doe
Deposited $500. New balance: $1500
Withdrew $200. New balance: $1300
Final Balance: $1300
```

### Example 3: Inheritance

```csharp
using System;

// Base class
class Animal
{
    public string Name { get; set; }

    public Animal(string name)
    {
        Name = name;
    }

    public virtual void MakeSound()
    {
        Console.WriteLine($"{Name} makes a sound");
    }
}

// Derived classes
class Dog : Animal
{
    public Dog(string name) : base(name) { }

    public override void MakeSound()
    {
        Console.WriteLine($"{Name} barks: Woof! Woof!");
    }
}

class Cat : Animal
{
    public Cat(string name) : base(name) { }

    public override void MakeSound()
    {
        Console.WriteLine($"{Name} meows: Meow! Meow!");
    }
}

class Program
{
    static void Main()
    {
        Animal animal = new Animal("Generic Animal");
        Dog dog = new Dog("Buddy");
        Cat cat = new Cat("Whiskers");

        animal.MakeSound();
        dog.MakeSound();
        cat.MakeSound();

        // Polymorphism
        Animal polymorphicDog = new Dog("Max");
        polymorphicDog.MakeSound();
    }
}
```

**Output:**
```
Generic Animal makes a sound
Buddy barks: Woof! Woof!
Whiskers meows: Meow! Meow!
Max barks: Woof! Woof!
```

### Example 4: Static Members

```csharp
using System;

class Counter
{
    // Static field
    private static int count = 0;

    // Instance field
    public int InstanceNumber { get; private set; }

    // Constructor
    public Counter()
    {
        count++;
        InstanceNumber = count;
    }

    // Static method
    public static int GetTotalCount()
    {
        return count;
    }

    // Instance method
    public void Display()
    {
        Console.WriteLine($"Instance #{InstanceNumber}");
    }
}

class Program
{
    static void Main()
    {
        Console.WriteLine($"Initial count: {Counter.GetTotalCount()}");

        Counter c1 = new Counter();
        Counter c2 = new Counter();
        Counter c3 = new Counter();

        c1.Display();
        c2.Display();
        c3.Display();

        Console.WriteLine($"Total instances created: {Counter.GetTotalCount()}");
    }
}
```

**Output:**
```
Initial count: 0
Instance #1
Instance #2
Instance #3
Total instances created: 3
```

### Example 5: Abstract Classes

```csharp
using System;

// Abstract class
abstract class Shape
{
    public string Name { get; set; }

    public Shape(string name)
    {
        Name = name;
    }

    // Abstract method
    public abstract double CalculateArea();

    // Concrete method
    public void Display()
    {
        Console.WriteLine($"{Name} - Area: {CalculateArea():F2}");
    }
}

class Circle : Shape
{
    public double Radius { get; set; }

    public Circle(double radius) : base("Circle")
    {
        Radius = radius;
    }

    public override double CalculateArea()
    {
        return Math.PI * Radius * Radius;
    }
}

class Rectangle : Shape
{
    public double Width { get; set; }
    public double Height { get; set; }

    public Rectangle(double width, double height) : base("Rectangle")
    {
        Width = width;
        Height = height;
    }

    public override double CalculateArea()
    {
        return Width * Height;
    }
}

class Program
{
    static void Main()
    {
        Shape circle = new Circle(5);
        Shape rectangle = new Rectangle(4, 6);

        circle.Display();
        rectangle.Display();
    }
}
```

**Output:**
```
Circle - Area: 78.54
Rectangle - Area: 24.00
```

### Example 6: Sealed Classes and Methods

```csharp
using System;

class BaseClass
{
    public virtual void Method()
    {
        Console.WriteLine("BaseClass Method");
    }
}

class DerivedClass : BaseClass
{
    public sealed override void Method()
    {
        Console.WriteLine("DerivedClass Method (sealed)");
    }
}

// Cannot override Method() because it's sealed
// class FurtherDerived : DerivedClass
// {
//     public override void Method() { } // ERROR!
// }

// Sealed class - cannot be inherited
sealed class FinalClass
{
    public void Display()
    {
        Console.WriteLine("This is a sealed class");
    }
}

// class CannotInherit : FinalClass { } // ERROR!

class Program
{
    static void Main()
    {
        DerivedClass derived = new DerivedClass();
        derived.Method();

        FinalClass final = new FinalClass();
        final.Display();
    }
}
```

**Output:**
```
DerivedClass Method (sealed)
This is a sealed class
```

## Key Points

- Classes are reference types stored on the heap
- Support inheritance (single inheritance for classes)
- Constructors initialize objects; can be overloaded
- Properties provide controlled access to fields
- Virtual methods can be overridden in derived classes
- Abstract classes cannot be instantiated
- Sealed classes cannot be inherited
- Static members belong to the class, not instances
- Access modifiers control encapsulation
