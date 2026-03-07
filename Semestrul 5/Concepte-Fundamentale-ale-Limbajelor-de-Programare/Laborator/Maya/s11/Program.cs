using System;
using System.Collections.Generic;
using System.Linq;

public class Game
{
    public string Name { get; }
    public string Developer { get; }
    public DateTime ReleaseDate { get; }
    public float Price { get; }
    public List<string> Tags { get; }

    public Game(string name, string developer, DateTime releaseDate, float price, List<string> tags)
    {
        Name = name;
        Developer = developer;
        ReleaseDate = releaseDate;
        Price = price;
        Tags = tags;
    }

    public override string ToString()
    {
        string tagsString = string.Join(", ", Tags);
        return $"{Name} | Dev: {Developer} | Release: {ReleaseDate.ToShortDateString()} | Price: {Price} | Tags: [{tagsString}]";
    }
}

public class Store
{
    private List<Game> games = new List<Game>();

    public void AddGame(Game game)
    {
        games.Add(game);
    }

    public List<Game> GamesBefore(DateTime date)
    {
        return games
            .Where(g => g.ReleaseDate < date)
            .ToList();
    }

    public int GamesBetween(int year1, int year2)
    {
        return games
            .Count(g => g.ReleaseDate.Year >= year1 && g.ReleaseDate.Year <= year2);
    }

    public List<Game> OrderByDeveloperAndByName()
    {
        return games
            .OrderBy(g => g.Developer)
            .ThenBy(g => g.Name)
            .ToList();
    }

    public List<Game> GamesByDeveloperOrderedByPrice(string developer, bool descending = false)
    {
        return descending
            ? games.Where(g => g.Developer == developer)
                   .OrderByDescending(g => g.Price)
                   .ToList()
            : games.Where(g => g.Developer == developer)
                   .OrderBy(g => g.Price)
                   .ToList();
    }

    public Game FirstGameByDeveloper(string developer)
    {
        return games
            .Where(g => g.Developer == developer)
            .OrderBy(g => g.ReleaseDate)
            .FirstOrDefault();
    }

    public bool GameMoreExpensiveThan(float price)
    {
        return games.Any(g => g.Price > price);
    }

    public float SumOfPriceForGamesWithTag(string tag)
    {
        return games
            .Where(g => g.Tags.Contains(tag))
            .Sum(g => g.Price);
    }

    public List<Game> GamesWhichContainAtLeastOneTag(List<string> tags)
    {
        return games
            .Where(g => g.Tags.Any(t => tags.Contains(t)))
            .ToList();
    }
}

public class Program
{
    public static void Main()
    {
        Store store = new Store();

        store.AddGame(new Game(
            "Cyberpunk 2077",
            "CD Projekt",
            new DateTime(2020, 12, 10),
            59.99f,
            new List<string> { "RPG", "Action" }
        ));

        store.AddGame(new Game(
            "The Witcher 3",
            "CD Projekt",
            new DateTime(2015, 5, 18),
            39.99f,
            new List<string> { "RPG", "Open World" }
        ));

        store.AddGame(new Game(
            "Portal 2",
            "Valve",
            new DateTime(2011, 4, 19),
            19.99f,
            new List<string> { "Puzzle", "Co-op" }
        ));

        Console.WriteLine(" Toate jocurile ordonate dupa developer si nume ");
        store.OrderByDeveloperAndByName().ForEach(g => Console.WriteLine(g));

        Console.WriteLine("\n Jocuri inainte de 2018 ");
        store.GamesBefore(new DateTime(2018, 1, 1)).ForEach(g => Console.WriteLine(g));

        Console.WriteLine("\n Primul joc de la CD Projekt ");
        Console.WriteLine(store.FirstGameByDeveloper("CD Projekt"));

        Console.WriteLine("\n Exista jocuri mai scumpe de 50? ");
        Console.WriteLine(store.GameMoreExpensiveThan(50));

        Console.WriteLine("\n Suma preturilor pentru jocuri cu tag 'RPG' ");
        Console.WriteLine(store.SumOfPriceForGamesWithTag("RPG"));

        Console.WriteLine("\n Jocuri care contin cel putin un tag din lista [\"Action\", \"Co-op\"] ");
        store.GamesWhichContainAtLeastOneTag(
            new List<string> { "Action", "Co-op" }
        ).ForEach(g => Console.WriteLine(g));
    }
}