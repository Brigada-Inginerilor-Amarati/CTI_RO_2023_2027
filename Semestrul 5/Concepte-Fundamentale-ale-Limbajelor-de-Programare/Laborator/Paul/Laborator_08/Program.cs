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

namespace Laborator_08;

class Program
{
    static async Task Main(string[] args)
    {
        InputReader inputReader = new InputReader();
        Tamagotchi tamagotchi = new Tamagotchi("Paul", 10, 2, 'p', inputReader);

        Task runTask = tamagotchi.Run();
        Task readTask = Task.Run(() => inputReader.ReadKeys());

        await Task.WhenAny(runTask, readTask);
    }
}
