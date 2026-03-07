using System;
using System.Collections.Generic;
using System.Threading.Tasks;

// 3. Implementati o clasa Ticker, care contine un event public Action<int> onEventTrigger.
// Evenimentul va fi invocat de o metoda async o data la x secunde (primit prin constructor),
// cu valoarea trimisa fiind numarul de secunde trecute de la inceputul rularii. (1p)
class Ticker
{
    public event Action<int> onEventTrigger; // Nume, "onEventTrigger" conform cerintei anterioare, pastram conventia
    private int _intervalSeconds;
    
    public Ticker(int intervalSeconds)
    {
        _intervalSeconds = intervalSeconds;
    }

    public async Task Start()
    {
        int elapsedTotal = 0;
        // int counter = 0;
        // Cerinta: "valoarea trimisa fiind numarul de secunde trecute de la inceputul rularii"
        // Daca evenimentul se declanseaza la x secunde, inseamna ca elapsed creste cu x.
        
        while (true)
        {
            await Task.Delay(_intervalSeconds * 1000);
            elapsedTotal += _intervalSeconds;
            onEventTrigger?.Invoke(elapsedTotal);
        }
    }
}

// Creati urmatoarea ierarhie de clase:
// - o clasa abstracta TimeDevice, cu o metoda abstracta HandleEvent si o metoda Subscribe
// care aboneaza metoda HandleEvent la evenimentul din Ticker (primit ca parametru).
// TimeDevice contine si un constructor care seteaza denumirea device-ului (proprietate string)
// si apeleaza Subscribe. (1.5p)
abstract class TimeDevice
{
    public string Name { get; set; }

    public TimeDevice(string name, Ticker ticker)
    {
        Name = name;
        Subscribe(ticker);
    }

    public void Subscribe(Ticker ticker)
    {
        ticker.onEventTrigger += HandleEvent;
    }

    public abstract void HandleEvent(int time);
}

// - o clasa Stopwatch, care mosteneste TimeDevice. Stopwatch implementeaza HandleEvent
// si printeaza timpul trecut de la crearea obiectului Stopwatch. (1.5p)
class Stopwatch : TimeDevice
{
    private DateTime _creationTime;

    public Stopwatch(string name, Ticker ticker) : base(name, ticker)
    {
        _creationTime = DateTime.Now;
    }

    public override void HandleEvent(int timeFromTicker)
    {
        // "timpul trecut de la crearea obiectului"
        double elapsedSinceCreation = (DateTime.Now - _creationTime).TotalSeconds;
        Console.WriteLine($"[{Name}] Stopwatch time: {elapsedSinceCreation:F1}s (Ticker says {timeFromTicker}s)");
    }
}

// - o clasa Timer, care mosteneste TimeDevice. Constructorul din Timer primeste un interval
// de timp in secunde. In plus, Timer implementeaza HandleEvent si printeaza “Timpul a expirat”
// dupa ce a trecut timpul setat si dezaboneaza HandleEvent de la evenimentul din TimeDevice. (1.5p)
class Timer : TimeDevice
{
    private int _timeoutSeconds;
    private DateTime _startTime;
    private Ticker _tickerRef; // Avem nevoie de referinta pentru dezabonare

    public Timer(string name, Ticker ticker, int timeoutSeconds) : base(name, ticker)
    {
        _timeoutSeconds = timeoutSeconds;
        _startTime = DateTime.Now;
        _tickerRef = ticker;
    }

    public override void HandleEvent(int timeFromTicker)
    {
        double elapsed = (DateTime.Now - _startTime).TotalSeconds;
        
        // Verificam daca a expirat
        if (elapsed >= _timeoutSeconds)
        {
            Console.WriteLine($"[{Name}] Timpul a expirat ({elapsed:F1}s >= {_timeoutSeconds}s)");
            _tickerRef.onEventTrigger -= HandleEvent;
            Console.WriteLine($"[{Name}] Dezabonat.");
        }
        else
        {
            Console.WriteLine($"[{Name}] Timer tick... ({elapsed:F1}s / {_timeoutSeconds}s)");
        }
    }
}


class Program
{
    static async Task Main(string[] args)
    {
        Console.WriteLine("=== Exercitiul 3 (Set 2): Ticker ===");

        Ticker ticker = new Ticker(1); // Tick every 1 second

        List<TimeDevice> devices = new List<TimeDevice>
        {
            new Stopwatch("SW1", ticker),
            new Stopwatch("SW2", ticker),
            new Timer("Timer1", ticker, 3), // Expira after 3s
            new Timer("Timer2", ticker, 5)  // Expira after 5s
        };

        Console.WriteLine("Starting Ticker...");
        await ticker.Start();
    }
}
