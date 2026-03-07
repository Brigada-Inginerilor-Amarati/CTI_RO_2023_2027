using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    // 2.a) Folosind LINQ, implementati o functie care primeste o lista de float si returneaza lista
    // elementelor impare. (1p)
    static List<float> GetOddElements(List<float> list)
    {
        // Impare se refera de obicei la numere intregi, dar lucram cu float.
        // Vom converti la int sau verificam restul impartirii cu 2.
        // float x % 2 returneaza restul
        // Ex: 3.0 % 2 = 1.0 (impar), 4.0 % 2 = 0.0 (par), 3.5 % 2 = 1.5 (neclar)
        // Presupunem numere intregi stocate ca float.
        return list.Where(x => Math.Abs(x % 2) >= 0.9f && Math.Abs(x % 2) <= 1.1f || Math.Abs(x % 2) != 0).Where(x => (int)x % 2 != 0).ToList();
        // Mai simplu si robust pentru cerinta scolara tipica: verificam cast la int
        // return list.Where(x => ((int)x) % 2 != 0).ToList();
        // Sau folosind operatorul % pe float direct daca valorile sunt intregi
    }

    static List<float> GetOddElementsSimple(List<float> list)
    {
         return list.Where(x => ((int)x) % 2 != 0).ToList();
    }


    // 2.b) Folosind LINQ, implementati o functie care primeste o lista de float si o conditie
    // (Func<float, bool>) si returneaza true daca cel putin un element din lista indeplineste conditia. (1p)
    static bool CheckAny(List<float> list, Func<float, bool> condition)
    {
        return list.Any(condition);
    }

    static void Main(string[] args)
    {
        Console.WriteLine("=== Exercitiul 2 (Set 2): LINQ ===");

        List<float> numbers = new List<float> { 1.0f, 2.0f, 3.0f, 4.0f, 5.5f };

        // Test elemente impare
        List<float> odd = GetOddElementsSimple(numbers);
        Console.WriteLine($"Lista: {string.Join(", ", numbers)}");
        Console.WriteLine($"Elemente impare (cast la int): {string.Join(", ", odd)}");
        // 1, 3, 5 (din 5.5 cast la 5)

        // Test Any
        bool hasGreaterThanFour = CheckAny(numbers, x => x > 4);
        Console.WriteLine($"Exista element > 4? {hasGreaterThanFour}"); // True

        bool hasNegative = CheckAny(numbers, x => x < 0);
        Console.WriteLine($"Exista element negativ? {hasNegative}"); // False
    }
}
