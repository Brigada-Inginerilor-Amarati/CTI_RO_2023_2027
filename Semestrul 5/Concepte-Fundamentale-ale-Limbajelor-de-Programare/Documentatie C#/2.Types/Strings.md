# Strings in C#

## Description

Strings in C# are immutable sequences of Unicode characters represented by the `System.String` class (alias: `string`). Once created, a string cannot be modified; any operation that appears to modify a string actually creates a new string object.

### Key Features:
- **Immutable**: Cannot be changed after creation
- **Reference Type**: Stored on the heap
- **Unicode Support**: Supports international characters
- **Rich API**: Extensive methods for manipulation and querying
- **String Interpolation**: Modern syntax for formatting
- **Verbatim Strings**: `@` prefix for literal strings

### Common Operations:
- Concatenation, comparison, searching, formatting, splitting, trimming, replacing

## Code Examples

### Example 1: String Creation and Basics

```csharp
using System;

class Program
{
    static void Main()
    {
        // Different ways to create strings
        string str1 = "Hello, World!";
        string str2 = new string('A', 5); // "AAAAA"
        string str3 = string.Empty;
        string str4 = "";

        Console.WriteLine($"str1: '{str1}'");
        Console.WriteLine($"str2: '{str2}'");
        Console.WriteLine($"str3: '{str3}'");
        Console.WriteLine($"str4: '{str4}'");

        // String properties
        Console.WriteLine($"\nLength of str1: {str1.Length}");
        Console.WriteLine($"str3 is empty: {string.IsNullOrEmpty(str3)}");
        Console.WriteLine($"str3 is null or whitespace: {string.IsNullOrWhiteSpace(str3)}");
    }
}
```

**Output:**
```
str1: 'Hello, World!'
str2: 'AAAAA'
str3: ''
str4: ''

Length of str1: 13
str3 is empty: True
str3 is null or whitespace: True
```

### Example 2: String Concatenation

```csharp
using System;
using System.Text;

class Program
{
    static void Main()
    {
        string firstName = "John";
        string lastName = "Doe";

        // Using + operator
        string fullName1 = firstName + " " + lastName;
        Console.WriteLine($"Using +: {fullName1}");

        // Using String.Concat
        string fullName2 = string.Concat(firstName, " ", lastName);
        Console.WriteLine($"Using Concat: {fullName2}");

        // Using String.Join
        string fullName3 = string.Join(" ", firstName, lastName);
        Console.WriteLine($"Using Join: {fullName3}");

        // Using StringBuilder (efficient for multiple concatenations)
        StringBuilder sb = new StringBuilder();
        sb.Append(firstName);
        sb.Append(" ");
        sb.Append(lastName);
        string fullName4 = sb.ToString();
        Console.WriteLine($"Using StringBuilder: {fullName4}");
    }
}
```

**Output:**
```
Using +: John Doe
Using Concat: John Doe
Using Join: John Doe
Using StringBuilder: John Doe
```

### Example 3: String Interpolation and Formatting

```csharp
using System;

class Program
{
    static void Main()
    {
        string name = "Alice";
        int age = 30;
        double price = 19.99;

        // String interpolation (C# 6.0+)
        string message1 = $"Name: {name}, Age: {age}";
        Console.WriteLine(message1);

        // With formatting
        string message2 = $"Price: ${price:F2}";
        Console.WriteLine(message2);

        // String.Format (older style)
        string message3 = string.Format("Name: {0}, Age: {1}", name, age);
        Console.WriteLine(message3);

        // Composite formatting
        Console.WriteLine("Balance: {0:C}", 1234.56);

        // Alignment and padding
        Console.WriteLine($"|{"Left",-10}|{"Center",10}|{"Right",10}|");
        Console.WriteLine($"|{name,-10}|{age,10}|{price,10:F2}|");
    }
}
```

**Output:**
```
Name: Alice, Age: 30
Price: $19.99
Name: Alice, Age: 30
Balance: $1,234.56
|Left      |    Center|     Right|
|Alice     |        30|     19.99|
```

### Example 4: String Comparison

```csharp
using System;

class Program
{
    static void Main()
    {
        string str1 = "Hello";
        string str2 = "hello";
        string str3 = "Hello";

        // Equality operators
        Console.WriteLine($"str1 == str3: {str1 == str3}");
        Console.WriteLine($"str1 == str2: {str1 == str2}");

        // Equals method (case-sensitive)
        Console.WriteLine($"\nstr1.Equals(str2): {str1.Equals(str2)}");
        Console.WriteLine($"str1.Equals(str3): {str1.Equals(str3)}");

        // Case-insensitive comparison
        Console.WriteLine($"\nCase-insensitive:");
        Console.WriteLine($"str1.Equals(str2, StringComparison.OrdinalIgnoreCase): {str1.Equals(str2, StringComparison.OrdinalIgnoreCase)}");

        // CompareTo (returns <0, 0, or >0)
        int result = string.Compare(str1, str2);
        Console.WriteLine($"\nstring.Compare(str1, str2): {result}");
        Console.WriteLine($"string.Compare(str1, str2, true): {string.Compare(str1, str2, true)}"); // ignore case
    }
}
```

**Output:**
```
str1 == str3: True
str1 == str2: False

str1.Equals(str2): False
str1.Equals(str3): True

Case-insensitive:
str1.Equals(str2, StringComparison.OrdinalIgnoreCase): True

string.Compare(str1, str2): -1
string.Compare(str1, str2, true): 0
```

### Example 5: String Searching

```csharp
using System;

class Program
{
    static void Main()
    {
        string text = "The quick brown fox jumps over the lazy dog";

        // Contains
        Console.WriteLine($"Contains 'fox': {text.Contains("fox")}");
        Console.WriteLine($"Contains 'cat': {text.Contains("cat")}");

        // StartsWith and EndsWith
        Console.WriteLine($"\nStarts with 'The': {text.StartsWith("The")}");
        Console.WriteLine($"Ends with 'dog': {text.EndsWith("dog")}");

        // IndexOf (first occurrence)
        int index1 = text.IndexOf("the");
        Console.WriteLine($"\nFirst 'the' at index: {index1}");

        // LastIndexOf
        int index2 = text.LastIndexOf("the");
        Console.WriteLine($"Last 'the' at index: {index2}");

        // IndexOf with case-insensitive
        int index3 = text.IndexOf("THE", StringComparison.OrdinalIgnoreCase);
        Console.WriteLine($"'THE' (ignore case) at index: {index3}");

        // Substring
        string word = text.Substring(4, 5); // "quick"
        Console.WriteLine($"\nSubstring(4, 5): '{word}'");
    }
}
```

**Output:**
```
Contains 'fox': True
Contains 'cat': False

Starts with 'The': True
Ends with 'dog': True

First 'the' at index: 31
Last 'the' at index: 31

'THE' (ignore case) at index: 0

Substring(4, 5): 'quick'
```

### Example 6: String Manipulation

```csharp
using System;

class Program
{
    static void Main()
    {
        string text = "  Hello, World!  ";

        // Trim
        Console.WriteLine($"Original: '{text}'");
        Console.WriteLine($"Trim: '{text.Trim()}'");
        Console.WriteLine($"TrimStart: '{text.TrimStart()}'");
        Console.WriteLine($"TrimEnd: '{text.TrimEnd()}'");

        // Case conversion
        string sample = "Hello World";
        Console.WriteLine($"\nOriginal: {sample}");
        Console.WriteLine($"ToUpper: {sample.ToUpper()}");
        Console.WriteLine($"ToLower: {sample.ToLower()}");

        // Replace
        string sentence = "I like cats. Cats are cute.";
        Console.WriteLine($"\nOriginal: {sentence}");
        Console.WriteLine($"Replace 'cats' with 'dogs': {sentence.Replace("cats", "dogs")}");
        Console.WriteLine($"Replace 'Cats' with 'Dogs': {sentence.Replace("Cats", "Dogs")}");

        // Remove
        string word = "programming";
        Console.WriteLine($"\nOriginal: {word}");
        Console.WriteLine($"Remove(3, 4): {word.Remove(3, 4)}"); // Remove "gram"

        // Insert
        Console.WriteLine($"Insert(3, 'XYZ'): {word.Insert(3, "XYZ")}");
    }
}
```

**Output:**
```
Original: '  Hello, World!  '
Trim: 'Hello, World!'
TrimStart: 'Hello, World!  '
TrimEnd: '  Hello, World!'

Original: Hello World
ToUpper: HELLO WORLD
ToLower: hello world

Original: I like cats. Cats are cute.
Replace 'cats' with 'dogs': I like dogs. Cats are cute.
Replace 'Cats' with 'Dogs': I like cats. Dogs are cute.

Original: programming
Remove(3, 4): proing
Insert(3, 'XYZ'): proXYZgramming
```

### Example 7: String Splitting and Joining

```csharp
using System;
using System.Linq;

class Program
{
    static void Main()
    {
        // Split
        string sentence = "apple,banana,cherry,date";
        string[] fruits = sentence.Split(',');

        Console.WriteLine("Fruits:");
        foreach (string fruit in fruits)
        {
            Console.WriteLine($"  - {fruit}");
        }

        // Split with multiple delimiters
        string text = "one;two,three:four five";
        string[] words = text.Split(new char[] { ';', ',', ':', ' ' });

        Console.WriteLine("\nWords:");
        Console.WriteLine(string.Join(" | ", words));

        // Split with options
        string data = "a,,b,,,c";
        string[] parts1 = data.Split(',');
        string[] parts2 = data.Split(',', StringSplitOptions.RemoveEmptyEntries);

        Console.WriteLine($"\nWith empty entries: {parts1.Length} items");
        Console.WriteLine($"Without empty entries: {parts2.Length} items");

        // Join
        string[] items = { "C#", "Java", "Python", "JavaScript" };
        string joined = string.Join(", ", items);
        Console.WriteLine($"\nJoined: {joined}");
    }
}
```

**Output:**
```
Fruits:
  - apple
  - banana
  - cherry
  - date

Words:
one | two | three | four | five

With empty entries: 6 items
Without empty entries: 3 items

Joined: C#, Java, Python, JavaScript
```

### Example 8: Verbatim Strings and Escape Sequences

```csharp
using System;

class Program
{
    static void Main()
    {
        // Regular string with escape sequences
        string path1 = "C:\\Users\\Documents\\file.txt";
        Console.WriteLine($"Regular: {path1}");

        // Verbatim string (no escape sequences)
        string path2 = @"C:\Users\Documents\file.txt";
        Console.WriteLine($"Verbatim: {path2}");

        // Multi-line verbatim string
        string multiLine = @"Line 1
Line 2
Line 3";
        Console.WriteLine($"\nMulti-line:\n{multiLine}");

        // Escape sequences
        string escapes = "Tab:\tNewline:\nQuote:\"Hello\"";
        Console.WriteLine($"\nEscape sequences:\n{escapes}");

        // Verbatim string with quotes (doubled)
        string quote = @"She said, ""Hello!""";
        Console.WriteLine($"\nVerbatim quote: {quote}");
    }
}
```

**Output:**
```
Regular: C:\Users\Documents\file.txt
Verbatim: C:\Users\Documents\file.txt

Multi-line:
Line 1
Line 2
Line 3

Escape sequences:
Tab:	Newline:
Quote:"Hello"

Verbatim quote: She said, "Hello!"
```

### Example 9: String Immutability

```csharp
using System;

class Program
{
    static void Main()
    {
        string original = "Hello";
        Console.WriteLine($"Original: {original}");
        Console.WriteLine($"Original hash: {original.GetHashCode()}");

        // "Modifying" creates a new string
        string modified = original + " World";
        Console.WriteLine($"\nModified: {modified}");
        Console.WriteLine($"Modified hash: {modified.GetHashCode()}");

        Console.WriteLine($"\nOriginal unchanged: {original}");
        Console.WriteLine($"Original hash unchanged: {original.GetHashCode()}");

        // ToUpper creates new string
        string upper = original.ToUpper();
        Console.WriteLine($"\nUpper: {upper}");
        Console.WriteLine($"Upper hash: {upper.GetHashCode()}");
        Console.WriteLine($"Original still: {original}");
    }
}
```

**Output:**
```
Original: Hello
Original hash: 984949437

Modified: Hello World
Modified hash: -2039840067

Original unchanged: Hello
Original hash unchanged: 984949437

Upper: HELLO
Upper hash: 984944829
Original still: Hello
```

### Example 10: StringBuilder for Efficient String Building

```csharp
using System;
using System.Text;
using System.Diagnostics;

class Program
{
    static void Main()
    {
        int iterations = 10000;

        // Using string concatenation (slow)
        Stopwatch sw1 = Stopwatch.StartNew();
        string result1 = "";
        for (int i = 0; i < iterations; i++)
        {
            result1 += "x";
        }
        sw1.Stop();

        // Using StringBuilder (fast)
        Stopwatch sw2 = Stopwatch.StartNew();
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < iterations; i++)
        {
            sb.Append("x");
        }
        string result2 = sb.ToString();
        sw2.Stop();

        Console.WriteLine($"String concatenation: {sw1.ElapsedMilliseconds}ms");
        Console.WriteLine($"StringBuilder: {sw2.ElapsedMilliseconds}ms");
        Console.WriteLine($"\nSpeedup: {(double)sw1.ElapsedMilliseconds / sw2.ElapsedMilliseconds:F2}x faster");

        // StringBuilder methods
        StringBuilder builder = new StringBuilder("Hello");
        builder.Append(" World");
        builder.AppendLine("!");
        builder.Insert(6, "Beautiful ");
        builder.Replace("World", "C#");

        Console.WriteLine($"\nStringBuilder result:\n{builder}");
    }
}
```

**Output:**
```
String concatenation: 245ms
StringBuilder: 1ms

Speedup: 245.00x faster

StringBuilder result:
Hello Beautiful C#!

```

### Example 11: String Padding and Alignment

```csharp
using System;

class Program
{
    static void Main()
    {
        string text = "Hello";

        // PadLeft
        Console.WriteLine($"PadLeft(10): '{text.PadLeft(10)}'");
        Console.WriteLine($"PadLeft(10, '*'): '{text.PadLeft(10, '*')}'");

        // PadRight
        Console.WriteLine($"PadRight(10): '{text.PadRight(10)}'");
        Console.WriteLine($"PadRight(10, '-'): '{text.PadRight(10, '-')}'");

        // Table formatting
        Console.WriteLine("\nProduct Table:");
        Console.WriteLine($"{"Name",-15} {"Price",10} {"Stock",8}");
        Console.WriteLine(new string('-', 35));
        Console.WriteLine($"{"Laptop",-15} {999.99,10:C} {5,8}");
        Console.WriteLine($"{"Mouse",-15} {29.99,10:C} {50,8}");
        Console.WriteLine($"{"Keyboard",-15} {79.99,10:C} {20,8}");
    }
}
```

**Output:**
```
PadLeft(10): '     Hello'
PadLeft(10, '*'): '*****Hello'
PadRight(10): 'Hello     '
PadRight(10, '-'): 'Hello-----'

Product Table:
Name                 Price    Stock
-----------------------------------
Laptop            $999.99        5
Mouse              $29.99       50
Keyboard           $79.99       20
```

## Key Points

- Strings are immutable; operations create new strings
- Use `string` (lowercase) as alias for `System.String`
- String interpolation: `$"text {variable}"` (C# 6.0+)
- Verbatim strings: `@"text"` (no escape sequences)
- Use `StringBuilder` for efficient string building in loops
- Rich set of methods: `Substring`, `Replace`, `Split`, `Join`, `Trim`, etc.
- String comparison supports case-sensitive and case-insensitive options
- Strings are reference types but have value-type equality semantics
- Use `string.IsNullOrEmpty()` and `string.IsNullOrWhiteSpace()` for validation
- String interning: identical string literals share the same memory
