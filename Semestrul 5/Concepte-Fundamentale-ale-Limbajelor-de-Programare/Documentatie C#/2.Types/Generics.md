# Generics in C#

## Description

Generics allow you to define type-safe classes, interfaces, methods, and delegates without committing to a specific data type. They provide code reusability, type safety, and better performance by eliminating boxing/unboxing and casting.

### Key Features:
- **Type Safety**: Compile-time type checking
- **Code Reusability**: Write once, use with multiple types
- **Performance**: No boxing/unboxing for value types
- **Constraints**: Restrict type parameters to specific types
- **Type Parameters**: Denoted by angle brackets `<T>` (T is conventional)

### Common Generic Collections:
- `List<T>`, `Dictionary<TKey, TValue>`, `Queue<T>`, `Stack<T>`, `HashSet<T>`

## Code Examples

### Example 1: Generic Class

```csharp
using System;

class Box<T>
{
    private T content;

    public void Pack(T item)
    {
        content = item;
        Console.WriteLine($"Packed: {content}");
    }

    public T Unpack()
    {
        Console.WriteLine($"Unpacked: {content}");
        return content;
    }

    public void Display()
    {
        Console.WriteLine($"Box contains: {content} (Type: {typeof(T).Name})");
    }
}

class Program
{
    static void Main()
    {
        // Box for integers
        Box<int> intBox = new Box<int>();
        intBox.Pack(42);
        intBox.Display();

        Console.WriteLine();

        // Box for strings
        Box<string> stringBox = new Box<string>();
        stringBox.Pack("Hello Generics");
        stringBox.Display();

        Console.WriteLine();

        // Box for doubles
        Box<double> doubleBox = new Box<double>();
        doubleBox.Pack(3.14);
        double value = doubleBox.Unpack();
    }
}
```

**Output:**
```
Packed: 42
Box contains: 42 (Type: Int32)

Packed: Hello Generics
Box contains: Hello Generics (Type: String)

Packed: 3.14
Unpacked: 3.14
```

### Example 2: Generic Methods

```csharp
using System;

class Utilities
{
    public static void Swap<T>(ref T a, ref T b)
    {
        Console.WriteLine($"Before swap: a={a}, b={b}");
        T temp = a;
        a = b;
        b = temp;
        Console.WriteLine($"After swap: a={a}, b={b}");
    }

    public static T Max<T>(T a, T b) where T : IComparable<T>
    {
        return a.CompareTo(b) > 0 ? a : b;
    }

    public static void PrintArray<T>(T[] array)
    {
        Console.Write("[");
        for (int i = 0; i < array.Length; i++)
        {
            Console.Write(array[i]);
            if (i < array.Length - 1)
                Console.Write(", ");
        }
        Console.WriteLine("]");
    }
}

class Program
{
    static void Main()
    {
        // Swap integers
        int x = 10, y = 20;
        Utilities.Swap(ref x, ref y);

        Console.WriteLine();

        // Swap strings
        string s1 = "Hello", s2 = "World";
        Utilities.Swap(ref s1, ref s2);

        Console.WriteLine();

        // Max method
        Console.WriteLine($"Max(15, 25) = {Utilities.Max(15, 25)}");
        Console.WriteLine($"Max('A', 'Z') = {Utilities.Max('A', 'Z')}");

        Console.WriteLine();

        // Print arrays
        int[] numbers = { 1, 2, 3, 4, 5 };
        string[] words = { "apple", "banana", "cherry" };

        Console.Write("Numbers: ");
        Utilities.PrintArray(numbers);
        Console.Write("Words: ");
        Utilities.PrintArray(words);
    }
}
```

**Output:**
```
Before swap: a=10, b=20
After swap: a=20, b=10

Before swap: a=Hello, b=World
After swap: a=World, b=Hello

Max(15, 25) = 25
Max('A', 'Z') = Z

Numbers: [1, 2, 3, 4, 5]
Words: [apple, banana, cherry]
```

### Example 3: Generic Constraints

```csharp
using System;

// Class constraint
class Repository<T> where T : class
{
    private T item;

    public void Store(T item)
    {
        this.item = item;
        Console.WriteLine($"Stored: {item}");
    }
}

// Struct constraint
class Calculator<T> where T : struct
{
    public T Add(T a, T b)
    {
        dynamic x = a;
        dynamic y = b;
        return x + y;
    }
}

// Interface constraint
interface IAnimal
{
    string Name { get; }
    void MakeSound();
}

class Dog : IAnimal
{
    public string Name { get; set; }
    public Dog(string name) { Name = name; }
    public void MakeSound() { Console.WriteLine($"{Name} says: Woof!"); }
}

class Cat : IAnimal
{
    public string Name { get; set; }
    public Cat(string name) { Name = name; }
    public void MakeSound() { Console.WriteLine($"{Name} says: Meow!"); }
}

class AnimalShelter<T> where T : IAnimal
{
    private T animal;

    public void AddAnimal(T animal)
    {
        this.animal = animal;
        Console.WriteLine($"Added {animal.Name} to shelter");
        animal.MakeSound();
    }
}

class Program
{
    static void Main()
    {
        // Class constraint
        Repository<string> stringRepo = new Repository<string>();
        stringRepo.Store("Hello");

        Console.WriteLine();

        // Struct constraint
        Calculator<int> intCalc = new Calculator<int>();
        Console.WriteLine($"5 + 10 = {intCalc.Add(5, 10)}");

        Console.WriteLine();

        // Interface constraint
        AnimalShelter<Dog> dogShelter = new AnimalShelter<Dog>();
        dogShelter.AddAnimal(new Dog("Buddy"));

        Console.WriteLine();

        AnimalShelter<Cat> catShelter = new AnimalShelter<Cat>();
        catShelter.AddAnimal(new Cat("Whiskers"));
    }
}
```

**Output:**
```
Stored: Hello

5 + 10 = 15

Added Buddy to shelter
Buddy says: Woof!

Added Whiskers to shelter
Whiskers says: Meow!
```

### Example 4: Generic Collections

```csharp
using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        // List<T>
        List<int> numbers = new List<int> { 1, 2, 3, 4, 5 };
        numbers.Add(6);
        Console.WriteLine("List: " + string.Join(", ", numbers));

        // Dictionary<TKey, TValue>
        Dictionary<string, int> ages = new Dictionary<string, int>
        {
            { "Alice", 30 },
            { "Bob", 25 },
            { "Charlie", 35 }
        };
        ages["David"] = 28;

        Console.WriteLine("\nDictionary:");
        foreach (var kvp in ages)
        {
            Console.WriteLine($"  {kvp.Key}: {kvp.Value}");
        }

        // Queue<T>
        Queue<string> queue = new Queue<string>();
        queue.Enqueue("First");
        queue.Enqueue("Second");
        queue.Enqueue("Third");

        Console.WriteLine("\nQueue:");
        while (queue.Count > 0)
        {
            Console.WriteLine($"  Dequeued: {queue.Dequeue()}");
        }

        // Stack<T>
        Stack<string> stack = new Stack<string>();
        stack.Push("Bottom");
        stack.Push("Middle");
        stack.Push("Top");

        Console.WriteLine("\nStack:");
        while (stack.Count > 0)
        {
            Console.WriteLine($"  Popped: {stack.Pop()}");
        }

        // HashSet<T>
        HashSet<int> set = new HashSet<int> { 1, 2, 3, 4, 5 };
        set.Add(3); // Duplicate, won't be added
        set.Add(6);

        Console.WriteLine("\nHashSet: " + string.Join(", ", set));
    }
}
```

**Output:**
```
List: 1, 2, 3, 4, 5, 6

Dictionary:
  Alice: 30
  Bob: 25
  Charlie: 35
  David: 28

Queue:
  Dequeued: First
  Dequeued: Second
  Dequeued: Third

Stack:
  Popped: Top
  Popped: Middle
  Popped: Bottom

HashSet: 1, 2, 3, 4, 5, 6
```

### Example 5: Multiple Type Parameters

```csharp
using System;

class Pair<TFirst, TSecond>
{
    public TFirst First { get; set; }
    public TSecond Second { get; set; }

    public Pair(TFirst first, TSecond second)
    {
        First = first;
        Second = second;
    }

    public void Display()
    {
        Console.WriteLine($"({First}, {Second})");
    }
}

class Converter<TInput, TOutput>
{
    private Func<TInput, TOutput> converter;

    public Converter(Func<TInput, TOutput> converter)
    {
        this.converter = converter;
    }

    public TOutput Convert(TInput input)
    {
        return converter(input);
    }
}

class Program
{
    static void Main()
    {
        // Pair with different types
        Pair<string, int> person = new Pair<string, int>("Alice", 30);
        Console.Write("Person: ");
        person.Display();

        Pair<int, int> coordinates = new Pair<int, int>(10, 20);
        Console.Write("Coordinates: ");
        coordinates.Display();

        Console.WriteLine();

        // Converter
        Converter<int, string> intToString = new Converter<int, string>(x => $"Number: {x}");
        Console.WriteLine(intToString.Convert(42));

        Converter<string, int> stringToInt = new Converter<string, int>(s => s.Length);
        Console.WriteLine($"Length of 'Hello': {stringToInt.Convert("Hello")}");
    }
}
```

**Output:**
```
Person: (Alice, 30)
Coordinates: (10, 20)

Number: 42
Length of 'Hello': 5
```

### Example 6: Generic Interfaces

```csharp
using System;

interface IRepository<T>
{
    void Add(T item);
    T Get(int id);
    void Display();
}

class Product
{
    public int Id { get; set; }
    public string Name { get; set; }
    public decimal Price { get; set; }

    public override string ToString()
    {
        return $"[{Id}] {Name} - ${Price:F2}";
    }
}

class ProductRepository : IRepository<Product>
{
    private Product[] products = new Product[10];
    private int count = 0;

    public void Add(Product item)
    {
        if (count < products.Length)
        {
            products[count++] = item;
            Console.WriteLine($"Added: {item}");
        }
    }

    public Product Get(int id)
    {
        for (int i = 0; i < count; i++)
        {
            if (products[i].Id == id)
                return products[i];
        }
        return null;
    }

    public void Display()
    {
        Console.WriteLine("\nProduct Repository:");
        for (int i = 0; i < count; i++)
        {
            Console.WriteLine($"  {products[i]}");
        }
    }
}

class Program
{
    static void Main()
    {
        IRepository<Product> repo = new ProductRepository();

        repo.Add(new Product { Id = 1, Name = "Laptop", Price = 999.99m });
        repo.Add(new Product { Id = 2, Name = "Mouse", Price = 29.99m });
        repo.Add(new Product { Id = 3, Name = "Keyboard", Price = 79.99m });

        repo.Display();

        Console.WriteLine("\nSearching for product with ID 2:");
        Product found = repo.Get(2);
        Console.WriteLine(found != null ? found.ToString() : "Not found");
    }
}
```

**Output:**
```
Added: [1] Laptop - $999.99
Added: [2] Mouse - $29.99
Added: [3] Keyboard - $79.99

Product Repository:
  [1] Laptop - $999.99
  [2] Mouse - $29.99
  [3] Keyboard - $79.99

Searching for product with ID 2:
[2] Mouse - $29.99
```

### Example 7: Covariance and Contravariance

```csharp
using System;
using System.Collections.Generic;

class Animal
{
    public string Name { get; set; }
    public Animal(string name) { Name = name; }
}

class Dog : Animal
{
    public Dog(string name) : base(name) { }
    public override string ToString() => $"Dog: {Name}";
}

class Cat : Animal
{
    public Cat(string name) : base(name) { }
    public override string ToString() => $"Cat: {Name}";
}

class Program
{
    static void DisplayAnimals(IEnumerable<Animal> animals)
    {
        foreach (Animal animal in animals)
        {
            Console.WriteLine($"  {animal}");
        }
    }

    static void Main()
    {
        // Covariance: IEnumerable<Dog> can be assigned to IEnumerable<Animal>
        List<Dog> dogs = new List<Dog>
        {
            new Dog("Buddy"),
            new Dog("Max"),
            new Dog("Charlie")
        };

        Console.WriteLine("Dogs:");
        DisplayAnimals(dogs); // Covariance in action

        Console.WriteLine("\nCats:");
        List<Cat> cats = new List<Cat>
        {
            new Cat("Whiskers"),
            new Cat("Mittens")
        };
        DisplayAnimals(cats); // Covariance in action
    }
}
```

**Output:**
```
Dogs:
  Dog: Buddy
  Dog: Max
  Dog: Charlie

Cats:
  Cat: Whiskers
  Cat: Mittens
```

### Example 8: Generic Delegates

```csharp
using System;

// Generic delegate
delegate T Operation<T>(T a, T b);

class Program
{
    static int Add(int a, int b)
    {
        return a + b;
    }

    static int Multiply(int a, int b)
    {
        return a * b;
    }

    static string Concat(string a, string b)
    {
        return a + b;
    }

    static void ExecuteOperation<T>(Operation<T> op, T a, T b)
    {
        T result = op(a, b);
        Console.WriteLine($"Result: {result}");
    }

    static void Main()
    {
        // Using with integers
        Operation<int> intOp = Add;
        Console.Write("Add(5, 3): ");
        ExecuteOperation(intOp, 5, 3);

        intOp = Multiply;
        Console.Write("Multiply(5, 3): ");
        ExecuteOperation(intOp, 5, 3);

        Console.WriteLine();

        // Using with strings
        Operation<string> stringOp = Concat;
        Console.Write("Concat('Hello', ' World'): ");
        ExecuteOperation(stringOp, "Hello", " World");

        Console.WriteLine();

        // Using built-in generic delegates
        Func<int, int, int> func = (x, y) => x - y;
        Console.WriteLine($"Func(10, 4): {func(10, 4)}");

        Action<string> action = msg => Console.WriteLine($"Action: {msg}");
        action("Hello from Action!");
    }
}
```

**Output:**
```
Add(5, 3): Result: 8
Multiply(5, 3): Result: 15

Concat('Hello', ' World'): Result: Hello World

Func(10, 4): 6
Action: Hello from Action!
```

## Key Points

- Generics provide type safety and code reusability
- Type parameters use angle brackets: `<T>`, `<TKey, TValue>`
- Constraints limit type parameters: `where T : class`, `where T : struct`, `where T : IInterface`
- Generic collections are preferred over non-generic ones
- Generics eliminate boxing/unboxing overhead
- Support covariance (`out`) and contravariance (`in`) for interfaces and delegates
- Can be applied to classes, interfaces, methods, and delegates
- Multiple type parameters are supported
- Built-in generic delegates: `Func<>`, `Action<>`, `Predicate<>`
- Generic constraints: `class`, `struct`, `new()`, base class, interface
