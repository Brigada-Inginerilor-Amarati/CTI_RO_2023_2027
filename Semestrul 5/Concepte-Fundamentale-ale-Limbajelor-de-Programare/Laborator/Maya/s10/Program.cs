using System;
using System.Threading.Tasks;

public class CititorIntrare
{
    public event EventHandler<string>? OnKeyPressed;

    public void ReadKeys()
    {
        string? input;
        // Citeste de la consola pana cand se primeste un sir gol
        while (!string.IsNullOrEmpty(input = Console.ReadLine()))
        {
            OnKeyPressed?.Invoke(this, input);
        }
    }
}

public class Tamagotchi
{
    public string Nume { get; set; }
    public int Mancare { get; set; }
    public int RataFoamei { get; set; } // in milisecunde
    public bool InViata { get; set; }
    public char Tasta { get; set; }

    public Tamagotchi(string nume, int mancare, int rataFoamei, char tasta, CititorIntrare cititor)
    {
        Nume = nume;
        Mancare = mancare;
        RataFoamei = rataFoamei;
        Tasta = tasta;
        InViata = true;

        // Abonare la evenimentul OnKeyPressed
        cititor.OnKeyPressed += HandleKeyPressed;
    }

    private void HandleKeyPressed(object? sender, string key)
    {
        if (!InViata) return;

        // Verificam daca tasta apasata corespunde (presupunem ca inputul trebuie sa fie exact caracterul)
        if (key.Length == 1 && key[0] == Tasta)
        {
            Mancare += 5;
            if (Mancare > 20)
            {
                InViata = false;
                Console.WriteLine(this);
            }
        }
    }

    public async Task Run()
    {
        while (InViata)
        {
            await Task.Delay(RataFoamei);
            
            if (!InViata) break; // Daca a murit intre timp (ex: hranit excesiv)

            Mancare -= 3;

            if (Mancare <= 0 || Mancare > 20)
            {
                InViata = false;
            }

            Console.WriteLine(this);
        }
    }

    public override string ToString()
    {
        if (InViata)
        {
            return $"{Nume} este sănătos și în viață. Mâncare rămasă: {Mancare}";
        }
        else
        {
            return $"{Nume} este mort :(";
        }
    }
}

public class Program
{
    public static void Main(string[] args)
    {
        CititorIntrare cititor = new CititorIntrare();
        
        // Exemplu de initializare: Nume="Maya", Mancare=10, RataFoamei=3000ms (3 sec), Tasta='f'
        Tamagotchi tamagotchi = new Tamagotchi("Maya", 10, 3000, 'f', cititor);

        Console.WriteLine($"Tamagotchi {tamagotchi.Nume} a inceput! Apesi '{tamagotchi.Tasta}' si Enter pentru a hrani. Enter gol pentru a iesi.");
        Console.WriteLine(tamagotchi);

        // Pornim simularea vietii pe un alt thread (task)
        Task lifeTask = tamagotchi.Run();

        // Citim intrarile de la utilizator pe thread-ul principal
        cititor.ReadKeys();

        // Opțional: marcam ca mort daca iesim din joc manual, pentru a opri loop-ul din Run
        tamagotchi.InViata = false;
    }
}
