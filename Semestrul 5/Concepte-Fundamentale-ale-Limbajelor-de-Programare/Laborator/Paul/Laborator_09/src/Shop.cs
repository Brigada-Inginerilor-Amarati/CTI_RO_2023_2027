/*
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
*/
namespace Laborator_09;

class Shop
{
    public List<Game> Games { get; init; }

    public Shop()
    {
        Games = new List<Game>();
    }

    public void AddGame(Game game)
    {
        Games.Add(game);
    }

    public List<Game> GetGamesBefore(DateTime date)
    {
        return Games.Where(game => game.LaunchDate < date).ToList();
    }

    public int GameCountBetween(int yearAfter, int yearBefore)
    {
        return Games
            .Where(game => game.LaunchDate.Year >= yearAfter && game.LaunchDate.Year <= yearBefore)
            .Count();
    }

    public List<Game> SortByDeveloperAndName()
    {
        return Games.OrderBy(game => game.Developer).ThenBy(game => game.Name).ToList();
    }

    public List<Game> SortByPriceGamesMadeByDeveloper(string developer, bool ascending = true)
    {
        var filteredGames = Games.Where(game => game.Developer == developer);

        return ascending
            ? filteredGames.OrderBy(game => game.Price).ToList()
            : filteredGames.OrderByDescending(game => game.Price).ToList();
    }

    public Game FirstGameMadeByDeveloper(string developer)
    {
        return Games.Where(game => game.Developer == developer).First();
    }

    public bool GamesMoreExpensiveThan(float price)
    {
        return Games.Where(game => game.Price > price).Count() > 0;
    }

    public float SumOfPricesForGamesWithLabel(string label)
    {
        return Games.Where(game => game.Labels.Contains(label)).Sum(game => game.Price);
    }

    public List<Game> GamesThatContainAtLeastOneLabel(List<string> labels)
    {
        return Games.Where(game => game.Labels.Intersect(labels).Any()).ToList();
    }
}
