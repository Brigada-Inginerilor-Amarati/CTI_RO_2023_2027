using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    // 1. Implementati o functie MaxInX care primeste ca parametri o lista de intregi intList si o
    // functie f (Func<int, int>). MaxInX va returna valoarea maxima pe care o returneaza apelul
    // functiei f dintre toate elementele din intList. (1.5p)
    static int MaxInX(List<int> intList, Func<int, int> f)
    {
        // Aplicam f pe fiecare element si luam maximul rezultatelor
        // Putem folosi LINQ Select + Max
        return intList.Select(f).Max();
    }

    static void Main(string[] args)
    {
        Console.WriteLine("=== Exercitiul 1 (Set 2): MaxInX ===");

        List<int> numbers = new List<int> { 1, 2, 3, -4, 5 };
        
        // Functie: patratul numarului
        Func<int, int> square = x => x * x;
        
        // Rezultate: 1, 4, 9, 16, 25. Maximul ar trebui sa fie 25.
        int maxSquare = MaxInX(numbers, square);
        Console.WriteLine($"Numere: {string.Join(", ", numbers)}");
        Console.WriteLine($"Max(x^2): {maxSquare}");

        // Functie: x + 10
        // Rezultate: 11, 12, 13, 6, 15. Maximul 15
        int maxPlusTen = MaxInX(numbers, x => x + 10);
        Console.WriteLine($"Max(x+10): {maxPlusTen}");
    }
}
