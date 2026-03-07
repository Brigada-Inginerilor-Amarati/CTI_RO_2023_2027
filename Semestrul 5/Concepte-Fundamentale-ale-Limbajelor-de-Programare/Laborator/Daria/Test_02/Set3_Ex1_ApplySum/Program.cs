using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    // 1. Implementati o functie ApplyAndSum. Functia primeste:
    // o lista de numere intregi,
    // o functie Func<int,int> transformer. Returnati suma tuturor valorilor obtinute dupa aplicarea transformaririi asupra fiecarui element. (1 p)
    static int ApplyAndSum(List<int> list, Func<int, int> transformer)
    {
        return list.Select(transformer).Sum();
    }

    static void Main(string[] args)
    {
        Console.WriteLine("=== Exercitiul 1 (Set 3): ApplyAndSum ===");

        List<int> numbers = new List<int> { 1, 2, 3, 4, 5 };
        
        // Transformare: x * 2. Suma: 2 + 4 + 6 + 8 + 10 = 30
        Func<int, int> doubleTrans = x => x * 2;
        
        int sum = ApplyAndSum(numbers, doubleTrans);
        
        Console.WriteLine($"Lista: {string.Join(", ", numbers)}");
        Console.WriteLine($"Suma (x*2): {sum}"); // Expect 30
        
        // Transformare: x * x. Suma: 1 + 4 + 9 + 16 + 25 = 55
        int sumSq = ApplyAndSum(numbers, x => x * x);
        Console.WriteLine($"Suma (x^2): {sumSq}"); // Expect 55
    }
}
