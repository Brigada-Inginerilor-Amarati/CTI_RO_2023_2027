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

namespace Laborator_09;

class Program
{
    static void Main(string[] args)
    {
        // Create a shop instance
        var shop = new Shop();

        // Create test games with various properties
        var game1 = new Game(
            "The Witcher 3",
            "CD Projekt Red",
            new DateTime(2015, 5, 19),
            39.99f,
            new List<string> { "RPG", "Open World", "Fantasy" }
        );

        var game2 = new Game(
            "Cyberpunk 2077",
            "CD Projekt Red",
            new DateTime(2020, 12, 10),
            59.99f,
            new List<string> { "RPG", "Sci-Fi", "Open World" }
        );

        var game3 = new Game(
            "Portal 2",
            "Valve",
            new DateTime(2011, 4, 19),
            19.99f,
            new List<string> { "Puzzle", "Sci-Fi", "Co-op" }
        );

        var game4 = new Game(
            "Half-Life 2",
            "Valve",
            new DateTime(2004, 11, 16),
            9.99f,
            new List<string> { "FPS", "Sci-Fi", "Story Rich" }
        );

        var game5 = new Game(
            "Dota 2",
            "Valve",
            new DateTime(2013, 7, 9),
            0.00f,
            new List<string> { "MOBA", "Multiplayer", "Strategy" }
        );

        var game6 = new Game(
            "Minecraft",
            "Mojang",
            new DateTime(2011, 11, 18),
            26.95f,
            new List<string> { "Sandbox", "Survival", "Multiplayer" }
        );

        var game7 = new Game(
            "Hollow Knight",
            "Team Cherry",
            new DateTime(2017, 2, 24),
            14.99f,
            new List<string> { "Metroidvania", "Indie", "Platformer" }
        );

        var game8 = new Game(
            "Silksong",
            "Team Cherry",
            new DateTime(2025, 12, 31),
            29.99f,
            new List<string> { "Metroidvania", "Indie", "Platformer" }
        );

        // Add all games to the shop
        shop.AddGame(game1);
        shop.AddGame(game2);
        shop.AddGame(game3);
        shop.AddGame(game4);
        shop.AddGame(game5);
        shop.AddGame(game6);
        shop.AddGame(game7);
        shop.AddGame(game8);

        Console.WriteLine("=== All Games in Shop ===");
        foreach (var game in shop.Games)
        {
            Console.WriteLine(game);
        }
        Console.WriteLine();

        // Test 1: GetGamesBefore
        Console.WriteLine("=== Test 1: Games Before 2015 ===");
        var gamesBefore2015 = shop.GetGamesBefore(new DateTime(2015, 1, 1));
        foreach (var game in gamesBefore2015)
        {
            Console.WriteLine(game);
        }
        Console.WriteLine($"Total: {gamesBefore2015.Count} games\n");

        // Test 2: GameCountBetween
        Console.WriteLine("=== Test 2: Games Between 2010-2015 ===");
        int countBetween = shop.GameCountBetween(2010, 2015);
        Console.WriteLine($"Number of games launched between 2010-2015: {countBetween}\n");

        // Test 3: SortByDeveloperAndName
        Console.WriteLine("=== Test 3: Sort by Developer and Name ===");
        var sortedGames = shop.SortByDeveloperAndName();
        foreach (var game in sortedGames)
        {
            Console.WriteLine(game);
        }
        Console.WriteLine();

        // Test 4: SortByPriceGamesMadeByDeveloper (ascending)
        Console.WriteLine("=== Test 4a: Valve Games Sorted by Price (Ascending) ===");
        var valveGamesAsc = shop.SortByPriceGamesMadeByDeveloper("Valve", ascending: true);
        foreach (var game in valveGamesAsc)
        {
            Console.WriteLine(game);
        }
        Console.WriteLine();

        // Test 4b: SortByPriceGamesMadeByDeveloper (descending)
        Console.WriteLine("=== Test 4b: CD Projekt Red Games Sorted by Price (Descending) ===");
        var cdprGamesDesc = shop.SortByPriceGamesMadeByDeveloper(
            "CD Projekt Red",
            ascending: false
        );
        foreach (var game in cdprGamesDesc)
        {
            Console.WriteLine(game);
        }
        Console.WriteLine();

        // Test 5: FirstGameMadeByDeveloper
        Console.WriteLine("=== Test 5: First Game by Valve ===");
        try
        {
            var firstValveGame = shop.FirstGameMadeByDeveloper("Valve");
            Console.WriteLine(firstValveGame);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }
        Console.WriteLine();

        // Test 6: GamesMoreExpensiveThan
        Console.WriteLine("=== Test 6: Games More Expensive Than $30 ===");
        bool hasExpensiveGames = shop.GamesMoreExpensiveThan(30.0f);
        Console.WriteLine($"Are there games more expensive than $30? {hasExpensiveGames}");

        bool hasVeryExpensiveGames = shop.GamesMoreExpensiveThan(100.0f);
        Console.WriteLine($"Are there games more expensive than $100? {hasVeryExpensiveGames}\n");

        // Test 7: SumOfPricesForGamesWithLabel
        Console.WriteLine("=== Test 7: Sum of Prices for Sci-Fi Games ===");
        float sciFiSum = shop.SumOfPricesForGamesWithLabel("Sci-Fi");
        Console.WriteLine($"Total price of all Sci-Fi games: ${sciFiSum:F2}");

        float rpgSum = shop.SumOfPricesForGamesWithLabel("RPG");
        Console.WriteLine($"Total price of all RPG games: ${rpgSum:F2}\n");

        // Test 8: GamesThatContainAtLeastOneLabel
        Console.WriteLine(
            "=== Test 8a: Games with at least one label from [Multiplayer, Co-op] ==="
        );
        var multiplayerGames = shop.GamesThatContainAtLeastOneLabel(
            new List<string> { "Multiplayer", "Co-op" }
        );
        foreach (var game in multiplayerGames)
        {
            Console.WriteLine(game);
        }
        Console.WriteLine($"Total: {multiplayerGames.Count} games\n");

        Console.WriteLine(
            "=== Test 8b: Games with at least one label from [Story Rich, Fantasy] ==="
        );
        var storyGames = shop.GamesThatContainAtLeastOneLabel(
            new List<string> { "Story Rich", "Fantasy" }
        );
        foreach (var game in storyGames)
        {
            Console.WriteLine(game);
        }
        Console.WriteLine($"Total: {storyGames.Count} games");
    }
}
