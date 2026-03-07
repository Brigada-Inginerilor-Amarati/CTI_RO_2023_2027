using System;

class Program
{
    // 1. Implementati o functie MaxF care primeste ca parametri un intreg x si doua functii
    // (Func<int, int>) f si g, si returneaza functia care are valoarea maxima in punctul x. (1.5p)
    static Func<int, int> MaxF(int x, Func<int, int> f, Func<int, int> g)
    {
        // Evaluam ambele functii in punctul x
        int valF = f(x);
        int valG = g(x);

        // Returnam functia care a produs valoarea mai mare
        if (valF > valG)
        {
            return f;
        }
        else
        {
            return g;
        }
    }

    static void Main(string[] args)
    {
        Console.WriteLine("=== Exercitiul 1: MaxF ===");

        // Definim doua functii simple pentru testare
        Func<int, int> square = val => val * val;
        Func<int, int> plusTen = val => val + 10;

        int testPoint = 4;
        // square(4) = 16
        // plusTen(4) = 14
        // Max ar trebui sa fie square

        Console.WriteLine($"Test Point: {testPoint}");
        Console.WriteLine($"Function 1 (x^2): {square(testPoint)}");
        Console.WriteLine($"Function 2 (x+10): {plusTen(testPoint)}");

        Func<int, int> maxFunc = MaxF(testPoint, square, plusTen);

        // Verificam rezultatul apeland functia returnata
        // Putem verifica daca e aceeasi referinta (daca delegate-urile sunt cache-uite) sau doar valoarea
        // Pentru demonstratie, afisam rezultatul aplicarii functiei maxime pe un alt numar, sau chiar pe x
        
        Console.WriteLine($"Max Function result at {testPoint}: {maxFunc(testPoint)}");
        
        // Testam un caz invers
        testPoint = 2;
        // square(2) = 4
        // plusTen(2) = 12
        // Max ar trebui sa fie plusTen

        Console.WriteLine($"\nTest Point: {testPoint}");
        Console.WriteLine($"Function 1 (x^2): {square(testPoint)}");
        Console.WriteLine($"Function 2 (x+10): {plusTen(testPoint)}");

        maxFunc = MaxF(testPoint, square, plusTen);
        Console.WriteLine($"Max Function result at {testPoint}: {maxFunc(testPoint)}");
    }
}
