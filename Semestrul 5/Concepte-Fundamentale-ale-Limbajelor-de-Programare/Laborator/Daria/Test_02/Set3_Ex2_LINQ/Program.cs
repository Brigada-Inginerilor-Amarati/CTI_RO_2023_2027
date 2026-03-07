using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    // 2.a) Folosind LINQ, implementati o functie care primeste o lista de propozitii 
    // si returneaza numarul total de cuvinte din propozitiile care contin cel putin un semn de punctuatie (., !, ?). (1p)
    static int CountWordsInPunctuationSentences(List<string> sentences)
    {
        char[] punctuation = { '.', '!', '?' };
        char[] separators = { ' ', '\t' }; // pt split cuvinte

        return sentences
            .Where(s => s.IndexOfAny(punctuation) >= 0) // Filtrare propozitii cu punctuatie
            .Select(s => s.Split(separators, StringSplitOptions.RemoveEmptyEntries).Length) // Numar cuvinte per propozitie
            .Sum(); // Suma totala
    }

    // 2.b) Folosind LINQ, implementati o functie care primeste o lista de float si un predicat Func<float,bool>
    // si verifica daca exista cel putin un element care satisface predicatul. (1p)
    static bool CheckAny(List<float> list, Func<float, bool> predicate)
    {
        return list.Any(predicate);
    }

    static void Main(string[] args)
    {
        Console.WriteLine("=== Exercitiul 2 (Set 3): LINQ Propozitii & Predicate ===");

        // Test a)
        List<string> sentences = new List<string>
        {
            "Hello world.",       // Are '.' -> 2 words
            "No punctuation here", // Skip
            "Are you ok?",        // Are '?' -> 3 words
            "Yes!"                // Are '!' -> 1 word
        };
        // Total words: 2 + 3 + 1 = 6

        int wordCount = CountWordsInPunctuationSentences(sentences);
        Console.WriteLine($"Propozitii: \n {string.Join("\n ", sentences)}");
        Console.WriteLine($"Numar cuvinte in propozitii cu punctuatie: {wordCount}"); // Expect 6

        // Test b)
        List<float> floats = new List<float> { 1.5f, 2.5f, -3.0f };
        bool hasNegative = CheckAny(floats, x => x < 0);
        Console.WriteLine($"\nLista float: {string.Join(", ", floats)}");
        Console.WriteLine($"Are negative? {hasNegative}"); // True
    }
}
