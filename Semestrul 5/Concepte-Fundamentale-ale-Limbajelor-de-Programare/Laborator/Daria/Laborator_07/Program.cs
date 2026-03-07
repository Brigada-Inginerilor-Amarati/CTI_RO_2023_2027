/*
Creați un proiect cu 3 clase: CititorIntrare, AscultatorCaracter, AscultatorComplex.

CititorIntrare va avea un EventHandler<string> numit OnKeyPressed și o metodă ReadKeys() 

care citește de la consolă folosind metoda Console.ReadLine() până când este citit un șir gol. 

După citirea fiecărui șir, evenimentul OnKeyPressed va fi invocat.


Constructorul clasei AscultatorCaracter va primi un caracter care va fi salvat ca un câmp și un obiect CititorIntrare. 

Constructorul se va abona la evenimentul OnKeyPressed din CititorIntrare. AscultatorCaracter va avea o metodă HandleKeyPressed

(abonată la eveniment), care primește șirul de la eveniment și afișează un mesaj dacă șirul conține caracterul specificat în constructor.


Constructorul clasei AscultatorComplex va primi un int numit strNo care specifică numărul de șiruri reținute și un obiect CititorIntrare. 

Constructorul se va abona la evenimentul OnKeyPressed din CititorIntrare. AscultatorComplex va avea o metodă HandleKeyPressed (abonată la eveniment), 

care primește șirul de la eveniment și îl adaugă într-o listă de șiruri. Doar ultimele strNo șiruri vor fi păstrate în listă (cele mai vechi vor fi eliminate). 

Dacă metoda primește „afișează ultimul”, va afișa ultima intrare din listă și va returna. Dacă primește „afișează toate”, va afișa toate șirurile din listă 

și va returna.


În metoda main, veți crea un CititorIntrare și apoi doi AscultatoriCaracter și un AscultatorComplex. 

După aceea, cititorul va fi folosit pentru a citi șiruri ca intrare.

*/

using System;
using System.Collections.Generic;

public class CititorIntrare
{
    public event EventHandler<string> OnKeyPressed;

    public void ReadKeys()
    {
        string input;
        do
        {
            input = Console.ReadLine();
            if (!string.IsNullOrEmpty(input))
            {
                OnKeyPressed?.Invoke(this, input);
            }
        } while (!string.IsNullOrEmpty(input));
    }
}

public class AscultatorCaracter
{
    private readonly char key;

    public AscultatorCaracter(char key, CititorIntrare reader)
    {
        this.key = key;
        reader.OnKeyPressed += HandleKeyPressed;
    }

    private void HandleKeyPressed(object sender, string input)
    {
        // Ignore special commands for AscultatorComplex
        string trimmedInput = input.Trim();
        if (trimmedInput.Equals("show last", StringComparison.OrdinalIgnoreCase) ||
            trimmedInput.Equals("show all", StringComparison.OrdinalIgnoreCase))
        {
            return; // Don't process these commands
        }
        
        if (input.Contains(key))
        {
            Console.WriteLine($"AscultatorCaracter: Input '{input}' contains the character '{key}'.");
        }
    }
}

public class AscultatorComplex
{
    private readonly int strNo;
    private readonly List<string> storedStrings;

    public AscultatorComplex(int strNo, CititorIntrare reader)
    {
        this.strNo = strNo;
        storedStrings = new List<string>();
        reader.OnKeyPressed += HandleKeyPressed;
    }

    private void HandleKeyPressed(object sender, string input)
    {
        string trimmedInput = input.Trim();
        
        // Check for "show last" command (case-insensitive)
        if (trimmedInput.Equals("show last", StringComparison.OrdinalIgnoreCase))
        {
            if (storedStrings.Count > 0)
            {
                Console.WriteLine($"AscultatorComplex: Last input: {storedStrings[^1]}");
            }
            else
            {
                Console.WriteLine("AscultatorComplex: No inputs stored.");
            }
            return; // Don't store the command
        }
        // Check for "show all" command (case-insensitive)
        else if (trimmedInput.Equals("show all", StringComparison.OrdinalIgnoreCase))
        {
            Console.WriteLine("AscultatorComplex: All stored inputs:");
            foreach (var str in storedStrings)
            {
                Console.WriteLine(str);
            }
            return; // Don't store the command
        }
        // Store regular input
        else
        {
            if (storedStrings.Count >= strNo)
            {
                storedStrings.RemoveAt(0); // Remove the oldest entry
            }
            storedStrings.Add(input);
        }
    }
}

class Program
{
    static void Main(string[] args)
    {
        // Create a CititorIntrare
        var cititorIntrare = new CititorIntrare();

        // Create two AscultatoriCaracter
        var ascultatorCaracter1 = new AscultatorCaracter('a', cititorIntrare);
        var ascultatorCaracter2 = new AscultatorCaracter('e', cititorIntrare);

        // Create one AscultatorComplex
        var ascultatorComplex = new AscultatorComplex(5, cititorIntrare);

        Console.WriteLine("Start typing strings. Press Enter on an empty line to stop.");

        // Read keys from the console
        cititorIntrare.ReadKeys();
    }
}