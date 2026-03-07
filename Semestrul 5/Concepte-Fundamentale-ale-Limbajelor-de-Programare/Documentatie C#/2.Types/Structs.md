# Structs in C#

## Description

Structs are value types that are typically used to encapsulate small groups of related variables. Unlike classes (reference types), structs are stored on the stack and are copied by value. They are ideal for lightweight objects that represent simple data structures.

### Key Features:
- **Value Type**: Stored on the stack, not the heap
- **No Inheritance**: Cannot inherit from other structs or classes (except from System.ValueType)
- **Cannot be null**: Unless declared as nullable (`Nullable<T>` or `T?`)
- **Default Constructor**: Always have a parameterless constructor that initializes all fields to default values
- **Performance**: Better for small, simple data structures

### When to Use Structs:
- Small data structures (generally < 16 bytes)
- Immutable data
- Value semantics (copy behavior) is desired
- No inheritance needed

## Code Examples

### Example 1: Basic Struct Definition

```csharp
using System;

struct Point
{
    public int X;
    public int Y;

    public Point(int x, int y)
    {
        X = x;
        Y = y;
    }

    public void Display()
    {
        Console.WriteLine($"Point: ({X}, {Y})");
    }
}

class Program
{
    static void Main()
    {
        Point p1 = new Point(10, 20);
        p1.Display();

        // Default constructor
        Point p2 = new Point();
        p2.Display();
    }
}
```

**Output:**
```
Point: (10, 20)
Point: (0, 0)
```

### Example 2: Value Type Behavior (Copy Semantics)

```csharp
using System;

struct Rectangle
{
    public int Width;
    public int Height;

    public Rectangle(int width, int height)
    {
        Width = width;
        Height = height;
    }

    public void Display()
    {
        Console.WriteLine($"Rectangle: {Width}x{Height}");
    }
}

class Program
{
    static void Main()
    {
        Rectangle rect1 = new Rectangle(10, 5);
        Console.WriteLine("Original rect1:");
        rect1.Display();

        // Copy by value
        Rectangle rect2 = rect1;
        rect2.Width = 20;
        rect2.Height = 10;

        Console.WriteLine("\nAfter modifying rect2:");
        Console.WriteLine("rect1 (unchanged):");
        rect1.Display();
        Console.WriteLine("rect2 (modified):");
        rect2.Display();
    }
}
```

**Output:**
```
Original rect1:
Rectangle: 10x5

After modifying rect2:
rect1 (unchanged):
Rectangle: 10x5
rect2 (modified):
Rectangle: 20x10
```

### Example 3: Struct with Properties

```csharp
using System;

struct Temperature
{
    private double celsius;

    public double Celsius
    {
        get { return celsius; }
        set { celsius = value; }
    }

    public double Fahrenheit
    {
        get { return (celsius * 9 / 5) + 32; }
        set { celsius = (value - 32) * 5 / 9; }
    }

    public Temperature(double celsius)
    {
        this.celsius = celsius;
    }

    public void Display()
    {
        Console.WriteLine($"{Celsius:F1}°C = {Fahrenheit:F1}°F");
    }
}

class Program
{
    static void Main()
    {
        Temperature temp1 = new Temperature(25);
        Console.WriteLine("Setting Celsius to 25:");
        temp1.Display();

        Temperature temp2 = new Temperature(0);
        temp2.Fahrenheit = 100;
        Console.WriteLine("\nSetting Fahrenheit to 100:");
        temp2.Display();
    }
}
```

**Output:**
```
Setting Celsius to 25:
25.0°C = 77.0°F

Setting Fahrenheit to 100:
37.8°C = 100.0°F
```

### Example 4: Readonly Struct

```csharp
using System;

readonly struct ImmutablePoint
{
    public int X { get; }
    public int Y { get; }

    public ImmutablePoint(int x, int y)
    {
        X = x;
        Y = y;
    }

    public double DistanceFromOrigin()
    {
        return Math.Sqrt(X * X + Y * Y);
    }

    public void Display()
    {
        Console.WriteLine($"Immutable Point: ({X}, {Y}), Distance: {DistanceFromOrigin():F2}");
    }
}

class Program
{
    static void Main()
    {
        ImmutablePoint point = new ImmutablePoint(3, 4);
        point.Display();

        // point.X = 10; // ERROR: Cannot modify readonly property
    }
}
```

**Output:**
```
Immutable Point: (3, 4), Distance: 5.00
```

### Example 5: Struct with Methods

```csharp
using System;

struct Vector2D
{
    public double X;
    public double Y;

    public Vector2D(double x, double y)
    {
        X = x;
        Y = y;
    }

    public double Magnitude()
    {
        return Math.Sqrt(X * X + Y * Y);
    }

    public Vector2D Add(Vector2D other)
    {
        return new Vector2D(X + other.X, Y + other.Y);
    }

    public void Display()
    {
        Console.WriteLine($"Vector: ({X:F2}, {Y:F2}), Magnitude: {Magnitude():F2}");
    }
}

class Program
{
    static void Main()
    {
        Vector2D v1 = new Vector2D(3, 4);
        Vector2D v2 = new Vector2D(1, 2);

        Console.WriteLine("Vector 1:");
        v1.Display();

        Console.WriteLine("\nVector 2:");
        v2.Display();

        Vector2D v3 = v1.Add(v2);
        Console.WriteLine("\nVector 1 + Vector 2:");
        v3.Display();
    }
}
```

**Output:**
```
Vector 1:
Vector: (3.00, 4.00), Magnitude: 5.00

Vector 2:
Vector: (1.00, 2.00), Magnitude: 2.24

Vector 1 + Vector 2:
Vector: (4.00, 6.00), Magnitude: 7.21
```

### Example 6: Nullable Structs

```csharp
using System;

struct Coordinate
{
    public int X;
    public int Y;

    public Coordinate(int x, int y)
    {
        X = x;
        Y = y;
    }

    public override string ToString()
    {
        return $"({X}, {Y})";
    }
}

class Program
{
    static void Main()
    {
        // Nullable struct
        Coordinate? coord1 = new Coordinate(5, 10);
        Coordinate? coord2 = null;

        Console.WriteLine($"coord1 has value: {coord1.HasValue}");
        if (coord1.HasValue)
        {
            Console.WriteLine($"coord1 value: {coord1.Value}");
        }

        Console.WriteLine($"\ncoord2 has value: {coord2.HasValue}");
        Console.WriteLine($"coord2 value: {coord2?.ToString() ?? "null"}");

        // GetValueOrDefault
        Coordinate defaultCoord = coord2.GetValueOrDefault(new Coordinate(0, 0));
        Console.WriteLine($"\nDefault coordinate: {defaultCoord}");
    }
}
```

**Output:**
```
coord1 has value: True
coord1 value: (5, 10)

coord2 has value: False
coord2 value: null

Default coordinate: (0, 0)
```

### Example 7: Struct vs Class Comparison

```csharp
using System;

// Struct (value type)
struct PointStruct
{
    public int X;
    public int Y;

    public PointStruct(int x, int y)
    {
        X = x;
        Y = y;
    }
}

// Class (reference type)
class PointClass
{
    public int X;
    public int Y;

    public PointClass(int x, int y)
    {
        X = x;
        Y = y;
    }
}

class Program
{
    static void ModifyStruct(PointStruct p)
    {
        p.X = 100;
        p.Y = 100;
    }

    static void ModifyClass(PointClass p)
    {
        p.X = 100;
        p.Y = 100;
    }

    static void Main()
    {
        // Struct behavior
        PointStruct ps = new PointStruct(10, 20);
        Console.WriteLine($"Before: Struct ({ps.X}, {ps.Y})");
        ModifyStruct(ps);
        Console.WriteLine($"After: Struct ({ps.X}, {ps.Y}) - unchanged");

        Console.WriteLine();

        // Class behavior
        PointClass pc = new PointClass(10, 20);
        Console.WriteLine($"Before: Class ({pc.X}, {pc.Y})");
        ModifyClass(pc);
        Console.WriteLine($"After: Class ({pc.X}, {pc.Y}) - changed");
    }
}
```

**Output:**
```
Before: Struct (10, 20)
After: Struct (10, 20) - unchanged

Before: Class (10, 20)
After: Class (100, 100) - changed
```

## Key Points

- Structs are value types; classes are reference types
- Structs are copied by value; classes are copied by reference
- Structs cannot inherit from other structs or classes
- Structs always have a parameterless default constructor
- Use structs for small, simple, immutable data structures
- `readonly struct` ensures immutability
- Structs can be nullable using `Nullable<T>` or `T?`
- Structs are stored on the stack (better performance for small objects)
- Avoid using structs for large data structures
