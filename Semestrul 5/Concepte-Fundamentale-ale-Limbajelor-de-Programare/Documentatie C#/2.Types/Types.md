# Types in C#

## Description

C# is a strongly-typed language where every variable and constant has a type. Types define the kind of data that can be stored and the operations that can be performed on that data.

### Type Categories:
- **Value Types**: Store data directly (int, double, bool, struct, enum)
- **Reference Types**: Store references to data (class, interface, delegate, string)
- **Pointer Types**: Used in unsafe code contexts

### Built-in Types:
- **Integral**: `byte`, `sbyte`, `short`, `ushort`, `int`, `uint`, `long`, `ulong`
- **Floating-point**: `float`, `double`, `decimal`
- **Boolean**: `bool`
- **Character**: `char`

## Code Examples

### Example 1: Value Types

```csharp
using System;

class Program
{
    static void Main()
    {
        // Integral types
        int age = 25;
        long population = 7800000000L;

        // Floating-point types
        double price = 19.99;
        decimal precise = 19.99m;

        // Boolean
        bool isActive = true;

        // Character
        char grade = 'A';

        Console.WriteLine($"Age: {age}");
        Console.WriteLine($"Population: {population}");
        Console.WriteLine($"Price: {price}");
        Console.WriteLine($"Precise: {precise}");
        Console.WriteLine($"Is Active: {isActive}");
        Console.WriteLine($"Grade: {grade}");
    }
}
```

**Output:**
```
Age: 25
Population: 7800000000
Price: 19.99
Precise: 19.99
Is Active: True
Grade: A
```

### Example 2: Type Conversion

```csharp
using System;

class Program
{
    static void Main()
    {
        // Implicit conversion (safe)
        int num = 123;
        long bigNum = num;

        // Explicit conversion (casting)
        double d = 123.45;
        int i = (int)d;

        // Using Convert class
        string str = "456";
        int parsed = Convert.ToInt32(str);

        Console.WriteLine($"Implicit: {bigNum}");
        Console.WriteLine($"Explicit: {i}");
        Console.WriteLine($"Parsed: {parsed}");
    }
}
```

**Output:**
```
Implicit: 123
Explicit: 123
Parsed: 456
```

### Example 3: Nullable Types

```csharp
using System;

class Program
{
    static void Main()
    {
        // Nullable value types
        int? nullableInt = null;
        bool? nullableBool = true;

        Console.WriteLine($"Nullable Int: {nullableInt?.ToString() ?? "null"}");
        Console.WriteLine($"Has Value: {nullableInt.HasValue}");

        nullableInt = 42;
        Console.WriteLine($"Nullable Int: {nullableInt}");
        Console.WriteLine($"Has Value: {nullableInt.HasValue}");
        Console.WriteLine($"Value: {nullableInt.Value}");
    }
}
```

**Output:**
```
Nullable Int: null
Has Value: False
Nullable Int: 42
Has Value: True
Value: 42
```

### Example 4: var and Type Inference

```csharp
using System;

class Program
{
    static void Main()
    {
        // Type inference with var
        var number = 42;           // int
        var text = "Hello";        // string
        var pi = 3.14;            // double
        var isValid = true;       // bool

        Console.WriteLine($"{number} is {number.GetType()}");
        Console.WriteLine($"{text} is {text.GetType()}");
        Console.WriteLine($"{pi} is {pi.GetType()}");
        Console.WriteLine($"{isValid} is {isValid.GetType()}");
    }
}
```

**Output:**
```
42 is System.Int32
Hello is System.String
3.14 is System.Double
True is System.Boolean
```

## Key Points

- C# is strongly-typed; type safety is enforced at compile time
- Value types are stored on the stack; reference types on the heap
- Nullable types allow value types to represent null
- `var` keyword enables type inference but maintains strong typing
- Type conversion can be implicit (safe) or explicit (requires casting)
