/*

Creați un joc Tamagotchi. Fiecare animal de companie Tamagotchi trebuie hrănit regulat, altfel va muri de foame. Dacă îl hrăniți excesiv, Tamagotchi va muri de asemenea. Scopul jocului este să-l țineți în viață cât mai mult timp posibil.

Clasele necesare sunt următoarele:

CititorIntrare va avea un EventHandler<string> numit OnKeyPressed și o metodă ReadKeys() care citește de la consolă folosind metoda Console.ReadLine() până când este citit un șir gol. După citirea fiecărui șir, evenimentul OnKeyPressed va fi invocat.
Clasa Tamagotchi va fi responsabilă de gestionarea vieții unui Tamagotchi. Aceasta va avea următoarele proprietăți:
string Nume
int Mâncare - dacă ajunge la zero, Tamagotchi va muri de foame
int RataFoamei - timpul necesar pentru ca Tamagotchi să piardă mâncare, exprimat în milisecunde
bool ÎnViață - statusul Tamagotchi
char Tasta - tasta necesară pentru a hrăni Tamagotchi
Constructorul va primi numele, cantitatea inițială de mâncare, rata foamei, tasta și un CititorIntrare. După setarea proprietăților, acesta trebuie să se aboneze la evenimentul OnKeyPressed din CititorIntrare cu o metodă HandleKeyPressed. Această metodă va hrăni Tamagotchi cu 5 unități de mâncare de fiecare dată când este apăsată tasta specificată. Dacă este hrănit în exces (Mâncare > 20), Tamagotchi va muri.

O metodă asincronă Run va fi folosită pentru a simula viața Tamagotchi. Această metodă trebuie să continue să ruleze cât timp Tamagotchi este în viață. După fiecare interval de timp specificat de RataFoamei, 3 unități de mâncare vor fi scăzute. Dacă Mâncarea ajunge la 0 sau depășește 20, Tamagotchi va muri (de foame sau din cauza hrănirii excesive). După scăderea cantității de mâncare, statusul lui Tamagotchi va fi afișat.

O metodă ToString() va fi folosită pentru a afișa statusul lui Tamagotchi. Următoarele mesaje vor fi afișate în funcție de statusul ÎnViață:

Nume + "este sănătos și în viață. Mâncare rămasă: " + Mâncare;
Nume + "este mort :("

*/
using System;
using System.Threading;
using System.Threading.Tasks;

public class CititorIntrare
{
    public event EventHandler<string>? OnKeyPressed;

    public async Task ReadKeysAsync(CancellationToken token)
    {
        string? input;
        do
        {
            try
            {
                input = await Task.Run(() => Console.ReadLine(), token);
            }
            catch (OperationCanceledException)
            {
                break;
            }
            if (!string.IsNullOrEmpty(input))
            {
                OnKeyPressed?.Invoke(this, input);
            }
        } while (!string.IsNullOrEmpty(input) && !token.IsCancellationRequested);
    }
}

public class Tamagotchi
{
    public string Nume { get; private set; }
    public int Mancare { get; private set; }
    public int RataFoamei { get; private set; }
    public bool InViata { get; private set; }
    public char Tasta { get; private set; }
    private CititorIntrare Cititor;
    private CancellationTokenSource? _cts;

    public Tamagotchi(string nume, int mancareInitiala, int rataFoamei, char tasta, CititorIntrare cititor)
    {
        Nume = nume;
        Mancare = mancareInitiala;
        RataFoamei = rataFoamei;
        Tasta = tasta;
        Cititor = cititor;
        InViata = true;

        Cititor.OnKeyPressed += HandleKeyPressed;
        Console.WriteLine($"\nTamagotchi {Nume} has been created with Food: {Mancare}. Feeding key is '{Tasta}'.");
    }

    private void HandleKeyPressed(object? sender, string input)
    {
        if (!InViata) return;

        if (input.Length == 1 && input[0] == Tasta)
        {
            Mancare += 5;
            Console.WriteLine($"\n--- Feeding: {Nume} has been fed. Food: {Mancare}. ---");
            if (Mancare > 20)
            {
                Console.WriteLine($"\n!!! {Nume} died from overfeeding (Food > 20). !!!");
                InViata = false;
                _cts?.Cancel();
            }
            else
            {
                Console.WriteLine(ToString());
            }
        }
    }

    public async Task Run(CancellationToken token)
    {
        _cts = CancellationTokenSource.CreateLinkedTokenSource(token);
        try
        {
            while (InViata && !_cts.Token.IsCancellationRequested)
            {
                await Task.Delay(RataFoamei, _cts.Token);
                Mancare -= 3;

                if (Mancare <= 0)
                {
                    Console.WriteLine($"\n!!! {Nume} died of starvation (Food <= 0). !!!");
                    InViata = false;
                }
                else 
                {
                    Console.WriteLine($"\n--- Hunger: Food reduced by 3. ---");
                    Console.WriteLine(ToString());
                }
            }
        }
        catch (TaskCanceledException)
        {   
        }
        finally
        {
            if (!InViata)
            {
                Console.WriteLine(ToString());
            }
            _cts.Dispose();
        }
    }

    public override string ToString()
    {
        if (InViata)
        {
            return $"{Nume} is healthy and alive. Food remaining: {Mancare}";
        }
        else
        {
            return $"{Nume} is dead :(";
        }
    }
}

class Program
{
    static async Task Main(string[] args)
    {
        Console.WriteLine("---------------- Tamagotchi Game ----------------");
        
        Console.Write("Enter Tamagotchi name: ");
        string? nume = Console.ReadLine();
        if (string.IsNullOrEmpty(nume)) nume = "Noname";

        int mancareInitiala;
        do
        {
            Console.Write("Enter initial food amount (ideally under 20): ");
        } while (!int.TryParse(Console.ReadLine(), out mancareInitiala) || mancareInitiala < 1);

        int rataFoamei;
        do
        {
            Console.Write("Enter hunger rate (in milliseconds, e.g., 2000 for 2 seconds): ");
        } while (!int.TryParse(Console.ReadLine(), out rataFoamei) || rataFoamei < 100);

        Console.Write("Enter key to feed Tamagotchi (single letter): ");
        char tasta = Console.ReadKey().KeyChar;
        Console.WriteLine();

        var cititorIntrare = new CititorIntrare();
        var tamagotchi = new Tamagotchi(nume, mancareInitiala, rataFoamei, tasta, cititorIntrare);

        using var cts = new CancellationTokenSource();

        Console.WriteLine("\n================================================");
        Console.WriteLine($"Feed the Tamagotchi by pressing the specified key: '{tasta}'.");
        Console.WriteLine("To stop the game, press Enter on an empty line.");
        Console.WriteLine("================================================");

        var lifeTask = tamagotchi.Run(cts.Token);
        var inputTask = cititorIntrare.ReadKeysAsync(cts.Token);

        await inputTask;
        cts.Cancel();

        try
        {
            await lifeTask;
        }
        catch (TaskCanceledException)
        {
        }

        Console.WriteLine("\n---------------- Game Over ----------------");
    }
}