using System;
using System.Collections.Generic;
using System.Threading.Tasks;

// 3. Implementati o clasa Alternator, care contine un event public Action<bool> onEventTrigger.
// Evenimentul va fi invocat de o metoda async o data la x secunde (primit prin constructor),
// cu valoarea trimisa alternand intre true si false. (1p)
class Alternator
{
    public event Action<bool> onEventTrigger;
    private int _seconds;
    private bool _currentState = false;

    public Alternator(int seconds)
    {
        _seconds = seconds;
    }

    public async Task Start()
    {
        while (true)
        {
            await Task.Delay(_seconds * 1000);
            _currentState = !_currentState;
            // Inovcam evenimentul (cu null check ?.Invoke)
            onEventTrigger?.Invoke(_currentState);
        }
    }
}

// Creati urmatoarea ierarhie de clase:
// - o clasa abstracta Appliance, cu o metoda abstracta HandleEvent si o metoda Subscribe
// care aboneaza metoda HandleEvent la evenimentul din Alternator (primit ca parametru).
// Appliance contine si un constructor care seteaza denumirea produsului (proprietate string)
// si apeleaza Subscribe. (1.5p)
abstract class Appliance
{
    public string Name { get; set; }

    public Appliance(string name, Alternator alternator)
    {
        Name = name;
        Subscribe(alternator);
    }

    public void Subscribe(Alternator alternator)
    {
        alternator.onEventTrigger += HandleEvent;
    }

    public abstract void HandleEvent(bool state);
}

// - o clasa Dishwasher, care mosteneste Appliance. Dishwasher implementeaza HandleEvent
// si printeaza “{Denumire} a pornit”, respectiv “{Denumire} s-a oprit”. (1.5p)
class Dishwasher : Appliance
{
    public Dishwasher(string name, Alternator alternator) : base(name, alternator) { }

    public override void HandleEvent(bool state)
    {
        if (state)
        {
            Console.WriteLine($"{Name} a pornit");
        }
        else
        {
            Console.WriteLine($"{Name} s-a oprit");
        }
    }
}

// - o clasa SmartVacuum, care mosteneste Appliance. SmartVacuum implementeaza HandleEvent
// si printeaza “{Denumire} a pornit” daca parametrul are valoarea true. Daca parametrul
// are valoarea false, printeaza “{Denumire} se intoarce la statia de incarcare”,
// urmat la 5 secunde de “{Denumire} s-a oprit”. Intoarcerea nu poate fi intrerupta de un nou semnal de pornire. (1.5p)
class SmartVacuum : Appliance
{
    private bool _isReturning = false;

    public SmartVacuum(string name, Alternator alternator) : base(name, alternator) { }

    // Folosim async void aici pentru a permite await fara a bloca executia evenimentului general
    // (Atentie: async void e in general descurajat exceptand event handlers, ceea ce este cazul aici indirect)
    public override async void HandleEvent(bool state)
    {
        if (state)
        {
            if (!_isReturning)
            {
                Console.WriteLine($"{Name} a pornit");
            }
            // "Intoarcerea nu poate fi intrerupta de un nou semnal de pornire"
            // Deci daca _isReturning e true, ignoram pornirea
        }
        else
        {
            if (!_isReturning)
            {
                _isReturning = true;
                Console.WriteLine($"{Name} se intoarce la statia de incarcare");
                await Task.Delay(5000);
                Console.WriteLine($"{Name} s-a oprit");
                _isReturning = false;
            }
        }
    }
}

class Program
{
    static async Task Main(string[] args)
    {
        Console.WriteLine("=== Exercitiul 3: Smart Home ===");

        // In metoda main sau top level statements creati un Alternator si o lista de Appliance
        // care contine cel putin 2 din fiecare tip.
        
        // Setam alternator la 2 secunde pentru a vedea efectul rapid
        Alternator alternator = new Alternator(2);

        List<Appliance> appliances = new List<Appliance>
        {
            new Dishwasher("Dishwasher 1", alternator),
            new Dishwasher("Dishwasher 2", alternator),
            new SmartVacuum("Vacuum 1", alternator),
            new SmartVacuum("Vacuum 2", alternator)
        };

        // Pornim alternatorul. Deoarece Start() e o bucla infinita cu await, 
        // daca ii dam await aici, nu vom ajunge niciodata la linia de jos.
        // Totusi, vrem ca programul sa ruleze continuu.
        
        // Lansam task-ul pe un fir paralel/fundal fara await imediat ca sa putem face si altceva (daca e cazul)
        // Sau pur si simplu ii dam await daca e singurul lucru pe care il face aplicatia.
        
        Console.WriteLine("Pornire Alternator (Ctrl+C pentru a opri)...");
        await alternator.Start();
    }
}
