/*
2. Având clasa PC_Game cu următoarele câmpuri: name, producer, release_year, number_of_quests, number_of_opponents, scrie cod declarativ LINQ pentru a rezolva următoarele cerințe:
*/

record PC_Game(
    string Name,
    string Producer,
    int ReleaseYear,
    int NumberOfQuests,
    int NumberOfOpponents
);

class PC_GameRepository
{
    private readonly List<PC_Game> games = new List<PC_Game>();

    public void Add(PC_Game game)
    {
        games.Add(game);
    }

    // i) Selectează toate obiectele PC_Game unde release_year este mai mic decât 2025.
    public List<PC_Game> GetGamesReleasedBefore2025()
    {
        return (from g in games where g.ReleaseYear < 2025 select g).ToList();
    }

    // ii) Găsește obiectul PC_Game cu cea mai mare valoare a câmpului number_of_quests.
    public PC_Game GetHighestQuestCountGame()
    {
        return (
            from g in games
            where g.NumberOfQuests == games.Max(g => g.NumberOfQuests)
            select g
        ).First();
    }

    // iii) Calculează valoarea medie a câmpului number_of_opponents pentru toate obiectele PC_Game care au number_of_quests mai mare decât 10.
    public double GetAverageNumberOfOpponentsWhereQuestCountGreaterThan10()
    {
        return (from g in games where g.NumberOfQuests > 10 select g.NumberOfOpponents).Average();
    }

    //iv) Grupează obiectele PC_Game după câmpul release_year și afișează câte obiecte sunt în fiecare grup.
    public void PrintGamesGroupedByReleaseYear()
    {
        var groups = from g in games group g by g.ReleaseYear into gr select gr.ToList();

        foreach (var group in groups)
        {
            Console.WriteLine("Year: " + group[0].ReleaseYear);
            Console.WriteLine("Count: " + group.Count);
        }
    }
}

class MainClass
{
    static void Main(string[] args)
    {
        var repo = new PC_GameRepository();
        repo.Add(new PC_Game("Game1", "Producer1", 2020, 10, 5));
        repo.Add(new PC_Game("Game2", "Producer2", 2022, 20, 10));
        repo.Add(new PC_Game("Game3", "Producer3", 2023, 30, 15));

        var a = repo.GetGamesReleasedBefore2025();
        Console.WriteLine("Games released before 2025: " + a.Count);

        var b = repo.GetHighestQuestCountGame();
        Console.WriteLine("Highest quest count game: " + b.Name);

        var c = repo.GetAverageNumberOfOpponentsWhereQuestCountGreaterThan10();
        Console.WriteLine("Average number of opponents where quest count is greater than 10: " + c);

        repo.PrintGamesGroupedByReleaseYear();
    }
}
