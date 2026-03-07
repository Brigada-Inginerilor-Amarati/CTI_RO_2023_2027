using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    // 2. Folosind LINQ, implementati o functie care primeste o lista de float si returneaza suma
    // elementelor divizibile cu 3. (1p)
    static float SumDivisibleBy3(List<float> list)
    {
        // Nota: float-urile rar sunt exact divizibile, dar verificam modulo 3 == 0 pe valoarea intreaga sau exact
        // Dat fiind enuntul, presupunem verificare "matematica" (x % 3 == 0)
        return list.Where(x => x % 3 == 0).Sum();
    }

    // 2.b) Folosind LINQ, implementati o functie care primeste o lista de float si o conditie
    // (Func<float, bool>) si returneaza true daca toate elementele din lista indeplinesc conditia. (1p)
    static bool CheckCondition(List<float> list, Func<float, bool> condition)
    {
        return list.All(condition);
    }

    static void Main(string[] args)
    {
        Console.WriteLine("=== Exercitiul 2: LINQ ===");

        List<float> numbers = new List<float> { 1.0f, 3.0f, 4.0f, 6.0f, 9.0f, 10.0f, 12.0f };

        // Test SumDivisibleBy3
        // Divizibile cu 3: 3, 6, 9, 12 => Suma = 30
        float sum = SumDivisibleBy3(numbers);
        Console.WriteLine($"Lista: {string.Join(", ", numbers)}");
        Console.WriteLine($"Suma elementelor divizibile cu 3: {sum}");

        // Test CheckCondition
        bool allPositive = CheckCondition(numbers, n => n > 0);
        Console.WriteLine($"Toate pozitive? {allPositive}");

        bool allGreaterThanFive = CheckCondition(numbers, n => n > 5);
        Console.WriteLine($"Toate mai mari ca 5? {allGreaterThanFive}"); // False
    }
}
