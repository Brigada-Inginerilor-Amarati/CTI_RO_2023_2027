/*

Creați o aplicație folosită pentru stocarea și căutarea titlurilor de jocuri. Vor fi necesare următoarele două clase:

Joc - această clasă va stoca următoarele proprietăți:

string Nume
string Dezvoltator
DateTime DataLansare
float Preț
List<string> Etichete
Proprietățile vor fi setate folosind constructorul. O metodă ToString() va fi folosită pentru afișare.

Magazin - această clasă va conține o listă de jocuri disponibile. Vor fi disponibile următoarele metode:

void AdaugăJoc(Joc joc) - adaugă un joc nou în listă;
List<Joc> JocuriÎnainteDe(DateTime data) - returnează o listă de jocuri lansate înainte de data specificată;
int JocuriÎntre(int an1, int an2) - returnează numărul de jocuri lansate între anii specificați (Sugestie: folosiți metoda Count din linq);
List<Joc> OrdoneazăDupăDezvoltatorȘiNume() - returnează o listă cu toate jocurile, ordonată mai întâi după numele dezvoltatorului, apoi după numele jocului;
List<Joc> JocuriDupăDezvoltatorOrdonateDupăPreț(string dezvoltator, bool descrescător = false) - returnează o listă de jocuri făcute de dezvoltatorul specificat, ordonată după preț. Al doilea parametru este opțional și specifică ordinea crescătoare / descrescătoare;
Joc PrimulJocAlDezvoltatorului(string dezvoltator) - returnează cel mai vechi joc făcut de dezvoltatorul specificat;
bool JocMaiScumpDecât(float preț) - returnează true dacă cel puțin un joc costă mai mult decât prețul specificat. Folosiți metoda Any;
float SumaPrețurilorPentruJocurileCuEtichetă(string etichetă) - returnează suma prețurilor pentru toate jocurile care conțin eticheta specificată;
List<Joc> JocuriCareConținCelPuținOEtichetă(List<string> etichete) - returnează o listă de jocuri care conțin cel puțin una dintre etichetele specificate în listă (Sugestie: puteți folosi metodele Any sau Intersect).
Toate interogările vor fi implementate folosind Linq. Instrucțiuni ca for, while, do while nu vor fi acceptate.

*/
using System;
using System.Collections.Generic;
using System.Linq; 

using System.IO;

namespace Laborator_09;

class Game{
    public string Name { get; set; }
    public string Developer { get; set; }
    public DateTime LaunchDate { get; set; }
    public float Price { get; set; }
    public List<string> Labels { get; set; }

    public Game(string name, string developer, DateTime launchDate, float price, List<string> labels){
        Name = name;
        Developer = developer;
        LaunchDate = launchDate;
        Price = price;
        Labels = labels;
    }

    public override string ToString(){
        return $"Name: {Name}; Developer: {Developer}; Launch Date: {LaunchDate:yyyy-MM-dd}; Price: ${Price:F2}; Labels: {string.Join(", ", Labels)}";
    }
}

class Shop{
    public List<Game> Games { get; set; } = new List<Game>();

    public Shop(){}

    public void AddGame(Game game){
        Games.Add(game);
    }

    public List<Game> GetGamesBefore(DateTime date){
        return Games.Where(game => game.LaunchDate < date).ToList();
    }

    public int GameCountBetween(int yearAfter, int yearBefore){
        return Games.Where(game => game.LaunchDate.Year >= yearAfter && game.LaunchDate.Year <= yearBefore).Count();
    }

    public List<Game> SortByDeveloperAndName(){
        return Games.OrderBy(game => game.Developer).ThenBy(game => game.Name).ToList();
    }

    public List<Game> SortByPriceGamesMadeByDeveloper(string developer, bool descrescător = false){
        var filteredGames = Games.Where(game => game.Developer == developer);
        return descrescător ? filteredGames.OrderByDescending(game => game.Price).ToList() : filteredGames.OrderBy(game => game.Price).ToList();
    }

    public Game FirstGameMadeByDeveloper(string developer){
        return Games.Where(game => game.Developer == developer).OrderBy(game => game.LaunchDate).First();
    }

    public bool GamesMoreExpensiveThan(float price){
        return Games.Any(game => game.Price > price);
    }

    public float SumOfPricesForGamesWithLabel(string label){
        return Games.Where(game => game.Labels.Contains(label)).Sum(game => game.Price);
    }

    public List<Game> GamesThatContainAtLeastOneLabel(List<string> labels){
        return Games.Where(game => game.Labels.Intersect(labels).Any()).ToList();
    }
}

class Program{
    static void Main(string[] args){
        Shop shop = new Shop();

        // Adding games to the shop
        shop.AddGame(new Game("The Witcher 3", "CD Projekt Red", new DateTime(2015, 5, 19), 29.99f, new List<string> { "RPG", "Open World", "Fantasy" }));
        shop.AddGame(new Game("Cyberpunk 2077", "CD Projekt Red", new DateTime(2020, 12, 10), 59.99f, new List<string> { "RPG", "Sci-Fi", "Open World" }));
        shop.AddGame(new Game("Half-Life 2", "Valve", new DateTime(2004, 11, 16), 9.99f, new List<string> { "FPS", "Sci-Fi", "Action" }));
        shop.AddGame(new Game("Portal 2", "Valve", new DateTime(2011, 4, 19), 19.99f, new List<string> { "Puzzle", "Sci-Fi", "Co-op" }));
        shop.AddGame(new Game("Elden Ring", "FromSoftware", new DateTime(2022, 2, 25), 59.99f, new List<string> { "RPG", "Fantasy", "Souls-like" }));
        shop.AddGame(new Game("Dark Souls", "FromSoftware", new DateTime(2011, 9, 22), 39.99f, new List<string> { "RPG", "Fantasy", "Souls-like", "Action" }));
        shop.AddGame(new Game("Minecraft", "Mojang", new DateTime(2011, 11, 18), 26.95f, new List<string> { "Sandbox", "Survival", "Creative" }));
        shop.AddGame(new Game("Terraria", "Re-Logic", new DateTime(2011, 5, 16), 9.99f, new List<string> { "Sandbox", "Survival", "2D" }));

        Console.WriteLine("=== All Games in Shop ===");
        shop.Games.ForEach(game => Console.WriteLine(game));
        Console.WriteLine();

        // Test GetGamesBefore
        Console.WriteLine("=== Games Released Before 2012 ===");
        var gamesBefore2012 = shop.GetGamesBefore(new DateTime(2012, 1, 1));
        gamesBefore2012.ForEach(game => Console.WriteLine(game));
        Console.WriteLine();

        // Test GameCountBetween
        Console.WriteLine("=== Number of Games Released Between 2010 and 2015 ===");
        int count = shop.GameCountBetween(2010, 2015);
        Console.WriteLine($"Count: {count}");
        Console.WriteLine();

        // Test SortByDeveloperAndName
        Console.WriteLine("=== Games Sorted by Developer and Name ===");
        var sortedGames = shop.SortByDeveloperAndName();
        sortedGames.ForEach(game => Console.WriteLine(game));
        Console.WriteLine();

        // Test SortByPriceGamesMadeByDeveloper (ascending - default)
        Console.WriteLine("=== CD Projekt Red Games Sorted by Price (Ascending) ===");
        var cdProjektGamesAsc = shop.SortByPriceGamesMadeByDeveloper("CD Projekt Red");
        cdProjektGamesAsc.ForEach(game => Console.WriteLine(game));
        Console.WriteLine();

        // Test SortByPriceGamesMadeByDeveloper (descending)
        Console.WriteLine("=== CD Projekt Red Games Sorted by Price (Descending) ===");
        var cdProjektGamesDesc = shop.SortByPriceGamesMadeByDeveloper("CD Projekt Red", true);
        cdProjektGamesDesc.ForEach(game => Console.WriteLine(game));
        Console.WriteLine();

        // Test FirstGameMadeByDeveloper
        Console.WriteLine("=== First Game Made by FromSoftware ===");
        var firstFromSoftware = shop.FirstGameMadeByDeveloper("FromSoftware");
        Console.WriteLine(firstFromSoftware);
        Console.WriteLine();

        // Test GamesMoreExpensiveThan
        Console.WriteLine("=== Are There Games More Expensive Than $50? ===");
        bool hasExpensiveGames = shop.GamesMoreExpensiveThan(50f);
        Console.WriteLine($"Result: {hasExpensiveGames}");
        Console.WriteLine();

        // Test SumOfPricesForGamesWithLabel
        Console.WriteLine("=== Sum of Prices for Games with 'RPG' Label ===");
        float rpgSum = shop.SumOfPricesForGamesWithLabel("RPG");
        Console.WriteLine($"Total: ${rpgSum:F2}");
        Console.WriteLine();

        // Test GamesThatContainAtLeastOneLabel
        Console.WriteLine("=== Games with 'Sandbox' or 'FPS' Labels ===");
        var gamesWithLabels = shop.GamesThatContainAtLeastOneLabel(new List<string> { "Sandbox", "FPS" });
        gamesWithLabels.ForEach(game => Console.WriteLine(game));
        Console.WriteLine();
    }
}